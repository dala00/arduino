#include <SD.h>

const int soundPort  =  3;  // sound out
const int chipSelect = 4;  // SD CS
#define BUFF_SIZE 256  // buffer size

unsigned char  buffs[BUFF_SIZE * 2];
volatile unsigned short bufGP;  // buffer pointer for GET
volatile unsigned short bufPP;  // buffer pointer for PUT

ISR(TIMER2_OVF_vect)  // Timer2 overflow ISR
{
  static unsigned char intCnt = 0;

  if (++intCnt >= 4) {  // 8:8kHz, 4:16kHz
    intCnt = 0;
    if (bufGP != bufPP) {
      analogWrite(soundPort, buffs[bufGP]);
      if (++bufGP >= sizeof(buffs)) bufGP = 0;
    }
  }
}

void dispErr(int rc)
{
  Serial.println(rc);
}

int playWav(char *waveFile)
{
  File dataFile;

  if (!(dataFile = SD.open(waveFile))) return(2);  // can't open File.
  bufPP = dataFile.read((void *)&buffs[0], BUFF_SIZE);

  bufGP = 44;
  TIMSK2 |= _BV(TOIE2);  // Timer2 overflow interrupt enable

  while (dataFile.available()) {
    if (((bufPP < bufGP) && ((bufPP + BUFF_SIZE) < bufGP)) ||
        ((bufPP > bufGP) && ((bufPP - BUFF_SIZE) < bufGP))) {
//      digitalWrite(debugPort, HIGH);
      bufPP += dataFile.read((void *)&buffs[bufPP], BUFF_SIZE);
      if (bufPP >= sizeof(buffs)) bufPP = 0;
//      digitalWrite(debugPort, LOW);
    }
  }

  while (bufGP != bufPP) ;
  TIMSK2 &= ~_BV(TOIE2);  // Timer2 overflow interrupt disable
  dataFile.close();
  Serial.println("end");
  return(10);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("start");
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) dispErr(1);  // can't open SD.
  // Timer2 Setup
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);  // Mode = 3(First PWM)
  TCCR2B = _BV(CS20);  // Prescale factor = 1:1
  dispErr(playWav("test.wav"));
}

void loop()
{
}
