#ifndef FS1000ARECEIVERTRANSLATOR
#define FS1000ARECEIVERTRANSLATOR

#include <IArduinoCompontent.h>
#include <RH_ASK.h>
#include <SPI.h>

/**
 * Tradutor de dados do receptor via RF FS1000A.
 * 
 * See: https://www.instructables.com/id/Arduino-433mhz-Wireless-Transmitter-Receiver-SWITC/
 */
class FS1000AReceiverTranslator: public IArduinoComponent {
	private:
	RH_ASK *driver;
	public:
	FS1000AReceiverTranslator(int pin, int bitsPerSec)
	{
		pinMode(pin, OUTPUT);
		this->driver = new RH_ASK(bitsPerSec, pin, 12);
		if (!this->driver->init()) Serial.println("init failed");
	};

	void listen()
	{
		uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
		uint8_t buflen = sizeof(buf);
		uint8_t i;
		if (this->driver->recv(buf, &buflen)) {
			//    driver.printBuffer("Received:", buf, buflen);
			Serial.print("Received:");
			for (i = 0; i < buflen; i++) Serial.print(buf[i]);
			Serial.println("");
		}
	}
};

#endif