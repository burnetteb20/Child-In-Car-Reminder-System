/*
 * Project babysaver
 * Description:
 * Author:
 * Date:
*/

String body = "Your child is in the car";  //body of SMS message to send

const int usbReadings = 2;
int usbIndex = 0;              // the index of the current reading
float usbTotal = 0;                  // the running total
float usbAverage = 0;                // the average

const int childReadings = 5;
int childIndex = 0;              // the index of the current reading
float childTotal = 0;                  // the running total
float childAverage = 0;                // the average

const int tempReadings = 5;
int tempIndex = 0;              // the index of the current reading
float tempTotal = 0;                  // the running total
float tempAverage = 0;                // the average


//test the car going from on to off
float usb[usbReadings] = {1,0};
float child[childReadings] = {1, 1, 1, 1, 1};
float temp[tempReadings] = {75, 75, 75, 75, 75};
//worked

// setup() runs once, when the device is first turned on.
void setup() 
{
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() 
{
  childTotal = 0;
  for (int thisReading = 0; thisReading <= childReadings - 1; thisReading++) 
  {
    childTotal = childTotal + child[thisReading];
  }
  childAverage = childTotal / childReadings;    //running average

  Serial.print("The child is in the car if the average < 3: ");
  Serial.println(childAverage);

  if (childAverage < 3)                         //if the child is in the seat
  {
    Serial.println("child in car");

    // Serial.print("the usb array is:  ");
    // Serial.print(usb[0]);
    // Serial.println(usb[1]);

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
    
    // Serial.print("The temp average is:  ");
    // Serial.println(tempAverage);

    if (tempAverage >= 80 && tempAverage < 90)  //if the temp is too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temperature is too hot");
    }

    if (tempAverage >= 90 && tempAverage < 100) //if the temp is way too hot
    {
      sendMessage(body);
      Serial.println("Sending message because temp is critical");
    }

    if (tempAverage >= 100)
    {
      sendMessage(body);
      Serial.println("Sending message because temp is critical");
    }
  }
  delay(2000);
}

void sendMessage(const String& body)            //function that triggers twilio webhook
{
  Particle.publish("twilio_sms", body, PRIVATE);
  Serial.println("SendingMessage");
}