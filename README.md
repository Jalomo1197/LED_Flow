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
● 2 Laptops for battery supply
● 20+ Wires

# References
### User Mode

https://www.arduino.cc/en/Reference/LiquidCrystalhttps://somtips.com/connect-lcd-displ
ay-with-arduino-without-i2c-module-pot/
https://www.instructables.com/id/Arduino-Interfacing-With-LCD-Without-Potentiometer/

### LED Algorithm
https://github.com/FastLED/FastLED
https://github.com/octref/LatticeSnake/blob/master/photon/include/FastLED/FastLED.h

### Serial Communication
https://www.arduino.cc/en/Tutorial/MasterWriter
https://www.arduino.cc/reference/en/language/functions/communication/serial/
