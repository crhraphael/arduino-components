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
const int VOLT_READ_PIN = 7;

 
void setup() 
{ 
  Serial.begin(9600);

  pinMode(VOLT_READ_PIN, INPUT);
  const int value = analogRead( VOLT_READ_PIN );
  const int voltage = value * 5.0 / 1023.0;

  servoImpl = new ServoImplementation(SERVO_PIN);
  potentiometerTranslator = new A50KPotentiometerTranslator(POT_PIN, voltage);
  servoTranslator = new MG90SCustomTranslator(servoImpl);
  velocityController = new VelocityInputController(servoTranslator, potentiometerTranslator);
} 

 
void loop() 
{ 
  velocityController->update();
  Serial.println(velocityController->currentVelocity);
} 