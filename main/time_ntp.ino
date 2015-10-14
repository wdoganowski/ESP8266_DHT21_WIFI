void setup_Time() 
{
  rest.function("datetime", set_date_time);
}

#ifndef DEBUG_TIME_NTP
time_t prevDisplay = 0; // when the digital clock was displayed
#endif

void handle_Time()
{  
  #ifndef DEBUG_TIME_NTP
  // Debug display
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();  
    }
  }
  #endif  
}

/*
 * Set time: YYYYMMDDhhmmss
 */
int set_date_time(String t) {
  // setTime(hr,min,sec,day,month,yr);
  #ifdef DEBUG_TIME_NTP
  Serial.println(t);    
  Serial.print(t.substring(8,10).toInt());
  printDigits(t.substring(10,12).toInt());
  printDigits(t.substring(12,14).toInt());
  Serial.print(" ");
  Serial.print(t.substring(6,8).toInt());
  Serial.print(" ");
  Serial.print(t.substring(4,6).toInt());
  Serial.print(" ");
  Serial.print(t.substring(0,4).toInt()); 
  Serial.println();
#  endif  
  setTime(t.substring(8,10).toInt(), // hour
          t.substring(10,12).toInt(), // min
          t.substring(12,14).toInt(), // sec
          t.substring(6,8).toInt(), // day
          t.substring(4,6).toInt(), // month
          t.substring(0,4).toInt());// year
  return 0;
}

/*
 * Debug functions
 */
#ifndef DEBUG_TIME_NTP

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

#endif
