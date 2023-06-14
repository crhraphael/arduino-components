#ifndef ESP12EVEHICLEEXAMPLE
#define ESP12EVEHICLEEXAMPLE

#include <Arduino.h>

#include <Config/WIFICredentials.h>

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/WiFi/ESP8266WiFiImplementation.h>
#include <Implementations/Websocket/WebsocketServerImplementation.h>

#include <examples/Vehicle/VehicleData.h>

#include <InputControllers/InputController.h>
#include <InputControllers/AccelerationController.h>
#include <InputControllers/SteeringController.h>
#include <InputControllers/HeadLightsController.h>

#include <Devices/LEDs/CommonLED.h>
#include <Devices/Servo/MG90S-DriverOnly/MG90SCustomDevice.h>
#include <Devices/Servo/GS1502/GS1502Servo.h>
#include <Devices/LEDs/CommonLED.h>

#include <Helpers/CharIdFloatInputParser.h>
#include <Helpers/HeadlightInputParser.h>

// #include <States/IState.h>

#ifndef WIFICREDENTIALS
#error "This example must include the Config/WIFICredentials.h"
#endif


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
 * Devices' pins.
 */
const int SERVO_DIRECTION_PIN = D2; 
const int SERVO_ACCELERATION_PIN = D7; 

const int LED_PIN = LED_BUILTIN | 2;

const int DEFAULT_BAULD_RATE = 115200;

/**
 * Experiment using an ESP32 Lolin v3 as prototype board
 * 
 * Controls the velocity and direction of two servos
 * using a wifi module.
 **/
class ESP12EVehicleExample {
	public:
	IControllableComponent *servoDirComp;
	IControllableComponent *servoVelComp;

	IInputParser *accelerationParser;
	IInputParser *directionParser;
	// IInputParser *headlightsParser;
	
	IWirelessWiFiImplementation *wifiService;
	IWebsocketImplementation *websocketService;

	IServoImplementation *servoDirImpl;
	IServoImplementation *servoVelImpl;

	IControllerComponent *debugComp;

	SteeringController *steController;
	AccelerationController *accelController;
	HeadLightsController *headlightsController;
	
	CommonLED *boardStatusLED;	

	CommonLED *frontLeftHeadlightLED;
	CommonLED *frontRightHeadlightLED;

	bool hasSentVehicleData = false;

	const char* vehicleInfo = "{\"type\":'car-info',\"title\":'John',\"year\":'1000'}";
	// IState* currentState;

	VehicleData vehicleData;

	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		vehicleData = VehicleData();
		this->boardStatusLED = new CommonLED(LED_PIN);
		this->boardStatusLED->set(LED_OFF);
		this->defineServoDevices();
		this->defineInputParsers();
		this->defineWiFIModule();
		this->defineControllers();
	}

	void loop()
	{ 
		// Not connected to the network...
		if(this->wifiService->GetStatus() != wl_status_t::WL_CONNECTED) {
			this->boardStatusLED->blink(1000);
			this->resetControllables(0);
			return;
		}

		// Not connected to the network...
		if(!this->websocketService->IsOpen()) {
			this->boardStatusLED->blink(500);
			this->wifiService->printIP();
			this->websocketService->open();
			this->resetControllables(0);
			return;
		}		

			this->websocketService->listen();

		if(!this->websocketService->HasClientsConnected()) {
			this->boardStatusLED->blink(100);
			this->resetControllables(0);
			return;
		} 

		if(!this->hasSentVehicleData && this->websocketService->HasClientsConnected()) {
			this->websocketService->send(vehicleInfo);
			this->hasSentVehicleData = true;
			this->boardStatusLED->set(LED_ON);
		}


		this->accelController->update(this->websocketService);
		// this->steController->update(this->websocketService);

		// this->headlightsController->update();

	}
	
	/**
	 * Resets controllables to a default value.
	 **/
	void resetControllables(int value) {
		this->accelController->setSpeed(value);
		this->steController->setSpeed(value);
	}
	
	void defineServoDevices() {
		this->servoDirImpl = new ServoImplementation(SERVO_DIRECTION_PIN);
		const int maxIncrement = 45;
		const int neutralValue = 100;
		this->servoDirComp = new GS1502Servo(
			this->servoDirImpl, 
			maxIncrement, 
			neutralValue
		);

		const int maxIncrementAccellServo = 14;
		const int neutralValueAccellServo = 88;
		this->servoVelImpl = new ServoImplementation(SERVO_ACCELERATION_PIN);
		this->servoVelComp = new MG90SCustomDevice(
			this->servoVelImpl, 
			maxIncrementAccellServo, 
			neutralValueAccellServo
		);
	}

	void defineInputParsers() {
		this->accelerationParser = new CharIdFloatInputParser();
		this->directionParser = new CharIdFloatInputParser();
		// this->headlightsParser = new HeadlightInputParser();
	}

	void defineWiFIModule() {
		const int WEBSOCKET_PORT = 81;
		this->wifiService = new ESP8266WiFiImplementation(MY_SSID, MY_PASS);
		this->websocketService = new WebsocketServerImplementation(WEBSOCKET_PORT);
	}

	void defineControllers(){
		this->accelController = new AccelerationController(
			this->servoVelComp, 			
			this->accelerationParser
		);

		this->steController = new SteeringController(			
			this->servoDirComp, 
			this->directionParser
		);

		// this->headlightsController = new HeadLightsController(
		// 	frontLeftHeadlightLED,
		// 	frontRightHeadlightLED,
		// 	this->websocketService,
		// 	this->headlightsParser
		// );
	}

};

#endif
