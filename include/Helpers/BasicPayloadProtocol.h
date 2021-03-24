#ifndef BASICPAYLOADPROTOCOL
#define BASICPAYLOADPROTOCOL
#include <string.h>
#include <stdlib.h>

int  getSubString(char *source, char *target,int from, int to)
{
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

// class BasicPayloadProtocol {
// 	private:
// 	int accelerationValue = 0;
// 	int directionValue = 0;
// 	public:
// 	BasicPayloadProtocol(char *payload) {
// 		const char accelerationFlag = 'a';
// 		if(strcmp(&payload[0], &accelerationFlag) == 0) {
// 			const int lenght = strlen(payload);
// 			char *target = "\0";
// 			getSubString(payload, target, 2, lenght);
// 			const int value = atoi(target);

// 			this->accelerationValue = value;
// 		}

// 		const char directionFlag = 'd';
// 		if(strcmp(&payload[0], &directionFlag) == 0) {
// 			const int lenght = strlen(payload);
// 			char *target = "\0";
// 			getSubString(payload, target, 2, lenght);
// 			const int value = atoi(target);

// 			this->directionValue = value;
// 		}
// 	}

// 	int getAcceleration() {
// 		return this->accelerationValue;
// 	}

// 	int getDirection() {
// 		return this->directionValue;
// 	}
// };

#endif