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
	float currentPosition = 0;
	int direction = -1;
	int inputValue = 0;
	
	public:
	SteeringController(
		IControllableComponent *controllableComponent,
		IControllerComponent *controllerComponent,
		const int maxInputValue = 0
	):
	RIGHT(-1),
	LEFT(1)
	{
		this->controllableComponent = controllableComponent;
		this->controllerComponent = controllerComponent;
		this->neutralPointValue = (maxInputValue != 0)
			? maxInputValue / 2
			: this->controllerComponent->MAX_VALUE / 2;
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
	
	int teste = 0;

	void update() {
		char buff[3] = "\0";
		char debug[3] = "\0";

		this->controllerComponent->read(buff);

		if(strcmp(buff, debug) != 0) {
			this->inputValue = atoi(buff);
			Serial.println(buff);
		}

		//this->direction = this->getDirection(this->inputValue);
		this->currentPosition = this->inputValue;//this->translateAcceleration(this->inputValue);
		
		// int mapVal = map(
		// 	this->inputValue, 
		// 	0, this->controllerComponent->MAX_VALUE, 
		// 	40, 180);
		
			//Serial.print("Map: ");		
			//Serial.println(mapVal);

			// this->controllableComponent->set(this->inputValue);
			// if(this->teste > 2) this->teste = 0;
			// else this->teste++;
	}

	float getCurrentAcceleration() {
		return this->currentPosition;
	}
};

#endif