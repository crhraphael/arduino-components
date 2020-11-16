#ifndef ICONTROLLABLECOMPONENT
#define ICONTROLLABLECOMPONENT

class IControllableComponent {
	private:
	public:
  virtual void set(float vel) = 0;

	const int MAX_ACCELERATION; 

	const int SERVO_STOPPED_VALUE;
};

#endif