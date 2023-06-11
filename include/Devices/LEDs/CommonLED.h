#ifndef COMMONLED
#define COMMONLED

#include <Devices/LEDs/ILEDComponent.h>
#include <InputControllers/IControllableComponent.h>

#define LED_ON LOW
#define LED_OFF HIGH

/**
 * Tradutor de dados para LEDs comuns.
 */
class CommonLED: public ILEDComponent {
	int pin;
	int val;
	unsigned int lastMillis = 0;
	public:
	CommonLED(int pin) {
		this->pin = pin;
		pinMode(pin, OUTPUT);
	}

	// TODO: Criar abstração de motor controlável para estes valores.
	int getMaxAcceleration() { return 0; }; 
	
	// TODO: Criar abstração de motor controlável para estes valores.
	int getServoNeutralValue() { return 0; }; 

	int get() {
		return this->val;
	}

	void blink(unsigned int microseconds) {
		unsigned int currentMillis = millis();
		if(currentMillis - this->lastMillis > microseconds) {
			this->set(this->reverseValue());
			this->lastMillis = currentMillis;
		}
	}

	int reverseValue() {
		return this->val == LED_ON ? LED_OFF : LED_ON;
	}



  void set(float val) { 
		this->val = (int)val;
		digitalWrite(this->pin, this->val);
	}
	void setRaw(int val) {
		this->val = val;
		digitalWrite(this->pin, val);
	}
};

#endif