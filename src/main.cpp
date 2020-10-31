#include <examples/ESP12EVehicleExample.h>
//#include <examples/ESP32LolinLEDExample.h>


ESP12EVehicleExample* impl = new ESP12EVehicleExample();
// ESP32LolinLEDExample* impl = new ESP32LolinLEDExample();

void setup() 
{ 
  impl->setup();
}  
 
void loop()
{ 
  impl->loop();
} 
