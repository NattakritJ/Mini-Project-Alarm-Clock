int year_set = 2010;
int month_set = 01;
int day_set = 01;

int hour_set = 00;
int minute_set = 00;
int second_set = 00;

int date_start = 23;
int time_start = 27;

int bye = 0;

long previousMillis = 0;
long interval = 500;
int textState = LOW;

String set_date_str, set_time_str;

void setDate()
{
  current();
  oled.LED_P8x16Str(30, 6, "Use this?");
  if (digitalRead(sel) == LOW || rtc.lostPower())
  {
    oled.LED_CLS();
    while (1)
    {
      oled.LED_P8x16Str(10, 0, "Set Date");
      while (1)
      {
        set_date_str = convertSet('d', year_set, month_set, day_set);

        int set_date_str_len = set_date_str.length() + 1;
        char set_date_str_array[set_date_str_len];
        set_date_str.toCharArray(set_date_str_array, set_date_str_len);

        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis > interval) {
          previousMillis = currentMillis;
          if (textState == LOW) {
            textState = HIGH;
            oled.LED_P8x16Str(date_start, 2, set_date_str_array);
          }
          else {
            textState = LOW;
            oled.LED_P8x16Str(date_start, 2, "    ");
          }
        }
        if (digitalRead(sel) == LOW)
        {
          year_set++;
          oled.LED_P8x16Str(date_start, 2, set_date_str_array);
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
        set_date_str = convertSet('d', year_set, month_set, day_set);

        int set_date_str_len = set_date_str.length() + 1;
        char set_date_str_array[set_date_str_len];
        set_date_str.toCharArray(set_date_str_array, set_date_str_len);

        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis > interval) {
          previousMillis = currentMillis;
          if (textState == LOW) {
            textState = HIGH;
            oled.LED_P8x16Str(date_start, 2, set_date_str_array);
          }
          else {
            textState = LOW;
            oled.LED_P8x16Str(date_start + 40, 2, "  ");
          }
        }
        if (digitalRead(sel) == LOW)
        {
          month_set++;
          if (month_set > 12) month_set = 1;
          oled.LED_P8x16Str(date_start, 2, set_date_str_array);
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
        set_date_str = convertSet('d', year_set, month_set, day_set);

        int set_date_str_len = set_date_str.length() + 1;
        char set_date_str_array[set_date_str_len];
        set_date_str.toCharArray(set_date_str_array, set_date_str_len);

        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis > interval) {
          previousMillis = currentMillis;
          if (textState == LOW) {
            textState = HIGH;
            oled.LED_P8x16Str(date_start, 2, set_date_str_array);
          }
          else {
            textState = LOW;
            oled.LED_P8x16Str(date_start + 65, 2, "  ");
          }
        }
        if (digitalRead(sel) == LOW)
        {
          day_set++;
          if ((month_set == 2) && (year_set % 4 == 0) && (day_set > 29)) day_set = 1;
          else if ((month_set == 2) && (year_set % 4 != 0) && (day_set > 28)) day_set = 1;
          else if ((month_set == 1 || month_set == 3 || month_set == 5 || month_set == 7 || month_set == 8 || month_set == 10 || month_set == 12) && day_set > 31) day_set = 1;
          else if ((month_set == 4 || month_set == 6 || month_set == 9 || month_set == 11) && day_set > 30) day_set = 1;
          oled.LED_P8x16Str(date_start, 2, set_date_str_array);
          delay(250);
        }
        if (digitalRead(set) == LOW)
        {
          delay(500);
          break;
        }
      }

      while (1) {
        set_date_str = convertSet('d', year_set, month_set, day_set);

        int set_date_str_len = set_date_str.length() + 1;
        char set_date_str_array[set_date_str_len];
        set_date_str.toCharArray(set_date_str_array, set_date_str_len);

        oled.LED_P8x16Str(date_start, 2, set_date_str_array);
        oled.LED_P8x16Str(date_start - 10, 4, "Confirm date?");
        if (digitalRead(set) == LOW)
        {
          delay(500);
          setTime();
          bye = 1;
          break;
        }
        if (digitalRead(sel) == LOW)
        {
          delay(500);
          oled.LED_CLS();
          year_set = 2000;
          month_set = 01;
          day_set = 01;
          break;
        }
      }
      if (bye == 1) break;
    }
  }
}

