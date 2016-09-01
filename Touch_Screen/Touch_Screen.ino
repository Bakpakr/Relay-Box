/* This is my Sketch for the Touch Screen interface for the relay box that will be installed in my Jeep
    Robert L. Wardecker
    cna2rn@gmail.com

    This is the updated sketch to utilize XBee boards to make this wireless.
    
    This code is in public domain. 

Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.

NonCommercial — You may not use the material for commercial purposes.

ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original. 

No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. 
*/

#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial mySerial =  SoftwareSerial(2, 3); 



const int relayaPin = 52;
const int relaybPin = 53;
const int relaycPin = 50;
const int relaydPin = 51;


SoftwareSerial nextion(10, 11);// Nextion TX to pin 10 and RX to pin 11 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

boolean button1State;
boolean button2State;
boolean button3State;
boolean button4State;
boolean button5State;


void setup() {

  Serial.begin(9600);
  myNextion.init(); // send the initialization commands for Page 0

  mySerial.begin(9600);

  pinMode(relayaPin, OUTPUT);
  pinMode(relaybPin, OUTPUT);
  pinMode(relaycPin, OUTPUT);
  pinMode(relaydPin, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {

  String message = myNextion.listen(); //check for message

  //52" Lightbar
  if (message == "65 0 1 1 ffff ffff ffff") {
    myNextion.buttonToggle(button1State, "b0", 0, 2);

    if (button1State == HIGH) {
      // turn Relay on:
      digitalWrite(relayaPin, HIGH);
    } else {
      // turn Relay off:
      digitalWrite(relayaPin, LOW);
    }
  }

  //6" Pods
  if (message == "65 0 2 1 ffff ffff ffff") {
    myNextion.buttonToggle(button2State, "b1", 0, 2);
    if (button2State == HIGH) {
      // turn Relay on:
      digitalWrite(relaybPin, HIGH);
    } else {
      // turn Relay off:
      digitalWrite(relaybPin, LOW);
    }
  }

  //Fender Pods
  if (message == "65 0 3 1 ffff ffff ffff") {
    myNextion.buttonToggle(button3State, "b2", 0, 2);
    if (button3State == HIGH) {
      // turn Relay on:
      digitalWrite(relaycPin, HIGH);
    } else {
      // turn Relay off:
      digitalWrite(relaycPin, LOW);
    }
  }

  //Rock Lights
  if (message == "65 0 4 1 ffff ffff ffff") {
    myNextion.buttonToggle(button4State, "b3", 0, 2);
    if (button4State == HIGH) {
      // turn Relay on:
      digitalWrite(relaydPin, HIGH);
    } else {
      // turn Relay off:
      digitalWrite(relaydPin, LOW);
    }
  }

  //All On
  if (message == "65 0 5 1 ffff ffff ffff") {
    myNextion.buttonToggle(button5State, "b4", 0, 2);

    if (button5State == HIGH) {
      digitalWrite(relayaPin, HIGH);
      digitalWrite(relaybPin, HIGH);
      digitalWrite(relaycPin, HIGH);
      digitalWrite(relaydPin, HIGH);
    }
    else {
      digitalWrite(relayaPin, LOW);
      digitalWrite(relaybPin, LOW);
      digitalWrite(relaycPin, LOW);
      digitalWrite(relaydPin, LOW);
    }
  }

}
