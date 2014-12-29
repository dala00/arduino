const int PIN = 7;
const long TIMEOUT = 250000;
const int DATA_MAX = 400;

unsigned int lastInput = HIGH;
unsigned long startTime = micros();
int inputCount = 0;
int dataCount = 0;
unsigned int val;
unsigned long currentTime;
boolean data[100];
boolean highVal;
boolean isSony = false;
String str = "";

void setup() {
  Serial.begin(57600);
  pinMode(PIN, INPUT);
}

void loop() {
  val = digitalRead(PIN);
  unsigned long time;
 
  while (val == lastInput) {
    if (micros() - startTime > TIMEOUT) {
      if (inputCount > 2 && isSony) {
        String tmp = "";
        for (int i = 0; i < dataCount; i++) {
          tmp += String(data[i]) + " ";
        }
        Serial.println(tmp);
//        Serial.println(str);
      }
      isSony = false;
      inputCount = 0;
      dataCount = 0;
      str = "";
      break;
    }
    val = digitalRead(PIN);
  }
  
  currentTime = micros();
  time = currentTime - startTime;
  str += String(time) + " ";
  inputCount++;
  if (inputCount == 3) {
    if (1800 < time && time < 3000) {
      isSony = true;
    }
  } else if (inputCount > 3) {
    if (isSony && (inputCount % 2)) {
      if (time < 1000) {
        data[dataCount] = 0;
      } else {
        data[dataCount] = 1;
      }
      dataCount++;
    }
  }
  lastInput = val;
  startTime = currentTime;
}

