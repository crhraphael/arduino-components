#ifndef ESP12ETRANSLATOR
#define ESP12ETRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>
#include <InputControllers/IWirelessCommComponent.h>


/**
 * Tradutor de dados via WiFI ESP-12E.
 */
class ESP12ETranslator: public IArduinoComponent, public IWirelessCommComponent {
	private:
  IWirelessWiFiImplementation* moduleImpl;
	public:
	ESP12ETranslator(
		IWirelessWiFiImplementation *moduleImpl
	):
		IWirelessCommComponent()
	{
		this->moduleImpl = moduleImpl;
	};

	void send (char *message)
	{
		this->moduleImpl->send(message);
	}

	void listen(char *buff) {}
	void listen() {
		this->moduleImpl->listen();
	}
	
	void read(char *buff) {
		this->moduleImpl->listen();
	}
};

#endif