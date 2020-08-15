#ifndef HC06TRANSLATOR
#define HC06TRANSLATOR

#include <Translators/Potentiometer/IPotentiometerInputTranslator.h>
#include <Implementations/Wireless/Bluetooth/IBluetoothImplementation.h>

#include <InputControllers/IControllerComponent.h>
#include <IArduinoCompontent.h>

class HC06Translator: public IArduinoComponent, public IControllerComponent {
	private:
	float voltage = 5.0f;
	IBluetoothImplementation *implm;

	public:	
	HC06Translator(IBluetoothImplementation *implm, int maxValue):
		IControllerComponent(maxValue)
	{
		this->implm = implm;
	}

	void read(char *buf) {
		this->implm->listen(buf);
		// if (buf != '\0')	{
		// 	Serial.println(buf);
		// }
	}
};

#endif