#ifndef IBLUETOOTHIMPLEMENTATION
#define IBLUETOOTHIMPLEMENTATION

#include <Arduino.h>

class IBluetoothImplementation {
  private:
  public:
  virtual ~IBluetoothImplementation() = 0;
  virtual void listen(char *buf) = 0;

	virtual void reset() = 0;
	virtual bool isFillingBuffer() = 0;
};

IBluetoothImplementation::~IBluetoothImplementation() {};
#endif