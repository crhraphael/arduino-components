#ifndef HC06TRANSLATOR
#define HC06TRANSLATOR

#include <Devices/Potentiometer/IPotentiometerInputTranslator.h>
#include <Implementations/Wireless/Bluetooth/IBluetoothImplementation.h>

#include <InputControllers/IControllerComponent.h>
#include <IArduinoCompontent.h>

class HC06Device: public IArduinoComponent, public IControllerComponent {
	private:
	float voltage = 5.0f;
	IBluetoothImplementation *implm;

	public:	
	HC06Device(IBluetoothImplementation *implm, int maxValue):
		IControllerComponent(maxValue)
	{
		this->implm = implm;
	}

	void read(char *buf) {
		this->implm->listen(buf);
	}
};

#endif