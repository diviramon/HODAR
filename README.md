# HODAR

This project aims to do 3D volumetric bounding using a 1D LIDAR and a camera. It can be divided into two main sections:

- **LIDAR turret and viewer**: which makes for the 3D CAD design, the Arduino code to control the motors and the LIDAr, the 3D viewer to plot the results.
- **Fast Object Detection**: which relates to the work done using the YOLO neural network, OPENCV, and CUDA to detect new objects.

## Fast Object Detection

This project uses the You-Only-Look-Once (YOLO) neural network with CUDA and OPENCV to achieve rapid object detection and image processing.
