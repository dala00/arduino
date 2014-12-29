const int IR = 8;
const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(IR, INPUT);
}

void loop() {
  digitalWrite(LED, 1 - digitalRead(IR));
}
