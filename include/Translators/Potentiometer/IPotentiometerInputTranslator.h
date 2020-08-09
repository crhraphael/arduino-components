#ifndef IPOTENTIOMETERINPUTTRANSLATOR
#define IPOTENTIOMETERINPUTTRANSLATOR
#include <IArduinoCompontent.h>

class IPotentiometerInputTranslator: public IArduinoComponent {
	private:
	int pin;

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
  virtual int MAX_POT_VALUE() = 0;

	/**
	 * Valor de aceitacao para continuar na posição neutra.
	 */
	virtual int NEUTRAL_POT_SENSITIVITY() = 0;
	
  virtual int read() = 0;
};
IPotentiometerInputTranslator::~IPotentiometerInputTranslator() {};

#endif