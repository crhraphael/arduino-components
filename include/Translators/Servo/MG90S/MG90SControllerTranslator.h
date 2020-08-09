#ifndef MG90SCONTROLLERTRANSLATOR
#define MG90SCONTROLLERTRANSLATOR

#include <Translators/Servo/IServoInputTranslator.h>
#include <IArduinoCompontent.h>

class MG90SControllerTranslator: public IArduinoComponent, public IServoInputTranslator {
	private:
	Servo servo;

	public:
	MG90SControllerTranslator(int pin): 
		MAX_VELOCITY(10), 
		SERVO_STOPPED_VALUE(135) 
	{
		pinMode(pin, OUTPUT);
		this->servo.attach(pin);
	};

	/**
	 * Valor máximo da velocidade do motor.
	 */
	const int MAX_VELOCITY; 

	/**
	 * Valor que mantem o servo parado.
	 */
	const int SERVO_STOPPED_VALUE;


  int translate(float velocityCap, int dir) {
		return (int)(this->SERVO_STOPPED_VALUE + (dir * (MG90SControllerTranslator::MAX_VELOCITY * velocityCap)));
	}
  void setVelocity(float vel, int dir) {
		int value = this->translate(vel, dir);
		this->servo.write(value);
	}
};

#endif