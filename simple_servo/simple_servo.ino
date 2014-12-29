#include <Servo.h>

Servo servo;

int pos = 0;


void setup() {
  Serial.begin(9600);
  servo.attach(9);
}

void loop() {
  if (Serial.available() > 0) {
    byte val = Serial.read();
    servo.write(val);
  }
  delay(100);
}
