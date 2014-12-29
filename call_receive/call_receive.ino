const int SENSOR = 8;
const int PERIOD = 900;
const unsigned long TIMEOUT = 250000;

int lastInput = HIGH;
unsigned long startTime;
byte reading = false;
byte inputCount = 0;
byte readCount = 0;
byte readValue = 0;
unsigned long currentTime;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(SENSOR, INPUT);
  startTime = micros();
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(SENSOR);
  unsigned long time;
  if (val == LOW) {
    Serial.println("low");
  }
  
  while (val == lastInput) {
    if (micros() - startTime > TIMEOUT) {
      reading = false;
      inputCount = 0;
      readCount = 0;
      readValue = 0;
      break;
    }
    val = digitalRead(SENSOR);
  }
  
  currentTime = micros();
  time = currentTime - startTime;
  if (time < TIMEOUT) {
    Serial.println((String)"" + time + "(" + lastInput + ")");
  }
  inputCount++;
  if (inputCount == 3) {
    if (3400 < time && time < 3800) {
      reading = true;
    }
  } else if (inputCount > 3) {
    if (reading && (inputCount % 2)) {
      if (time > PERIOD + 50) {
        readValue |= 1 << readCount;
      }
      readCount++;
    }
    if (readCount == 8) {
      Serial.println("read:" + readValue);
      readValue = 0;
      readCount = 0;
      inputCount = 0;
      reading = false;
    }
  }
  
  lastInput = val;
  startTime = currentTime;
}
