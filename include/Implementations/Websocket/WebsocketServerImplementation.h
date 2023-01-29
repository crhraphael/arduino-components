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
	char buffer[10];
	uint8_t clientNumber = 0;
	public:
	WebsocketServerImplementation(
		const int websocketPort,
		unsigned int bufferLength = 10
	)	:	
		webSocket(websocketPort) 
	{
		this->bufferLength = bufferLength;
		this->buffer[0] = '\0';
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
		strcpy(buff, msg);
	}


	void send(const char *message) {
		this->webSocket.sendTXT(this->clientNumber, message);
	}

	void webSocketEvent(
		uint8_t num, 
		WStype_t type, 
		uint8_t * payload, 
		size_t length
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
					Serial.print("Client connected: ");
					Serial.println(ip);
					this->clientNumber = num;
					this->hasClientsConnected = true;
				}
				break;	
			case WStype_TEXT:
				{ 
					if(length <= this->bufferLength) {
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