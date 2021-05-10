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

	int valueToSend;
	int lastValueSent;

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
		valueToSend = SERVO_STOPPED_VALUE;
		lastValueSent = valueToSend;
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
		valueToSend = this->translate(vel);

		if(valueToSend != lastValueSent) {
			Serial.println(valueToSend);
		}
		this->servoImpl->send(valueToSend);
		lastValueSent = valueToSend;
	}

	void setRaw(int vel) {
		valueToSend = (vel);

		if(valueToSend != lastValueSent) {
			Serial.println(valueToSend);
		}
		this->servoImpl->send(valueToSend);
		lastValueSent = valueToSend;
	}

};

#endif