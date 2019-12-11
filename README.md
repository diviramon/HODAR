# HODAR

This project aims to do 3D volumetric bounding using a 1D LIDAR and a camera. It can be divided into two main sections:

- [Fast Object Detection](#fast-object-detection)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
  * [Usage](#usage)
  * [Implementation](#implementation)
    + [yolo.cpp](#yolocpp)
- [LIDAR Turret](#lidar-turret)
  * [CAD design](#cad-design)
    + [Components](#components)
  * [Arduino Code](#arduino-code)
- [LIDAR Viewer](#lidar-viewer)


## Fast Object Detection

Deep learning has been proved to be a very fast and reliable manner to carry out object detection. There are different neural networks dedicated to this task such as: CNN, R-CNN, YOLO... For this project I decided to choose You Only Look Once (**YOLO**) since it was proven to be the fast one and accuracy was not as important as speed. HODAR purpose is to detect and bound any new object that enters the scene, clasifying it is out of the scope for now. For this reason, YOLO was the best choice. In order to install YOLO a set of prerequisites must be met.

### Prerequisites

- First make sure your Graphic Card is GPU compatible, running YOLO on the CPU is very slow.
- Install CMake >= 3.8: https://cmake.org/download/
- Make sure that you have Python 3 installed, if not install it and make it default. Pip3 will also be helpful.
- Install CUDA >= 10.0, which it can be done in different ways:
    - Got to https://developer.nvidia.com/cuda-toolkit-archive and select the version that you want to install.
    - There are different ways to install CUDA, I personally recommend using the deb-network option if you are on Ubuntu.
    - Once that is finished you need to do the additional steps listed here: https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#post-installation-actions (all of them)
- Next Install cuDNN for the appropriate CUDA version that you chose: https://developer.nvidia.com/rdp/cudnn-archive
    - You will need a NVIDIA developer account to access: https://developer.nvidia.com/rdp/cudnn-archive
    - After downloading the TAR file, finish the steps outlined here: https://docs.nvidia.com/deeplearning/sdk/cudnn-install/index.html#installlinux-tar
    - When I did them the chmod would not do the required steps, and the linking would be unsuccessful. If it does not work for you, follow this community answer to fix it: https://askubuntu.com/questions/1025928/why-do-i-get-sbin-ldconfig-real-usr-local-cuda-lib64-libcudnn-so-7-is-not-a
- Finally, install OpenCV, which was the most problematic step for me. First refrain from using pip to install python-opencv as you need the complete installation to compile darknet. In addition, I recommend using OpenCV 4.1. However, make sure that during the installation method of your choice the .pc package file gets generated. For example if you are using cmake, you need to include the flag: **-D OPENCV_GENERATE_PKGCONFIG=YES**.

### Installation

Now you can clone this repository into the folder of your choice. The makefile has already being configured with all the required dependecies. Consequently, cd into the darknet folder and type **make** to trigger the build process.

Next, you need to add the library files to the **LIBRARY PATH**:

`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<path to darknet folder>`

Finally, the only thing missing is the pretrained weights for the COCO dataset. From the darknet folder run:

` wget https://pjreddie.com/media/files/yolov3.weights`

If you wish, you can train the neural network to work with your marked dataset. However, for the purposes of this project the pretrained model is good enough and saves time.

### Usage

Once darknet has been successfuly configured you can start working the application. To compile it there is a shell script in the parent folder:

`/bin/sh ./compile.sh`

Make sure you have an USB camera connected and this one is recognized by your computer (you can use cheese software to check it out). Next just type `./hodar` and the application will trigger and display the object detection in real time.

You can interact with the application by pressing the key **Enter** to only display any new objects that enter escense, and **ESC** to end it.

### Implementation

There are two source files that you should be aware of and modify:

- hodar.cpp: which is the main file that builds the app.
- yolo.cpp: which is the file where I added the changes to the API and implemented the further work (yolo_v2_class.hpp).

For any future work or modifications these are the two files that you should refer to. I also had to do some minor modifications to the yolo_v2_class.hpp to alter the detection algorithm. However, it is not likely that you will have to do so.

#### yolo.cpp

The main function in this file is detect, which launches different CUDA threads to carry out the object detection. There are 4 main threads that you should be familiar with:

- t_cap: which uses OPENCV to connect to the camera and retrieve the frames.
- t_prepare: it receives the frames from t_cap and preprocesses them to carry out the detection. It resizes and converts the images as needed.
- t_detect: where the YOLO detection happens.
- t_draw: it receives the frame and the YOLO results, and it draws boxes on the frames as needed. Additionally, it uses a modified kahman filter to track the objects between frames and classifies them. 

Finally, all of the data is displayed using OPENCV. There are also a couple of additional threads that offer additional capability such as sending the video to the network or saving it. However, I have not tested them much. 

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
