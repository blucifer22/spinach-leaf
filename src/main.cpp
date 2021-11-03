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
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }

  // loop through and initialize the LIDARs
  for (byte i = 0; i < NUM_SENSORS; i++) {
    myMux.setPort(i);
    //check if LIDAR will acknowledge over I2C
    if (myLIDAR[i].begin() == false) {
      Serial.println("Device did not acknowledge! Freezing.");
      while(1);
    }

      Serial.println("LIDAR acknowledged!");
      myLIDAR[i].configure(2);
  }
}


void loop() {
  if (enable) {
    float newDistance;

    //getDistance() returns the distance reading in cm
    newDistance = myLIDAR.getDistance();

    //Print to Serial port
    //SerialBT.printf("New distance: %f cm\n", newDistance);
    Serial.printf("New distance: %f cm\n", newDistance);
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

/*

  bool begin(uint8_t deviceAddress = QWIIC_MUX_DEFAULT_ADDRESS, TwoWire &wirePort = Wire); //Check communication and initialize device
  bool isConnected();                                                                      //Returns true if device acks at the I2C address
  bool setPort(uint8_t portNumber);                                                        //Enable a single port. All other ports disabled.
  bool setPortState(uint8_t portBits);                                                     //Overwrite port register with all 8 bits. Allows multiple bit writing in one call.
  uint8_t getPort();                                                                       //Returns the bit position of the first enabled port. Useful for IDing which port number is enabled.
  uint8_t getPortState();                                                                  //Returns current 8-bit wide state. May have multiple bits set in 8-bit field.
  bool enablePort(uint8_t portNumber);                                                     //Enable a single port without affecting other bits
  bool disablePort(uint8_t portNumber); 
*/