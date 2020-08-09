#ifndef ISERVOINPUTTRANSLATOR
#define ISERVOINPUTTRANSLATOR

#include <Servo.h>

class IServoInputTranslator {
  private:
  public:
  virtual ~IServoInputTranslator() = 0;

  virtual int translate(float vel, int dir) = 0;
  virtual void setVelocity(float vel, int dir) = 0;
};

IServoInputTranslator::~IServoInputTranslator() {};
#endif