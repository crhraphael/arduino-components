#include <examples/ESP12EVehicleExample.h>
//#include <examples/ESP32LolinLEDExample.h>
// #include <examples/NonClassExample.h>
// #include <examples/ESP12EVehicleExample.h>

ESP12EVehicleExample impl;
//ESP32LolinLEDExample* implLED = new ESP32LolinLEDExample();

void setup() 
{ 
	impl = ESP12EVehicleExample();
  impl.setup();
}  
 
void loop()
{ 
  impl.loop();
} 
