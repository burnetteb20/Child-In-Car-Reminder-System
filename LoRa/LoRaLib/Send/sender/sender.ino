/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>
#include "Adafruit_Si7021.h"

//define the pins used by the transceiver module
#define ss 8
#define rst 4
#define dio0 3

//define the pins reading the voltage from the different sensors and voltage dividers
#define childPin
#define batPin 
#define usbPin

//define variables to be checked against
int childSensVal = 0;
int batValue = 0;
int usbValue = 0;

Adafruit_Si7021 sensor = Adafruit_Si7021();   //initialize temperature sensor

void setup() 
{
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //915E6 for North America
  while (!LoRa.begin(905E6)) 
  {
    Serial.println(".");
    delay(500);
  }

  // The sync word is supposed to assure that you don't get LoRa messages from other LoRa transceivers
  LoRa.setSyncWord(0x13);
  Serial.println("LoRa Initializing OK!");
  if (!sensor.begin()) 
    {
      Serial.println("Did not find Temp sensor!");
      while (true);
    }
    else
    {
      Serial.println("Temp sensor ready");
    }

  //Set transmission power to maximum
  LoRa.setTxPower(20);
}

void loop() 
{

  //Check to see if the child is in car seet (infrared voltage or pressure mat)
  //Check to see if  the usb port goes from power to no power
  //Check for battery life
  
  Serial.println(proximity);
  if (proximity == LOW)
  {
    Serial.println("Switch Closed");
    Serial.println(sensor.readTemperature());
    if (sensor.readTemperature() > 24)
    {
  
      float temp = sensor.readTemperature();
      float fTemp = temp*(9.0/5.0) + 32.0;
      Serial.print("Sending packet: ");
      Serial.println(counter);
  
      //Send LoRa packet to receiver
      LoRa.beginPacket();
      LoRa.print("Child in car ");
      LoRa.print(fTemp);
      LoRa.print("F");
      LoRa.endPacket();
     }
  }
  else
  {
    LoRa.sleep();
    Serial.println("Asleep");
    delay(1000);
  }
    delay(1000);
}

bool childInSeat()
{
  //returns true if the child is in the seat
  if (analogRead(childPin) >= childSensVal)
  {
    return true
  }
  else
  {
    return false
  }
}

bool checkUSB()
{
  //returns true if usb is plugged in
  if (analogRead(usbPin) >= usbValue)
  {
    return true
  }
  else
  {
    return false
  }
}

bool checkBat()
{
  //returns true if battery does not need charging
  if (analogRead(batPin) <= batValue)
  {
    return false
  }
  else
  {
    return true
  }
}

void sleepTimer()
{
  //makes the breakout board put microcontroller to sleep
  
}

void sendReminder()
{
  //Sends a single alert if parent turns off car with child in seat
  LoRa.beginPacket();
  LoRa.print("Child in car");
  LoRa.endPacket();
}

void sendMessage()
{
  //sends a message if the child is warm or getting warm
  float temp = sensor.readTemperature();
  float fTemp = temp*(9.0/5.0) + 32.0;
  Serial.print("Sending packet: ");
  LoRa.beginPacket();
  LoRa.print("Your Child is Getting Hot ");
  LoRa.print(fTemp);
  LoRa.print("F");
  LoRa.endPacket();
}

void sendCritical
{
  //sends repeated messages if the child is getting hot or is already hot
  int i = 0;
  while (i <= 10)
  {
    float temp = sensor.readTemperature();
    float fTemp = temp*(9.0/5.0) + 32.0;
    Serial.print("Sending packet: ");
    LoRa.beginPacket();
    LoRa.print("Your Child is Hot! ");
    LoRa.print(fTemp);
    LoRa.print("F");
    LoRa.endPacket();
    i++;
    delay(5000);
  }
}
