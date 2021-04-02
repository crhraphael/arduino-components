// #include <examples/ESP12EVehicleExample.h>
//#include <examples/ESP32LolinLEDExample.h>
// #include <examples/NonClassExample.h>
#include <examples/ESP12EVehicleExample.h>

ESP12EVehicleExample* impl;
//ESP32LolinLEDExample* implLED = new ESP32LolinLEDExample();

void setup() 
{ 
	impl = new ESP12EVehicleExample();
  impl->setup();
  //implLED->setup();
}  
 
void loop()
{ 
  impl->loop();
  //implLED->loop();
} 
