/*
 * Project powertest
 * Description:
 * Author:
 * Date:
 */

#include <adafruit-sht31.h>

#define DONEPIN  12
#define PRESSURE_PIN A2

String body = "Your child is in the car!";

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() 
{
    Serial.begin(9600);
    sht31.begin(0x44);
    Serial.begin(115200);
    delay(100);
}

void loop() 
{
    float temp = sht31.readTemperature();
    Serial.print(temp);
    float pressure = analogRead(PRESSURE_PIN);
    Serial.print(pressure);
    sendMessage(body);
    delay(100);
}

void sendMessage(const String& body)
{
    Particle.publish("twilio_sms", body, PRIVATE);
    Serial.print("SendingMessage");
}