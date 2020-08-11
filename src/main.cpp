#include <VelocityInputController/VelocityInputController.h>
#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/RF/RadioHeadRFImplementation.h>

#include <Translators/Wireless/RF/FS1000ATransmitterTranslator.h>
#include <Translators/Wireless/RF/FS1000AReceiverTranslator.h>
#include <Arduino.h>

VelocityInputController *velocityController;
IServoInputTranslator *servoTranslator;
IPotentiometerInputTranslator *potentiometerTranslator;
IServoImplementation *servoImpl;
FS1000ATransmitterTranslator *transmitterController;
FS1000AReceiverTranslator *receiverController;
IWirelessRFImplementation *rfImpl;

/**
 * Portas dos devices.
 */
const int SERVO_PIN = 9;
const int POT_PIN = 0;
const int VOLT_READ_PIN = 7;

const int TRASMITTER_PIN = 8;
const int RECEIVER_PIN = 3;

 
void setup() 
{ 
  Serial.begin(9600);

  pinMode(VOLT_READ_PIN, INPUT);
  const int value = analogRead( VOLT_READ_PIN );
  const float voltage = value * 5.0 / 1023.0;

  servoImpl = new ServoImplementation(SERVO_PIN);
  potentiometerTranslator = new A50KPotentiometerTranslator(POT_PIN, voltage);
  servoTranslator = new MG90SCustomTranslator(servoImpl);
  velocityController = new VelocityInputController(servoTranslator, potentiometerTranslator);

  rfImpl = new RadioHeadRFImplementation(TRASMITTER_PIN, RECEIVER_PIN, 2000);
  transmitterController = new FS1000ATransmitterTranslator(rfImpl);
  receiverController = new FS1000AReceiverTranslator(rfImpl);
} 

int send_or_receive = 1;
 
void loop() 
{ 
  if(send_or_receive == 1) {
    constexpr char* ch = "StackOverflow!";
    transmitterController->send(ch);
    send_or_receive = -1;
  } else {
    receiverController->listen();
    send_or_receive = 0;

  }
  velocityController->update();
  
  // Serial.println(velocityController->currentVelocity);
} 