# HODAR - Arduino

This is the only arduino file needed to control HODAR. It can be ran uisng the Arduino IDE or from Visual Studio using Visual Micro. 

## Installation

Even if you prefere using Visual Studio, you need to download the Arduino IDE to install the needed libraries. Once you have done that, open any sketch and go to Tools -> Manage Libraries.

A new window will pop up where you can search for libraries. Look for Lidar-Lite by Garmin and install it. Additionally, there is another library that needs to be installed, but it is not in the default library directory.

First you need to download the ziper from: https://playground.arduino.cc/uploads/ComponentLib/SoftwareServo/index.zip

Then go back to the sketch that you previously opened and click on Sketch -> Add .ZIP library. In the new pop up window select the Zip file that you just downloaded. 

## Usage

The code is not very complex and it has been heavily tested. In addition, I have tried to comment as much as possible to facilitate its understanding. 

There are two main parameters that you need to make sure they match the current HODAR set up:
- The first one is the stepper step that needs to match the stepper default size and the step mode selected on the A4988. Currently it is one 1/16 of 1.8 degrees.
- The second one is the number of steps needed for one full 360 turn. If using the 1/16 mode, you need 3200 steps for a full 360 rotation. This value needs to match in the interrupt set up and the tick function.
