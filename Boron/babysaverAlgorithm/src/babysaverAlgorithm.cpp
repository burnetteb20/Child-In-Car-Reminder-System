/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/BryceBurnette/Documents/ParticleProjects/babysaverAlgorithm/src/babysaverAlgorithm.ino"
/*
 * Project babysaver
 * Description:
 * Author:
 * Date:
*/

void setup();
void loop();
void collect();
int randomNumber(int minVal, int maxVal);
void sendMessage(const String& body);
#line 8 "c:/Users/BryceBurnette/Documents/ParticleProjects/babysaverAlgorithm/src/babysaverAlgorithm.ino"
#define DONEPIN 7
#define VELOSTATPIN 8

String body = "Your child is in the car";  //body of SMS message to send

const int usbReadings = 2;
float usb[usbReadings];      // the readings from the usb pin
int usbIndex = 0;              // the index of the current reading
float usbTotal = 0;                  // the running total
float usbAverage = 0;                // the average

const int childReadings = 5;
float child[childReadings];      // the readings from the pressure mat
int childIndex = 0;              // the index of the current reading
float childTotal = 0;                  // the running total
float childAverage = 0;                // the average

const int tempReadings = 5;
float temp[tempReadings];      // the readings from the temperature sensor
int tempIndex = 0;              // the index of the current reading
float tempTotal = 0;                  // the running total
float tempAverage = 0;                // the average

// setup() runs once, when the device is first turned on.
void setup() 
{
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < usbReadings; thisReading++) 
  {
    usb[thisReading] = randomNumber(0, 1);
  }

  for (int thisReading = 0; thisReading < childReadings; thisReading++) 
  {
    child[thisReading] = randomNumber(0, 2);
  }

  for (int thisReading = 0; thisReading < tempReadings; thisReading++) 
  {
    temp[thisReading] = randomNumber(80, 150);
  }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() 
{
  digitalWrite(DONEPIN, HIGH);
  collect();

  childTotal = 0;
  for (int thisReading = 0; thisReading <= childReadings - 1; thisReading++) 
  {
    childTotal = childTotal + child[thisReading];
  }
  childAverage = childTotal / childReadings;    //running average

  Serial.print("The child average is:  ");
  Serial.println(childAverage);

  if (childAverage < 3)                         //if the child is in the seat
  {
    Serial.println("child in car");

    Serial.print("the usb array is:  ");
    Serial.print(usb[0]);
    Serial.print(" ");
    Serial.println(usb[1]);

    if (usb[0] == 1 && usb[1] == 0)   //check to see if the car went from on to off
    {
      sendMessage(body);
      Serial.println("Sending message because car turned off and child is in the car");
    }

    //check if the temperature is too hot or rising too fast

    if (temp[tempReadings - 1] - temp[0] >= 10)     //if temperature is rising too fast
    {
      sendMessage(body);
      Serial.println("The temperature is rising too fast");
    }

    //average for tester examples
    tempTotal = 0;
    for (int thisReading = 0; thisReading <= tempReadings - 1; thisReading++) 
    {
      tempTotal = tempTotal + temp[thisReading];
    }
    tempAverage = tempTotal / tempReadings;       //calculate running average
    
    Serial.print("The temp average is:  ");
    Serial.println(tempAverage);

    if (tempAverage >= 80 && tempAverage < 90)  //if the temp is too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temperature is too hot");
    }

    while (tempAverage >= 90) //if the temp is way too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temp is critical");
    }
  }
  digitalWrite(DONEPIN, LOW);              //toggle the done pin to let tpl know to sleep
  delay(2000);
}

void collect()
{  
  int carOn = randomNumber(0, 1);       //generate random value for if the car is on
  // Serial.print("car val: ");
  // Serial.println(carOn);
  digitalWrite(VELOSTATPIN, HIGH);     //power the velostat
  int childVal = randomNumber(0, 2);    //generate random value for if the child is in the car
  digitalWrite(VELOSTATPIN, LOW);      //turn power off to the velostat
  // Serial.print("child val: ");
  // Serial.println(childVal);
  int tempVal = randomNumber(90, 150);  //generate random value for the temperature reading
  // Serial.print("temperature: ");
  // Serial.println(tempVal);
  

  //check if the child is in the seat

  childTotal = childTotal - child[childIndex];  //drop the last value
  child[childIndex] = childVal;                 //get the current value
  childTotal = childTotal + child[childIndex];  //add to total
  childIndex++;                                 //increment the index
  

  if (childIndex >= childReadings)  // ...wrap around to the beginning:
  {
    childIndex = 0;  
  }
  
  //car on/off check
  
  usb[usbIndex] = carOn;  //read the value
  usbIndex++;   //increase the index
  

  if (usbIndex >= usbReadings)  // ...wrap around to the beginning:
  {
    usbIndex = 0;  
  }

  //Tempearature readings 
  tempTotal = tempTotal - temp[tempIndex];    //drop the last value
  temp[tempIndex] = tempVal;                  //get the current value
  tempTotal = tempTotal + temp[tempIndex];    //add to total
  tempIndex++;                                //increment the index
  
  if (tempIndex >= tempReadings)  // ...wrap around to the beginning:
  {
    tempIndex = 0;  
  }
  delay(100);
}

int randomNumber(int minVal, int maxVal)              //function to generate random values within a range
{
  return rand() % (maxVal-minVal+1) + minVal;
}

void sendMessage(const String& body)            //function that triggers twilio webhook
{
  Particle.publish("twilio_sms", body, PRIVATE);
  Serial.println("SendingMessage");
}