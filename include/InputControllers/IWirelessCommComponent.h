#ifndef IWIRELESSCOMMCOMPONENT
#define IWIRELESSCOMMCOMPONENT

#include "InputControllers/IControllerComponent.h"

/**
 * A Wireless Communication Controller Component interface.
*/
class IWirelessCommComponent: public IControllerComponent {
	private:
	public:
	virtual ~IWirelessCommComponent() = 0;
	virtual void listen(char *buff) = 0;
	virtual void listen() = 0;
	virtual void read(char *buff) = 0;
	virtual void send(const char *msg) = 0;
};
IWirelessCommComponent::~IWirelessCommComponent() {};

#endif