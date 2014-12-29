#include <Servo.h>

#define LED 13
#define MOTOR1 2
#define MOTOR2 4

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  servo.attach(9);
  delay(2000);
  
}

void motorGo() {
  delay(100);
  digitalWrite(MOTOR1, HIGH);
  digitalWrite(MOTOR2, LOW);
}

void motorBack() {
  delay(100);
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, HIGH);
}

void motorStop() {
  delay(100);
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    switch(c) {
    case '0':
      digitalWrite(LED, LOW);
      break;
    case '1':
      digitalWrite(LED, HIGH);
      break;
    case 'j':
      motorGo();
      break;
    case 'k':
      motorStop();
      break;
    case 'l':
      motorBack();
      break;
    case 'a':
      servo.write(70);
      break;
    case 's':
      servo.write(90);
      break;
    case 'd':
      servo.write(110);
      break;
    }
  }
}


