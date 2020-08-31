#ifndef ESP32LOLINMOTOREXAMPLE
#define ESP32LOLINMOTOREXAMPLE

#include <Implementations/Servo/ESP32ServoImplementation.h>

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>
#include <Translators/LEDs/CommonLED.h>

#include <InputControllers/InputController.h>
#include <InputControllers/VelocityController.h>
#include <InputControllers/SteeringController.h>

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

#define D1 5;
#define D7 13;
/**
 * Portas dos devices.
 */
const int SERVO_PIN = D1; 
const int POT_PIN = D7;

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
	IControllableComponent *servoComponent;

	IControllerComponent *potentiometerComponent;

	IServoImplementation *servoImpl;

	InputController *inputController;
	SteeringController *steController;
	VelocityController *velController;
	
	void defineServoDevice() {
		this->servoImpl = new ESP32ServoImplementation(SERVO_PIN);
		this->servoComponent = new MG90SCustomTranslator(this->servoImpl);
	}

	void definePotentiometerDevice() {
		this->potentiometerComponent = new A50KPotentiometerTranslator(POT_PIN, 3.3f, 720);
	}

	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		this->defineServoDevice();
		this->definePotentiometerDevice();
		
		this->velController = new VelocityController(
			this->servoComponent, 
			this->potentiometerComponent);
		this->steController = new SteeringController();

	} 
	 
	void loop()
	{ 
		this->velController->update();
		///Serial.println((int)this->velController->getCurrentVelocity());
	} 
};

#endif