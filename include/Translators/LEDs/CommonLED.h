#ifndef COMMONLED
#define COMMONLED

#include <Translators/Servo/IServoInputTranslator.h>
#include <IArduinoCompontent.h>
#include <InputControllers/IControllableComponent.h>

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

  void set(float vel) {
		analogWrite(this->pin, (int)vel);
	}
};

#endif