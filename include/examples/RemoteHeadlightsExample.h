#ifndef REMOTEHEADLIGHTEXAMPLE
#define REMOTEHEADLIGHTEXAMPLE

#include <Arduino.h>
#include <Config/WIFICredentials.h>

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/WiFi/ESP8266WiFiImplementation.h>
#include <Implementations/Websocket/WebsocketServerImplementation.h>

#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Servo/GS1502/GS1502Translator.h>

#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>

#include <Translators/LEDs/CommonLED.h>

#include <Translators/Debug/DebuggerTranslator.h>

#include <InputControllers/InputController.h>
#include <InputControllers/AccelerationController.h>
#include <InputControllers/SteeringController.h>
#include <Translators/LEDs/CommonLED.h>


#include <Helpers/CharIdFloatInputParser.h>
#include <Helpers/HeadlightInputParser.h>


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
 * Portas dos devices.
 */
const int SERVO_DIRECTION_PIN = D2; 
const int SERVO_ACCELERATION_PIN = D7; 

const int LED_PIN = LED_BUILTIN | 2;

const int DEFAULT_BAULD_RATE = 9600;

/**
 * Experiment using an ESP32 Lolin v3 as prototype board
 * 
 * Controls the state of some LEDs via wifi.
 **/
class RemoteHeadlightsExample {
	IInputParser *headlightsParser;
	
	IWirelessWiFiImplementation *wifiService;
	IWebsocketImplementation *websocketService;


	HeadLightsController *headlightsController;
	
	CommonLED *boardStatusLED;	
	bool isHigh = true;

	CommonLED *frontLeftHeadlightLED;
	CommonLED *frontRightHeadlightLED;

	void defineInputParsers() {
		this->headlightsParser = new HeadlightInputParser();
	}

	void defineWiFIModule() {
		const int WEBSOCKET_PORT = 81;
		this->wifiService = new ESP8266WiFiImplementation(MY_SSID, MY_PASS);
		this->websocketService = new WebsocketServerImplementation(WEBSOCKET_PORT);
	}

	void defineControllers(){
		this->headlightsController = new HeadLightsController(
			frontLeftHeadlightLED,
			frontRightHeadlightLED,
			this->websocketService,
			this->headlightsParser
		);
	}

	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);
		this->boardStatusLED = new CommonLED(LED_PIN);

		this->defineInputParsers();
		this->defineWiFIModule();
		this->defineControllers();

	} 
	bool isConnected = false;	
	
	unsigned int lastMillis = 0;
	const unsigned int interv = 500;
	
	void loop()
	{ 
		if(this->wifiService->IsConnected() != wl_status_t::WL_CONNECTED) {
			unsigned int currentMillis = millis();
			uint8_t ledStatus = (this->isHigh) ? LED_ON : LED_OFF;


			this->boardStatusLED->set(ledStatus);

			if(currentMillis - lastMillis > interv) {
				this->isHigh = !this->isHigh;
				lastMillis = currentMillis;
			}
		} else {
			if(isConnected == false) {
				isConnected = true;
				this->wifiService->WriteIP();

				this->boardStatusLED->set(LED_ON);
			}

			this->websocketService->listen();

			this->headlightsController->update();
		}


	} 
};

#endif