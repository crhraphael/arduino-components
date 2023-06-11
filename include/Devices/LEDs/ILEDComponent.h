#ifndef ILEDCOMPONENT
#define ILEDCOMPONENT

#include <IArduinoCompontent.h>
#include <InputControllers/IControllableComponent.h>

class ILEDComponent: public IArduinoComponent, public IControllableComponent {
	
	virtual int get() = 0;

	virtual int reverseValue() = 0;

	virtual void blink(unsigned int microseconds) = 0;
};

#endif