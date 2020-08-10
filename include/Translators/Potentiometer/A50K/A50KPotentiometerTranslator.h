#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>

class A50KPotentiometerTranslator: public IPotentiometerInputTranslator {
	private:
	int pin;
	int voltage;

	public:	
	A50KPotentiometerTranslator(int pin, int voltage):
		IPotentiometerInputTranslator(pin)
	{
		this->pin = pin;
		this->voltage = voltage;
		pinMode(pin, INPUT);
	}

  int MAX_POT_VALUE() { return this->voltage > 4 ? 1024 : 680; };

	/**
	 * Valor de aceitacao para continuar na posição neutra.
	 */
	int NEUTRAL_POT_SENSITIVITY() { return 10; };

	int read() {
		return analogRead(this->pin);
	}
};