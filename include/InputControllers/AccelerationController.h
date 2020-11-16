#ifndef ACCELERATIONCONTROLLER
#define ACCELERATIONCONTROLLER

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <InputControllers/IControllableComponent.h>
#include <InputControllers/IControllerComponent.h>
#include <Arduino.h>

/**
 * Controlador de aceleração. 
 **/
class AccelerationController {
	private:
	IControllableComponent *controllableComponent;
	IControllerComponent *controllerComponent;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 5;
	const int RIGHT;
	const int LEFT;
	float currentAcceleration = 0;
	int reverse = -1;
	int inputValue = 500;

	
	public:
	AccelerationController(
		IControllableComponent *controllableComponent,
		IControllerComponent *controllerComponent
	):
	RIGHT(-1),
	LEFT(1)
	{
		this->controllableComponent = controllableComponent;
		this->controllerComponent = controllerComponent;
		this->neutralPointValue = this->controllableComponent->SERVO_STOPPED_VALUE;
	}

	/**
	 * Retorna a velocidade do motor. 
	 */
	float translateAcceleration(int potValue) {
		float capValue = 1;
		int potDiff = abs(this->neutralPointValue - potValue);

		if(potValue > 0) {
			capValue = this->neutralPointValue != 0 
				? (potDiff / (float)this->neutralPointValue)
				: 0;
		}
		return capValue;
	}

	/**
	 * Retorna a direcao do motor. 
	 */
	int getDirection(int potValue) {
		int neutralPotVal = this->neutralPointValue;
		
		int rightVal = neutralPotVal + this->neutralPointSensitivity;
		int leftVal = neutralPotVal - this->neutralPointSensitivity;
		
		int dir = (potValue > rightVal)
			? this->RIGHT
			: (potValue < leftVal) 
				? this->LEFT
				: 0;

		return dir;
	}

	void update() {
		char buff[] = "\0";
		char debug[] = "\0";

		this->controllerComponent->read(buff);
		if(strcmp(buff, debug) != 0) {
			this->inputValue = atoi(buff);
		}

		this->reverse = this->getDirection(this->inputValue);
		this->currentAcceleration = this->translateAcceleration(this->inputValue);
		this->controllableComponent->set(this->reverse * this->currentAcceleration);
	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}
};

#endif