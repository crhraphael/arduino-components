#ifndef STRUCTUREDMOTOREXAMPLE
#define STRUCTUREDMOTOREXAMPLE

#include <Arduino.h>

#include <Implementations/Wireless/WiFi/ESP8266WiFiImplementation.h>
#include <Servo.h>

#include <Translators/Wireless/WIFI/ESP12ETranslator.h>
#include <Helpers/CharIdFloatInputParser.h>

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
int SERVO_ACCELERATION_PIN = D7;
int DEFAULT_BAULD_RATE = 9600;

/**
 * Experiment using an ESP32 Lolin v3 as prototype board
 * 
 * Autonomous Controls  of the servo velocity and direction 
 **/
class StructuredMotorExample {
	public:
	StructuredMotorExample() {

	}

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
	int MAX_ACCELERATION = 40;

	/**
	 * Valor que mantem o servo parado.
	 */
	int SERVO_STOPPED_VALUE = 60;

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
		Serial.println(value);
		send(value);
	}
  void setRaw(float val) {
		int value = (int)(val);
		Serial.println(value);
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

	void updateVelocity() {	
		// Valor de velocidade do motor usado.
		// 73 - 83-89 - 100
		int i = 0;
		for(i = 73; i < 100; i+=1) {
			this->inputValue = i;
			setRaw(this->inputValue);
			delay(2000);
		}
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

	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);

		this->defineServoDevices();

		AccelerationController();
	} 
	
	void loop()
	{ 
		this->updateVelocity();
	} 
};

#endif