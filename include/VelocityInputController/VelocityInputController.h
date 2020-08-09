#ifndef VELOCITYINPUTCONTROLLER
#define VELOCITYINPUTCONTROLLER

#include <Translators/Servo/IServoInputTranslator.h>
#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <Arduino.h>

class VelocityInputController {
	private:
	IServoInputTranslator *servoInputTranslator;
	IPotentiometerInputTranslator *potentiometerTranslator;

	public:
	VelocityInputController(
		IServoInputTranslator *servoInputTranslator,
		IPotentiometerInputTranslator *potentiometerTranslator
	)	{
		this->servoInputTranslator = servoInputTranslator;
		this->potentiometerTranslator = potentiometerTranslator;
	}

	const int NEUTRAL_POT_VALUE = (int)(this->potentiometerTranslator->MAX_POT_VALUE() / 2);

	const int RIGHT = -1;
	const int LEFT = 1;

	float currentVelocity = 0;
	int currentDirection = 0;


	/**
	 * Retorna a velocidade do motor. 
	 */
	float getVelocity(int potValue) {
		float capValue = 1;
		int potDiff = abs(this->NEUTRAL_POT_VALUE - potValue);

		if(potValue > 0) {
			capValue = (potDiff / (float)this->NEUTRAL_POT_VALUE);
		}
		return capValue;
	}

	/**
	 * Retorna a direcao do motor. 
	 */
	int getDirection(int potValue) {
		int neutralPotVal = this->NEUTRAL_POT_VALUE;
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
		int potDiff = abs(this->NEUTRAL_POT_VALUE - potValue);

		if(potValue > 0) {
			capValue = (potDiff / (float)this->NEUTRAL_POT_VALUE);
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