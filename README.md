**Authors:  Bryce Burnette, Jack Robey, Karlens Joas**

**University:  Washington and Lee University, Lexington, VA**

**Professors:  Professor Jon Erickson and Professor Joel Kuehner**
***

# Child-In-Car-Reminder-System
![Project status badge](https://img.shields.io/badge/Project%20status-ACTIVE-brightgreen.svg)

Senior Capstone Project that alerts caregiver's if they leave a child in the car seat and the child experiences unsafe temperature. Attaches to any car seat and does not impede functionality.

## Communicating with Caregiver

![Figure 1](/Figures/senderAndReceiver.jpg)

**Figure 1** *Picture of the Sender and Receiver with size comparisons*

### Boron (Option 2)
The [Particle Boron](https://docs.particle.io/boron/) mcu is the choice for communicating with the caregiver. This will be in a blackbox on the car seat and will process information about the temperature and presence of a child. If the requirements are reached, the mcu will communicate via LTE to a Twilio Webhook that will send an SMS message to the caregiver's phone. The Boron connects to the Particle Cloud via LTE. A SMS text will be triggered using a Webhook in the cloud. LTE range an connectivity is outstanding, making us able to connect with the cloud in most areas and send messages to people practically anywhere.

#### Twilio Webhook
The [webhook](https://docs.particle.io/tutorials/device-cloud/webhooks/) is a Particle feature that allows a message to be sent from a purchased number to the verified numbers of the caregivers. This Webhook practically connects my mcu to a phone number that allows me to send messages.

#### Connectivity
We performed connectivity testing in a lot of different places. We sent over 100 pings (connection checks) and got a 100% return rate. We checked in downtown parking garages, downtown streets, rural roads, and in stores.

## Reading Temperature

A core temperature of 107 degrees Fahrenheit is fatal for a child. We will send temperature alerts at 80, 90, and a 100 degrees Fahrenheit. We will also send an alert if the temperature is rising extremely fast at any point.

### Temperature Sensor

### Box

We are using an aluminum box with machined vents because this will give the best temperature response to give the most accurate temperature reading

## Detecting the Presence of a child

### Pressure Mat (Option 1)
A homemade pressure sensitive matt made using conductive fabric and velostat laminated together. Velostat is a pressure sensitive material that changes resistance based on applied pressure. This would be placed under the child to detect if the child is in the car.

![Figure 2](/Figures/velostatCircuit.png)

**Figure 2** *Voltage divider circuit connecting pressure mat to mcu*

### Infrared (Option 2)
A [Sharp GP2Y0A21YK0F](https://global.sharp/products/device/lineup/data/pdf/datasheet/gp2y0a21yk_e.pdf) Analog Infrared sensor. This sensor detects any object from 10 - 80 cm and sends a corresponding voltage output. We are using the [Arduino_SharpIR](https://github.com/qub1750ul/Arduino_SharpIR) from Giuseppe Masino to interpret the voltage output as a precise distance. This will be clipped to the car seat and stay out of arms reach of the child looking facing into the car seat 

## Battery Life

Power Consumption measurements are currently underway

### Battery

A 3.7 V, 500 mAh LiPo Battery to power the mcu's. These can be charged by microusb. 

### TPL 5111

The [TPL5111](https://learn.adafruit.com/adafruit-tpl5111-reset-enable-timer-breakout/overview) is a breakout board from Adafruit that uses the Enable pin on the mcu to turn off the microcontroller for a specified period of time
