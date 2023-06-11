#ifndef FS1000ATRANSMITTERTRANSLATOR
#define FS1000ATRANSMITTERTRANSLATOR

#include <IArduinoCompontent.h>
#include <Implementations/Wireless/RF/IWirelessRFImplementation.h>


/**
 * Tradutor de dados do transmissor via RF FS1000A.
 * 
 * See: https://www.instructables.com/id/Arduino-433mhz-Wireless-Transmitter-Receiver-SWITC/
 */
class FS1000ATransmitterTranslator: public IArduinoComponent {
	private:
  IWirelessRFImplementation* rfImpl;
	public:
	FS1000ATransmitterTranslator(IWirelessRFImplementation *rfImpl)
	{
		this->rfImpl = rfImpl;
	};

	void send (char *message)
	{
		this->rfImpl->send(message);
	}
};

#endif