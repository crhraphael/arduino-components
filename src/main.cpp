#include <VelocityInputController/VelocityInputController.h>
#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>

VelocityInputController *velocityController;
IServoInputTranslator *servoTranslator;
IPotentiometerInputTranslator *potentiometerTranslator;

/**
 * Portas dos devices.
 */
const int SERVO_PIN = 0;
const int POT_PIN = 0;

 
void setup() 
{ 
  Serial.begin(9600);  
  
  servoTranslator = new MG90SCustomTranslator(SERVO_PIN);
  potentiometerTranslator = new A50KPotentiometerTranslator(POT_PIN);
  velocityController = new VelocityInputController(servoTranslator, potentiometerTranslator);
} 

 
void loop() 
{ 
  velocityController->update();
  Serial.println(velocityController->getInput());
} 