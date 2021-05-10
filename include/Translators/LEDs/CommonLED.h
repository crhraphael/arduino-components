#ifndef COMMONLED
#define COMMONLED

#include <Translators/Servo/IServoInputTranslator.h>
#include <IArduinoCompontent.h>
#include <InputControllers/IControllableComponent.h>

#define LED_ON LOW
#define LED_OFF HIGH

/**
 * Tradutor de dados para LEDs comuns.
 */
class CommonLED: public IArduinoComponent, public IControllableComponent {
	int pin;
	public:
	CommonLED(int pin) {
		this->pin = pin;
		pinMode(pin, OUTPUT);
	}

	// TODO: Criar abstração de motor controlável para estes valores.
	int getMaxAcceleration() { return 0; }; 
	
	// TODO: Criar abstração de motor controlável para estes valores.
	int getServoNeutralValue() { return 0; }; 

  void set(float val) {
		digitalWrite(this->pin, (int)val);
	}
	void setRaw(int val) {
		digitalWrite(this->pin, val);
	}
};

#endif