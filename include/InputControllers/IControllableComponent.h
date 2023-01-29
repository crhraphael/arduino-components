#ifndef ICONTROLLABLECOMPONENT
#define ICONTROLLABLECOMPONENT


/**
 * All devices that can be controlled via a pin port or wifi must implement this contract.
 * As it represents a device that can be controlled. 
*/
class IControllableComponent {
	private:
	public:
  virtual void set(float vel) = 0;
  virtual int get() = 0;
	virtual void setRaw(int vel) = 0;
	virtual int getMaxAcceleration() = 0; 

	virtual int getServoNeutralValue() = 0;
};

#endif