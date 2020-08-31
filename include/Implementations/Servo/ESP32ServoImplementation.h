#ifndef ESP32SERVOIMPLEMENTATION
#define ESP32SERVOIMPLEMENTATION

#include <Implementations/Servo/IServoImplementation.h>
#include <ESP32Servo.h>

/**
 * 
 */
class ESP32ServoImplementation: public IServoImplementation, public Servo {
	private:
	Servo servo;

	public:
	ESP32ServoImplementation(int pin)
	{
		pinMode(pin, OUTPUT);
		this->servo.attach(pin);
	};

  void send(int value) {
		this->servo.write(value);
	}
};

#endif