#ifndef RADIOHEADRFIMPLEMENTATION
#define RADIOHEADRFIMPLEMENTATION

#include <Implementations/Wireless/RF/IWirelessRFImplementation.h>
#include <RH_ASK.h>
#include <SPI.h>

/**
 * TODO: Ver necessidade de separar receiver e transmitter em arquivos distintos.
 * 
 * RadioHead e uma lib para comunicacao Wireless.
 * Esta implementacao usa apenas o recurso de Radio Frequencia da lib.
 * 
 * ATENCAO: Algumas libs (Servo.h) causam conflito de constantes (timer).
 * Caso aconteca visite o link `TIMER_CONFLICT_FIX`.
 * 
 * ------LINKS------`
 * 
 * TIMER_CONFLICT_FIX: https://arduino.stackexchange.com/questions/35721/arduino-uno-not-including-two-header-files-at-the-same-time`
 */
class RadioHeadRFImplementation: public IWirelessRFImplementation, public RH_ASK {
	private:
  RH_ASK driver;

	public:
	RadioHeadRFImplementation(
		int transmitterPin, 
		int receiverPin,
		int bitsPerSec)
	{
		this->driver = RH_ASK(bitsPerSec, receiverPin, transmitterPin);
  	if(!this->driver.init()) Serial.println("init failed");
	};

	void listen()
	{
		uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
		uint8_t buflen = sizeof(buf);
		uint8_t i;
		if(this->driver.available()) {
			Serial.println("trying to read...");
			Serial.println(this->driver.recv(buf, &buflen));
			if (this->driver.recv(buf, &buflen)) {
				Serial.print("Received:");
				for (i = 0; i < buflen; i++) Serial.print(buf[i]);
				Serial.println("");
			}

		}
	}

	void send(const char *message)
	{
		uint8_t* msg = (uint8_t *)message;
		bool hasSent = this->driver.send(msg, strlen(message));
		this->driver.waitPacketSent();
		Serial.println(this->driver.available());
	}
};

#endif