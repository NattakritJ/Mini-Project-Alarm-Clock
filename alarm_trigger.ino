int rgbIndex;
int enterLight = 0;
int alarmBlinkState = 0;

String repeat_alarm_str;

void alarmTrigger()
{
  while (1)
  {
    current();
    if (digitalRead(sel) == LOW || digitalRead(set) == LOW)
    {
      analogWrite(RED_LED, 0);
      analogWrite(GREEN_LED, 0);
      analogWrite(BLUE_LED, 0);
      digitalWrite(LED1, LOW);
      delay(250);
      oled.LED_CLS();
      while (1)
      {
        repeat_alarm_str = convertSet('t', alarm_hr, alarm_min, alarm_sec);
        int repeat_alarm_str_len = repeat_alarm_str.length() + 1;
        char repeat_alarm_str_array[repeat_alarm_str_len];
        repeat_alarm_str.toCharArray(repeat_alarm_str_array, repeat_alarm_str_len);

        oled.LED_P8x16Str(8, 0, "   Alarm off");
        oled.LED_P8x16Str(alarm_start - 16, 2, "Repeat alarm?");
        oled.LED_P8x16Str(alarm_start, 4, repeat_alarm_str_array);
        if (digitalRead(set) == LOW)
        {
          delay(500);
          rtc.clearAlarm(1);
          DateTime now = rtc.now();
          rtc.setAlarm1(DateTime(now.year(), now.month(), now.day(),
                                 alarm_hr, alarm_min, alarm_sec), DS3231_A1_Hour);
          mode = 1;
          oled.LED_CLS();
          break;
        }
        if (digitalRead(sel) == LOW)
        {
          delay(500);
          rtc.clearAlarm(1);
          alarm_set = 0;
          mode = 1;
          oled.LED_CLS();
          break;
        }
      }
      break;
    }
    else if (enterLight == 0)
    {
      enterLight = 1;
      analogWrite(RED_LED, random(0, 255));
      analogWrite(GREEN_LED, random(0, 255));
      analogWrite(BLUE_LED, random(0, 255));
      digitalWrite(LED1, LOW);
      oled.LED_P8x16Str(40, 6, "ALARM!");
    }
    else if (enterLight == 1)
    {
      enterLight = 0;
      analogWrite(RED_LED, 0);
      analogWrite(GREEN_LED, 0);
      analogWrite(BLUE_LED, 0);
      digitalWrite(LED1, HIGH);
      oled.LED_P8x16Str(40, 6, "      ");
    }
  }
}
