#include <Translators/Servo/MG90S-DriverOnly/MG90SCustomTranslator.h>
#include <Translators/Potentiometer/A50K/A50KPotentiometerTranslator.h>

#include <Implementations/Servo/ServoImplementation.h>
#include <Implementations/Wireless/RF/RadioHeadRFImplementation.h>
#include <Implementations/Wireless/Bluetooth/BTSoftwareSerialImplementation.h>

#include <Translators/Wireless/RF/FS1000ATransmitterTranslator.h>
#include <Translators/Wireless/RF/FS1000AReceiverTranslator.h>
#include <Translators/Wireless/Bluetooth/HC06Translator.h>

#include <InputControllers/InputController.h>
#include <InputControllers/VelocityController.h>
#include <InputControllers/SteeringController.h>

#include <Arduino.h>

IControllableComponent *servoComponent;
IControllerComponent *potentiometerComponent;
IControllerComponent *bluetoothComponent;

IServoImplementation *servoImpl;
IWirelessRFImplementation *rfImpl;
IBluetoothImplementation *btImpl;

FS1000ATransmitterTranslator *transmitterController;
FS1000AReceiverTranslator *receiverController;


InputController *inputController;
SteeringController *steController;
VelocityController *velController;

/**
 * Portas dos devices.
 */
const int SERVO_PIN = 9;
const int POT_PIN = 0;
const int VOLT_READ_PIN = 7;

const int TRANSMITTER_PIN = 2;
const int RECEIVER_PIN = 3;

const int DEFAULT_BAULD_RATE = 9600;
 
void setup() 
{ 
  Serial.begin(DEFAULT_BAULD_RATE);

  //pinMode(VOLT_READ_PIN, INPUT);
  //const int value = analogRead( VOLT_READ_PIN );
  //const float voltage = value * 5.0 / 1023.0;


  servoImpl = new ServoImplementation(SERVO_PIN);
  servoComponent = new MG90SCustomTranslator(servoImpl);

  // potentiometerComponent = new A50KPotentiometerTranslator(POT_PIN, voltage, 1024);

  btImpl = new BTSoftwareSerialImplementation(
    TRANSMITTER_PIN, 
    RECEIVER_PIN, 
    DEFAULT_BAULD_RATE);    
  bluetoothComponent = new HC06Translator(btImpl, 1000);

  velController = new VelocityController(servoComponent, bluetoothComponent);
  steController = new SteeringController();
  inputController = new InputController(steController, velController);

  //rfImpl = new RadioHeadRFImplementation(TRASMITTER_PIN, RECEIVER_PIN, 2000);
  //transmitterController = new FS1000ATransmitterTranslator(rfImpl);
  //receiverController = new FS1000AReceiverTranslator(rfImpl);

} 

int send_or_receive = 1;
 
void loop()
{ 
  inputController->update();
  //btImpl->listen();
  // Serial.println(velController->getCurrentVelocity());
} 