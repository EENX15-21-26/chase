
void getAngles(float footCoords[3], float anglesOut[3]){
  float x = footCoords[0];
  float y = footCoords[1];
  float z = footCoords[2];
  
  float l1 = HIP_LENGTH;
  float l2 = LEG_LENGTH;
  float l3 = LEVER_LENGTH;
  float l4 = LEVER_LENGTH;

  float c1 = sqrt(sq(x) + sq(y) + sq(z) - sq(l1));
  float c2 = sqrt(sq(l2 + l4) - (l4 * sq(c1)) / l2);
  float c3 = acos((sq(l2) + sq(l3) - sq(c2)) / (2 * l2 * l3));
  float c4 = sqrt(2 * (sq(l2) * sq(l3) + sq(l2) * sq(c2) + sq(l3) * sq(c2)) - pow(l2, 4) - pow(l3, 4) - pow(c2, 4)) / 4;
  float c5 = sqrt(2 * (sq(l2) * sq(l4) + sq(l2) * sq(c2) + sq(l4) * sq(c2)) - pow(l2, 4) - pow(l3, 4) - pow(c2, 4)) / 4;

  anglesOut[0] = acos(c1/(2 * l2)) - asin(x/c1);
  anglesOut[1] = c3 - anglesOut[0] + asin(2 * c4/(l2 * c2)) - asin(2 * c5/(l2*c2));
  anglesOut[2] = HALF_PI + acos(y/sqrt(sq(y) + sq(z))) - acos(l1/sqrt(sq(y) + sq(z)));
}
