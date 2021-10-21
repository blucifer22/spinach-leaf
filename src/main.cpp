/** A simple example program that allows us to flash an LED over a Bluetooth "classic"
 * connection.
 * Author: Marc Chmielewski 
 **/

#include "Arduino.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  SerialBT.begin("SpinachLeaf"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    int sentInt = SerialBT.parseInt();
    if(sentInt == 1) {
      digitalWrite(BUILTIN_LED, LOW);
      Serial.println("Now you don't!");
    }
    else if(sentInt == 2) {
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("Now you see me!");
    }
    else {
      Serial.println("Invalid input!");
    }
  }
  delay(20);
}