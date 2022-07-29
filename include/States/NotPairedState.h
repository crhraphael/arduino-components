#ifndef NOTPAIREDSTATE
#define NOTPAIREDSTATE

#include <States/IState.h>
#include <examples/ESP12EVehicleExample.h>

class NotPairedState : IState {
	private:
	ESP12EVehicleExample* currentExample;

	public:	

	void start() {
		this->currentExample->resetControllables();
	}

	void exit() {
		
	}

	void update() {
	
		this->currentExample->websocketService->listen();

		this->currentExample->boardStatusLED->blink(1000);
		if(this->currentExample->websocketService->HasClientsConnected()) {
			return;
		} 


		// if(!this->websocketService->IsOpen()) {
		// 	this->boardStatusLED->blink(500);
		// 	this->wifiService->WriteIP();
		// 	this->websocketService->open();
		// 	this->resetControllables();
		// 	return;
		// }

	}
};

#endif