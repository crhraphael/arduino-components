#ifdef _SS_MAX_RX_BUFF
#ifndef BTSOFTWARESERIALIMPLEMENTATION
#define BTSOFTWARESERIALIMPLEMENTATION

#include <Implementations/Wireless/Bluetooth/IBluetoothImplementation.h>
#include <SoftwareSerial.h>

/**
 * Implementacao de conexão bluetooth via SoftwareSerial.h
 **/
class BTSoftwareSerialImplementation: public IBluetoothImplementation {
	private:
  SoftwareSerial driver;
	char buffer[_SS_MAX_RX_BUFF] = { '\0' };
  int cursor = 0;
	const char BUFFER_END_CHAR = '.';
	bool receivedWholeMessage = false;

	public:
	BTSoftwareSerialImplementation(
		int transmitterPin, 
		int receiverPin,
		int serialRate,
		char bufferEndChar
	): 
		driver(transmitterPin, receiverPin),
		BUFFER_END_CHAR(bufferEndChar)
	{
		this->driver.begin(9600);
	};

	void reset() {
		this->buffer[_SS_MAX_RX_BUFF] = { '\0' };
		this->buffer[_SS_MAX_RX_BUFF - 1] = this->BUFFER_END_CHAR;
		this->cursor = 0;
		this->receivedWholeMessage = false;
	}

	bool isFillingBuffer() {
		bool isAvailable = (bool)this->driver.available();
		if(isAvailable){ 
			char *currentChar = new char(this->driver.read());

			this->receivedWholeMessage = (strcmp(&this->BUFFER_END_CHAR, currentChar) == 0);

			this->buffer[this->cursor] = (this->receivedWholeMessage)
			  ? '\0'
				: currentChar[0];
			
			this->cursor++;
		}
		return new bool(isAvailable);
	}


	void listen(char *buf)
	{
		if(!this->isFillingBuffer()) {
			if(this->receivedWholeMessage) {
				int i = 0;
				int max = this->cursor;

				for(i = 0; (i < max); i = i+1) buf[i] = char(this->buffer[i]);
				this->reset();
			}
		}
	}
};

#endif
#endif