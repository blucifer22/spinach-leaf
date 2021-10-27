#ifndef STRING_KEYED_DATA_SOURCE_H
#define STRING_KEYED_DATA_SOURCE_H

#include<string>
#include <unordered_map>

using namespace std;

template<typename T>
class StringKeyedDataSource {
public:
  virtual unordered_map<string, T>* getData() = 0;
};

#endif
