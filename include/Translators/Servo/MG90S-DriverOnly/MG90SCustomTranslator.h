#ifndef MG90SCUSTOMTRANSLATOR
#define MG90SCUSTOMTRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Servo/IServoImplementation.h>
#include <InputControllers/IControllableComponent.h>

/**
 * Tradutor de dados customizado do Servo MG90S da `Tower Pro`.
 * 
 * Aplicacao em projetos onde o potenciometro dentro do 
 * servo não é usado/alterado com a rotacao do motor, mantendo assim 
 * apenas a funcionalidade do driver de motor do conjunto.
 * 
 * See: https://www.towerpro.com.tw/product/mg90s-3/
 */
class MG90SCustomTranslator: public IArduinoComponent, public IControllableComponent {
	private:
	IServoImplementation* servoImpl;
	
	/**
	 * Valor máximo da velocidade do motor.
	 */
	const int MAX_ACCELERATION; 

	/**
	 * Valor que mantem o servo parado.
	 */
	const int SERVO_STOPPED_VALUE;

	public:
	MG90SCustomTranslator(
		IServoImplementation* servoImpl, 
		int maxIncrement, 
		int neutralValue
	): 
		MAX_ACCELERATION(maxIncrement), 
		SERVO_STOPPED_VALUE(neutralValue)
	{
		this->servoImpl = servoImpl;
	};


	int getMaxAcceleration() {
		return this->MAX_ACCELERATION;
	}

	int getServoNeutralValue() {
		return this->SERVO_STOPPED_VALUE;
	}

  int translate(float accelCap) {
		return (int)(this->SERVO_STOPPED_VALUE + ((float)MG90SCustomTranslator::MAX_ACCELERATION * accelCap));
	}
  void set(float vel) {
		int value = this->translate(vel);
		this->servoImpl->send(value);
	}

	void setRaw(float vel) {
		int value = (int)(vel);
		this->servoImpl->send(value);
	}
};

#endif