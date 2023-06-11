#ifndef FS1000ARECEIVERTRANSLATOR
#define FS1000ARECEIVERTRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Wireless/RF/IWirelessRFImplementation.h>


/**
 * Tradutor de dados do receptor via RF FS1000A.
 * 
 * See: https://www.instructables.com/id/Arduino-433mhz-Wireless-Transmitter-Receiver-SWITC/
 */
class FS1000AReceiverTranslator: public IArduinoComponent {
	private:
	IWirelessRFImplementation *rfImpl;
	public:
	FS1000AReceiverTranslator(IWirelessRFImplementation* rfImpl)
	{
		this->rfImpl = rfImpl;
	};

	void listen()
	{
		this->rfImpl->listen();
	}
};

#endif