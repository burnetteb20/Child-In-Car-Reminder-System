/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_GFX.h>       //for screen
#include <Adafruit_SSD1306.h>   //for screen

//define the pins used by the transceiver module
#define ss 8
#define rst 4
#define dio0 3
#define BUTTON_A  9             //to connect screen
#define BUTTON_B  6             //to connect screen
#define BUTTON_C  5             //to connect screen
int piezoPin = 10;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);    //initialize screen

void setup() 
{
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);    //start up display
  display.display();
  delay(1000);
  //clear the buffer.
  display.clearDisplay();
  display.display();
  //setup buttons
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  delay(100);
  display.println("LoRa radio ready");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //915E6 for North America
  while (!LoRa.begin(905E6)) 
  {
    Serial.println(".");
    delay(500);
  }
  
  //the sync word assures you don't get LoRa messages from other LoRa transceivers
  LoRa.setSyncWord(0x13);

  //set transmission power to max
  LoRa.setTxPower(20);
  
  Serial.println("LoRa Initializing OK!");

  //attach function to interrupt pin
  attachInterrupt(dio0, sendReply, CHANGE);
}

void loop() 
{
 
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    // received a packet
    Serial.print("Received packet '");
    String LoRaData;
    // read packet
    while (LoRa.available()) 
    {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
      // print RSSI of packet
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());

      display.setCursor(0,0);
      tone(piezoPin, 2000, 700);
      display.println(LoRaData);
      display.display();
      delay(3000);
      display.clearDisplay();
      display.display();

      Serial.println("Sending Reply");
      int i = LoRa.beginPacket();
      LoRa.print("Coming to get you");
      Serial.println(i);
      int x = LoRa.endPacket();
      Serial.println(x);
    }

    LoRa.beginPacket();
    LoRa.print("Coming to get you");
    LoRa.endPacket();
  }
}

void sendReply()
{
   Serial.println("Sending Reply");
   int i = LoRa.beginPacket();
   LoRa.print("Coming to get you");
   Serial.println(i);
   int x = LoRa.endPacket();
   Serial.println(x);
}
