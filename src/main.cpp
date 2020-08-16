#include <examples/MotorBluetoothExample.h>

MotorBluetoothExample* impl = new MotorBluetoothExample();
void setup() 
{ 
  impl->setup();
} 

int send_or_receive = 1;
 
void loop()
{ 
  impl->loop();

} 