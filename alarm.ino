String set_alarm_str;

int alarm_hr = 00;
int alarm_min = 00;
int alarm_sec = 00;

int alarm_set = 0;

long pMill = 0;
long intervall = 500;
int alarmState = LOW;

int alarm_start = 33;
int bye_bye = 0;

long stayPreviousMillis = 0;
long stayInterval = 10000;

void alarm()
{
  oled.LED_CLS();
  if (alarm_set == 0)
  {
    oled.LED_P8x16Str(43, 0, "Alarm");
    oled.LED_P8x16Str(10, 2, "Alarm not set.");
    oled.LED_P8x16Str(alarm_start - 10, 4, "Set alarm?");
    while (1)
    {
      if (digitalRead(set) == LOW)
      {
        delay(500);
        oled.LED_CLS();
        setAlarm();
        break;
      }
      if (digitalRead(sel) == LOW)
      {
        oled.LED_CLS();
        mode = 1;
        break;
      }
    }
  }
  else if (alarm_set == 1)
  {
    oled.LED_P8x16Str(43, 0, "Alarm");
    set_alarm_str = convertSet('t', alarm_hr, alarm_min, alarm_sec);

    int set_alarm_str_len = set_alarm_str.length() + 1;
    char set_alarm_str_array[set_alarm_str_len];
    set_alarm_str.toCharArray(set_alarm_str_array, set_alarm_str_len);

    oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
    while (1)
    {
      if (rtc.alarmFired(1) == 1)
      {
        oled.LED_CLS();
        alarmTrigger();
        break;
      }
      oled.LED_P8x16Str(alarm_start - 13, 4, "Reset alarm?");
      if (digitalRead(set) == LOW)
      {
        alarm_set = 0;
        delay(500);
        oled.LED_CLS();
        setAlarm();
        break;
      }
      if (digitalRead(sel) == LOW)
      {
        oled.LED_CLS();
        mode = 1;
        break;
      }
    }
  }
}

void setAlarm()
{
  DateTime now = rtc.now() + TimeSpan(60);
  alarm_hr = now.hour();
  alarm_min = now.minute();
  while (1)
  {
    oled.LED_P8x16Str(10, 0, "Set Alarm");
    while (1)
    {
      set_alarm_str = convertSet('t', alarm_hr, alarm_min, alarm_sec);

      int set_alarm_str_len = set_alarm_str.length() + 1;
      char set_alarm_str_array[set_alarm_str_len];
      set_alarm_str.toCharArray(set_alarm_str_array, set_alarm_str_len);

      unsigned long currentMillis = millis();

      if (currentMillis - pMill > intervall) {
        pMill = currentMillis;
        if (alarmState == LOW) {
          alarmState = HIGH;
          oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
        }
        else {
          alarmState = LOW;
          oled.LED_P8x16Str(alarm_start, 2, "  ");
        }
      }
      if (digitalRead(sel) == LOW)
      {
        alarm_hr++;
        if (alarm_hr > 23) alarm_hr = 0;
        oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
        delay(250);
      }
      if (digitalRead(set) == LOW)
      {
        delay(500);
        break;
      }
    }

    while (1)
    {
      set_alarm_str = convertSet('t', alarm_hr, alarm_min, alarm_sec);

      int set_alarm_str_len = set_alarm_str.length() + 1;
      char set_alarm_str_array[set_alarm_str_len];
      set_alarm_str.toCharArray(set_alarm_str_array, set_alarm_str_len);

      unsigned long currentMillis = millis();

      if (currentMillis - pMill > intervall) {
        pMill = currentMillis;
        if (alarmState == LOW) {
          alarmState = HIGH;
          oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
        }
        else {
          alarmState = LOW;
          oled.LED_P8x16Str(alarm_start + 25, 2, "  ");
        }
      }
      if (digitalRead(sel) == LOW)
      {
        alarm_min++;
        if (alarm_min > 59) alarm_min = 0;
        oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
        delay(250);
      }
      if (digitalRead(set) == LOW)
      {
        delay(500);
        break;
      }
    }

    while (1)
    {
      set_alarm_str = convertSet('t', alarm_hr, alarm_min, alarm_sec);

      int set_alarm_str_len = set_alarm_str.length() + 1;
      char set_alarm_str_array[set_alarm_str_len];
      set_alarm_str.toCharArray(set_alarm_str_array, set_alarm_str_len);

      unsigned long currentMillis = millis();

      if (currentMillis - pMill > intervall) {
        pMill = currentMillis;
        if (alarmState == LOW) {
          alarmState = HIGH;
          oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
        }
        else {
          alarmState = LOW;
          oled.LED_P8x16Str(alarm_start + 48, 2, "  ");
        }
      }
      if (digitalRead(sel) == LOW)
      {
        alarm_sec++;
        if (alarm_sec > 59) alarm_sec = 0;
        oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
        delay(250);
      }
      if (digitalRead(set) == LOW)
      {
        delay(500);
        break;
      }
    }

    while (1) {
      set_alarm_str = convertSet('t', alarm_hr, alarm_min, alarm_sec);

      int set_alarm_str_len = set_alarm_str.length() + 1;
      char set_alarm_str_array[set_alarm_str_len];
      set_alarm_str.toCharArray(set_alarm_str_array, set_alarm_str_len);

      oled.LED_P8x16Str(8, 0, "  Your Alarm");
      oled.LED_P8x16Str(alarm_start, 2, set_alarm_str_array);
      oled.LED_P8x16Str(alarm_start, 4, "Confirm?");
      if (digitalRead(set) == LOW)
      {
        delay(500);
        DateTime now = rtc.now();
        rtc.setAlarm1(DateTime(now.year(), now.month(), now.day(),
                               alarm_hr, alarm_min, alarm_sec), DS3231_A1_Hour);
        alarm_set = 1;
        bye_bye = 1;
        break;
      }
      if (digitalRead(sel) == LOW)
      {
        delay(500);
        oled.LED_CLS();
        alarm_sec = 00;
        break;
      }
    }
    if (bye_bye == 1)
    {

      mode = 1;
      break;
    }
  }
}
