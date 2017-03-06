/*
  Reading a serial ASCII-encoded string.

 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.

 Circuit: Common-Cathode RGB LED wired like so:
 * Red anode: digital pin 3
 * Green anode: digital pin 5
 * Blue anode: digital pin 6
 * Cathode : GND

 created 13 Apr 2012
 by Tom Igoe
 
 modified 14 Mar 2016
 by Arturo Guadalupi

 This example code is in the public domain.
 */
/*
PROTOCOL OVERVIEW
b1    b2
0 -   FULL STOP
1-100 0-256





*/
// pins for the LEDs:
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int STOP_CMD = 0;
const int SPEED_CMD = 1;

int comState = 0;
int comChannel = 0;
const int RECIEVING_SPEED = 1;
void setup() {
  // initialize serial:
  Serial1.begin(115200);
  Serial.begin(115200);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial1.available() > 0) {
    Serial.print("recieved message");
    //Save the incoming byte in a variable
    byte incomingByte = Serial1.read();
    //If the program was in a receiving_speed state 
    if (comState == RECIEVING_SPEED){
      Serial.print("Speed");
        comState = 0;
        int singedValue = incomingByte -127;
        Serial.print(singedValue);
        speedCommand(comChannel,singedValue);
        Serial.println();
    }else{
      if (incomingByte == STOP_CMD){
        Serial.println("STOP");
        stopCommand();
        comState = 0;
      }else{
        Serial.print("Channel ");
        comChannel = incomingByte;
        Serial.print(comChannel);
        comState = RECIEVING_SPEED;
      }
    }
  }
}
void stopCommand(){
  
}
void speedCommand(byte channel,int channelSpeed){
  if (channelSpeed > 0){
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    }else{
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
  }
    analogWrite(11,abs(channelSpeed));
}








