# HODAR

This project aims to do 3D volumetric bounding using a 1D LIDAR and a camera. It can be divided into two main sections:

- **LIDAR turret and viewer**: which makes for the 3D CAD design, the Arduino code to control the motors and the LIDAr, the 3D viewer to plot the results.
- **Fast Object Detection**: which relates to the work done using the YOLO neural network, OPENCV, and CUDA to detect new objects.


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

Finally, the only thing missing is the pretrained weights for the COCO dataset. From the darknet folder run:

` wget https://pjreddie.com/media/files/yolov3.weights`
