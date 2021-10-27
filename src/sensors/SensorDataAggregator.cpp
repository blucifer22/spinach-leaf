/**
 * Implementations for SensorDataAggregator.
 *
 * Author: David Coffman
 **/

#include <string>
#include <unordered_map>
#include "Sensor.h"
#include "SensorDataAggregator.h"

using namespace std;

SensorDataAggregator::SensorDataAggregator() {
  this->sensor_data = new unordered_map<string, float>;
  this->invalid_sensors = new unordered_set<string>;
}

void SensorDataAggregator::registerSensor(string sensorID) {
  this->invalid_sensors->insert(sensorID);
}

void SensorDataAggregator::postSensorData(string sensorID, float& measurement) {
  if (this->invalid_sensors->find(sensorID) == this->invalid_sensors->end()) {
    this->invalid_sensors->erase(sensorID);
  }
  this->sensor_data->emplace(sensorID, measurement);
}

void SensorDataAggregator::invalidateSensorData(string sensorID) {
  this->invalid_sensors->insert(sensorID);
}

unordered_map<string, float>* SensorDataAggregator::getData() {
  return this->sensor_data;
}
