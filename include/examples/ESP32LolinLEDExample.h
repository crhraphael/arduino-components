#ifndef ESP32LOLINLEDEXAMPLE
#define ESP32LOLINLEDEXAMPLE



#include <Translators/LEDs/CommonLED.h>


#include <Arduino.h>


/**
 * Portas dos devices.
 */
const int LED_PIN = LED_BUILTIN | 2;
// const int DEFAULT_BAULD_RATE = 9600;

class ESP32LolinLEDExample {
	CommonLED *led;
	bool isHigh = true;

	
	public:
	void setup() 
	{ 
		// Serial.begin(DEFAULT_BAULD_RATE);
		this->led = new CommonLED(LED_PIN);

		
	} 

	unsigned int lastMillis = 0;
	const unsigned int interv = 500;

	void loop()
	{ 
		unsigned int currentMillis = millis();
		uint8_t ledStatus = (this->isHigh) ? LOW : HIGH;


		this->led->set(ledStatus);

		if(currentMillis - lastMillis > interv) {
			this->isHigh = !this->isHigh;
			lastMillis = currentMillis;
		}
	} 
};

#endif