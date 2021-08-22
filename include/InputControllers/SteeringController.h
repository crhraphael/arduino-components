#ifndef STEERINGCONTROLLER
#define STEERINGCONTROLLER

#include <Helpers/IInputParser.h>
#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <InputControllers/IControllableComponent.h>
#include <InputControllers/IControllerComponent.h>

#include <Helpers/BasicPayloadProtocol.h>

#include <Arduino.h>

/**
 * Controlador de direção.
 **/
class SteeringController {
	private:
	IControllableComponent *controllableComponent;
	IInputParser *inputParser;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 1;
	const int RIGHT;
	const int LEFT;
	float currentPosition = 0;
	float oldPosition = 0;
	int direction = -1;
	float inputValue = 0.0f;
	
	public:
	SteeringController(
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

	void update(IControllerComponent* controller) {
		char buff[10] = "\000000000";

		controller->read(buff);
		this->inputParser->parse(buff, this->inputValue, 's');

		this->currentPosition = this->inputValue;

		this->controllableComponent->set(this->inputValue);

	}
};

#endif