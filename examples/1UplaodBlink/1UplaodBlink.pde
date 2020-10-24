#include <krabiIOT.h>
#define power 2
void setup()
{
  krabiInit();	   
}
void loop()
{
	digitalWrite(power,1);
	delay(500);
	digitalWrite(power,0);
	delay(500);
}