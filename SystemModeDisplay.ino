#include <Wire.h>
#include <LiquidCrystal.h>
/*
Functionality includes:
*Button for user mode
*LCD display for user
*/
const int btn_pin = 8;
int btn_state; // For the state of the button
int function_mode = 0; // System mode (bass sync, fully lit, or off)
int debounce; //To ensure proper press
// intialize display for user
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Contrast=75;
void setup() {
//Button
Serial.begin(9600);
pinMode(btn_pin,INPUT);
btn_state = digitalRead(btn_pin); // Initial state
//LCD
analogWrite(6,Contrast);
lcd.begin(16, 2);
//Serial communication
Wire.begin(8);
Wire.onRequest(Request); // What to do when the master arduino request data
}
/* This function runs whenever the master arduino *
* requests data (function_mode) from this arduino */
void Request(){
Serial.print("Sending: ");
Wire.write(function_mode >> 8);
Wire.write(function_mode & 255);
Serial.println(function_mode);
}
/* This function adjust the LCD screen to show the *
* current mode the system is in. */
void lcd_mode(){
if(function_mode == 2){
lcd.setCursor(0, 0);
lcd.print("Mode: Bass Mode");
Serial.write("Mode: Bass Mode\n");
}
else if(function_mode == 1){
lcd.setCursor(0, 0);
lcd.print("Mode: Fully Lit ");
Serial.write("Mode: Fully/Lit \n");
}
else{
lcd.setCursor(0, 0);
lcd.print("Mode:Quiet/Study ");
Serial.write("Mode: Quiet/Study \n");
}
}
//loop function
void loop() {
debounce = digitalRead(btn_pin);
delay(10);
if(debounce == digitalRead(btn_pin)){
if(debounce != btn_state){
if(debounce == HIGH){
function_mode++;
//Prevent overflow
if(function_mode == 3)
function_mode = 0;
}
}
btn_state = debounce; //Correct button press
}
lcd_mode();
}
