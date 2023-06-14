#ifndef IWIRELESSWIFIIMPLEMENTATION
#define IWIRELESSWIFIIMPLEMENTATION
#include <ESP8266WiFi.h>

class IWirelessWiFiImplementation {
  private:
  public:
  virtual ~IWirelessWiFiImplementation() = 0;
	virtual wl_status_t GetStatus() = 0;
	virtual void printIP() = 0;
};

IWirelessWiFiImplementation::~IWirelessWiFiImplementation() {};
#endif