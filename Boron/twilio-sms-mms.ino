/* 
More complex example of sending a MMS with Twilio and a Particle Electron.

We can publish to two event names:
- twilio_sms, which works like the basic example
- twilio_mms, which adds picture_url support

Author: Paul Kamp, Twilio Developer Education
License: MIT
*/

const int numReadings = 10;
String body = "Your child is in the car!";
bool childInCar = null;
float temp = null;
float readings[numReadings];

void sendMessage(const String& body)
{
    
    /* 
     * Function to send either a MMS or a SMS depending on the content of 'image'
     *
     * Note that your application will have to mind character encodings and limits.
     * The '"' character, in particular, will need to be escaped.
    */
    Particle.publish("twilio_sms", body, PRIVATE);
    
}

void setup() 
{
    Serial.begin(115200);
    for (int thisReading = 0; thisReading < numReadings; thisReading++) 
    {
        readings[thisReading] = 0;
    }
}

void loop() 
{
    //if voltage in threshold
        childInCar = true;
    //else
        childInCar = false;
    while childInCar = true;
    {
        if (readings[numReadings] - readings[0] >= 10) or temp > 90
        {
            sendMessage(body);
        }
    }
    delay(60000);
}