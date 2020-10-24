#include <krabiIOT.h>
#define buzzer 14
void setup()
{
  krabiInit(); 
}
void loop()
{
 tone32(buzzer,500);
 delay(200);
 noTone32(buzzer);
 delay(200);
}