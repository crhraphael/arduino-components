#ifndef STRUCTUREDWIRELESSMOTOREXAMPLE
#define STRUCTUREDWIRELESSMOTOREXAMPLE

#include <Arduino.h>
#include <Config/WIFICredentials.h>

// #include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/WiFi/ESP8266WiFiImplementation.h>
#include <Servo.h>

#include <Implementations/Websocket/WebsocketServerImplementation.h>

// #include <Devices/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
// #include <Devices/Servo/GS1502/GS1502Translator.h>

// #include <Devices/Potentiometer/A50K/A50KPotentiometerTranslator.h>

// #include <Devices/LEDs/CommonLED.h>

#include <Helpers/CharIdFloatInputParser.h>

// #include <Devices/Debug/DebuggerTranslator.h>

// #include <InputControllers/InputController.h>
// #include <InputControllers/AccelerationController.h>
// #include <InputControllers/SteeringController.h>



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
// const int SERVO_DIRECTION_PIN = D1; 
int SERVO_ACCELERATION_PIN = D2;
//D2; 
// const int POT_PIN = A0;

int DEFAULT_BAULD_RATE = 9600;

// const char END_MSG_BT = '.';


/**
 * Experiment using an ESP32 Lolin v3 as prototype board
 * 
 * Controls the velocity and direction of a servo
 * using a wifi module.
 **/
struct StructuredWirelessMotorExample {
	IWirelessCommComponent *websocketService;
	IWirelessWiFiImplementation *wifiService;

	public:
	// SERVO
	Servo servo;
	void ServoImplementation(int pin)
	{
		pinMode(pin, OUTPUT);
		this->servo.attach(pin);
	};

  void sendMicroseconds(int value) {
		this->servo.writeMicroseconds(value);
	}

	void send(int value) {
		this->servo.write(value);
	}
	//---------

	// GS1502Translator
	int MAX_ACCELERATION = 13;

	/**
	 * Valor que mantem o servo parado.
	 */
	int SERVO_STOPPED_VALUE = 86;

	int getMaxAcceleration() {
		return MAX_ACCELERATION;
	}

	int getServoNeutralValue() {
		return SERVO_STOPPED_VALUE;
	}

  int translate(float accelCap) {
		return SERVO_STOPPED_VALUE + ((int)(MAX_ACCELERATION * accelCap));
	}

  void set(float val) {
		int value = this->translate(val);

		send(value);
	}

	// ------------
	// Velocity Controller
  int neutralPointValue = 0;
	int neutralPointSensitivity = 5;
	int RIGHT = -1;
	int LEFT = 1;
	float currentAcceleration = 0;
	int reverse = -1;
	float inputValue = 0.0f;

	
	void AccelerationController()	{
		this->neutralPointValue = getServoNeutralValue();
	}


	/**
	 * Retorna a direcao do motor. 
	 */
	void configureDirection() {
		int neutralPotVal = this->neutralPointValue;
		
		int rightVal = neutralPotVal + this->neutralPointSensitivity;
		int leftVal = neutralPotVal - this->neutralPointSensitivity;
		
		int dir = (this->inputValue > rightVal)
			? this->RIGHT
			: (this->inputValue < leftVal) 
				? this->LEFT
				: 0;

		this->reverse = dir;
	}
	IInputParser *parser;

	void updateVelocity() {
		char buff[10] = "\0";
		char debug[10] = "\0";

		this->websocketService->read(buff);
		this->parser->parse(buff, this->inputValue, 'a');

		set(this->inputValue);
	}

	float getCurrentAcceleration() {
		return this->currentAcceleration;
	}

	int getSubString(char *source, char *target,int from, int to) {
		int length=0;
		int i=0,j=0;
		
		//get length
		while(source[i++]!='\0')
			length++;
		
		if(from<0 || from>length){
			return 1;
		}
		if(to>length){
			return 1;
		}	
		
		for(i=from,j=0;i<=to;i++,j++){
			target[j]=source[i];
		}
		
		//assign NULL at the end of string
		target[j]='\0'; 
		
		return 0;	
	}



	
	void defineServoDevices() {
		this->ServoImplementation(SERVO_ACCELERATION_PIN);
	}

	void defineWiFIModule() {
		int WEBSOCKET_PORT = 81;
		this->parser = new CharIdFloatInputParser();

		this->wifiService = new ESP8266WiFiImplementation(MY_SSID, MY_PASS);
		this->websocketService = new WebsocketServerImplementation(WEBSOCKET_PORT);
	}

	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		this->defineServoDevices();
		this->defineWiFIModule();

		AccelerationController();
	} 
	
	void loop()
	{ 
		this->websocketService->listen();
		this->updateVelocity();
	} 
};

#endif