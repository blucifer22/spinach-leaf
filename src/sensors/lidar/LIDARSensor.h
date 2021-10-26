/**
 * Light wrapper for the LIDAR sensor to implement virtual methods from Sensor.
 *
 * Author: David Coffman
 **/

#ifndef LIDAR_SENSOR_H
#define LIDAR_SENSOR_H

#include <string>
#include <vector>
#include "../Sensor.h"
#include "LIDARLite_v4LED.h"

class LIDARSensor: Sensor {
private:
  string sensorID;
  bool enabled;
  LIDARLite_v4LED* sensor;
  vector<SensorDataListener*>* listeners;
public:
  LIDARSensor(string sensorID, LIDARLite_v4LED* sensor);
  void registerListener(SensorDataListener* listener);
  void measure();
  void disable();
  void enable();
};

#endif
