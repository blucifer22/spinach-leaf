/** A simple example program that allows us to flash an LED over a Bluetooth "classic"
 * connection.
 * Author: Marc Chmielewski
 **/

#include "Arduino.h"
#include "BluetoothSerial.h"
#include "LIDARLite_v4LED.h"

#include "SparkFun_I2C_Mux_Arduino_Library.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define NUM_SENSORS 2

#define CLOSE_RANGE 2

QWIICMUX myMux;

BluetoothSerial SerialBT;
LIDARLite_v4LED myLIDAR[2];

// CHANGED for development purposes since I don't have a bluetooth serial monitor
bool enable = 1;


void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  SerialBT.begin("SpinachLeaf"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Wire.begin(); //Join I2C bus

  
  // check if Feather can find the mux board
  if (myMux.begin() == false) {
    Serial.println("Device did not acknowledge! Not Freezing.");
    while(1);
  }

  // loop through and initialize the LIDARs
  for (byte i = 0; i < NUM_SENSORS; i++) {
    myMux.setPort(i);
    //check if LIDAR will acknowledge over I2C
    if (myLIDAR[i].begin() == false) {
      Serial.printf("Sensor: %d", i);
      Serial.println("Device did not acknowledge! Freezing.");
      while(1);
    }

      Serial.println("LIDAR acknowledged!");
      myLIDAR[i].configure(CLOSE_RANGE);
  }

}


void loop() {
  if (enable) {
    // loop through LIDARs and get distance readings
    for (byte i = 0; i < NUM_SENSORS; i++) {
      myMux.setPort(i);

      //getDistance() returns the distance reading in cm
      float newDistance = myLIDAR[i].getDistance();

      //Print to Serial port
      //SerialBT.printf("New distance: %f cm\n", newDistance);
      Serial.printf("New distance, lidar %d: %f cm ", i, newDistance);
    }
    Serial.printf("\n");

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