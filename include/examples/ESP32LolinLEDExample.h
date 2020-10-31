#ifndef ESP32LOLINLEDEXAMPLE
#define ESP32LOLINLEDEXAMPLE



#include <Translators/LEDs/CommonLED.h>


#include <Arduino.h>


/**
 * Portas dos devices.
 */
const int LED_PIN = LED_BUILTIN | 2;
const int DEFAULT_BAULD_RATE = 9600;

class ESP32LolinLEDExample {
	CommonLED *led;
	bool isHigh = false;

	
	public:
	void setup() 
	{ 
		Serial.begin(DEFAULT_BAULD_RATE);
		this->led = new CommonLED(LED_PIN);

		
	} 

	void loop()
	{ 
		uint8_t ledStatus = (this->isHigh) ? LOW : HIGH;
		this->led->set(ledStatus);
		this->isHigh = !this->isHigh;
	} 
};

#endif