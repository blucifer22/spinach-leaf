/**
* Sensor data aggregation class. Allows for sensors to be registered and their data to be stored.
*
* Author: David Coffman
**/

#ifndef SENSOR_DATA_AGGREGATOR_H
#define SENSOR_DATA_AGGREGATOR_H

#include <unordered_map>
#include <unordered_set>
#include "Sensor.h"

using namespace std;

class SensorDataAggregator: SensorDataListener {
private:
  unordered_map<string, float>* sensor_data;
  unordered_set<string>* invalid_sensors;
public:
  SensorDataAggregator();

  // virtual methods to implement
  void registerSensor(string sensorID);
  void postSensorData(string sensorID, float& measurement);
  void invalidateSensorData(string sensorID);
};

#endif
