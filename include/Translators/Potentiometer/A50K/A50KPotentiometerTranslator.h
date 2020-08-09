#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>

class A50KPotentiometerTranslator: public IPotentiometerInputTranslator {
	private:
	int pin;

	public:	
	A50KPotentiometerTranslator(int pin):
		IPotentiometerInputTranslator(pin)
	{
		this->pin = pin;
		pinMode(pin, INPUT);
	}

  int MAX_POT_VALUE() { return 1023; };

	/**
	 * Valor de aceitacao para continuar na posição neutra.
	 */
	int NEUTRAL_POT_SENSITIVITY() { return 10; };

	int read() {
		return analogRead(this->pin);
	}
};