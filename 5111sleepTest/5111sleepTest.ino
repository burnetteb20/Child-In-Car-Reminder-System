#include <Adafruit_SleepyDog.h>
#define DONEPIN  12 
#define LED 13
 
void setup() 
{
  pinMode(DONEPIN, OUTPUT);
  digitalWrite(DONEPIN, LOW);
  Serial.begin(115200);
  Serial.println("Light up!");
  pinMode(LED, OUTPUT);
}
 
void loop() 
{
  // toggle DONE so TPL knows to cut power!
  digitalWrite(LED, HIGH);
  digitalWrite(DONEPIN, LOW);
  delay(1000);
  digitalWrite(DONEPIN, HIGH);
  delay(1000);
  
  Serial.println("Awake!");
}
