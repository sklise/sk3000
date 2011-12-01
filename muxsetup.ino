// Names for MUX control pins
#define CONTROL3 2
#define CONTROL2 3
#define CONTROL1 4
#define CONTROL0 5
// Output pin

// Arrays for 16 pins on each multiplexer
int mux0[16];
int mux1[16];
int mux2[16];

void muxStart() {
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
}

int muxAnalogRead(int mux, int pin) {
  addressPin(pin);
  return analogRead(mux);
}

void muxDigitalWrite(int mux, int pin, int level) {
  muxDigitalSet(OUTPUT, mux);
  addressPin(pin);
  digitalWrite(muxDigitalPin(mux), level);
}

int muxDigitalRead(int mux, int pin) {
  muxDigitalSet(INPUT, mux);
  addressPin(pin);
  return digitalRead(muxDigitalPin(mux));
}

int muxDigitalPin(int mux) {
  return mux+14;
}

void muxDigitalSet(int mode, int mux) {
  // mode = [INPUT=0, OUTPUT=1]
  int modeAnti = (mode+1)%2;
  switch(mux) {
    case 0:
      pinMode(14, mode);
      pinMode(15, modeAnti);
      pinMode(16, modeAnti);
      break;
    case 1:
      pinMode(14, modeAnti);
      pinMode(15, mode);
      pinMode(16, modeAnti);
      break;
    case 2:
      pinMode(14, modeAnti);
      // HACK! Mux 2 is used as input,
      // And Mux 1 is an output,
      // So I can't set Mux 1 to output when reading Mux2.
      pinMode(15, mode);
      pinMode(16, mode);
      break;
    default:
      pinMode(14, mode);
      pinMode(15, mode);
      pinMode(16, mode);
  }
}

void addressPin(int p)
{
  digitalWrite(CONTROL0, (p&15)>>3); 
  digitalWrite(CONTROL1, (p&7)>>2);  
  digitalWrite(CONTROL2, (p&3)>>1);  
  digitalWrite(CONTROL3, (p&1)); 
}