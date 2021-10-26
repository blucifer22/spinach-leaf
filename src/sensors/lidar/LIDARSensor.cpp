/**
 * LIDARSensor implementation.
 *
 * Author: David Coffman
 **/

#include "LIDARSensor.h"
#include <string>

LIDARSensor::LIDARSensor(string sensorID, LIDARLite_v4LED* sensor) {
  this->sensorID = sensorID;
  this->sensor = sensor;
  this->enabled = false;
}

void LIDARSensor::registerListener(SensorDataListener *listener) {
  this->listeners->push_back(listener);
}

void LIDARSensor::measure() {
  if (this->enabled) {
    float measurement = sensor->getDistance();
    for (int i = 0; i < this->listeners->size(); i++) {
      listeners->at(i)->postSensorData(this->sensorID, measurement);
    }
  }
}

void LIDARSensor::enable() {
  this->enabled = true;
}

void LIDARSensor::disable() {
  this->enabled = false;
}
