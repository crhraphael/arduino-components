#ifndef ESP12ETRANSLATOR
#define ESP12ETRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>


/**
 * Tradutor de dados via WiFI ESP-12E.
 */
class ESP12ETranslator: public IArduinoComponent {
	private:
  IWirelessWiFiImplementation* rfImpl;
	public:
	ESP12ETranslator(IWirelessWiFiImplementation *rfImpl)
	{
		this->rfImpl = rfImpl;
	};

	void send (char *message)
	{
		this->rfImpl->send(message);
	}
};

#endif