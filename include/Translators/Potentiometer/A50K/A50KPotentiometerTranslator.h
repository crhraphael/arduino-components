#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>

class A50KPotentiometerTranslator: public IPotentiometerInputTranslator {
	private:
	int pin;
	float voltage = 5.0f;

	public:	
	A50KPotentiometerTranslator(int pin, float voltage):
		IPotentiometerInputTranslator(pin)
	{
		this->pin = pin;
		this->voltage = voltage;
		pinMode(pin, INPUT);
	}

  float MAX_POT_VALUE() { return (this->voltage > 4 ? 1023.0f : 680.0f); };

	/**
	 * Valor de aceitacao para continuar na posição neutra.
	 */
	int NEUTRAL_POT_SENSITIVITY() { return 10; };

	int read() {
		return analogRead(this->pin);
	}
};