
#ifndef ESP8266WIFIIMPLEMENTATION
#define ESP8266WIFIIMPLEMENTATION

#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>
#include <ESP8266WiFi.h>

// Correção nível lógico invertido para ESP12E 
// TODO: Colocar em outro arquivo
#define ON LOW
#define OFF HIGH
 



/**
 * ESP8266WiFi é uma lib focada em transmissoes via WiFi para placas ESP (NodeMCU).
 * 
 * É totalmente compatível com o arduino caso ele possua o firmware 
 * para receber comandos AT.
 * 
 **/
class ESP8266WiFiImplementation: public IWirelessWiFiImplementation {
	private:
	bool isListening = false;
	ESP8266WiFiClass wifiImpl;

	unsigned int bufferLength = 10;

	public:
	ESP8266WiFiImplementation(
		const char *ssid, 
		const char *password)
	{
		this->connect(ssid, password);
	}

	public: void WriteIP() {
		Serial.println(this->wifiImpl.localIP());
	}	

	void connect(		
		const char *ssid, 
		const char *password
	) {
		this->wifiImpl.begin(ssid, password);
	}

	public: wl_status_t IsConnected() {
		return this->wifiImpl.status();
	}

	void scanNetworks() {
		int numberOfNetworks = this->wifiImpl.scanNetworks();

		for(int i = 0; i < numberOfNetworks; i++) {
			Serial.print("Network name: ");
			Serial.println(this->wifiImpl.SSID(i));
			Serial.print("Signal strength: ");
			Serial.println(this->wifiImpl.RSSI(i));
			Serial.println("-----------------------");
		}
	}
};


typedef enum {
	ACCELERATION = 0,
	STEERING = 1,
	CONFIG = 2
} PayloadProtocolType;

class PayloadProtocol {
	public:
	PayloadProtocolType type = PayloadProtocolType::ACCELERATION;

	PayloadProtocol() {

	}
};

#endif
