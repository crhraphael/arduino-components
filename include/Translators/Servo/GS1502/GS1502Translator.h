#ifndef GS1502TRANSLATOR
#define GS1502TRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Servo/IServoImplementation.h>
#include <InputControllers/IControllableComponent.h>

/**
 * Linear Servo Motor used mainly on airplane models.
 */
class GS1502Translator: public IArduinoComponent, public IControllableComponent {
	private:
	IServoImplementation* servoImpl;
	
	/**
	 * Valor máximo da velocidade do motor.
	 */
	const int MAX_ACCELERATION; 

	/**
	 * Valor que mantem o servo parado.
	 */
	const int SERVO_STOPPED_VALUE;
	public:
	GS1502Translator(
		IServoImplementation* servoImpl, 
		const int maxIncrement, 
		const int neutralValue
	): 
		MAX_ACCELERATION(maxIncrement), 
		SERVO_STOPPED_VALUE(neutralValue)
	{
		this->servoImpl = servoImpl;
	};



	int getMaxAcceleration() {
		return this->MAX_ACCELERATION;
	}

	int getServoNeutralValue() {
		return this->SERVO_STOPPED_VALUE;
	}

  int translate(float accelCap) {
		return this->SERVO_STOPPED_VALUE + ((int)(GS1502Translator::MAX_ACCELERATION * accelCap));
	}
	void setRaw(float vel) {
		int value = (int)(vel);
		this->servoImpl->send(value);
	}
  void set(float val) {
		int value = this->translate(val);
		this->servoImpl->send(value);
	}
};

#endif