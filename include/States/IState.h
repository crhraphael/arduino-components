#ifndef ISTATE
#define ISTATE

class IState {
	public:
	virtual void initialize() = 0;
	virtual void update() = 0;

	virtual ~IState() = 0;


};
IState::~IState() {};

#endif