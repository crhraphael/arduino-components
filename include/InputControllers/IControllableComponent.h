#ifndef ICONTROLLABLECOMPONENT
#define ICONTROLLABLECOMPONENT

class IControllableComponent {
	private:
	public:
  virtual void set(float vel) = 0;

	int MAX_ACCELERATION; 

	int SERVO_STOPPED_VALUE;
};

#endif