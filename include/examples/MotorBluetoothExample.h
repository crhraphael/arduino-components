#ifndef MOTORBLUETOOTHEXAMPLE
#define MOTORBLUETOOTHEXAMPLE

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/Bluetooth/BTSoftwareSerialImplementation.h>

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Wireless/Bluetooth/HC06Translator.h>

#include <InputControllers/InputController.h>
#include <InputControllers/VelocityController.h>
#include <InputControllers/SteeringController.h>

#include <Arduino.h>


/**
 * Portas dos devices.
 */
const int SERVO_PIN = 9;
const int POT_PIN = 0;

const int TRANSMITTER_PIN = 2;
const int RECEIVER_PIN = 3;

const int DEFAULT_BAULD_RATE = 9600;


class MotorBluetoothExample {
	IControllableComponent *servoComponent;
	IControllerComponent *potentiometerComponent;
	IControllerComponent *bluetoothComponent;

	IServoImplementation *servoImpl;
	IBluetoothImplementation *btImpl;

	InputController *inputController;
	SteeringController *steController;
	VelocityController *velController;
	
	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		this->servoImpl = new ServoImplementation(SERVO_PIN);
		this->servoComponent = new MG90SCustomTranslator(this->servoImpl);

		this->btImpl = new BTSoftwareSerialImplementation(
			TRANSMITTER_PIN, 
			RECEIVER_PIN, 
			DEFAULT_BAULD_RATE,
			'.');    
		this->bluetoothComponent = new HC06Translator(this->btImpl, 1000);

		this->velController = new VelocityController(
			this->servoComponent, 
			this->bluetoothComponent);
		this->steController = new SteeringController();
		this->inputController = new InputController(
			this->steController, 
			this->velController);
	} 
	 
	void loop()
	{ 
		this->inputController->update();
	} 
};

#endif