/* 
More complex example of sending a MMS with Twilio and a Particle Electron.

We can publish to two event names:
- twilio_sms, which works like the basic example
- twilio_mms, which adds picture_url support

Author: Paul Kamp, Twilio Developer Education
License: MIT
*/

String body = "Your child is in the car!";

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
    sendMessage(body);
    Serial.begin(115200);
}

void loop() 
{
    Serial.println("That's all!  You can restart or edit the code now.");
    delay(60000);
}