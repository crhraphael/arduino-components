#ifndef ESP32LOLINMOTOREXAMPLE
#define ESP32LOLINMOTOREXAMPLE
#include <Implementations/Servo/ServoImplementation.h>

#include <Implementations/Wireless/WiFi/ESP8266WiFiImplementation.h>

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>
#include <Translators/LEDs/CommonLED.h>
#include <Translators/Wireless/WIFI/ESP12ETranslator.h>

#include <InputControllers/InputController.h>
#include <InputControllers/AccelerationController.h>
#include <InputControllers/SteeringController.h>

#include <Config/WIFICredentials.h>

#include <Arduino.h>


// Label	GPIO	  Input						Output	Notes
// D0   	GPIO16   no						interrupt		no PWM or I2C support	HIGH at boot used to wake up from deep sleep
// D1   	GPIO5    OK								OK			often used as SCL (I2C)
// D2   	GPIO4    OK								OK			often used as SDA (I2C)
// D3   	GPIO0   pulled up					OK			connected to FLASH button, boot fails if pulled LOW
// D4   	GPIO2   pulled up					OK			HIGH at boot connected to on-board LED, boot fails if pulled LOW
// D5   	GPIO14   OK								OK			SPI (SCLK)
// D6   	GPIO12   OK								OK			SPI (MISO)
// D7   	GPIO13   OK								OK			SPI (MOSI)
// D8   	GPIO15  pulled to GND			OK			SPI (CS) Boot fails if pulled HIGH
// RX   	GPIO3    OK							RX pin		HIGH at boot
// TX   	GPIO1    TX pin						OK			HIGH at boot debug output at boot, boot fails if pulled LOW
// A0   	ADC0    Analog Input			X	

/**
 * Portas dos devices.
 */
const int SERVO_DIRECTION_PIN = D1; 
const int SERVO_ACCELERATION_PIN = D7; 
const int POT_PIN = A0;

const int DEFAULT_BAULD_RATE = 9600;

const char END_MSG_BT = '.';


/**
 * Experiment using an ESP32 Lolin v3 as prototype board
 * 
 * Controls the velocity and direction of a DC Motor 
 * by interacting with it's driver without 
 * modifying the potentiometer axle.
 **/
class ESP32LolinMotorExample {
	IControllableComponent *servoDirComp;
	IControllableComponent *servoVelComp;
	
	IControllerComponent *potentiometerComponent;

	IServoImplementation *servoDirImpl;
	IServoImplementation *servoVelImpl;

	SteeringController *steController;
	AccelerationController *accelController;
	
	void defineServoDevices() {
		// this->servoDirImpl = new ServoImplementation(SERVO_DIRECTION_PIN);
		// this->servoDirComp = new MG90SCustomTranslator(this->servoDirImpl);

		// this->servoVelImpl = new ServoImplementation(SERVO_ACCELERATION_PIN);
		// this->servoVelComp = new MG90SCustomTranslator(this->servoVelImpl);
	}

	void definePotentiometerDevice() {
		this->potentiometerComponent = new A50KPotentiometerTranslator(POT_PIN, 5.0f, 1024);
	}

	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		this->defineServoDevices();
		this->definePotentiometerDevice();

		this->accelController = new AccelerationController(
			this->servoVelComp, 
			this->potentiometerComponent);
		// this->steController = new SteeringController(			
		// 	this->servoDirComp, 
		// 	this->potentiometerComponent);
	} 

	void loop()
	{ 
		//this->steController->update();
		this->accelController->update();

		//Serial.println((int)this->accelController->getCurrentAcceleration());
	} 
};

#endif