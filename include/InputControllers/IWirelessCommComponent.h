#ifndef IWIRELESSCOMMCOMPONENT
#define IWIRELESSCOMMCOMPONENT

class IWirelessCommComponent {
	private:
	public:
	virtual ~IWirelessCommComponent() = 0;
	virtual void listen(char *buff) = 0;
	virtual void send(char *msg) = 0;
};
IWirelessCommComponent::~IWirelessCommComponent() {};

#endif