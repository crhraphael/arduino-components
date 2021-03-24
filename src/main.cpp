// #include <examples/ESP12EVehicleExample.h>
// #include <examples/ESP32LolinLEDExample.h>
#include <examples/NonClassExample.h>

NonClassExample* impl;
// ESP32LolinLEDExample* implLED = new ESP32LolinLEDExample();

void setup() 
{ 
	impl = new NonClassExample();
  impl->setup();
  // implLED->setup();
}  
 
void loop()
{ 
  impl->loop();
  // implLED->loop();
} 
