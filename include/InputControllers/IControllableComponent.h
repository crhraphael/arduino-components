#ifndef ICONTROLLABLECOMPONENT
#define ICONTROLLABLECOMPONENT

class IControllableComponent {
	private:
	public:
  virtual void set(float vel) = 0;

	virtual int getMaxAcceleration() = 0; 

	virtual int getServoNeutralValue() = 0;
};

#endif