#ifndef ISERVOIMPLEMENTATION
#define ISERVOIMPLEMENTATION

class IServoImplementation {
  private:
  public:
  virtual ~IServoImplementation() = 0;
	virtual void send(int value) = 0;
	virtual void sendMicroseconds(int value) = 0;
};

IServoImplementation::~IServoImplementation() {};
#endif