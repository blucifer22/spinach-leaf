/**
 * Basic abstract classes for sensor data aggregation and transmission.
 *
 * Author: David Coffman
 **/

#ifndef SENSOR_H
#define SENSOR_H

#include <string>

using namespace std;

class SensorDataListener {
public:
  virtual void registerSensor(string sensorID) = 0;
  virtual void postSensorData(string sensorID, float& measurement) = 0;
  virtual void invalidateSensorData(string sensorID) = 0;
};

class Sensor {
public:
  virtual void registerListener(SensorDataListener* listener) = 0;
  virtual void measure() = 0;
  virtual void disable() = 0;
  virtual void enable() = 0;
};

#endif
