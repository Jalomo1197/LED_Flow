# Description

Idea is to create a Master Writer/Slave Receiver configuration which
will allow each individually programmable LED strip to synchronize to the beat of music
playing via a speaker while reducing any noise in the environment. 
The Master Writer/Slave Receiver configuration via the i2c protocol will be connected to a
bluetooth speaker, two unit controlled strip LEDs which concurrently light up with the
beat/bass of the music being outputted through the speaker recorded by Piezo vibration
sensor, and the synchronization mode will be controlled in a separate unit via the user
through a button system.

### Three Ardunios
The first Arduino will be in charge of displaying the mode of the LED strips on a LCD display. 
Modes may be “Fully light” and “Bass Sync”. “Fully light” mode will light all the unit led on 
the strip; this mode is meant to just light up the room. “Bass Sync” mode will sync the led strips 
to light up to the music on a speaker via vibration reads. The second Arduino will be in charge of 
the reading from the vibration sensor, which is connected to the speaker. It will also send the
data (reads) to the third Arduino. The third Arduino will be in charge of the led algorithm
which lights up the LED strips. It will also incorporate a touch sensor to turn the strips on.

#### Note: 
All functionality could be supported by one ardunio. However, I eventaully 
want to push an update that allows communication via Wifi. So separating functionality was 
my intial design. 


# Materials Needed
● 3 breadboards

● 3 Arduino Uno’s

● 3 X 220 Ohms resistor

● 1 Liquid Crystal Display(16 X 2)

● 1 button

● 1 JBL speaker

● 1 Piezo sensor

● 1 Individually Addressable LED Strip Light 5050 RGB

● Two power supplies (If limited, use two laptops for power supply)

● 20+ Wires


# How to build the project

## Communication between arduinos
A master-multi-servent system is in place. Implement this system using the
Wire library (wire.h). The master arduino is the arduino with the LED algorithm.
The arduino with the vibration sensor was given a servant ID equal to 9. The arduino in
control of the system mode was given a servant ID equal to 8. The reason for this design 
is to have control of when data is being transferred instead of spamming data. Ever time 
the master arduino’s data needs to be updated, it simply will request the appropriate 
data bytes from both servants. The wire connections to support this functionality is shown 
below.

NOTE: This is a new board
      Black wires: Ground connection
      Green wires: A5 connection
      Purple wires: A4 connection

## Arduino in charge of lighting the LED strip/strips (MASTER)
This arduino lights the led strip accordingly; based on the Mode and Amount data it
receives from the servant arduinos. This arduino continuously request the data from the
servants. It is in charge of implementing the different modes (fully lit, bass sync, and
off). It is capable of doing so by the FastLED.h library. The wire connections to support
this functionality is shown below.

NOTE: These wires will connection to the LED strip. All led strips have three
      connections; one for ground, one for data (I choose pin 5 for data 
      transfer to led), one for 5v.

## Arduino in charge of the reading vibrations values (SERVANT #9)
This arduino simply takes data from the vibration sensor and converts it into the amount
of leds to light up (via map function). Whenever the master arduino requests an update,
the arduino simply sends the amount (int) via Request() function. The wire connections
to support this functionality is shown below.

NOTE: Due to limitations, the vibration sensor in the diagram does not exactly resemble
      the piezo vibration sensor. The piezo vibration sensor has an additional connection
      (green wire). The addition connection is for analog reads from the sensor. (picture
      shows a vibration monitor not a piezo sensor)

## Arduino in charge of the led system mode (SERVANT #8)
This arduino keeps track of which mode the user has selected. This arduino
also displays the current mode on a 2x16 LCD. When ever the master arduino requests
an update, the arduino simply sends the mode (int) via Request() function. The code is
debounce safe (no false reads from button). The wire connections to support this
functionality is shown below.


# References
### User Mode

https://www.arduino.cc/en/Reference/LiquidCrystalhttps://somtips.com/connect-lcd-display-with-arduino-without-i2c-module-pot/
https://www.instructables.com/id/Arduino-Interfacing-With-LCD-Without-Potentiometer/

### LED Algorithm
https://github.com/FastLED/FastLED
https://github.com/octref/LatticeSnake/blob/master/photon/include/FastLED/FastLED.h

### Serial Communication
https://www.arduino.cc/en/Tutorial/MasterWriter
https://www.arduino.cc/reference/en/language/functions/communication/serial/


