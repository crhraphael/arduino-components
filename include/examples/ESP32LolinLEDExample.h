#ifndef ESP32LOLINLEDEXAMPLE
#define ESP32LOLINLEDEXAMPLE



#include <Translators/LEDs/CommonLED.h>


#include <Arduino.h>


/**
 * Portas dos devices.
 */
const int LED_PIN = 2;
const int DEFAULT_BAULD_RATE = 9600;

class ESP32LolinLEDExample {
	CommonLED *led;

	
	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);
		this->led = new CommonLED(LED_PIN);

		
	} 
	 
	void loop()
	{ 
		this->led->set(LOW);
		delay(1000);
		this->led->set(HIGH);
		delay(2000);
	} 
};

#endif