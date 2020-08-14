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
	char buffer[_SS_MAX_RX_BUFF];
  int cursor = 0;

	public:
	BTSoftwareSerialImplementation(
		int transmitterPin, 
		int receiverPin,
		int serialRate)
	: driver(transmitterPin, receiverPin)
	{
		this->driver.begin(9600);
	};

	void reset() {
		uint8_t i;
		for(i = 0; i < _SS_MAX_RX_BUFF; i++) this->buffer[i] = '\0';
		this->cursor = 0;
	}

	bool isFillingBuffer() {
		bool isAvailable = this->driver.available();
		if(isAvailable){ 
			char currentChar(this->driver.read());
			this->buffer[this->cursor] = currentChar;
			this->cursor += 1;
		}

		return new bool(isAvailable);
	}

	char* getMessage() {
		uint8_t i;
		char msg[this->cursor - 7];
		Serial.print(this->buffer);

		for(i = 0; i < this->cursor; i++) msg[i] = this->buffer[i];

		return new char(*msg);
	}

	char* listen()
	{
		if(this->isFillingBuffer()) return '\0';		
    char* msg = this->getMessage();
		this->reset();

		return msg;
	}
};

#endif