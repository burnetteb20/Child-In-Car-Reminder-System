#include <RadioHead.h>          //for lora signal
#include <SPI.h>                //for lora signal
#include <RH_RF95.h>            //for lora signal

#define RFM95_CS 8              //to connect lora
#define RFM95_RST 4             //to connect lora
#define RFM95_INT 3             //to connect lora
#define RF95_FREQ 905.0         //set lora radio frequency

RH_RF95 rf95(RFM95_CS, RFM95_INT);      //initialize radio

void setup() 
{
  //put your setup code here, to run once:
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  
  Serial.begin(115200);
  delay(10);
  Serial.println("Connected to Serial");
  Serial.println("LoRa Feather M0");
  while (!rf95.init()) 
  {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
  if (!rf95.setFrequency(RF95_FREQ))
  {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
}

void loop() 
{
  if (rf95.available())
  {
    //uint8_t message;
    // Should be a message for us now
    char radiopacket[] = "Child in car    ";
    //uint8_t message = (uint8_t*)radiopacket;
    uint8_t buf[sizeof(radiopacket)];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
       Serial.println(rf95.lastRssi(), DEC);      //Need to make sure the message is the right one
      //digitalWrite(LED, HIGH);
      //RH_RF95::printBuffer("Received: ", buf, len);
    }
  }
}
