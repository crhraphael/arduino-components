#ifndef TURNLIGHTSCONTROLLER
#define TURNLIGHTSCONTROLLER

#include <Arduino.h>

class TurnLightsController {
	int frontLeftTurnSignalLED;
	int frontRightTurnSignalLED;
	int backLeftTurnSignalLED;
	int backRightTurnSignalLED;

	void setTurnLights(int direction) {
		int rightSwitch = (int)(direction > 0);
		int leftSwitch = (int)(direction < 0);

		digitalWrite(this->frontLeftTurnSignalLED, leftSwitch);
		digitalWrite(this->frontRightTurnSignalLED, leftSwitch);
		digitalWrite(this->backLeftTurnSignalLED, rightSwitch);
		digitalWrite(this->backRightTurnSignalLED, rightSwitch);
	}
};

#endif