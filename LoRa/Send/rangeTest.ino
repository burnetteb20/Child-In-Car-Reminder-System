/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 8
#define rst 4
#define dio0 3

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(905E6)) {
    Serial.println(".");
    delay(100);
  }

  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  //LoRa.setSyncWord(0x13);
  //LoRa.setTxPower(20);
  Serial.println("LoRa Initializing OK!");
}

void loop() {

  counter++;
  //Serial.print("Sending packet: ");

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("Child in car ");
  LoRa.print(counter);
  LoRa.endPacket();
  Serial.println("packet sent");

  delay(5000);
}
