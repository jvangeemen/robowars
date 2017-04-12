/*
@Author: Geert Roumen
@Hardware:


             ---MOTOR---         ---MOTOR--
        |   M1    |    M2   |   M1    |    M2   |

                          L298N

ENABLE  |   M1    |   M2    |   M2    |   M1    |   ENABLE
10      |   8     |   9     |   4     |   5     |   6

                       ARDUINO YUN

Lucid Lustrum Makeathon exmaple code
For a <5 channel reciever using the Arduino Yun

@
*/

#include <EnableInterrupt.h>
//DOWNLOAD FROM https://github.com/GreyGnome/EnableInterrupt

/*
Refer those functions to the main interrupt function
*/
void functionOne(){quicfunc(0);}
void functionTwo(){quicfunc(1);}
void functionTree(){quicfunc(2);}
void functionFour(){quicfunc(3);}
void functionFive(){quicfunc(4);}

/*
Define the pins
Now only two channels are being used, the max on the Arduino Yun is five because of the interrupt pins
channel 1 and 2 are being used for the steering (normally) and the other channels can be used for weapons/arms.
*/

const int motorAPins[]      = {8  , 4,-1,-1};  //Normal digital or analog pin (analog with A prefix)
const int motorBPins[]      = {9  , 5,-1,-1};  //Normal digital or analog pin (analog with A prefix)
const int motorEnablePins[] = {10 , 6,-1,-1};  //MUST BE PWM (3,5,6,9,10,11 are PWM)
const int inputPins[]       = {2  , 3,  -1,  -1};  //MUST BE INTERUPT 2, 3, 7 or PIN CHANGE INTERRUPT 8, 9, 10, 11; keep in mind that 0 is RX and 1 is TX,
                                         //so don't use serial communication when useing those.
                                         //

//Those variables are 'volatile' because they are being used in the ISR (interrupt routine) below
//See https://www.arduino.cc/en/reference/volatile
volatile unsigned long testEnd[] =     {0  , 0,0,0};
volatile unsigned long testStart[] =   {0  , 0,0,0};
int value[]              =    {0  , 0,0,0};
const int channels          = 2;


/*
The min and maximum value that the remote sends
*/
const int map_max = 1975; //the max value recieved from the transmitter
const int map_min = 1000; //the min value recieved from the transmitter


void setup() {
  for(int i=0;i<sizeof(motorEnablePins);i++){
      pinMode(motorAPins[i],OUTPUT);
      pinMode(motorBPins[i],OUTPUT);
      pinMode(motorEnablePins[i],OUTPUT);
      pinMode(inputPins[i],INPUT);

    }
    //uncomment/comment the channels that are not being used. (Arduino can't attach an interrupt to a -1 pin)
    enableInterrupt(inputPins[0],functionOne, CHANGE);
    enableInterrupt(inputPins[1],functionTwo, CHANGE);
    //enableInterrupt(inputPins[2],functionTree, CHANGE);
    //enableInterrupt(inputPins[3],functionFour, CHANGE);

  Serial.begin(115200);
  Serial.println("---------------------------------------");
}

void loop() {
  for(int i=0;i<channels;i++){
  if (testStart[i]<testEnd[i]){
    int ra = testEnd[i]-testStart[i];
    int a = map(ra,map_min,map_max,-255,255);
    if (ra > 1){
      value[i] = a;
      speedCommand(i,a);
    }
    testEnd[i] = 0;
    }
  }
  Serial.print(value[0]);
  Serial.print(",");
  Serial.print(value[1]);
  Serial.print(",");
  Serial.print(value[2]);
  Serial.print(",");
  Serial.println(value[3]);
  delay(100);

}

/*
This is the ISR for the interrupts. Dont put any Delays, Serial.print or other realtime blocking functions in here.
*/
void quicfunc(int channel_number) {
  uint8_t latest_interrupted_pin=inputPins[channel_number];//PCintPort::arduinoPin;
  if (digitalRead(latest_interrupted_pin)==HIGH){
    testStart[channel_number] = micros();

  }else{
    testEnd[channel_number] = micros();
  }
};

/*
The function to send a speed value to a certain channel
*/
void speedCommand(byte channel,int channelSpeed){
  if (channelSpeed > 0){
    digitalWrite(motorAPins[channel],HIGH);
    digitalWrite(motorBPins[channel],LOW);
    digitalWrite(13,HIGH);
    }else{
      digitalWrite(13,LOW);
      digitalWrite(motorBPins[channel],HIGH);
      digitalWrite(motorAPins[channel],LOW);
  }
    if (abs(channelSpeed) < 10){
      //Disable the annoying sound (and make sure that the robot is not wasting power in stable mode)
      analogWrite(motorEnablePins[channel],0);
      }else{

      analogWrite(motorEnablePins[channel],min(255,abs(channelSpeed) + 10));
      }
}
