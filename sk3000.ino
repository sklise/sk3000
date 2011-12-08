#define SOUNDOUT 6

int currentStep;
int maxSteps = 8;

int startTime = 0;
int elapsedTime = 0;
int tempo = 200;
int skipStates[] = {0,0,0,0,0,0,0,0};

int melody[] = {
  110, 131, 165, 196, 247, 294, 349, 440};

int tempoUpState = 0;
int tempoDownState = 0;
int tempoPrevUpState = 0;
int tempoPrevDownState = 0;

void setup() {
  muxStart();
  pinMode(SOUNDOUT, OUTPUT);
  Serial.begin(9600);

  currentStep = 0;
}

void loop() {
  
  // TOGGLE SWITCH DEBUG
//  for(int i=0; i<16;i++){
//    Serial.print(muxDigitalRead(2,i));
//    Serial.print(',');
//  }
//  Serial.println();
    muxDigitalWrite(1,currentStep%8,HIGH);
    // tone(SOUNDOUT,map(muxAnalogRead(0,currentStep), 0, 700, 0, 1100));

    if(muxDigitalRead(2,currentStep+8) == 1) {
      noTone(SOUNDOUT);
    } else {
      tone(SOUNDOUT,melody[currentStep]);
    }
    Serial.println(melody[currentStep]);
    
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
    
    if(tempoDownState != tempoPrevDownState && tempoDownState == HIGH) {
      Serial.println("TempoDown");
      tempo += 10;
    }
    
    if(tempoUpState != tempoPrevUpState && tempoUpState == HIGH) {
      Serial.println("TempoUp");
      tempo -= 10;
      if (tempo <= 10) tempo = 10;
    }
    
    tempoPrevDownState = tempoDownState;
    tempoPrevUpState = tempoUpState;
}
