/** A simple example program that allows us to flash an LED over a Bluetooth "classic"
 * connection.
 * Author: Marc Chmielewski
 **/

#include "Arduino.h"
#include "BluetoothSerial.h"
#include "LIDARLite_v4LED.h"
#include "network/BLE.hpp"

#include "SparkFun_I2C_Mux_Arduino_Library.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define NUM_SENSORS 3
#define CLOSE_RANGE 2

QWIICMUX myMux;
LIDARLite_v4LED myLIDAR[NUM_SENSORS];
BLEProvider* ble;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  Wire.begin(); //Join I2C

  Serial.println("Powered on!");

  ble = new BLEProvider();

  // check if Feather can find the mux board
  if (myMux.begin() == false) {
    Serial.println("Device did not acknowledge! Not Freezing.");
    while(1);
  }

  // loop through and initialize the LIDARs
  for (byte i = 0; i < NUM_SENSORS; i++) {
    myMux.setPort(i);
    //check if LIDAR will acknowledge over I2C
    if (myLIDAR[i].begin()) {
      Serial.printf("LIDAR %d acknowledged!\n", i);
      myLIDAR[i].configure(CLOSE_RANGE);
    } else {
      Serial.printf("Sensor %d did not acknowledge! Freezing.\n", i);
      while(1);
    }
  }
}


void loop() {
  static float* distances = new float[3];
  if (ble->sensorsEnabled()) {
    // loop through LIDARs and get distance readings; print to serial
    printf("Sensors enabled; updating distances!\n");
    digitalWrite(BUILTIN_LED, HIGH);

    for (byte i = 0; i < NUM_SENSORS; i++) {
      myMux.setPort(i);
      myLIDAR[i].takeRange();
    }
    for (byte i = 0; i < NUM_SENSORS; i++) {
      myMux.setPort(i);
      myLIDAR[i].waitForBusy();
    }
    for (byte i = 0; i < NUM_SENSORS; i++) {
      myMux.setPort(i);
      distances[i] = myLIDAR[i].readDistance();
      Serial.printf("lidar %d: %f cm ", i, distances[i]);
    }
    Serial.printf("\n");
  } else {
    printf("Sensors disabled; skipping update and setting distances to 0!\n");
    for (byte i = 0; i < NUM_SENSORS; i++) distances[i] = 0;
    digitalWrite(BUILTIN_LED, LOW);
  }

  ble->updateLeftLidar((unsigned int) distances[0]);
  ble->updateCenterLidar((unsigned int) distances[1]);
  ble->updateRightLidar((unsigned int) distances[2]);

  delay(20);
}
