#ifndef SERVOIMPLEMENTATION
#define SERVOIMPLEMENTATION

#include <Implementations/Servo/IServoImplementation.h>
#include <Servo.h>
#include <Arduino.h>

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