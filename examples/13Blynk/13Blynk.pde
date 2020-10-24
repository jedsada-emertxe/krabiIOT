//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  Blynk.run();
}