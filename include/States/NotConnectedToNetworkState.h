#ifndef NOTCONNECTEDTONETWORKSTATE
#define NOTCONNECTEDTONETWORKSTATE

#include <States/IState.h>
#include <examples/ESP12EVehicleExample.h>

class NotConnectedToNetworkState : IState {
	private:
	ESP12EVehicleExample* currentExample;

	IWirelessWiFiImplementation* wifiService;
	CommonLED* boardStatusLED;

	SteeringController *steController;
	AccelerationController *accelController;

	public:	

	void start() {
		this->currentExample->resetControllables();
	}

	void exit() {
		
	}

	/**
	 * Resets controllables to a default value.
	 **/
	void resetControllables() {
		this->accelController->setSpeed(0);
		this->steController->setSpeed(0);
	}

	void update() {
		this->boardStatusLED->blink(250);
		this->resetControllables();

		// TODO: ChangeState
		if(this->currentExample->wifiService->GetStatus() == wl_status_t::WL_CONNECTED) return; 
	}
};

#endif