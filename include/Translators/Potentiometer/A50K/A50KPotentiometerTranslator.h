#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <InputControllers/IControllerComponent.h>

class A50KPotentiometerTranslator: public IPotentiometerInputTranslator, public IControllerComponent {
	private:
	int pin;
	float voltage = 5.0f;

	public:	
	A50KPotentiometerTranslator(int pin, float voltage, int maxValue):
		IPotentiometerInputTranslator(pin),
		IControllerComponent(maxValue)
	{
		this->pin = pin;
		this->voltage = voltage;
		pinMode(pin, INPUT);
	}

  float MAX_POT_VALUE() { return (this->voltage > 4 ? 1023.0f : 680.0f); };

	void read(char *buff) {
		itoa(analogRead(this->pin), buff, 10);
	}
};