#ifndef VELOCITYINPUTCONTROLLER
#define VELOCITYINPUTCONTROLLER

#include <Translators/Servo/IServoInputTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <Arduino.h>

/**
 * Controlador de velocidade e direcao de um motor dc com driver.
 */
class VelocityInputController {
	private:
	IServoInputTranslator *servoInputTranslator;
	IPotentiometerInputTranslator *potentiometerTranslator;
  int neutralPotValue = 0;
	public:
	VelocityInputController(
		IServoInputTranslator *servoInputTranslator,
		IPotentiometerInputTranslator *potentiometerTranslator
	):
	RIGHT(-1),
	LEFT(1)
	{
		this->servoInputTranslator = servoInputTranslator;
		this->potentiometerTranslator = potentiometerTranslator;
		this->neutralPotValue = this->potentiometerTranslator->MAX_POT_VALUE() / 2;
	}


	const int RIGHT;
	const int LEFT;

	float currentVelocity = 0;
	int currentDirection = 0;


	/**
	 * Retorna a velocidade do motor. 
	 */
	float getVelocity(int potValue) {
		float capValue = 1;
		int potDiff = abs(this->neutralPotValue - potValue);

		if(potValue > 0) {
			capValue = (potDiff / (float)this->neutralPotValue);
		}
		return capValue;
	}

	/**
	 * Retorna a direcao do motor. 
	 */
	int getDirection(int potValue) {
		int neutralPotVal = this->neutralPotValue;
		int neutralPotSensitivity = this->potentiometerTranslator->NEUTRAL_POT_SENSITIVITY();
		
		int rightVal = neutralPotVal + neutralPotSensitivity;
		int leftVal = neutralPotVal - neutralPotSensitivity;
		
		int dir = (potValue > rightVal)
			? this->RIGHT
			: (potValue < leftVal) 
				? this->LEFT
				: 0;

		return dir;
	}

	
	float getInput() {
		float capValue = 1;
		int potValue = this->potentiometerTranslator->read();
		int potDiff = abs(this->neutralPotValue - potValue);

		if(potValue > 0) {
			capValue = (potDiff / (float)this->neutralPotValue);
		}
		return capValue;
	}
	
	void update() {
		int potValue = this->potentiometerTranslator->read();
		this->currentDirection = this->getDirection(potValue);
		this->currentVelocity = this->getVelocity(potValue);

		this->servoInputTranslator->setVelocity(this->currentVelocity, this->currentDirection);
	}
};

#endif