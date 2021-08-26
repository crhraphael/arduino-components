#ifndef ACCELERATIONCONTROLLER
#define ACCELERATIONCONTROLLER

#define ACCELERATION_FLAG 'a'

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
		char buff[10] = "\000000000";
		controller->read(buff);
		this->inputParser->parse(buff, this->inputValue, ACCELERATION_FLAG);

		this->controllableComponent->set(this->inputValue);
	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}
};

#endif