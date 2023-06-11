#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>
#include <ESP8266WiFi.h>
#include <Config/WIFICredentials.h>

// Correção nível lógico invertido para ESP12E 
// TODO: Colocar em outro arquivo
#define ON LOW
#define OFF HIGH
 
struct ESP8266WiFiImplementation {
	bool isListening = false;
	ESP8266WiFiClass wifiImpl;

	void CreateConection(
		const char *ssid, 
		const char *password)
	{
		connect(ssid, password);
	}

	void WriteIP() {
		Serial.println(wifiImpl.localIP());
	}	

	void connect(		
		const char *ssid, 
		const char *password
	) {
		wifiImpl.mode(WIFI_STA);
		wifiImpl.setSleepMode(WIFI_NONE_SLEEP);
		wifiImpl.begin(ssid, password);
	}

	wl_status_t GetStatus() {
		return wifiImpl.status();
	}

	void scanNetworks() {
		int numberOfNetworks = wifiImpl.scanNetworks();

		for(int i = 0; i < numberOfNetworks; i++) {
			Serial.print("Network name: ");
			Serial.println(wifiImpl.SSID(i));
			Serial.print("Signal strength: ");
			Serial.println(wifiImpl.RSSI(i));
			Serial.println("-----------------------");
		}
	}
};
