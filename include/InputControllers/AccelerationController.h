#ifndef ACCELERATIONCONTROLLER
#define ACCELERATIONCONTROLLER

#define ACCELERATION_FLAG 'a'

#include <Helpers/IInputParser.h>
#include <InputControllers/IControllableComponent.h>
#include <InputControllers/IControllerComponent.h>

#include <Helpers/BasicPayloadProtocol.h>

#include <Arduino.h>

/**
 * Controlador de aceleração. 
 **/
class AccelerationController {
	private:
	IControllableComponent *controllableComponent;
	IInputParser *inputParser;

  int neutralPointValue = 0;
	int neutralPointSensitivity = 5;
	const int RIGHT;
	const int LEFT;
	float currentAcceleration = 0;
	int reverse = -1;
	float inputValue = 0.0f;

	// Constant car motor power.
	float motorPower = .4f;
	float gearMod = 0.0f;
	float currentVelocity = .0f;



	public:
	AccelerationController(
		IControllableComponent *controllableComponent,
		IInputParser *inputParser
	):
	RIGHT(-1),
	LEFT(1)
	{
		this->controllableComponent = controllableComponent;
		this->neutralPointValue = this->controllableComponent->getServoNeutralValue();
		this->inputParser = inputParser;
		this->inputValue = 0;
	}

	/**
	 * Retorna a direcao do motor. 
	 */
	void configureDirection() {
		int neutralPotVal = this->neutralPointValue;
		
		int rightVal = neutralPotVal + this->neutralPointSensitivity;
		int leftVal = neutralPotVal - this->neutralPointSensitivity;
		
		int dir = (this->inputValue > rightVal)
			? this->RIGHT
			: (this->inputValue < leftVal) 
				? this->LEFT
				: 0;

		this->reverse = dir;
	}

	void update(IControllerComponent* controller) {
		float currentInput = .0f;
		this->inputParser->parse(currentInput, controller, ACCELERATION_FLAG);
		this->controllableComponent->set(currentInput);

		// float maxVel = currentInput != 0 ? currentInput : 1;

	
		// if(this->currentVelocity <= 0) {
		// 	gearMod = .00008f;
		// } else if(this->currentVelocity > 0 && this->currentVelocity < 0.15f) {
		// 	gearMod = .000045f;
		// } else if(this->currentVelocity >= 0.15f && this->currentVelocity < 0.3f) {
		// 	gearMod = .00005f;
		// } else if(this->currentVelocity >= 0.3f && this->currentVelocity < 0.5f) {
		// 	gearMod = .00001f;
		// } else if(this->currentVelocity >= 0.5f && this->currentVelocity < 0.75f) {
		// 	gearMod = .000005f;
		// } else if(this->currentVelocity >= 0.75f && this->currentVelocity <= 1.0f) {
		// 	gearMod = .000001f;
		// }

		// unsigned int currentMillis = millis();
		// unsigned int lastMillis = currentMillis; // State Stored
		// unsigned int lastFrameMillis = currentMillis - lastMillis;

		// if(currentInput == 0) {
		// 	if(this->currentVelocity > 0) this->currentVelocity -= 0.0002f;
		// 	if(this->currentVelocity < 0) this->currentVelocity += 0.0002f;
		// } else {
		// 	float acceleration = currentInput * (motorPower * gearMod);
		// 	this->currentVelocity += acceleration;
		// }



		// Keeps the maximum velocity between -1 and 1.
		// if(this->currentVelocity >= 1) this->currentVelocity = 1;
		// if(this->currentVelocity <= -1) this->currentVelocity = -1;
		
		// if(this->currentVelocity > maxVel) this->currentVelocity = maxVel;

		// this->controllableComponent->set(currentInput);
	}

	/**
	 * Forces a specific value to the controllable component.
	 * It also updates the loop input with the same value.
	 **/
	void setSpeed(float speed) {
		this->inputValue = speed;
		this->controllableComponent->set(speed);
	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}
};

#endif

// class Gearbox {
// 	Gear gears[];
// 	int currentGear = 0;
// };

// class Gear {
// 	float modifier;
// };