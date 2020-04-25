#include <FastLED.h>
#include <Wire.h>
#define LED_WRITE 5 // data pin connected to the LED strip
#define NUM_LEDS 100 // Number of leds on strip
CRGB leds[NUM_LEDS]; // Array of leds
/*Updated values will be receive from servants */
int function_mode = 2; // The mode the system is in (fully lit, bass sync, and quite modes)
int amount = 0; // The amount of leds to light up
///LED control variables
int previous = 0; // Preivious amount value
int dif = 0; // to save difference between int previous and int amount (only when previous > amount)
int red = 0; // Red value (leds)
int green = 128; // Green value (leds)
int blue = 128; // Blue value (leds)
//setup function
void setup() {
Wire.begin(); // This arduino is the Master (No ID for master)
Serial.begin(9600);
FastLED.addLeds<NEOPIXEL,LED_WRITE>(leds,NUM_LEDS); //To enable library use
}
/* This function is continuously called to change the colors of the leds strip *
* providing a visually appealing effect when playing music */
void changeColors(){
//BLUE Control
if(100 <= blue && blue < 171 && red == 0){
blue +=1;
green -= 1;
red = 0;
}
//RED Control
else if(red <= 127){
red += 1;
}
//GREEN Control
else{
red = 0;
green = 200;
blue = 100;
}
}
//MODE: 2
/* This function runs when the system is in mode 2 (bass sync), which *
* lights the led strip in synchronization of the bass of the song being played */
void led_synch(){
//Go up
if(amount > previous){
previous = amount;
int i;
for(i = 0; i < amount; i++){
leds[i] = CHSV(red,green,blue);
}
}
//Go down
else{
if(previous != 0){
dif = previous - amount;
dif = map(dif,0,75,2,6);
for(int i= previous; i > previous-dif;i--){
leds[i] = CHSV(0,0,0);
previous -= dif;
}
}
}
changeColors();
FastLED.show();
}
//MODE: 1
/* This function runs when the system is in mode 1 (fully lit), which *
* is intended to just be a light source for the room. */
void fully_lit(){
int i;
for(i = 0;i < 75;i++){
leds[i] = CHSV(110,110,255);
}
FastLED.show();
}
//MODE: 0 (OFF)
/* This function runs when the system is in mode 0 (off/quite), which *
* is use when the user does not need a light source nor music sync */
void study_mode(){
int i;
for(i = 0;i < 75;i++){
leds[i] = CHSV(0,0,0);
}
FastLED.show();
}
void loop() {
//Requesting the system mode from servant #8
Wire.requestFrom(8,2);
while(!Wire.available());
function_mode = Wire.read() << 8;
function_mode |= Wire.read();
// FOR TESTING
//Serial.print("function_mode: ");
//Serial.println(function_mode);
if(function_mode == 2){
//Requesting the amount (leds to light up) from servant #9
Wire.requestFrom(9,2);
while(!Wire.available())
amount = Wire.read() << 8;
amount |= Wire.read();
// FOR TESTING
//Serial.print("amount: ");
//Serial.println(amount);
changeColors();
led_synch();
}
else if(function_mode == 1)
fully_lit();
else
study_mode();
}
