/*
 * Project  babysaver
 * Author:  Bryce Burnette, Jack Robey, Karlens Joas
 * Date:    2020
*/

#include <adafruit-sht31.h>

//constant value definitions
#define USBPIN 18           //analog pin that receives input from the USB pin
#define DONEPIN 8           //digital pin that outputs to the sleep breakout board
#define VELOSTATPIN 16      //analog pin that reads the output from the pressure mat
#define VELOSTATPOWER 6     //digital pin that ouputs power to the velostat pin
#define DELAYVAL 100        //value for delay function
#define CHILD 3             //voltage threshold to check for child
#define TEMP1 80            //first temperature threshold
#define TEMP2 90            //CRITICAL temperature threshold
#define TEMPRISING  10      //difference threshold for temperature increase rate

String body = "Your child is in the car";  //body of SMS message to send

//initialize storage arrays to be filled by data collection
const int usbReadings = 2;            //lenth of the storage array
float usb[usbReadings];               //the readings from the usb pin
int usbIndex = 0;                     //the index of the current reading
float usbTotal = 0;                   //the running total
float usbAverage = 0;                 //the average

const int childReadings = 5;          //length of the storage array
float child[childReadings];           //the readings from the pressure mat
int childIndex = 0;                   //the index of the current reading
float childTotal = 0;                 //the running total
float childAverage = 0;               //the average

const int tempReadings = 5;
float temp[tempReadings];             //the readings from the temperature sensor
int tempIndex = 0;                    //the index of the current reading
float tempTotal = 0;                  //the running total
float tempAverage = 0;                //the averagea

Adafruit_SHT31 sht31 = Adafruit_SHT31();    //initialize the temperature sensor

// setup() runs once, when the device is first turned on.
void setup() 
{
  Serial.begin(9600);     //Initialize serial monitor
  sht31.begin(0x44);      //Turn on the temperature sensor

  //fill the storage arrays with the current reading from all of the hardware
  for (int thisReading = 0; thisReading < usbReadings; thisReading++) 
  {
    usb[thisReading] = analogRead(USBPIN);
  }
  digitalWrite(VELOSTATPOWER, HIGH);
  for (int thisReading = 0; thisReading < childReadings; thisReading++) 
  {
    child[thisReading] = analogRead(VELOSTATPIN);
  }
  digitalWrite(VELOSTATPOWER, LOW);
  for (int thisReading = 0; thisReading < tempReadings; thisReading++) 
  {
    temp[thisReading] = sht31.readTemperature();
  }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() 
{
  digitalWrite(DONEPIN, HIGH);          //toggle the done pin
  collect();                    //collect all of the necessary data

  //check if the child is in the seat

  //iterate through the storage array of pressure mat values
  childTotal = 0;
  for (int thisReading = 0; thisReading <= childReadings - 1; thisReading++) 
  {
    childTotal = childTotal + child[thisReading];
  }
  childAverage = childTotal / childReadings;    //running average

  Serial.print("The child average is:  ");
  Serial.println(childAverage);

  if (childAverage < CHILD)                         //if the child is in the seat
  {
    // Serial.println("child in car");
    // Serial.print("the usb array is:  ");
    // Serial.print(usb[0]);
    // Serial.print(" ");
    // Serial.println(usb[1]);

    if (usb[0] == 1 && usb[1] == 0)   //check to see if the car went from on to off
    {
      sendMessage(body);
      Serial.println("Sending message because car turned off and child is in the car");
    }

    //check if the temperature is too hot or rising too fast

    if (temp[tempReadings - 1] - temp[0] >= TEMPRISING)     //if temperature is rising too fast
    {
      sendMessage(body);
      Serial.println("The temperature is rising too fast");
    }

    if (temp[tempReadings - 1] >= TEMP1 && tempAverage < TEMP2)  //if the temp is too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temperature is too hot");
    }

    while (temp[tempReadings - 1] >= 90) //if the temp is way too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temp is critical");
      collect();
      digitalWrite(DONEPIN, LOW);
      digitalWrite(DONEPIN, HIGH);
      delay(DELAYVAL);
    }
  }
  digitalWrite(DONEPIN, LOW);              //toggle the done pin to let TPL5111 know to sleep
  delay(DELAYVAL);
}

/*
Function that collects all of data from the temperature sensor
pressure mat, and usb, and attaches the value to the end of the 
storage array, dropping the first value
*/
void collect()
{  
  int carOn = analogRead(USBPIN);       //generate random value for if the car is on
  // Serial.print("car val: ");
  // Serial.println(carOn);
  digitalWrite(VELOSTATPOWER, HIGH);     //power the velostat
  int childVal = analogRead(VELOSTATPIN);    //generate random value for if the child is in the car
  digitalWrite(VELOSTATPOWER, LOW);      //turn power off to the velostat
  // Serial.print("child val: ");
  // Serial.println(childVal);
  int tempVal = sht31.readTemperature();  //generate random value for the temperature reading
  // Serial.print("temperature: ");
  // Serial.println(tempVal);

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
  delay(DELAYVAL);
}

/*
Function that triggers the Twilio Webhook by publishing to the
Particle Cloud with the desired message

Input: String with the desired text message body
*/
void sendMessage(const String& body)            //function that triggers twilio webhook
{
  Particle.publish("twilio_sms", body, PRIVATE);
  Serial.println("SendingMessage");
}