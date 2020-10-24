#include <krabiIOT.h>
void setup()
{
  krabiInit();  
}
void loop()
{
  if(!SETUP)
  {
    beep_on(3000);
    delay(50);
    beep_off(); 
  }
}