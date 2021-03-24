#ifndef ICONTROLLERCOMPONENT
#define ICONTROLLERCOMPONENT

class IControllerComponent {
	private:
	public:
	IControllerComponent(int maxValue): MAX_VALUE(maxValue)	{};
	IControllerComponent(): MAX_VALUE(0)	{};
	virtual void read(char *buff) = 0;
	const int MAX_VALUE;
};

#endif