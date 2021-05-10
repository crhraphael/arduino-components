#ifndef HEADLIGHTSCONTROLLER
#define HEADLIGHTSCONTROLLER

#include <Arduino.h>

class HeadLightsController {
	IControllableComponent *frontLeftHeadlightLED;
	IControllableComponent *frontRightHeadlightLED;
	IControllerComponent *controllerComponent;
	IInputParser *inputParser;
	char inputValue[4];

	public: 
	HeadLightsController(
		IControllableComponent *frontLeftHeadlightLED, 
		IControllableComponent *frontRightHeadlightLED,
		IControllerComponent *controllerComponent,
		IInputParser *inputParser
	) {
		this->frontLeftHeadlightLED = frontLeftHeadlightLED;
		this->frontRightHeadlightLED = frontRightHeadlightLED;
		this->controllerComponent = controllerComponent;
		this->inputParser = inputParser;
		this->inputValue[0] = char('\0');
	}

	void update() {
		// char buff[10] = "\0";

		// this->controllerComponent->read(buff);
		// this->inputParser->parse(buff, this->inputValue, 'a');
		// if('buff-flag' == 'h') {
		// 	if('buff-val' == '11') {}
		// 	if('buff-val' == '00') {}
		// }
		// this->frontRightHeadlightLED->set(LED_ON);
	}
};

#endif