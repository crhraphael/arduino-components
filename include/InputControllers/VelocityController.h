#ifndef VELOCITYCONTROLLER
#define VELOCITYCONTROLLER

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <InputControllers/IControllableComponent.h>
#include <InputControllers/IControllerComponent.h>
#include <Arduino.h>

/**
 * Tradutor de dados 
 **/
class VelocityController {
	private:
	IServoInputTranslator *controllableComponent;
	IControllerComponent *controllerComponent;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 10;
	const int RIGHT;
	const int LEFT;
	float currentVelocity = 0;
	int reverse = 0;
	
	public:
	VelocityController(
		IServoInputTranslator *controllableComponent,
		IControllerComponent *controllerComponent
	):
	RIGHT(-1),
	LEFT(1)
	{
		this->controllableComponent = controllableComponent;
		this->controllerComponent = controllerComponent;
		this->neutralPointValue = this->controllerComponent->MAX_VALUE / 2;
	}

	/**
	 * Retorna a velocidade do motor. 
	 */
	float translateVelocity(int potValue) {
		float capValue = 1;
		int potDiff = abs(this->neutralPointValue - potValue);

		if(potValue > 0) {
			capValue = (potDiff / (float)this->neutralPointValue);
		}
		return capValue;
	}

	/**
	 * Retorna a direcao do motor. 
	 */
	int getDirection(int potValue) {
		int neutralPotVal = this->neutralPointValue;
		int neutralPotSensitivity = this->neutralPointSensitivity;
		
		int rightVal = neutralPotVal + neutralPotSensitivity;
		int leftVal = neutralPotVal - neutralPotSensitivity;
		
		int dir = (potValue > rightVal)
			? this->RIGHT
			: (potValue < leftVal) 
				? this->LEFT
				: 0;

		return dir;
	}
	
	void update() {
		int potValue = this->controllerComponent->read();
		this->reverse = this->getDirection(potValue);
		this->currentVelocity = this->translateVelocity(potValue);

		this->controllableComponent->setVelocity(this->currentVelocity, this->reverse);
	}

	float getCurrentVelocity() {
		return this->currentVelocity;
	}
};

#endif