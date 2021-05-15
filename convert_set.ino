String convertSet(char type, int input1, int input2, int input3)

{
  String symbol;

  if (type == 'd') symbol = "-";
  else if (type == 't') symbol = ":";

  String input1_str, input2_str, input3_str;

  if (input1 < 10) input1_str = "0" + String(input1);
  else input1_str = String(input1);
  if (input2 < 10) input2_str = "0" + String(input2);
  else input2_str = String(input2);
  if (input3 < 10) input3_str = "0" + String(input3);
  else input3_str = String(input3);

  String combined_str = input1_str + symbol + input2_str + symbol + input3_str;

  return combined_str;
}
