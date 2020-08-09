#include <VelocityInputController/VelocityInputController.h>
#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>
#include <Implementations/Servo/ServoImplementation.h>
#include <Arduino.h>

VelocityInputController *velocityController;
IServoInputTranslator *servoTranslator;
IPotentiometerInputTranslator *potentiometerTranslator;
IServoImplementation *servoImpl;

/**
 * Portas dos devices.
 */
const int SERVO_PIN = 9;
const int POT_PIN = 0;

 
void setup() 
{ 
  Serial.begin(9600);  
  servoImpl = new ServoImplementation(SERVO_PIN);
  servoTranslator = new MG90SCustomTranslator(servoImpl);
  potentiometerTranslator = new A50KPotentiometerTranslator(POT_PIN);
  velocityController = new VelocityInputController(servoTranslator, potentiometerTranslator);
} 

 
void loop() 
{ 
  velocityController->update();
  Serial.println(velocityController->getInput());
} 