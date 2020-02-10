int batPin = 9; // Analogeingang
int usbPin = 10;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  float measVBat = analogRead(batPin);
  measVBat *= 2;    // we divided by 2, so multiply back
  measVBat *= 3.7;  // Multiply by 3.3V, our reference voltage
  measVBat /= 1024; // convert to voltage
  if (measVBat < 6.4)
  {
    Serial.println("battery plugged in");
  }
  else
  {
    Serial.println("battery not plugged in");
  }
  delay(500);

  float measUSB = analogRead(usbPin);
  measUSB *= 2;    // we divided by 2, so multiply back
  measUSB *= 3.3;  // Multiply by 3.3V, our reference voltage
  measUSB /= 1024; // convert to voltage
  Serial.println("USB: " ); Serial.println(measUSB);
  delay(2000);
  
}
