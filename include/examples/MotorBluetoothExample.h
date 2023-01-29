#ifndef MOTORBLUETOOTHEXAMPLE
#define MOTORBLUETOOTHEXAMPLE

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/Bluetooth/BTSoftwareSerialImplementation.h>

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Wireless/Bluetooth/HC06Translator.h>
#include <Translators/LEDs/CommonLED.h>

#include <InputControllers/InputController.h>
#include <InputControllers/AccelerationController.h>
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

const char END_MSG_BT = '.';


/**
 * Experiment using an Arduino UNO as prototype board
 * 
 * It controls the velocity and direction of a DC Motor 
 * by interacting with it's driver directly.
 **/
class MotorBluetoothExample {
	IControllableComponent *servoComponent;

	// IControllableComponent *frontLeftHeadlight;
	// IControllableComponent *frontRightHeadlight;
	// IControllableComponent *backLeftHeadlight;
	// IControllableComponent *backRightHeadlight;

	// IControllableComponent *leftBrakeLight;
	// IControllableComponent *rightBrakeLight;
	
	// IControllableComponent *leftReverseLight;
	// IControllableComponent *rightReverseLight;

	// IControllableComponent *frontLeftTurnLight;
	// IControllableComponent *frontRightTurnLight;
	// IControllableComponent *backLeftTurnLight;
	// IControllableComponent *backRightTurnLight;

	IControllerComponent *potentiometerComponent;
	IControllerComponent *bluetoothComponent;

	IServoImplementation *servoImpl;
	IBluetoothImplementation *btImpl;

	InputController *inputController;
	SteeringController *steController;
	AccelerationController *accelController;

	RearLightsController *rearLightsController;
	BrakeLightsController *brakeLightController;
	HeadLightsController *headLightController;
	TurnLightsController *turnLightController;
	
	void defineServoDevice() {
		this->servoImpl = new ServoImplementation(SERVO_PIN);
		this->servoComponent = new MG90SCustomDevice(this->servoImpl);
	}

	void defineBluetoothDevice() {
		this->btImpl = new BTSoftwareSerialImplementation(
			TRANSMITTER_PIN, 
			RECEIVER_PIN, 
			DEFAULT_BAULD_RATE,
			END_MSG_BT);    
		this->bluetoothComponent = new HC06Translator(this->btImpl, 1000);
	}

	void defineLEDDevices() {
		// this->frontLeftHeadlight = new CommonLED(1);
		// this->frontRightHeadlight = new CommonLED(1);
		// this->backLeftHeadlight = new CommonLED(1);
		// this->backRightHeadlight = new CommonLED(1);

		// this->leftBrakeLight = new CommonLED(1);
		// this->rightBrakeLight = new CommonLED(1);
		
		// this->frontLeftTurnLight = new CommonLED(1);
		// this->frontRightTurnLight = new CommonLED(1);
		// this->backLeftTurnLight = new CommonLED(1);
		// this->backRightTurnLight = new CommonLED(1);	
	}

	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		this->defineServoDevice();
		this->defineBluetoothDevice();
		// this->defineLEDDevices();
		
		this->accelController = new AccelerationController(
			this->servoComponent, 
			this->bluetoothComponent);
		this->steController = new SteeringController();

		// this->headLightController = new HeadLightsController();
		// this->turnLightController = new TurnLightsController();
		// this->brakeLightController = new BrakeLightsController();
		// this->brakeLightController = new BrakeLightsController();
		// this->rearLightsController = new RearLightsController();

		// this->inputController = new InputController(
		// 	this->steController, 
		// 	this->accelController,
		// 	this->headLightController,
		// 	this->turnLightController,
		// 	this->brakeLightController,
		// 	this->rearLightsController);
	} 
	 
	void loop()
	{ 
		this->accelController->update();
		///Serial.println((int)this->accelController->getCurrentAcceleration());
	} 
};

#endif