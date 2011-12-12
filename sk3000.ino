#define SOUNDOUT 6

int currentStep;
int currentTrack;

int trackSelectorPins[] = {0,0,0};


int startTime = 0;
int elapsedTime = 0;
int tempo = 200;
int skipStates[] = {0,0,0,0,0,0,0,0};

const int maxSteps = 8;
int melody[][maxSteps] = {
  {110, 131, 165, 196, 247, 294, 349, 440},
  {196,196,196,196,196,196,196,196},
  {240,350,480,500,500,440,240,350},
  {240,350,480,500,320,440,540,350},
  {240,350,280,110,320,440,540,350}
};

int tempoUpState = 0;
int tempoDownState = 0;
int tempoPrevUpState = 0;
int tempoPrevDownState = 0;

void setup() {
  muxStart();
  pinMode(SOUNDOUT, OUTPUT);
  Serial.begin(9600);

  currentStep = 0;
  currentTrack = 0;
}

void loop() {

  // Read Selector Switch
  for(int i=0; i<3; i++) {
    trackSelectorPins[i] = muxDigitalRead(0,i+8);
  }
  currentTrack = setCurrentTrack();

  // Read the sliders.
  for(int i=0; i<maxSteps; i++) {
    melody[currenTrack][i] = map(muxAnalogRead(0,i),0,1024,35,120);
  }

  // Light the LED
  muxDigitalWrite(1,currentStep%8,HIGH);

  // Play the note or make a rest.
  if(muxDigitalRead(2,currentStep+8) == 1) {
    noTone(SOUNDOUT);
  } else {
    tone(SOUNDOUT,melody[currentTrack][currentStep]);
  }

  elapsedTime = millis() - startTime;

  if(elapsedTime >= tempo) {
    for(int i=0;i<8;i++) {
      skipStates[i] = muxDigitalRead(2,i);
    }
    muxDigitalWrite(1,currentStep%8,LOW);
    currentStep = nextStep(nextStepMode(), currentStep, maxSteps);
    startTime = millis();
  }
  
  tempoDownState = muxDigitalRead(0,10);
  tempoUpState = muxDigitalRead(0,11);
  
  // if(tempoDownState != tempoPrevDownState && tempoDownState == HIGH) {
  //   // Serial.println("TempoDown");
  //   tempo += 10;
  // }
  // 
  // if(tempoUpState != tempoPrevUpState && tempoUpState == HIGH) {
  //   // Serial.println("TempoUp");
  //   tempo -= 10;
  //   if (tempo <= 10) tempo = 10;
  // }
  
  tempoPrevDownState = tempoDownState;
  tempoPrevUpState = tempoUpState;
}
