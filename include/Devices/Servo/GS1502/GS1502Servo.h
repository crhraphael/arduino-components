#ifndef GS1502TRANSLATOR
#define GS1502TRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Servo/IServoImplementation.h>
#include <InputControllers/IControllableComponent.h>

/**
 * Linear Servo Motor used mainly on airplane models.
 */
class GS1502Servo: public IArduinoComponent, public IControllableComponent {
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

	int valueToSend;
	int lastValueSent;
	public:
	GS1502Servo(
		IServoImplementation* servoImpl, 
		const int maxIncrement, 
		const int neutralValue
	): 
		MAX_ACCELERATION(maxIncrement), 
		SERVO_STOPPED_VALUE(neutralValue)
	{
		this->servoImpl = servoImpl;		
		this->set(0);
		valueToSend = SERVO_STOPPED_VALUE;
		lastValueSent = valueToSend;
	};



	int getMaxAcceleration() {
		return this->MAX_ACCELERATION;
	}

	int getServoNeutralValue() {
		return this->SERVO_STOPPED_VALUE;
	}

  int translate(float accelCap) {
		return (int)(this->SERVO_STOPPED_VALUE + ((float)GS1502Servo::MAX_ACCELERATION * accelCap));
	}

	int get() {
		return valueToSend;
	}

	void set(float vel) {
		this->valueToSend = this->translate(vel);


		this->servoImpl->send(this->valueToSend);
		lastValueSent = this->valueToSend;
	}

	void setRaw(int vel) {
		this->valueToSend = (vel);


		this->servoImpl->send(this->valueToSend);
		lastValueSent = this->valueToSend;
	}
};

#endif