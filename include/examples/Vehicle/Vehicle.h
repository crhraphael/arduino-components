#ifndef VEHICLE
#define VEHICLE

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/Bluetooth/BTSoftwareSerialImplementation.h>

#include <Devices/Servo/MG90S-DriverOnly/MG90SCustomDevice.h>
#include <Devices/Wireless/Bluetooth/HC06Device.h>
#include <Devices/LEDs/CommonLED.h>

#include <InputControllers/InputController.h>
#include <InputControllers/AccelerationController.h>
#include <InputControllers/SteeringController.h>

#include <Arduino.h>

class Vehicle {
	IControllableComponent* steeringMotor;
	IControllableComponent* accelerationMotor;

	CommonLED* commonLED;

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
	Vehicle(IControllableComponent* accelerationMotor) {
		this->accelerationMotor = accelerationMotor;
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