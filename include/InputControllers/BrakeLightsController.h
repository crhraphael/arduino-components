#ifndef BRAKELIGHTSCONTROLLER
#define BRAKELIGHTSCONTROLLER

#include <Arduino.h>

class BrakeLightsController {
	int backLeftBrakeLED;
	int backRightBrakeLED;
	
	void setBrakeLights(int state) {
		digitalWrite(this->backLeftBrakeLED, state);
		digitalWrite(this->backRightBrakeLED, state);
	}
};

#endif