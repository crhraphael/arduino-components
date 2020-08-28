#ifndef HEADLIGHTSCONTROLLER
#define HEADLIGHTSCONTROLLER

#include <Arduino.h>

class HeadLightsController {
	int frontLeftHeadlightLED;
	int frontRightHeadlightLED;
	int backLeftHeadlightLED;
	int backRightHeadlightLED;

	void setHeadlights(int state, int intensity) {
		int stt = (state * intensity) * 255;
		analogWrite(this->frontLeftHeadlightLED, stt);
		analogWrite(this->frontRightHeadlightLED, stt);
		analogWrite(this->backLeftHeadlightLED, stt);
		analogWrite(this->backLeftHeadlightLED, stt);
	}
};

#endif