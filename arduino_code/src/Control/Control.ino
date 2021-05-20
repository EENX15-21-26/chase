
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PID_v2.h>
#include <MPU6050.h>
#include <ros.h>
#include <std_msgs/Empty.h>
#include <chase_msgs/ChaseArduino.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define LOOP_TIME 40.0f

#define SERVOMIN  90
#define SERVOMAX  510
#define SERVO_FREQ 50

#define HIP_LENGTH 0.04
#define LEG_LENGTH 0.13
#define LEVER_LENGTH 0.024

#define MODE_SLEEP 0
#define MODE_STAND 1
#define MODE_WALK 2
#define MODE_TROT 3

#define PARAMS_LENGTH 5
#define PARAM_STAND_HEIGHT 0
#define PARAM_WALK_VELOCITY 0
#define PARAM_WALK_TURN 1
#define PARAM_WALK_HEIGHT 2

float counter = 0;

int mode = MODE_SLEEP;
float params[PARAMS_LENGTH];

void setup() {
  pwm.begin();
  pwm.setOscillatorFrequency(25000000);
  pwm.setPWMFreq(SERVO_FREQ);
  initPiListener();
  // initIMU();

  
  //float p[5] = {0.2, 0, 0.16, 0, 0};
  //setMode(MODE_TROT, p);
  
  
  float p[5] = {0.15, 0, 0.15, 0, 0};
  setMode(MODE_STAND, p);
}

void loop() {
  long t0 = millis();
  
  if(mode == MODE_SLEEP){
    
  }else if(mode == MODE_STAND){
    float height = params[PARAM_STAND_HEIGHT];
    stand(height);
    delay(10000);
    float p[5] = {0.2, 2, 0.16, 0, 0};
    setMode(MODE_TROT, p);
  }else if(mode == MODE_TROT){
    float velocity = params[PARAM_WALK_VELOCITY];
    float turnRadius = params[PARAM_WALK_TURN];
    float height = params[PARAM_WALK_HEIGHT];
    trot(velocity, turnRadius, height);
  }
  
  counter += 1;
  spin();

  long t = millis() - t0;
  if(t < LOOP_TIME){
    delay(LOOP_TIME-t);
  }else{
    logInfo(String("ERROR: loop time to short! Target was ") + LOOP_TIME + String(", loop took ") + t);
  }
}

void setMode(float m, const float p[]){
  if(m != mode){
    if(m == MODE_WALK){
      counter = 0;
    }
  }


  mode = m;
  
  for(int i = 0; i < PARAMS_LENGTH; i++){
    params[i] = p[i];
  }

/*
  logInfo("Mode:");
  logInfo(mode);
  logInfo("Params:");
  for(int i = 0; i < PARAMS_LENGTH; i++){
    logInfo(params[i]);
  }
*/
}

void trot(float velocity, float turnRadius, float height){
  float swingPortion = 0.5;
  float steplength = 0.06; //0.1
  float stepheight = 0.04; // 0.04

  int dataPoints = steplength / (velocity * (LOOP_TIME / 1000.0f) * (1.0f-swingPortion));
  float progress = counter / dataPoints;
  
  float flFootCoords[3];
  float flAngles[3];

  float frFootCoords[3];
  float frAngles[3];

  float blFootCoords[3];
  float blAngles[3];

  float brFootCoords[3];
  float brAngles[3];
  
  getFootCoords(fmod(progress, 1), height, steplength, stepheight, velocity, swingPortion, flFootCoords);
  getFootCoords(fmod(progress + 0.5, 1), height, steplength, stepheight, velocity, swingPortion, frFootCoords);
  getFootCoords(fmod(progress + 0.5, 1), height, steplength, stepheight, velocity, swingPortion, blFootCoords);
  getFootCoords(fmod(progress, 1), height, steplength, stepheight, velocity, swingPortion, brFootCoords);


  getAngles(flFootCoords, flAngles);
  getAngles(frFootCoords, frAngles);
  getAngles(blFootCoords, blAngles);
  getAngles(brFootCoords, brAngles);

  sendToFL(flAngles);
  sendToFR(frAngles);
  sendToBL(blAngles);
  sendToBR(brAngles);
}

void level(float height){
  float standCoordsFL[] = {0, HIP_LENGTH, -height};
  float standCoordsFR[] = {0, HIP_LENGTH, -height};
  float standCoordsBL[] = {-0.02, HIP_LENGTH, -height};
  float standCoordsBR[] = {-0.02, HIP_LENGTH, -height};
  

  float flAngles[3];
  float frAngles[3];
  float blAngles[3];
  float brAngles[3];

  float zCorr[4];
  levelBody(zCorr);
  standCoordsFL[2]+=zCorr[0];
  standCoordsFR[2]+=zCorr[1];
  standCoordsBL[2]+=zCorr[2];
  standCoordsBR[2]+=zCorr[3];

  getAngles(standCoordsFL, flAngles);
  getAngles(standCoordsFR, frAngles);
  getAngles(standCoordsBL, blAngles);
  getAngles(standCoordsBR, brAngles);

  sendToFL(flAngles);
  sendToFR(frAngles);
  sendToBL(blAngles);
  sendToBR(brAngles);
}

void pushups(){
  stand(sin(counter / 10) * 0.02 + 0.18);
}

void stand(float height){
  float standCoords[] = {0, HIP_LENGTH, -height};

  float flAngles[3];
  float frAngles[3];
  float blAngles[3];
  float brAngles[3];
  
  getAngles(standCoords, flAngles);
  getAngles(standCoords, frAngles);
  getAngles(standCoords, blAngles);
  getAngles(standCoords, brAngles);
Serial.println(String("FL> x: ") + standCoords[0] + String(", y: ") + standCoords[1] + String(", z: ") + standCoords[2]);

  sendToFL(flAngles);
  sendToFR(frAngles);
  sendToBL(blAngles);
  sendToBR(brAngles);
}
