#include <TM1637Display.h>

#define CLOCK_PIN 3
#define DATA_IO_PIN 4
#define PIPS_PIN 5

const uint8_t empty = 0;
const uint8_t number0 = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
const uint8_t number1 = SEG_B | SEG_C;
const uint8_t number2 = SEG_A | SEG_B | SEG_D | SEG_E | SEG_G;
const uint8_t number3 = SEG_A | SEG_B | SEG_C | SEG_D | SEG_G;
const uint8_t number4 = SEG_B | SEG_C | SEG_F | SEG_G;
const uint8_t number5 = SEG_A | SEG_C | SEG_D | SEG_F | SEG_G;
const uint8_t number6 = SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
const uint8_t number7 = SEG_A | SEG_B | SEG_C | SEG_F;
const uint8_t number8 = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
const uint8_t number9 = SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G;

uint8_t numberToSegments(int number) {
  switch (number) {
  case 0: return number0;
  case 1: return number1;
  case 2: return number2;
  case 3: return number3;
  case 4: return number4;
  case 5: return number5;
  case 6: return number6;
  case 7: return number7;
  case 8: return number8;
  case 9: return number9;
  default:
    Serial.println("Andreas hat irgendwas falsch gemacht"); 
    return empty;
  }
}

TM1637Display display(CLOCK_PIN, DATA_IO_PIN);

void ende() {
  if ((millis() % 2000) > 1000) {
    uint8_t allEmpty[] = {empty, empty, empty, empty};
    display.setSegments(allEmpty);

    tone(PIPS_PIN, 100);
    return;
  }

  uint8_t all0[] = {number0, number0, number0, number0};

  noTone(PIPS_PIN);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long millisSinceStart = millis();
  int secondsSinceStart = millisSinceStart/1000;
  
  int remainingSeconds = 90*60 - secondsSinceStart;
  remainingSeconds -= (secondsSinceStart/(3*60+10))*10;
  
  if (remainingSeconds <= 0) {
    ende();
    return;
  }
  
  int minutesToDisplay = remainingSeconds/60;
  int secondsToDisplay = remainingSeconds-(minutesToDisplay*60);

  int digit1Number = (minutesToDisplay/10)%10;
  int digit2Number = minutesToDisplay%10;
  int digit3Number = (secondsToDisplay/10)%10;
  int digit4Number = secondsToDisplay%10;

  uint8_t segments1 = numberToSegments(digit1Number);
  uint8_t segments2 = numberToSegments(digit2Number);
  uint8_t segments3 = numberToSegments(digit3Number);
  uint8_t segments4 = numberToSegments(digit4Number);
  uint8_t segments[] = {segments1, segments2, segments3, segments4};

  display.setSegments(segments);
  delay(1000 - (millis() % 1000));
}
