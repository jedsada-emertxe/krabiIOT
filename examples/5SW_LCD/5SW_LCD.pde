#include <krabiIOT.h>

LCD lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup()
{
  krabiInit();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("ElecKrabi");
  lcd.setCursor(0,1);
  lcd.print("Design By Sumate");
  delay(1000);
}
void loop()
{
  if(!SETUP)
  {
    lcd.setCursor(0,1);
    lcd.print("Push SETUP       ");
  }else
  {
    lcd.setCursor(0,1);
    lcd.print("Pull SETUP       ");
  }
}