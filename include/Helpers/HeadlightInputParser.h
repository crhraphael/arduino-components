#ifndef HEADLIGHTINPUTPARSER
#define HEADLIGHTINPUTPARSER

#include <Helpers/IInputParser.h>
#include <Arduino.h>

class HeadlightInputParser : public IInputParser {
  private:
	char debug[10] = "\0";

  public:
	void parse(char *buff, char result[4], char flagToCompare) {
		if(strcmp(buff, debug) != 0) {
			const char payloadFlag = char(buff[0]);


			if(payloadFlag == flagToCompare) {
				const int lenght = strlen(buff);
				char target[4] = "\0";
				getSubString(buff, target, 2, lenght);
				result = target;
			}
		}
	}

	void parse(char *buff, float &result, char flagToCompare) 
	{

	}

	void parse(char *buff, float *result, char flagToCompare) {}
	int getSubString(char *source, char *target,int from, int to) {
		int length=0;
		int i=0,j=0;
		
		//get length
		while(source[i++]!='\0')
			length++;
		
		if(from<0 || from>length){
			return 1;
		}
		if(to>length){
			return 1;
		}	
		
		for(i=from,j=0;i<=to;i++,j++){
			target[j]=source[i];
		}
		
		//assign NULL at the end of string
		target[j]='\0'; 
		
		return 0;	
	}
};
#endif
