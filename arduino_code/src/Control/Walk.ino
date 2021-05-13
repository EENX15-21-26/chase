
void getFootCoords(float progress, float height, float steplength, float stepheight, float velocity, float swingPortion, float footCoordsOut[3]){
  if(progress <= swingPortion){
    getSwingCoords(progress / swingPortion, height, steplength, stepheight, velocity, swingPortion, footCoordsOut);
  }else{
    getStanceCoords((progress - swingPortion) / (1-swingPortion), height, steplength, footCoordsOut);
  }
}

void getStanceCoords(float progress, float height, float steplength, float footCoordsOut[3]){
  footCoordsOut[0] = (0.5 - progress) * steplength;
  footCoordsOut[1] = HIP_LENGTH;
  footCoordsOut[2] = -height; // TODO
}

void getSwingCoords(float progress, float height, float steplength, float stepheight, float velocity, float dt, float footCoordsOut[3]){
  int binom[] = {1, 11, 55, 165, 330, 462, 462, 330, 165, 55, 11, 1};
  float px[] = {-0.5 * steplength,
              -0.5 * steplength - velocity/(13 * dt),
              -steplength * 0.89, -steplength * 0.89,
              -steplength * 0.89,
              0, 0, 0,
              steplength * 0.89,
              steplength * 0.89,
              0.5 * steplength + velocity/(13 * dt),
              0.5 * steplength};
  float pz[] = {-height,
                -height,
                stepheight - height,
                stepheight - height,
                stepheight - height,
                stepheight - height,
                stepheight - height,
                stepheight * 1.2 - height,
                stepheight * 1.2 - height,
                stepheight * 1.2 - height,
                -height,
                -height};

  footCoordsOut[0] = 0;
  footCoordsOut[1] = HIP_LENGTH;
  footCoordsOut[2] = 0;
  
  for(int i = 0; i < 12; i++){
    footCoordsOut[0] += binom[i] * px[i] * pow(progress, i) * pow(1-progress, 11-i);
    footCoordsOut[2] += binom[i] * pz[i] * pow(progress, i) * pow(1-progress, 11-i);
  } 

}
