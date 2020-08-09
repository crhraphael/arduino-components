#ifndef FS1000ATRANSMITTERTRANSLATOR
#define FS1000ATRANSMITTERTRANSLATOR

#include <IArduinoCompontent.h>
#include <RH_ASK.h>
#include <SPI.h> 

/**
 * Tradutor de dados do transmissor via RF FS1000A.
 * 
 * See: https://www.instructables.com/id/Arduino-433mhz-Wireless-Transmitter-Receiver-SWITC/
 */
class FS1000ATransmitterTranslator: public IArduinoComponent {
	private:
  RH_ASK* driver;
	public:
	FS1000ATransmitterTranslator(int pin, int bitsPerSec)
	{
		this->driver = new RH_ASK(bitsPerSec, pin, 12);
  	if(this->driver->init()) Serial.println("init failed");
	};

	void send (char *message)
	{
		this->driver->send((uint8_t *)message, strlen(message));
		this->driver->waitPacketSent();
	}
};

#endif