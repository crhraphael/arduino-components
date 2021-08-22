#ifndef WEBSOCKETSERVERIMPLEMENTATION
#define WEBSOCKETSERVERIMPLEMENTATION
#include <Implementations/Websocket/IWebsocketImplementation.h>

class WebsocketServerImplementation: 
	public IWebsocketImplementation
{
  private:
	WebSocketsServer webSocket;
	bool isOpen = false;
	bool hasClientsConnected = false;
	unsigned int bufferLength = 10;
	char *buffer = '\0';
	uint8_t clientNumber = 0;

	public:
	WebsocketServerImplementation(
		const int websocketPort,
		unsigned int bufferLength = 10
	)

	:	webSocket(websocketPort) {
		this->bufferLength = bufferLength;
		this->buffer = new char[bufferLength]();
	}

	bool IsOpen() {
		return this->isOpen;
	}

	bool HasClientsConnected() {
		return this->hasClientsConnected;
	}

	void open() {
		this->isOpen = true;
		this->webSocket.begin();
		this->webSocket.onEvent(
			std::bind(
				&WebsocketServerImplementation::webSocketEvent, 
				this,  
				std::placeholders::_1, 
				std::placeholders::_2, 
				std::placeholders::_3,
				std::placeholders::_4));
	}

	void close() {
		this->webSocket.close();
		this->isOpen = false;
	}

	void listen(char *buff) {}
	void listen() {
		this->webSocket.loop();
	}
	
	void read(char *buff) {
		const char *msg = this->buffer;
		strcpy(buffer, msg);
	}


	void send(const char *message) {
		this->webSocket.sendTXT(this->clientNumber, message);
	}

	void webSocketEvent(
		uint8_t num, 
		WStype_t type, 
		uint8_t * payload, 
		size_t lenght
	) {
		switch (type) {
			case WStype_DISCONNECTED:
				{
					strcpy(this->buffer, "");
					this->hasClientsConnected = false;
				}
				break;	
			case WStype_CONNECTED:
				{ 
					IPAddress ip = this->webSocket.remoteIP(num);
					Serial.println(ip);
					this->clientNumber = num;
					this->hasClientsConnected = true;
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
};

#endif