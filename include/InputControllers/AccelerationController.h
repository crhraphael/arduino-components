#ifndef ACCELERATIONCONTROLLER
#define ACCELERATIONCONTROLLER

#include <Helpers/IInputParser.h>
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
	IInputParser *inputParser;

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
		IControllerComponent *controllerComponent,
		IInputParser *inputParser
	):
	RIGHT(-1),
	LEFT(1)
	{
		this->controllableComponent = controllableComponent;
		this->controllerComponent = controllerComponent;
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

	void update() {
		char buff[10] = "\0";

		this->controllerComponent->read(buff);
		this->inputParser->parse(buff, this->inputValue, 'a');

		this->controllableComponent->set(this->inputValue);

		// this->configureDirection();
		// this->translateAcceleration();
		// Serial.print("reverse");
		// Serial.println(this->reverse);
		// Serial.print("currentAcceleration");
		// Serial.println(this->currentAcceleration);
		// Serial.print("*");
		// Serial.println(this->reverse * this->currentAcceleration);
		// int i = 0;
		// for(i = 0; i < 2000; i+=100) {
		// 	this->controllableComponent->setRaw(i);
		// 	delay(1000);
		// }
	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}
};

#endif