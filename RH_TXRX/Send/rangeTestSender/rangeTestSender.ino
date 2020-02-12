#include <RadioHead.h>    //for lora signal
#include <SPI.h>          //for lora signal
#include <RH_RF95.h>      //for lora signal
#include "Adafruit_Si7021.h"

#define RFM95_CS 8        //to connect lora
#define RFM95_RST 4       //to connect lora
#define RFM95_INT 3       //to connect lora
#define RF95_FREQ 905.0   //to set lora frequency

RH_RF95 rf95(RFM95_CS, RFM95_INT);    //initialize lora radio
int counter = 0;
void setup() 
{
  // put your setup code here, to run once:

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  Serial.begin(115200);
  delay(1);
  delay(100);
  Serial.println("Feather LoRa TX Test!");
  while (!rf95.init())    //making sure radio can start
  {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
  if (!rf95.setFrequency(RF95_FREQ))    //set the proper radio frequency
  {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  if (!rf95.sleep()) 
  {
    Serial.println("Could not sleep");
    while (true);
  }
  else
  {
    Serial.println("Sleep");
  }
  //rf95.setTxPower(23); // use PA_BOOST transmitter pin
  delay(5000);
}

void loop() 
{

  Serial.println("Transmitting..."); // Send a message to rf95_server
  delay(100);

  char radiopacket[] = "Child in car    ";
  counter++;
  itoa(counter, radiopacket+13, 10);
  Serial.print("Sending "); Serial.println(radiopacket);
  rf95.send((uint8_t *)radiopacket, sizeof(radiopacket));
  delay(10);
  rf95.waitPacketSent();
  delay(5000);
}
