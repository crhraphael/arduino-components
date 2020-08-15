#ifndef INPUTCONTROLLER
#define INPUTCONTROLLER

#include <InputControllers/SteeringController.h>
#include <InputControllers/VelocityController.h>
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

	public:
	InputController(
		SteeringController *steController, 
		VelocityController *velController)
	{
		this->steController = steController;
		this->velController = velController;
	}

	void update() {
		this->velController->update();
	}
};

#endif