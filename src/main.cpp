#include <examples/ESP12EVehicleExample.h>
#include <examples/ESP32LolinLEDExample.h>

ESP12EVehicleExample* impl = new ESP12EVehicleExample();
ESP32LolinLEDExample* implLED = new ESP32LolinLEDExample();

void setup() 
{ 
  impl->setup();
  implLED->setup();
}  
 
void loop()
{ 
  impl->loop();
  implLED->loop();
} 
