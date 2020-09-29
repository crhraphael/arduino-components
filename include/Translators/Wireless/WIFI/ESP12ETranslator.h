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
  IWirelessWiFiImplementation* rfImpl;
	public:
	ESP12ETranslator(
		IWirelessWiFiImplementation *rfImpl
	):
		IWirelessCommComponent()
	{
		this->rfImpl = rfImpl;
	};

	void send (char *message)
	{
		this->rfImpl->send(message);
	}

	void listen(char *buff) {
		this->rfImpl->listen();
	}

	void read(char *buff) {
		this->rfImpl->listen();
	}
};

#endif