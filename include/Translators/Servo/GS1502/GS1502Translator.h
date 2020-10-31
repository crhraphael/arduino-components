#ifndef GS1502TRANSLATOR
#define GS1502TRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Servo/IServoImplementation.h>
#include <InputControllers/IControllableComponent.h>

/**
 * Linear Servo Motor used mainly on airplane models.
 */
class GS1502Translator: public IArduinoComponent, public IControllableComponent {
	private:
	IServoImplementation* servoImpl;

	public:
	GS1502Translator(IServoImplementation* servoImpl): 
		MAX_ACCELERATION(1)
	{
		this->servoImpl = servoImpl;
	};

	/**
	 * Maximum mottor acceleration value.
	 */
	const int MAX_ACCELERATION; 


  int translate(float accelCap) {
		return (int)(GS1502Translator::MAX_ACCELERATION * accelCap);
	}

  void set(float vel) {
		int value = this->translate(vel);
		this->servoImpl->send(value);
	}
};

#endif