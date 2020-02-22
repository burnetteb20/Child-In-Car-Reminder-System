void setup() 
{
    Serial.begin(115200);
    //initialize temperature sensor
    //initialize the digital and analog pins
}

void loop() 
{
    Serial.println("That's all!  You can restart or edit the code now.");
    //check to see if child is in the car
        //check to see if car goes from on to off
        //check to see if temp is too high or rising too fast
            String body = "Your child is in the car!";
            sendMessage(body);

    //check battery life
}

void sendMessage(const String& body)
{
    /* 
     * Function to send SMS text to phone number
    */
    Particle.publish("twilio_sms", body, PRIVATE);
    
}