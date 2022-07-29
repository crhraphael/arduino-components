#ifndef VEHICLE
#define VEHICLE

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/Bluetooth/BTSoftwareSerialImplementation.h>

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Wireless/Bluetooth/HC06Translator.h>
#include <Translators/LEDs/CommonLED.h>

#include <InputControllers/InputController.h>
#include <InputControllers/AccelerationController.h>
#include <InputControllers/SteeringController.h>

#include <Arduino.h>


class Vehicle {
	IControllableComponent* steeringMotor;
	IControllableComponent* accelerationMotor;

	CommonLED* commonLED;


	char title[25] = "Custom Ford Maverick";
	char year[5] = "2019";



	int frontLeftHeadlightLED;
	int frontRightHeadlightLED;

	int backLeftBrakeLED;
	int backRightBrakeLED;
	
	int frontLeftTurnSignalLED;
	int frontRightTurnSignalLED;
	int backLeftTurnSignalLED;
	int backRightTurnSignalLED;

	bool isEngineOn = false;

	public:
	Vehicle(
		IControllableComponent* accelerationMotor,
		IControllableComponent* steeringMotor
	) {
		this->accelerationMotor = accelerationMotor;
		this->steeringMotor = steeringMotor;
		
		this->commonLED = new CommonLED(1);
		this->commonLED->set(HIGH);
	}

	void setHeadlights(int state, int intensity) {
		analogWrite(this->frontLeftHeadlightLED, (state * intensity) * 255);
		analogWrite(this->frontRightHeadlightLED, (state * intensity) * 255);
	}

	void setBrakeLights(int state) {
		digitalWrite(this->backLeftBrakeLED, state);
		digitalWrite(this->backRightBrakeLED, state);
	}

	void setTurnLights(int direction) {
		int rightSwitch = (int)(direction > 0);
		int leftSwitch = (int)(direction < 0);

		digitalWrite(this->frontLeftTurnSignalLED, leftSwitch);
		digitalWrite(this->frontRightTurnSignalLED, leftSwitch);
		digitalWrite(this->backLeftTurnSignalLED, rightSwitch);
		digitalWrite(this->backRightTurnSignalLED, rightSwitch);
	}

	void update() {
		int isEngineOn = (int)this->isEngineOn;
	}
};

#endif