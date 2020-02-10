# Child-In-Car-Reminder-System
Senior Capstone Project that alerts caregiver's if they leave a child in the car seat and the child experiences unsafe temperature

## Communicating with Caregiver

### LoRa
We are using the "LoRa" library from sandeepmistry to code. The goal is to send messages from a blackbox on the carseat to the caregiver outside of the car within a minimum range of 600 feet in urban areas.

#### Sender
We are using a LoRa Feather M0 microcontroller with a UFL antenna to send messages. The messages will be sent based on temperature readings only if the child is in the car. The controller will send messages repeatedly until it receives a reply message from the receiver to ensure that the message is received. Hopefully, an Adafruit TPL5111 breakout board will be used to put the microcontroller to sleep in order to save batter. A 3.3 volt LiPo battery will be used in conjunction with a breakaway micro-usb charger that will power the mcu and charge the battery while the car is on. This will receive and process information about the temperature and presence of the child

#### Receiver
We are using a LoRa Feather M0 microcontroller with a 7.8 cm wire antenna. The radio interrupt pin will be used to allow the microcontroller to sleep until a message is received in order to save power. If it receives a proper message, it will send a reply message if a button on the screen is pressed. The mcu will also be charged by a 3.3V LiPo batter, and it will be connected to an Adafruit Oled Featherwing screen. The screen will desplay the message about the status of the child, and a press of one of the buttons will send the reply message.

#### Range

### Boron
The Particle Boron mcu is another option that we are controlling. This will be in a blackbox on the car seat and will process information about the temperature and presence of a child. If the requirements are reachec, the mcu will communicate via LTE to a Twilio Webhook that will send an SMS message to the caregiver's phone

#### Twilio Webhook
The webhook is a Particle feather that allows a message to be sent from a purchased number to the verified numbers of the caregivers.

## Reading Temperature

### Temperature Sensor

## Detecting the Presence of a child

### Pressure Mat
A homemade pressure sensitive matt made using conductive fabric and velostat laminated together. Velostat is a pressure sensitive material that changes resistance based on applied pressure. This would be placed under the child to detect if the child is in the car.

### Infrared
A Sharp

## Battery Life

### TPL 5111

### Power Consumption
