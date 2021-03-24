#ifndef IINPUTPARSER
#define IINPUTPARSER

class IInputParser {
  private:
  public:
  virtual ~IInputParser() = 0;
	virtual void parse(char *buff, float &result, char flagToCompare)) = 0;
};

IInputParser::~IInputParser() {};
#endif
