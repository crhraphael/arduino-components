#ifndef MG90SCUSTOMTRANSLATOR
#define MG90SCUSTOMTRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Servo/IServoImplementation.h>
#include <InputControllers/IControllableComponent.h>

/**
 * Maps a Device with a modified `Tower Pro` MG90S Servo.
 * 
 * This code applies to modified servos where motor rotation
 * is infinite and it controls only the speed and rotation direction
 * (forward or backwards).
 * 
 * See: https://www.towerpro.com.tw/product/mg90s-3/
 */
class MG90SCustomDevice: public IArduinoComponent, public IControllableComponent {
	private:
	IServoImplementation* servoImpl;
	
	/**
	 * Constant value that represents  the max value to it's TOP ROTATION SPEED.
	 */
	const int MAX_ACCELERATION; 

	/**
	 * Constant value that represents a stopped (non rotating) servo.
	 */
	const int SERVO_STOPPED_VALUE;

	int valueToSend;
	int lastValueSent;

	public:
	MG90SCustomDevice(
		IServoImplementation* servoImpl, 
		int maxIncrement, 
		int neutralValue
	): 
		MAX_ACCELERATION(maxIncrement), 
		SERVO_STOPPED_VALUE(neutralValue)
	{
		this->servoImpl = servoImpl;
		this->set(0);
		this->valueToSend = SERVO_STOPPED_VALUE;
		this->lastValueSent = this->valueToSend;
	};


	int getMaxAcceleration() {
		return this->MAX_ACCELERATION;
	}

	int getServoNeutralValue() {
		return this->SERVO_STOPPED_VALUE;
	}

  int translate(float accelCap) {
		return (int)(this->SERVO_STOPPED_VALUE + ((float)MG90SCustomDevice::MAX_ACCELERATION * accelCap));
	}

	int get() {
		return this->valueToSend;
	}
  void set(float vel) {
		this->valueToSend = this->translate(vel);

		this->lastValueSent = this->valueToSend;
		this->servoImpl->send(this->valueToSend);
	}

	void setRaw(int vel) {
		this->valueToSend = (vel);

		this->servoImpl->send(this->valueToSend);
		lastValueSent = this->valueToSend;
	}

};

#endif