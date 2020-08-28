#ifndef REARLIGHTSCONTROLLER
#define REARLIGHTSCONTROLLER

#include <Arduino.h>

class RearLightsController {
	int leftRearLED;
	int rightRearLED;

	void setRearLights(int state) {
		digitalWrite(this->leftRearLED, state);
		digitalWrite(this->rightRearLED, state);
	}
};

#endif