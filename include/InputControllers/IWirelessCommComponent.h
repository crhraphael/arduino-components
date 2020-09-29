#ifndef IWIRELESSCOMMCOMPONENT
#define IWIRELESSCOMMCOMPONENT

#include "InputControllers/IControllerComponent.h"

class IWirelessCommComponent: public IControllerComponent {
	private:
	public:
	virtual ~IWirelessCommComponent() = 0;
	virtual void listen(char *buff) = 0;
	virtual void read(char *buff) = 0;
	virtual void send(char *msg) = 0;
};
IWirelessCommComponent::~IWirelessCommComponent() {};

#endif