#ifndef IWIRELESSWIFIIMPLEMENTATION
#define IWIRELESSWIFIIMPLEMENTATION
#include <ESP8266WiFi.h>

class IWirelessWiFiImplementation {
  private:
  public:
  virtual ~IWirelessWiFiImplementation() = 0;
	virtual wl_status_t IsConnected() = 0;
	virtual void WebSocketConnect() = 0;
  virtual void listen() = 0;
	virtual void send (char *message) = 0;
  virtual void readBuffer(char *buffer) = 0;
	virtual void WriteIP() = 0;
};

IWirelessWiFiImplementation::~IWirelessWiFiImplementation() {};
#endif