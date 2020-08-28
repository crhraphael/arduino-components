#include <examples/MotorBluetoothExample.h>

MotorBluetoothExample* impl = new MotorBluetoothExample();

const int LED = 6;

void setup() 
{ 
  // pinMode(LED, OUTPUT);
  // digitalWrite(LED, LOW);
  impl->setup();
} 
 
void loop()
{ 
  impl->loop();
} 