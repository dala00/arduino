const int SWITCH = 3;
const int LED = 4;
const int PERIOD = 900;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
}

void ledByte(byte value) {
  for (int i = 0; i < 8; i++) {
    byte currentBit = (value >> i) & 1;
    digitalWrite(LED, LOW);
    delayMicroseconds(PERIOD);
    digitalWrite(LED, HIGH);
    if (currentBit == 0) {
      delayMicroseconds(PERIOD);
    } else {
      delayMicroseconds(PERIOD * 2);
    }
  }
}

void loop() {
  if (digitalRead(SWITCH) == LOW) {
    //header
    digitalWrite(LED, HIGH);
    delayMicroseconds(PERIOD * 4);
    //data
    ledByte(1);
    //end
    digitalWrite(LED, LOW);
    while (digitalRead(SWITCH) == LOW);
  }
}
