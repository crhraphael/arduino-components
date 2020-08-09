#ifndef SERVOIMPLEMENTATION
#define SERVOIMPLEMENTATION

#include <Translators/Servo/IServoInputTranslator.h>
#include <Implementations/Servo/IServoImplementation.h>
#include <Servo.h>

/**
 * 
 */
class ServoImplementation: public IServoImplementation, public Servo {
	private:
	Servo servo;

	public:
	ServoImplementation(int pin)
	{
		pinMode(pin, OUTPUT);
		this->servo.attach(pin);
	};

  void send(int value) {
		this->servo.write(value);
	}
};

#endif