/** A simple example program that allows us to flash an LED over a Bluetooth "classic"
 * connection.
 * Author: Marc Chmielewski
 **/

#include "Arduino.h"
#include "BluetoothSerial.h"
#include "LIDARLite_v4LED.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
LIDARLite_v4LED myLIDAR;
bool enable = 0;


void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  SerialBT.begin("SpinachLeaf"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Wire.begin(); //Join I2C bus

  //check if LIDAR will acknowledge over I2C
  if (myLIDAR.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("LIDAR acknowledged!");

  myLIDAR.configure(2);
}

void loop() {
  if (enable) {
    float newDistance;

    //getDistance() returns the distance reading in cm
    newDistance = myLIDAR.getDistance();

    //Print to Serial port
    SerialBT.printf("New distance: %f cm\n", newDistance);
  }
  if (SerialBT.available()) {
    int sentInt = SerialBT.parseInt();
    if(sentInt == 1) {
      enable = 0;
      digitalWrite(BUILTIN_LED, LOW);
      Serial.println("Now you don't!");
    }
    else if(sentInt == 2) {
      enable = 1;
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("Now you see me!");
    }
    else {
      Serial.println("Invalid input!");
    }
  }
  delay(20);
}