void setTime()
{
  bye = 0;
  oled.LED_CLS();
  while (1)
  {
    oled.LED_P8x16Str(10, 0, "Set Time");
    while (1)
    {
      set_time_str = convertSet('t', hour_set, minute_set, second_set);

      int set_time_str_len = set_time_str.length() + 1;
      char set_time_str_array[set_time_str_len];
      set_time_str.toCharArray(set_time_str_array, set_time_str_len);

      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        if (textState == LOW) {
          textState = HIGH;
          oled.LED_P8x16Str(time_start, 2, set_time_str_array);
        }
        else {
          textState = LOW;
          oled.LED_P8x16Str(time_start, 2, "  ");
        }
      }
      if (digitalRead(sel) == LOW)
      {
        hour_set++;
        if (hour_set > 23) hour_set = 0;
        oled.LED_P8x16Str(time_start, 2, set_time_str_array);
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
      set_time_str = convertSet('t', hour_set, minute_set, second_set);

      int set_time_str_len = set_time_str.length() + 1;
      char set_time_str_array[set_time_str_len];
      set_time_str.toCharArray(set_time_str_array, set_time_str_len);

      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        if (textState == LOW) {
          textState = HIGH;
          oled.LED_P8x16Str(time_start, 2, set_time_str_array);
        }
        else {
          textState = LOW;
          oled.LED_P8x16Str(time_start + 25, 2, "  ");
        }
      }
      if (digitalRead(sel) == LOW)
      {
        minute_set++;
        if (minute_set > 59) minute_set = 0;
        oled.LED_P8x16Str(time_start, 2, set_time_str_array);
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
      set_time_str = convertSet('t', hour_set, minute_set, second_set);

      int set_time_str_len = set_time_str.length() + 1;
      char set_time_str_array[set_time_str_len];
      set_time_str.toCharArray(set_time_str_array, set_time_str_len);

      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        if (textState == LOW) {
          textState = HIGH;
          oled.LED_P8x16Str(time_start, 2, set_time_str_array);
        }
        else {
          textState = LOW;
          oled.LED_P8x16Str(time_start + 48, 2, "  ");
        }
      }
      if (digitalRead(sel) == LOW)
      {
        second_set++;
        if (second_set > 59) second_set = 0;
        oled.LED_P8x16Str(time_start, 2, set_time_str_array);
        delay(250);
      }
      if (digitalRead(set) == LOW)
      {
        delay(500);
        break;
      }
    }

    while (1) {
      set_date_str = convertSet('d', year_set, month_set, day_set);

      int set_date_str_len = set_date_str.length() + 1;
      char set_date_str_array[set_date_str_len];
      set_date_str.toCharArray(set_date_str_array, set_date_str_len);

      set_time_str = convertSet('t', hour_set, minute_set, second_set);

      int set_time_str_len = set_time_str.length() + 1;
      char set_time_str_array[set_time_str_len];
      set_time_str.toCharArray(set_time_str_array, set_time_str_len);

      oled.LED_P8x16Str(10, 0, "Your Setting");
      oled.LED_P8x16Str(date_start, 2, set_date_str_array);
      oled.LED_P8x16Str(time_start, 4, set_time_str_array);
      oled.LED_P8x16Str(time_start, 6, "Confirm?");
      if (digitalRead(set) == LOW)
      {
        delay(500);
        rtc.adjust(DateTime(year_set, month_set, day_set, hour_set, minute_set, second_set));
        bye = 1;
        break;
      }
      if (digitalRead(sel) == LOW)
      {
        delay(500);
        oled.LED_CLS();
        hour_set = 00;
        minute_set = 00;
        second_set = 00;
        break;
      }
    }
    if (bye == 1)
    {
      oled.LED_CLS();
      mode = 1;
      break;
    }
  }
}
