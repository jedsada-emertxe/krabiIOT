#include "krabiIOT.h"
#define Trig 13
#define Echo 12
LCD lcd(0x27,16,2); 
Ultrasonic ultrasonic(Trig,Echo);
int distance;
void setup()
{
  krabiInit();	
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("ElecKrabi");
}
void loop()
{  
  lcd.setCursor(0,1);
  lcd.print("Distance:     cm");
  distance = ultrasonic.read();
  lcd.setCursor(9,1);
  lcd.print(distance);
  delay(500);
}