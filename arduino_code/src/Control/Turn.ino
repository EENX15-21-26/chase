

void getTurn(float radius, float steplength, float out[4]){
  float r = sqrt(sq(ROBOT_LENGTH/2.0f) + sq(ROBOT_WIDTH/2.0f));
  float theta = atan(ROBOT_WIDTH/ROBOT_LENGTH);
  float ang1 = HALF_PI - theta;
  float ang2 = HALF_PI + theta;

  float centrang = asin(steplength/(2.0f * sqrt(sq(r) + sq(radius)-2.0f * r * radius * cos(ang2))));
  float a = 2.0f * r * sin(centrang);
  float b = 2.0f * abs(radius) * sin(centrang);
  float shortstep = sqrt(sq(a) + sq(b) - 2.0f * a * b * cos(ang1));
  float sideang1 = acos((sq(b) + sq(shortstep) - sq(a))/(2.0f * b * shortstep));
  float sideang2 = acos((sq(b) + sq(steplength) - sq(a))/(2.0f * b * steplength));

  // frontAngle and backAngle are the slopes of the front and back steps respectively
  // if the angle is 0 the step would be straight forward
  int radiusSign= (radius > 0) - (radius < 0);
  float frontAngle = -FRICTION * sideang1 * radiusSign;
  float backAngle = FRICTION * sideang2 * radiusSign;

  // rightDiff and leftDiff are used to shorten the inner leg when turning
  // Variables are adjusted according to direction of the turn
  float leftDiff = shortstep/steplength;
  float rightDiff = 1;
  if(radius < 0.0f){
    rightDiff = leftDiff;
    leftDiff = 1;
  }

  out[0] = frontAngle;
  out[1] = backAngle;
  out[2] = leftDiff;
  out[3] = rightDiff;
        
}
