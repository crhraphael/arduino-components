#ifndef IWIRELESSRFIMPLEMENTATION
#define IWIRELESSRFIMPLEMENTATION

class IWirelessRFImplementation {
  private:
  public:
  virtual ~IWirelessRFImplementation() = 0;
  virtual void listen() = 0;
	virtual void send (char *message) = 0;
};

IWirelessRFImplementation::~IWirelessRFImplementation() {};
#endif