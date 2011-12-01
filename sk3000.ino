#define SOUNDOUT 6

int currentStep;
int maxSteps = 8;

int startTime = 0;
int elapsedTime = 0;
int tempo = 200;
int skipStates[] = {0,0,0,0,0,0,0,0};

void setup() {
  muxStart();
  pinMode(SOUNDOUT, OUTPUT);
  Serial.begin(9600);

  currentStep = 0;
}

void loop() {
  muxDigitalWrite(1,currentStep%8,HIGH);
  tone(SOUNDOUT,map(muxAnalogRead(0,currentStep), 0, 700, 0, 1100));
  
  elapsedTime = millis() - startTime;
  if(elapsedTime >= tempo) {
    for(int i=0;i<8;i++) {
      skipStates[i] = muxDigitalRead(2,i);
    }
    muxDigitalWrite(1,currentStep%8,LOW);
    currentStep = nextStep(nextStepMode(), currentStep, maxSteps);
    startTime = millis();
  }
  // Serial.println(currentStep);
}
