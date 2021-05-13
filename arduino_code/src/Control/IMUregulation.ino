
MPU6050 mpu;
#define P 0.00
#define I 0.02
#define D 0.001
PID_v2 pitchPID(P,I,D, REVERSE);
PID_v2 rollPID(P,I,D, REVERSE); //CURRENTLY NOT IN USE

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
   return -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
}

float getRoll(){
  Vector normAccel = mpu.readNormalizeAccel();
  return atan2(normAccel.YAxis, normAccel.ZAxis)*180.0/M_PI;
}

void levelBody(float zCorr[4]){
  float pitch = getPitch();
  Serial.print(pitch);
  float roll = getRoll();
  float pitchDiff = asin(pitch*PI/180)*12;
  float rollDiff = asin(roll*PI/180)*8;
  float pitchFix = pitchPID.Run(pitchDiff);  //For some reason the PID only recognizes either positive or negative values, not both.
  float rollFix = rollPID.Run(rollDiff);
  //Below PID related
if(abs(pitchFix) <0.06){
  zCorr[0] = -pitchFix;//-rollFix;
  zCorr[1] = -pitchFix;//+rollFix;
  zCorr[2] =  pitchFix;//-rollFix;
  zCorr[3] =  pitchFix;//+rollFix;
  Serial.print("fix: ");
  Serial.print(zCorr[0],3);
}
}
