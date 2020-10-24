#include <krabiIOT.h>
void setup()
{
  krabiInit();	   
}
void loop()
{
  RELAY1_ON;
  delay(500);
  RELAY1_OFF;
  delay(500);
}