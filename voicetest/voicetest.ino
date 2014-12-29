#include <MIDI.h>

const int BASE_PITCH = 53;
const int MINVAL = 300;
const int MAXDIFF = 3;

int playing = -1;
unsigned long lastHigh = micros();
unsigned long lastVelo = micros();
byte currentVelocity;

void setup() {
  MIDI.begin();
}

void loop() {
  int val = analogRead(0);
  val = abs(val - 670);
  if (val < MINVAL) {
    if (playing) {
      if (micros() - lastHigh > 100000) {
        playing = 0;
        MIDI.sendNoteOff(BASE_PITCH, 0, 1);
      }
    }
  } else {
    if (micros() - lastVelo > 70000) {
      val = map(val, MINVAL, 1023 - 670, 64, 127);
      if (playing) {
        if (val > currentVelocity) {
          int plus = val - currentVelocity;
          if (plus > MAXDIFF) plus = MAXDIFF;
          if (plus + (int)currentVelocity > 127) {
            plus = 127 - currentVelocity;
          }
          currentVelocity += plus;
        } else if (val < currentVelocity) {
          int minus = currentVelocity - val;
          if (minus > MAXDIFF) minus = MAXDIFF;
          if (minus > currentVelocity) {
            minus = currentVelocity;
          }
          currentVelocity -= minus;
        }
        MIDI.sendControlChange(7, currentVelocity, 1);
      } else {
        MIDI.sendNoteOn(BASE_PITCH, val, 1);
        currentVelocity = val;
      }
      lastVelo = micros();
      playing = 1;
    }
    lastHigh = micros();
  }
}
