#ifndef ICONTROLLABLECOMPONENT
#define ICONTROLLABLECOMPONENT

class IControllableComponent {
	private:
	public:
  virtual void setVelocity(float vel,int dir) = 0;
};

#endif