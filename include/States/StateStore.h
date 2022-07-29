#ifndef STATESTORE
#define STATESTORE

#include <States/IState.h>

class StateStore {
	private:
	IState *currState;
	

	public:
	void initialize() {

	}

	void update() {
		currState->update();
	}
};

#endif