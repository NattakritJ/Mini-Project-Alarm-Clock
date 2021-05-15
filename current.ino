int base = 40;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int move_cur[7] = {0, 0, -5, -12, -7, 0, -7};

String current_date, current_time;

void current()
{
  DateTime now = rtc.now();
  
  current_date = convertSet('d', now.year(), now.month(), now.day());
  current_time = convertSet('t', now.hour(), now.minute(), now.second());
  
  int current_date_len = current_date.length() + 1;
  char current_date_array[current_date_len];
  current_date.toCharArray(current_date_array, current_date_len);

  int current_time_len = current_time.length() + 1;
  char current_time_array[current_time_len];
  current_time.toCharArray(current_time_array, current_time_len);

  int current_DOW = now.dayOfTheWeek();

  oled.LED_P8x16Str(base + move_cur[current_DOW], 0, daysOfTheWeek[current_DOW]);
  oled.LED_P8x16Str(23, 2, current_date_array);
  oled.LED_P8x16Str(32, 4, current_time_array);
}
