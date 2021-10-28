
#include <string>
#include <unordered_map>
#include "BluetoothSerial.h"
#include "../util/StringKeyedDataSource.h"
#include "BTNetworkOutput.h"

using namespace std;

template <typename T>
BTNetworkOutput<T>::BTNetworkOutput(BluetoothSerial* serial, StringConverter<T>* converter) {
  this->serial = serial;
  this->converter = converter;
}

template <typename T>
void BTNetworkOutput<T>::sendFromDataSource(StringKeyedDataSource<T>* source) {
  unordered_map<string, T>* dataMap = source->getData();
  string result = "{\n";
  for (string key: dataMap->enum_keys()) {
    result.append("\"");
    result.append(key);
    result.append("\": ");
    string valueString = this->converter->convert(dataMap[key]);
    result.append(valueString);
    result.append(",");
  }
  if (result.back() == ',') {
    result.pop_back();
  }
  result.append("\n}");
  char* res = result.c_str();
  serial->println(res);
}
