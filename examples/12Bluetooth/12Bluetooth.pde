#include "BluetoothSerial.h"
#include <krabiROBOT.h>
BluetoothSerial ESP_BT;

int dataBT;

void setup() {
  ROBOTinit();
  Serial.begin(9600);
  ESP_BT.begin("ESP32_IoTRobot");
  Serial.println("Bluetooth Device is Ready to Pair");
}

void loop() {
  if (ESP_BT.available())
  {
    dataBT = ESP_BT.read();
    Serial.print("Received:"); 
    Serial.println(dataBT);
    if (dataBT == 'A')
    {
      digitalWrite(4, HIGH);
      ESP_BT.println("LED ON");
    }else
    if (dataBT == 'B')
    {
      digitalWrite(4, LOW);
      ESP_BT.println("LED ON");
    }
  }  
  delay(20);
}