
MPU6050 mpu;
#define P 0.01
#define I 2
#define D 0
PID_v2 pitchPID(P,I,D, REVERSE);
PID_v2 rollPID(P,I,D, REVERSE); 

void initIMU(){
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
  pitchPID.SetSampleTime(200);
  //Below PID related
  //initialize the variables we're linked to
  //turn the PID on
  pitchPID.SetOutputLimits(-255,255);
  rollPID.SetOutputLimits(-255,255);
  pitchPID.Start(0,0,0); //Input, Output, Setpoint
  rollPID.Start(0,0,0);
}
float getPitch(){
   Vector normAccel = mpu.readNormalizeAccel();
   return -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis)));
}

float getRoll(){
  Vector normAccel = mpu.readNormalizeAccel();
  return atan2(normAccel.YAxis, normAccel.ZAxis);
}
//Main function for PID-controller.
void levelBody(float zCorr[4]){
  float pitch = getPitch();
  float roll = getRoll();
  if(roll>=0) roll = PI-roll; //This IF-Else case is due to the fact that the IMU is upside down and overflows if it goes past 180 degrees
  else roll = (PI-abs(roll))*-1; 
  float pitchDiff = asin(pitch)*0.12; //0.12 is distance from engine to middle, x axis.
  float rollDiff = asin(roll)*0.08; //0.08 is distance from engine to middle, y axis
  float pitchFix = pitchPID.Run(pitchDiff); 
  float rollFix = rollPID.Run(rollDiff);
  if(abs(pitchFix)+abs(rollFix) <0.06){ //Safety break
  zCorr[0] = -pitchFix-rollFix;
  zCorr[1] = -pitchFix+rollFix;
  zCorr[2] =  pitchFix-rollFix;
  zCorr[3] =  pitchFix+rollFix;
  Serial.print("fix: ");
  Serial.print(zCorr[0],3);
}
}
