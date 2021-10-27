#ifndef NETWORK_OUTPUT_H
#define NETWORK_INPUT_H

#include <string>
#include <unordered_map>
#include "../util/StringKeyedDataSource.h"

using namespace std;

template <typename DT>
class StringConverter {
public:
  virtual string convert(DT& data) = 0;
};

template <typename T>
class NetworkOutput {
public:
  virtual void sendFromDataSource(StringKeyedDataSource<T>* source) = 0;
};

#endif
