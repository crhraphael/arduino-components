#ifndef ISERVOINPUTTRANSLATOR
#define ISERVOINPUTTRANSLATOR

class IServoInputTranslator {
  private:
  public:
  virtual ~IServoInputTranslator() = 0;

  virtual int translate(float vel, int dir) = 0;
  virtual void set(float vel, int dir) = 0;
};

IServoInputTranslator::~IServoInputTranslator() {};
#endif