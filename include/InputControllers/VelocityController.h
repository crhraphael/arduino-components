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
	IControllableComponent *controllableComponent;
	IControllerComponent *controllerComponent;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 10;
	const int RIGHT;
	const int LEFT;
	float currentVelocity = 0;
	int reverse = -1;
	
	public:
	VelocityController(
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
		
		int rightVal = neutralPotVal + this->neutralPointSensitivity;
		int leftVal = neutralPotVal - this->neutralPointSensitivity;
		
		int dir = (potValue > rightVal)
			? this->RIGHT
			: (potValue < leftVal) 
				? this->LEFT
				: 0;

		return dir;
	}

	int inputValue = 500;
	
	void update() {
		char buff[] = {'\0'};
		char debug[] = {'\0'};

		// int *bf = 0;
		// this->controllerComponent->readInt(bf);
		
		// if(*bf != 0) {
		//  	Serial.print("Intereger: ");
		//  	Serial.println(*bf);
		// }

		this->controllerComponent->read(buff);
		if(strcmp(buff, debug) != 0) {
			this->inputValue = atoi(buff);
		 	Serial.print("Char: ");
			Serial.println(atoi(buff));
		}

		int potValue = this->inputValue;
		this->reverse = this->getDirection(potValue);
		this->currentVelocity = this->translateVelocity(potValue);
		Serial.println(this->currentVelocity);
		this->controllableComponent->set(this->reverse * this->currentVelocity);
	}

	float getCurrentVelocity() {
		return this->currentVelocity;
	}
};

#endif