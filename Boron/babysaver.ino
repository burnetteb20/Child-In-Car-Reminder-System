/*
 * Project babysaver
 * Description:
 * Author:
 * Date:
 */

String body = "Your child is in the car";  //body of SMS message to send
String bodyCritical = "Your child is in the car and it is too hot! Call 911 if necessary. Please send respons message of anything and go get them"; //body of critical sms prompting response

const int usbReadings = 2;
float usb[usbReadings];      // the readings from the usb pin
int usbIndex = 0;              // the index of the current reading
float usbTotal = 0;                  // the running total
float usbAverage = 0;                // the average

const int childReadings = 10;
float child[childReadings];      // the readings from the pressure mat
int childIndex = 0;              // the index of the current reading
float childTotal = 0;                  // the running total
float childAverage = 0;                // the average

const int tempReadings = 10;
float temp[tempReadings];      // the readings from the temperature sensor
int tempIndex = 0;              // the index of the current reading
float tempTotal = 0;                  // the running total
float tempAverage = 0;                // the average

// setup() runs once, when the device is first turned on.
void setup() 
{
  //initialize all the arrays to be filled with zero
  for (int thisReading = 0; thisReading < usbReadings; thisReading++) 
  {
    usb[thisReading] = 0;
  }

  for (int thisReading = 0; thisReading < childReadings; thisReading++) 
  {
    child[thisReading] = 0;
  }

  for (int thisReading = 0; thisReading < tempReadings; thisReading++) 
  {
    temp[thisReading] = 0;
  }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() 
{
  int carOn = randomNumber(0, 1);       //generate random value for if the car is on
  Serial.print("car val");
  Serial.println(carOn);
  int childVal = randomNumber(0, 5);    //generate random value for if the child is in the car
  Serial.print("child val");
  Serial.println(childVal);
  int tempVal = randomNumber(70, 150);  //generate random value for the temperature reading
  Serial.print("temperature");
  Serial.println("tempVal");

  //check if the child is in the seat

  childTotal = childTotal - child[childIndex];  //drop the last value
  child[childIndex] = childVal;                 //get the current value
  childTotal = childTotal + child[childIndex];  //add to total
  childIndex++;                                 //increment the index

  if (childIndex >= childReadings)  // ...wrap around to the beginning:
  {
    childIndex = 0;  
  }

  childAverage = childTotal / childReadings;    //get the running average
  Serial.print("The child average is:  ");
  Serial.println(childAverage);

  if (childAverage < 3)                         //if the child is in the seat
  {
    Serial.println("child in car");

      //car on/off check

      usb[usbIndex] = carOn;  //read the value
      usbIndex++;   //increase the index

      if (usbIndex >= usbReadings)  // ...wrap around to the beginning:
      {
        usbIndex = 0;  
      }

      Serial.print("the usb array is:  ");
      Serial.print(usb[0]);
      Serial.println(usb[1]);

      if (usb[0] == 1 && usb[1] == 0)   //check to see if the car went from on to off
      {
        sendMessage(body);
        Serial.println("Sending message because car turned off");
      }

    //check if the temperature is too hot or rising too fast

    tempTotal = tempTotal - temp[tempIndex];    //drop the last value
    temp[tempIndex] = tempVal;                  //get the current value
    tempTotal = tempTotal + temp[tempIndex];    //add to total
    tempIndex++;                                //increment the index

    if (tempIndex >= tempReadings)  // ...wrap around to the beginning:
    {
      tempIndex = 0;  
    }

    Serial.print("The first and last readings in the temp array:  ");
    Serial.print(temp[0]);
    Serial.println(temp[tempReadings - 1]);

    if (temp[tempReadings - 1] - temp[0] >= 10)     //if temperature is rising too fast
    {
      //send Critical message
      Serial.println("The temperature is rising too fast");
    }

    tempAverage = tempTotal / tempReadings;     //calculate the running average
    Serial.print("The temp average is:  ");
    Serial.println(tempAverage);

    if (tempAverage >= 80 && tempAverage < 90)  //if the temp is too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temperature is too hot");
    }

    if (tempAverage >= 90 && tempAverage < 100) //if the temp is way too hot
    {
      //send Critical message
      Serial.println("Sending message because temp is critical");
    }

    if (tempAverage >= 100)
    {
      //send message on loop
      Serial.println("Sending message because temp is critical");

    }
  }
  delay(5000);
}

int randomNumber(int minVal, int maxVal)              //function to generate random values within a range
{
  return rand() % (maxVal-minVal+1) + minVal;
}

void sendMessage(const String& body)            //function that triggers twilio webhook
{
  Particle.publish("twilio_sms", body, PRIVATE);
  Serial.print("SendingMessage");
}

void sendMessageCritical(const String& bodyCritical)  //function that sends triggers a critical twilio webhook
{
  Particle.publish("twilio_sms_critical", bodyCritical, PRIVATE);
  Serial.println("Sending Critical Message");
}