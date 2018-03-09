This tutorial was not made for the arduino uno, so the pin numbers may differ.

<img src="https://raw.githubusercontent.com/jvangeemen/robowars/master/Comparison-pinout-Arduino-Nano-and-Arduono-Uno.png"></img>

## Step 1
Breathe and stay calm

## Step 2
Install Arduino (if you didn't already do that), just choose the latest version...
https://www.arduino.cc/en/Main/Software

## Step 3
When you have your Arduino software installed, click Sketch>Include Library>Manage Libraries>And search for EnableInterrupt

## Step 4
Download (or copy paste) the code from this github into your arduino software.

## Step 5
Choose how many channels you'll need. (a normal bot usually takes 3-4 channels). 

(The remotes support up to 6 channels, but you'll need to solder potentiometers/switches to make them functional.)

To start (and make things move), lets just use 2 channels, you can just copy paste te code from the github.
When you have this working and tested you can move to step 7

## Troubelshooting

If you're not sure weather the RC reciever is actually connected to the RC transmitter, you can easily check that by connecting a (continious) servo to one of the ports on the RC reciever, play around with the controller and see if it changes the direction/position of the servo.

Make sure you connect the servo in the right way,
VCC -> red
GND -> black
Signal -> another color (usually white)

## Step 6

Connect the hardware (Different arduino!, so pins may be different)

<img src="https://raw.githubusercontent.com/lemio/robowars/master/breadboardview.png"></img>

## Step 7

If you want to use more than two channels you'll have to change the code a bit. First of all you have to change the line

```cpp
#define CHANNELS 2
```
To the number of channels that you want to control, it automatically enables the interrupts on the pins defined in inputPins[]

To assign interrupt pins to those channels you'll have to change inputPins[] make sure that you use INTERRUPT pins (or PIN CHANGE INTERRUPT PINS). Normal interrupt pins are faster, so first use 2 and 3 and afterwards use the PCI pins.

Also make sure you're not using those pins as output pins.

The code is setup for controlling DC motors using the red L298N motor controllers (you can choose pins to controll those in motorAPins, motorBPins and motorEnablePins). Please make sure that you use PWM pins for the motorEnablePins and don't use them also as interrupt pin

Orgininal code
```cpp
const int motorAPins[]      = {8  , 4,-1,-1};  //Normal digital or analog pin (analog with A prefix)
const int motorBPins[]      = {9  , 5,-1,-1};  //Normal digital or analog pin (analog with A prefix)
const int motorEnablePins[] = {10 , 6,-1,-1};  //MUST BE PWM (3,5,6,9,10,11 are PWM)
const int inputPins[]       = {2  , 3,  -1,  -1};  //MUST BE INTERUPT 2, 3, 7 or PIN CHANGE INTERRUPT 8, 9, 10, 11;
```

Example four channel setup for DC motor controllers
```cpp
const int motorAPins[]      = {A0  , A2,  A4, 12};  //Normal digital or analog pin (analog with A prefix)
const int motorBPins[]      = {A1  , A3,  A5, 13};  //Normal digital or analog pin (analog with A prefix)
const int motorEnablePins[] = {5   , 6,   10, 11};  //MUST BE PWM (3,5,6,9,10,11 are PWM)
const int inputPins[]       = {2  , 3,  8,  9};  //MUST BE INTERUPT 2, 3, 7 or PIN CHANGE INTERRUPT 8, 9, 10, 11;
```

You're also able to use more than 4 channels, but it might become difficult using DC motors (because of the amount of pins). You can force the motor driver to only turn in one direction, or use a non-pwm pin to control the speed (FULL SPEED, NO SPEED)


## Links and datasheets

Remote:
FS-I4X 4CH radio Mode 2

https://hobbyking.com/media/file/303007606X869309X7.pdf

https://www.sparkfun.com/tutorials/348




Motor Shield:
L298N Dual H Bridge 

https://opencircuit.nl/ProductInfo/1000189/L298N-module-informatie.pdf

https://opencircuit.nl/ProductInfo/1000188/L298N.pdf

http://www.instructables.com/id/Arduino-Modules-L298N-Dual-H-Bridge-Motor-Controll/




Lipo Battery:
Pack ZIPPY Compact 1000mAh 3S 25C Lipo




Arduino uno:
https://www.tinytronics.nl/shop/nl/arduino/main-boards/uno-r3-compatible-usb-b
