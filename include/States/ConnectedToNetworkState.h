#ifndef CONNECTEDTONETWORKSTATE
#define CONNECTEDTONETWORKSTATE

#include <States/IState.h>
#include <examples/ESP12EVehicleExample.h>

class ConnectedToNetworkState : IState {
	private:
	ESP12EVehicleExample* currentExample;

	public:	

	void start() {
		this->currentExample->resetControllables();
		this->currentExample->wifiService->WriteIP();
		this->currentExample->websocketService->open();
	}

	void exit() {
		
	}

	void update() {
		this->currentExample->boardStatusLED->blink(500);


		if(this->currentExample->websocketService->IsOpen()) return;
		
		// this->websocketService->listen();

		// if(!this->websocketService->HasClientsConnected()) {
		// 	this->boardStatusLED->blink(1000);
		// 	this->resetControllables();
		// 	return;
		// } 

		// if(!this->hasSentCarInfo) {
		// 	this->websocketService->send(vehicleInfo);
		// 	this->hasSentCarInfo = true;
		// 	this->boardStatusLED->set(LED_ON);
		// }


		// this->accelController->update(this->websocketService);
		// this->steController->update(this->websocketService);
	}
};

#endif