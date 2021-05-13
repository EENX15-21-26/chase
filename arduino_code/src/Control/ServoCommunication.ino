int angleToPwm(float angle){
  return SERVOMIN + (SERVOMAX-SERVOMIN) * angle / PI;
}

void sendToFL(float angles[3]){
    // Calibration
    float alpha = angles[0] - 0.05;
    float beta  = angles[1] - 0.10;
    float gamma = PI-angles[2] + 0.11;

    // Send angles to servos
    pwm.setPWM(0, 0, angleToPwm(alpha));
    pwm.setPWM(1, 0, angleToPwm(beta));
    pwm.setPWM(2, 0, angleToPwm(gamma));
}

void sendToFR(float angles[3]){
    // Calibration
    float alpha = PI-angles[0] - 0.06;
    float beta  = PI-angles[1] - 0.03;
    float gamma = angles[2];

    // Send angles to servos
    pwm.setPWM(3, 0, angleToPwm(alpha));
    pwm.setPWM(4, 0, angleToPwm(beta));
    pwm.setPWM(5, 0, angleToPwm(gamma));
}

void sendToBL(float angles[3]){
    // Calibration
    float alpha = angles[0];
    float beta  = angles[1];
    float gamma = PI-angles[2] - 0.11;

    // Send angles to servos
    pwm.setPWM(6, 0, angleToPwm(alpha));
    pwm.setPWM(7, 0, angleToPwm(beta));
    pwm.setPWM(8, 0, angleToPwm(gamma));
}

void sendToBR(float angles[3]){
    // Calibration
    float alpha = PI-angles[0];
    float beta  = PI-angles[1];
    float gamma = angles[2] + 0.37;

    // Send angles to servos
    pwm.setPWM(9, 0, angleToPwm(alpha));
    pwm.setPWM(10, 0, angleToPwm(beta));
    pwm.setPWM(11, 0, angleToPwm(gamma));
}
