#ifndef ACCELERATIONCONTROLLER
#define ACCELERATIONCONTROLLER

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
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
	IControllerComponent *controllerComponent;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 5;
	const int RIGHT;
	const int LEFT;
	float currentAcceleration = 0;
	int reverse = -1;
	float inputValue = 0.0f;

	
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
		this->neutralPointValue = this->controllableComponent->getServoNeutralValue();
	}

	/**
	 * Retorna a velocidade do motor. 
	 */
	void translateAcceleration() {
		int potDiff = abs(this->neutralPointValue - this->inputValue);

		float capValue = this->neutralPointValue != 0 
			? ((float)potDiff / (float)this->controllableComponent->getMaxAcceleration())
			: 0;
		// Serial.print("neutralPointValue");
		// Serial.println(this->neutralPointValue);		
		// Serial.print("inputValue");
		// Serial.println(this->inputValue);
		// Serial.print("potDiff");
		// Serial.println(potDiff);
		// Serial.print("capValue");
		// Serial.println(capValue);
		// Serial.print("getMaxAcceleration");
		// Serial.println(this->controllableComponent->getMaxAcceleration());
		
		this->currentAcceleration = capValue;
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

	void update() {
		char buff[10] = "\0";
		char debug[10] = "\0";

		this->controllerComponent->read(buff);
		if(strcmp(buff, debug) != 0) {
			const char flag = char(buff[0]);


			if(flag == 'a') {
				const int lenght = strlen(buff);
				char target[10] = "\0";
				getSubString(buff, target, 2, lenght);
				const float value = atoi(target);

				this->inputValue = value;

			}

		}

		// this->configureDirection();
		// this->translateAcceleration();
		// Serial.print("reverse");
		// Serial.println(this->reverse);
		// Serial.print("currentAcceleration");
		// Serial.println(this->currentAcceleration);
		// Serial.print("*");
		// Serial.println(this->reverse * this->currentAcceleration);
		int i = 1000;
		for(i = 1000; i< 2000; i++) {
			this->controllableComponent->set(i);
		}
	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}
};

#endif