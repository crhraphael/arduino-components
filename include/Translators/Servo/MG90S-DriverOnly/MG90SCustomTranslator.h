#ifndef MG90SCUSTOMTRANSLATOR
#define MG90SCUSTOMTRANSLATOR

#include <Translators/Servo/IServoInputTranslator.h>
#include <IArduinoCompontent.h>

/**
 * Tradutor de dados customizado do Servo MG90S da `Tower Pro`.
 * 
 * Aplicacao em projetos onde o potenciometro dentro do 
 * servo não é usado/alterado com a rotacao do motor, mantendo assim 
 * apenas a funcionalidade do driver de motor do conjunto.
 * 
 * See: https://www.towerpro.com.tw/product/mg90s-3/
 */
class MG90SCustomTranslator: public IArduinoComponent, public IServoInputTranslator {
	private:
	Servo servo;

	public:
	MG90SCustomTranslator(int pin): 
		MAX_VELOCITY(10), 
		SERVO_STOPPED_VALUE(135) 
	{
		pinMode(pin, OUTPUT);
		this->servo.attach(pin);
	};

	/**
	 * Valor máximo da velocidade do motor.
	 */
	const int MAX_VELOCITY; 

	/**
	 * Valor que mantem o servo parado.
	 */
	const int SERVO_STOPPED_VALUE;


  int translate(float velocityCap, int dir) {
		return (int)(this->SERVO_STOPPED_VALUE + (dir * (MG90SCustomTranslator::MAX_VELOCITY * velocityCap)));
	}
  void setVelocity(float vel, int dir) {
		int value = this->translate(vel, dir);
		this->servo.write(value);
	}
};

#endif