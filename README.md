# robowars
The example source files for the Lucid Lustrum Makeathon where battle robots start fighting

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
Choose how many channels you'll need. (a normal bot usually takes 3-4 channels). The remotes support up to 6 channels, but you'll need to solder potentiometers/switches to make them functional.

(To start (and make things move), lets just use 2 channels, you can just copy paste te code from the github). When you have this working and tested you can move to step 7

## Troubelshooting

If you're not sure weather the RC reciever is actually connected to the RC transmitter, you can easily check that by connecting a (continious) servo to one of the ports on the RC reciever, play around with the controller and see if it changes the direction/position of the servo.

Make sure you connect the servo in the right way,
VCC -> red
GND -> black
Signal -> another color (usually white)

## Step 6

Connect the hardware

<img src="https://raw.githubusercontent.com/lemio/robowars/master/breadboardview.png"></img>

## Step 6
