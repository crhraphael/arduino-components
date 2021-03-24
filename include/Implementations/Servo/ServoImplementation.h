#ifndef SERVOIMPLEMENTATION
#define SERVOIMPLEMENTATION

#include <Implementations/Servo/IServoImplementation.h>
#include <Servo.h>
#include <Arduino.h>

/**
 * 
 */
class ServoImplementation: public IServoImplementation {
	private:
	Servo servo;

	public:
	ServoImplementation(int pin)
	{
		pinMode(pin, OUTPUT);
		this->servo.attach(pin);
	};

  void sendMicroseconds(int value) {
		this->servo.writeMicroseconds(value);
	}

	void send(int value) {
		this->servo.write(value);
	}
};

#endif