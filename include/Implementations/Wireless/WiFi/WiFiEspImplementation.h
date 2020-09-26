#ifndef WIFIESPIMPLEMENTATION
#define WIFIESPIMPLEMENTATION

#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>

/**
 * WiFiEsp e uma lib focada em transmissoes via WiFi para placas ESP (NodeMCU).
 * 
 * É totalmente compatível com o arduino caso ele possua o firmware 
 * para receber comandos AT.
 **/
class WiFiEspImplementation: public IWirelessWiFiImplementation {
	private:

	public:
	WiFiEspImplementation(
		int transmitterPin, 
		int receiverPin,
		int bitsPerSec)
	{
	};

	void listen()
	{
	}

	void send(char *message)
	{
	}
};

#endif