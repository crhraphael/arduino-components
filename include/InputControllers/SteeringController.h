#ifndef STEERINGCONTROLLER
#define STEERINGCONTROLLER

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <InputControllers/IControllableComponent.h>
#include <InputControllers/IControllerComponent.h>
#include <Arduino.h>

/**
 * Controlador de direção.
 **/
class SteeringController {
	private:
	IControllableComponent *controllableComponent;
	IControllerComponent *controllerComponent;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 10;
	const int RIGHT;
	const int LEFT;
	float currentAcceleration = 0;
	int direction = -1;
	int inputValue = 500;
	
	public:
	SteeringController(
		IControllableComponent *controllableComponent,
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
	float translateAcceleration(int potValue) {
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
		char buff[] = {'\0'};
		char debug[] = {'\0'};

		this->controllerComponent->read(buff);

		if(strcmp(buff, debug) != 0) {
			this->inputValue = atoi(buff);
		}

		this->direction = this->getDirection(this->inputValue);
		this->currentAcceleration = this->translateAcceleration(this->inputValue);
		
		int mapVal = map(
			this->inputValue, 
			0, this->controllerComponent->MAX_VALUE, 
			40, 180);
		
			Serial.print("Map: ");		
			Serial.println(mapVal);

			this->controllableComponent->set(mapVal);

	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}
};

#endif