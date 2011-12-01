int nextStep(int mode, int currentStep, int maxSteps) {
  int newStep = 0;
  int response = 0;
  switch(mode) {
    case 1:
      newStep = currentStep - 1;
      if(newStep == -1) {
        response = maxSteps-1;
      } else {
        response = newStep;
      }
      break;
    case 2:
      newStep = currentStep+pow(-1,random(0,2));
      if(newStep == -1) {
        response = maxSteps-1;
      } else {
        response = newStep%maxSteps;
      }
      break;
    default:
      newStep = currentStep+1;
      response = (newStep)%maxSteps;
  }
  if(skipStates[response] == 1) {
    return nextStep(mode, response, maxSteps);
  } else {
    return response;
  }
}

int skip(int step, int maxSteps, int direction) {
  while(skipStates[step] == 1) {
    nextStep(direction, step, maxSteps);
    if(direction == 2) direction = 0;
    skip(step, maxSteps, direction);
  }
  return step;
}

int nextStepMode() {
  if( muxDigitalRead(2,9) ) {
    return 1;
  } else if ( muxDigitalRead(2,8) ) {
    return 2;
  } else {
    return 0;
  }
}