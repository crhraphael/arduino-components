#ifndef NONCLASSEXAMPLE
#define NONCLASSEXAMPLE

#include <Arduino.h>
#include <Config/WIFICredentials.h>
#include <Servo.h>

#include <Helpers/CharIdFloatInputParser.h>


	#include <WebSocketsServer.h>


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
 * Controls the velocity and direction of two servos
 * using a wifi module.
 **/
class NonClassExample {

	WebSocketsServer webSocket;
	

	const int websocketPort = 80;

	public:
	NonClassExample()	: webSocket(websocketPort) {	}

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

		this->read(buff);
		this->parser->parse(buff, this->inputValue, 'a');

		Serial.println(this->inputValue);

		// this->configureDirection();
		// this->translateAcceleration();
		// Serial.print("reverse");
		// Serial.println(this->reverse);
		// Serial.print("currentAcceleration");
		// Serial.println(this->currentAcceleration);
		// Serial.print("*");
		// Serial.println(this->reverse * this->currentAcceleration);
		
		// 73 - 83-89 - 100
		// int i = 0;
		// for(i = 70; i < 100; i+=1) {
		set(this->inputValue);
		// 	delay(2000);
		// }
		// for(i = 100; i < 70; i-=1) {
		// 	set(i);
		// 	delay(2000);
		// }
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

	//---------------- WIFI -------------------

	bool isListening = false;
	ESP8266WiFiClass wifiImpl;

	void ESP8266WiFiImplementation(
		const char *ssid, 
		const char *password
	) {
		this->connect(ssid, password);
	}

	void connect(		
		const char *ssid, 
		const char *password
	) {
		this->wifiImpl.setSleepMode(WIFI_NONE_SLEEP);
		this->wifiImpl.begin(ssid, password);
	}

	public: void WriteIP() {
		Serial.println(this->wifiImpl.localIP());
	}	

	public: wl_status_t GetStatus() {
		return this->wifiImpl.status();
	}

	void scanNetworks() {
		int numberOfNetworks = this->wifiImpl.scanNetworks();

		for(int i = 0; i < numberOfNetworks; i++) {
			Serial.print("Network name: ");
			Serial.println(this->wifiImpl.SSID(i));
			Serial.print("Signal strength: ");
			Serial.println(this->wifiImpl.RSSI(i));
			Serial.println("-----------------------");
		}
	}
	//---------------- WIFI -------------------

	// -------------- WEBSOCKET ---------------

	bool isOpen = false;
	bool hasClientsConnected = false;
	unsigned int bufferLength = 10;
	char buffer[10];
	uint8_t clientNumber = 0;

	void WebsocketServerImplementation(
		const int websocketPort,
		unsigned int bufferLength = 10
	)	
	{
		WebSocketsServer(websocketPort, "", "arduino");
		this->bufferLength = bufferLength;
		this->buffer[0] = '\0';
	}

	bool IsOpen() {
		return this->isOpen;
	}

	bool HasClientsConnected() {
		return this->hasClientsConnected;
	}

	void open() {
		this->isOpen = true;
		this->webSocket.begin();
		this->webSocket.onEvent(
			std::bind(
				&NonClassExample::webSocketEvent, 
				this,  
				std::placeholders::_1, 
				std::placeholders::_2, 
				std::placeholders::_3,
				std::placeholders::_4));
	}

	void close() {
		this->webSocket.close();
		this->isOpen = false;
	}

	void listen(char *buff) {}
	void listen() {
		this->webSocket.loop();
	}
	
	void read(char *buff) {
		const char *msg = this->buffer;
		strcpy(buff, msg);
	}


	void send(const char *message) {
		this->webSocket.sendTXT(this->clientNumber, message);
	}

	void webSocketEvent(
		uint8_t num, 
		WStype_t type, 
		uint8_t * payload, 
		size_t lenght
	) {
		switch (type) {
			case WStype_DISCONNECTED:
				{
					strcpy(this->buffer, "");
					this->hasClientsConnected = false;
				}
				break;	
			case WStype_CONNECTED:
				{ 
					IPAddress ip = this->webSocket.remoteIP(num);
					Serial.print("Client connected: ");
					Serial.println(ip);
					this->clientNumber = num;
					this->hasClientsConnected = true;
				}
				break;	
			case WStype_TEXT:
				{ 
					if(lenght <= this->bufferLength) {
						const char *text = (const char*)payload;
						strcpy(this->buffer, text);
					}
				}
				break;
			case WStype_ERROR:
			case WStype_FRAGMENT:
			case WStype_BIN:
			case WStype_FRAGMENT_TEXT_START:
			case WStype_FRAGMENT_BIN_START:
			case WStype_FRAGMENT_FIN:
			case WStype_PING:
			case WStype_PONG:
				{

				}
				break;
		}
	
	}

	void defineServoDevices() {
		this->ServoImplementation(SERVO_ACCELERATION_PIN);
	}

	void defineWiFIModule() {
		int WEBSOCKET_PORT = 81;
		this->parser = new CharIdFloatInputParser();

		this->ESP8266WiFiImplementation(MY_SSID, MY_PASS);
		WebsocketServerImplementation(WEBSOCKET_PORT);
	}

	// -------------- WEBSOCKET --------------------


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
		this->listen();

		this->updateVelocity();
		//Serial.println((int)this->accelController->getCurrentAcceleration());

		//this->steController->update();

	} 
};

#endif