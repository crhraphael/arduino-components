
#ifndef ESP8266WIFIIMPLEMENTATION
#define ESP8266WIFIIMPLEMENTATION

#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

//Correção nível lógico invertido para ESP12E
#define ON LOW
#define OFF HIGH
 



/**
 * ESP8266WiFi é uma lib focada em transmissoes via WiFi para placas ESP (NodeMCU).
 * 
 * É totalmente compatível com o arduino caso ele possua o firmware 
 * para receber comandos AT.
 * 
 * TODO: Futuramente será interessante abstrair as implementações de Websocket e 
 * Conexão de rede desta classe.
 **/
class ESP8266WiFiImplementation: public IWirelessWiFiImplementation {
	private:
	bool isListening = false;
	ESP8266WiFiClass wifiImpl;
	WebSocketsServer webSocket;

	unsigned int bufferLength = 10;

	public:
	char *buffer = '\0';
	ESP8266WiFiImplementation(
		const char *ssid, 
		const char *password, 
		const int websocketPort,
		unsigned int bufferLength = 10)
	: 
		webSocket(websocketPort) 
	{
		this->bufferLength = bufferLength;
		this->buffer = new char[bufferLength]();

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

	public: void WebSocketConnect() {
		this->webSocket.begin();
		this->webSocket.onEvent(
			std::bind(
				&ESP8266WiFiImplementation::webSocketEvent, 
				this,  
				std::placeholders::_1, 
				std::placeholders::_2, 
				std::placeholders::_3,
				std::placeholders::_4));
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

	void webSocketEvent(
		uint8_t num, 
		WStype_t type, 
		uint8_t * payload, 
		size_t lenght
	) {
		switch (type) {
			case WStype_DISCONNECTED:
				break;	
			case WStype_CONNECTED:
				{ 
					IPAddress ip = this->webSocket.remoteIP(num);
					Serial.println(ip);
				}
				break;	
			case WStype_TEXT:
				{ 
					if(lenght <= this->bufferLength) {
						const char *text = (const char*)payload;
						strcpy(this->buffer, text);
					}
				}
				break;
			case WStype_ERROR:
			case WStype_FRAGMENT:
			case WStype_BIN:
			case WStype_FRAGMENT_TEXT_START:
			case WStype_FRAGMENT_BIN_START:
			case WStype_FRAGMENT_FIN:
			case WStype_PING:
			case WStype_PONG:
				{

				}
				break;
		}
	
	}

	void listen()
	{
		this->webSocket.loop();
		this->isListening = true;
	}

	void readBuffer(char *buffer) {
		const char *msg = this->buffer;//"error: class is not listening. Did you called listen?";
		// (!this->isListening)
		// 	? "error: class is not listening. Did you called listen?"
		// 	: this->buffer;

		// Serial.println(msg);
		strcpy(buffer, msg);
	}

	void send(char *message)
	{
		this->webSocket.sendTXT(0, message);
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
