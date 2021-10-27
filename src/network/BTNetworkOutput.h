#ifndef BT_NETWORK_OUTPUT_H
#define BT_NETWORK_INPUT_H

#include <string>
#include <unordered_map>
#include "BluetoothSerial.h"
#include "../util/StringKeyedDataSource.h"
#include "NetworkOutput.h"

using namespace std;

template <typename T>
class BTNetworkOutput: NetworkOutput<T> {
private:
  BluetoothSerial* serial;
  StringConverter<T>* converter;
public:
  BTNetworkOutput(BluetoothSerial* serial, StringConverter<T>* converter);
  void sendFromDataSource(StringKeyedDataSource<T>* source);
};

#endif
