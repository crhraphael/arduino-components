#ifndef IWIRELESSWIFIIMPLEMENTATION
#define IWIRELESSWIFIIMPLEMENTATION

class IWirelessWiFiImplementation {
  private:
  public:
  virtual ~IWirelessWiFiImplementation() = 0;
  virtual void listen() = 0;
	virtual void send (char *message) = 0;
  virtual void readBuffer(char *buffer) = 0;
};

IWirelessWiFiImplementation::~IWirelessWiFiImplementation() {};
#endif