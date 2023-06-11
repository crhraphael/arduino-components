#ifndef INPUTCONTROLLER
#define INPUTCONTROLLER

#include <InputControllers/SteeringController.h>
#include <InputControllers/AccelerationController.h>
#include <InputControllers/BrakeLightsController.h>
#include <InputControllers/TurnLightsController.h>
#include <InputControllers/HeadLightsController.h>
#include <InputControllers/RearLightsController.h>

/**
 * Data translator
 **/
class InputController {
	private:
	float turningPoint = .0f;
	float currentAcceleration = .0f;
	int direction = 0;
	int reverse = 0;
	SteeringController* steController;
	AccelerationController* accelController;
	HeadLightsController *headLightsController;
	TurnLightsController *turnLightsController;
	BrakeLightsController *brakeLightsController;
	RearLightsController *rearLightsController;

	public:
	InputController(
		SteeringController *steController, 
		AccelerationController *accelController,
		HeadLightsController *headLightsController,
		TurnLightsController *turnLightsController,
		BrakeLightsController *brakeLightsController,
		RearLightsController *rearLightsController
	)	{
		this->steController = steController;
		this->accelController = accelController;
		this->headLightsController = headLightsController;
		this->turnLightsController = turnLightsController;
		this->brakeLightsController = brakeLightsController;
		this->rearLightsController = rearLightsController;
	}

	void update() {
		//this->accelController->update();
	}
};

#endif