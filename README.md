# HODAR

This project aims to do 3D volumetric bounding using a 1D LIDAR and a camera. HODAR can be broken down in four components: fast object detection module, Arduino schematic, Point Cloud viewer, and the Lidar turret. This file goal is to give an overview of each component and how they come together to form HODAR. For more information about each module, please refer to the readme files under their corresponding folders (for object detection you have one under [src](src/README.md) and another one under [darknet](darknet/README.md).

## Overview

HODAR uses three different applications to achieve its goal. The first one is the arduino code used to control the motors and to communicate with the Lidar. The second one is the object detection module that analyzes the scene and finds any new object that enters it. The last one is the viewer tool that plots the results. 

As of right now, the Arduino code and the Viewer can be executed together to carry out full 3D scans out of any indoor room. The object detection module is able to find any new objects and bound. However, further development is needed to create a function in the object detection module to send the results to the arduino. This can be achieved easily using the serial port, but I would recommend looking for alternatives so the serial port can be used to send the points for the Point CLoud viewer.

## Fast Object Detection

Deep learning has been proved to be a very fast and reliable manner to carry out object detection. There are different neural networks dedicated to this task such as: CNN, R-CNN, YOLO... For this project I decided to choose You Only Look Once (**YOLO**) since it was proven to be the fast one and accuracy was not as important as speed. HODAR purpose is to detect and bound any new object that enters the scene, clasifying it is out of the scope for now. For this reason, YOLO was the best choice. In order to install YOLO a set of prerequisites must be met.

More information about this module can be found under its own [Readme file](src/README.md). Additionally, you can find more information about the math behind the neural network in its [academic paper](https://pjreddie.com/media/files/papers/YOLOv3.pdf) and in the [darknet framework readme](darknet/README.md).

## Arduino - Schematic

In this project we use the Arduino UNO to control the turret motors and to communicate to the LIDAR. Below there is a schematic of the circuit sketched using Eagle CAD.

![HODAR-Schematic](media/schematic.jpg)


## LIDAR Turret

In this section I will cover the design of the lidar turret and the code.

### CAD design

The design was done using SOLIDWORKS and 3D printed. The files can be found:

`N:\ENGINEERING\dramonprados\HODAR Turret_SolidWorks`

#### Components

- LIDAR
- Stepper Motor
- Servo Motor
- 12 Wire Slip Ring

More info: https://christie.atlassian.net/wiki/spaces/~641488303/pages/149913613/HODAR

### Arduino Code

WIP...

## LIDAR Viewer

A simple tool visualization tool is included in the project. The viewer uses JAVA and the sketching software tool Processing to display the points in 3D. It also allows to save and or load points from xyz file. 

For real time output, it uses serial communication to read the data from the arduino. However, the object detection algorithm also uses serial data to send the location of the new object to the arduinon. Consequently, both of them are not compatible at the moment. 

## Future Work

HODAR is not a finished project at the current state, and it has several areas of improvement. I have grouped them into two categories: hardware and software.

### Hardware Improvements

The first are of improvement would be buying a better timing belt to the right size. The current timing belt had to be cut and then glued together to fit our needs. However, timing belts are very sensitive and skipping a...
