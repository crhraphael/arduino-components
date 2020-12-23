#ifndef STEERINGCONTROLLER
#define STEERINGCONTROLLER

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
	IControllerComponent *controllerComponent;
  int neutralPointValue = 0;
	int neutralPointSensitivity = 1;
	const int RIGHT;
	const int LEFT;
	float currentPosition = 0;
	int direction = -1;
	int inputValue = 0;
	
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
		this->neutralPointValue = this->controllableComponent->getServoNeutralValue();
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
		char buff[10] = "\0";
		char debug[10] = "\0";

		this->controllerComponent->read(buff);

		if(strcmp(buff, debug) != 0) {
			const char directionFlag = 'd';
			if(strcmp(&buff[0], &directionFlag) == 0) {
				const int lenght = strlen(buff);
				char *target = "\0";
				getSubString(buff, target, 2, lenght);
				const int value = atoi(target);

				this->inputValue = value;
			}
		}

		//this->direction = this->getDirection(this->inputValue);
		this->currentPosition = this->inputValue;
		this->controllableComponent->set(this->inputValue);

	}
};

#endif