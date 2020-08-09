#ifndef ISERVOIMPLEMENTATION
#define ISERVOIMPLEMENTATION

#include <Arduino.h>

class IServoImplementation {
  private:
  public:
  virtual ~IServoImplementation() = 0;
	virtual void send(int value) = 0;
};

IServoImplementation::~IServoImplementation() {};
#endif