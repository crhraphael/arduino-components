#ifndef IPOTENTIOMETERINPUTTRANSLATOR
#define IPOTENTIOMETERINPUTTRANSLATOR
#include <IArduinoCompontent.h>

class IPotentiometerInputTranslator: public IArduinoComponent {
	private:
	int pin;
	float voltage;

  public:
  int translate();
	IPotentiometerInputTranslator(int pin)
	{
		this->pin = pin;
		pinMode(pin, INPUT);
	}
  virtual ~IPotentiometerInputTranslator() = 0;
  
	/**
	 * Valor maximo do potenciometro.
	 */
  virtual float MAX_POT_VALUE() = 0;

  virtual int read() = 0;
};
IPotentiometerInputTranslator::~IPotentiometerInputTranslator() {};

#endif