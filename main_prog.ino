#include "RTClib.h"
#include "SSD1306.h"

#define set P1_1
#define sel P1_4

#define CLK_PIN P5_6
#define MOSI_PIN P2_4
#define RST_PIN P2_6
#define DC_PIN P2_7

int mode = 0;

RTC_DS3231 rtc;

SSD1306 oled(CLK_PIN, MOSI_PIN, RST_PIN, DC_PIN);

void setup () {
  pinMode(set, INPUT_PULLUP);
  pinMode(sel, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  oled.LEDPIN_Init();
  oled.LED_Init();
  rtc.begin();
  rtc.disable32K();
  rtc.clearAlarm(1);
  rtc.writeSqwPinMode(DS3231_OFF);
  //rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop () {
  if (rtc.alarmFired(1) == 1) alarmTrigger();
  else if (digitalRead(set) == LOW)
  {
    oled.LED_CLS();
    delay(250);
    mode++;
    if (mode == 3) mode = 1;
  }
  switch (mode) {
    case 0: setDate(); break;
    case 1: current(); break;
    case 2: alarm(); break;
  }
}
