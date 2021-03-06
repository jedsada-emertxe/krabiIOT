#include <krabiIOT.h>
LCD lcd(0x27,16,2); 
RTC rtc;
void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(3,0);
    lcd.print("ElecKrabi");
    Wire.begin();
    delay(2000);
    rtc.attach(Wire);
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("Time:  :  :       ");
  lcd.setCursor(5,0);
  lcd.print(rtc.hour());
  lcd.setCursor(8,0);
  lcd.print(rtc.minute());
  lcd.setCursor(11,0);
  lcd.print(rtc.second());
  
  lcd.setCursor(0,1);
  lcd.print("Date:  :  :       ");  
  lcd.setCursor(5,1);
  lcd.print(rtc.day());
  lcd.setCursor(8,1);
  lcd.print(rtc.month());
  lcd.setCursor(11,1);
  lcd.print(rtc.year());
  delay(1000);
}
