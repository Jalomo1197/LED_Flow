#include <Wire.h>
int vibration = 0; //Align with vibration of other code
int amount; // will be conversion of vibration


void setup() {
  //serial input
  Wire.begin(9); //servant ID = 9
  Wire.onRequest(Request);
  Serial.begin(9600);
}


void loop() {
  vibration = analogRead(1); //Analog read from vibration sensor
  //converting read to amount
  if(vibration > 20)
    vibration -= 17;
  //Prevent overflow
  if(vibration >= 320)
    amount = 75;
  else
    amount = map(vibration,0,320,0,75);
}


/* This function runs whenever the master arduino *
* requests data (int amount) from this arduino */
void Request(){
  Serial.print("Sending: ");
  Wire.write(amount >> 8);
  Wire.write(amount & 255);
  Serial.println(amount);
}
