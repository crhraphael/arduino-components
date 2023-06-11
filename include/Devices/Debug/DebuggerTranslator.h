#ifndef DEBUGGERTRANSLATOR
#define DEBUGGERTRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Wireless/WiFi/IWirelessWiFiImplementation.h>
#include <InputControllers/IControllerComponent.h>


/**
 * Tradutor de dados para debug.
 */
class DebuggerTranslator: public IArduinoComponent, public IControllerComponent {
	private:
	public:
	DebuggerTranslator(
		const int maxValue = 0
	):
		IControllerComponent(maxValue)
	{
	};

	void send (char *message)
	{
	}

	void listen(char *buff) {
	}

	void read(char *buff) {
	}
};

#endif