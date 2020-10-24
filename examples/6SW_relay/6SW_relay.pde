#include <krabiIOT.h>
void setup()
{
  krabiInit();  
}
void loop()
{
  if(!SETUP)
  {
    RELAY1_ON; 
  }else
  if(!UP)
  {
    RELAY2_ON; 
  }else
  if(!DN)
  {
    RELAY3_ON; 
  }else
  if(!OK)
  {
    RELAY4_ON; 
  }else
  {
    RELAY1_OFF;
    RELAY2_OFF;
    RELAY3_OFF;
    RELAY4_OFF;
  }
}