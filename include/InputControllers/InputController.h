#ifndef INPUTCONTROLLER
#define INPUTCONTROLLER

#include <InputControllers/SteeringController.h>
#include <InputControllers/VelocityController.h>
#include <InputControllers/BrakeLightsController.h>
#include <InputControllers/TurnLightsController.h>
#include <InputControllers/HeadLightsController.h>
#include <InputControllers/RearLightsController.h>

/**
 * Tradutor de dados 
 **/
class InputController {
	private:
	float turningPoint = .0f;
	float currentVelocity = .0f;
	int direction = 0;
	int reverse = 0;
	SteeringController* steController;
	VelocityController* velController;
	HeadLightsController *headLightsController;
	TurnLightsController *turnLightsController;
	BrakeLightsController *brakeLightsController;
	RearLightsController *rearLightsController;

	public:
	InputController(
		SteeringController *steController, 
		VelocityController *velController,
		HeadLightsController *headLightsController,
		TurnLightsController *turnLightsController,
		BrakeLightsController *brakeLightsController,
		RearLightsController *rearLightsController
	)	{
		this->steController = steController;
		this->velController = velController;
		this->headLightsController = headLightsController;
		this->turnLightsController = turnLightsController;
		this->brakeLightsController = brakeLightsController;
		this->rearLightsController = rearLightsController;
	}

	void update() {
		this->velController->update();
	}
};

#endif