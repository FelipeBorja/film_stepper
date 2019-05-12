/*
 * screenPrint - Prints a string 'str' to the LCD screen,
 * holds it for 'hold_time' amount of ms, and repeats it
 * 'total_times' amount of times
 * 
 * Note: has internal delay, so does not work with the current setup of
 *       the move motor function.
 *       Needs to be re-written with the same microsecond counting to work
 *       alongside the other function.
 */
void screenPrint(String str, int hold_time, int total_times)
{
  lcd.begin(16,2);
  for(int i=0; i<total_times; i++)
  {
    lcd.clear();
    lcd.print(str);
    delay(hold_time);
    lcd.clear();
    // only trigger delay for repeat cases
    if(total_times > 1){
      delay(500);
    }    
  }
}
