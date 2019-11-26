# HODAR

This project aims to do 3D volumetric bounding using a 1D LIDAR and a camera. It can be divided into two main sections:

- **LIDAR turret and viewer**: which makes for the 3D CAD design, the Arduino code to control the motors and the LIDAr, the 3D viewer to plot the results.
- **Fast Object Detection**: which relates to the work done using the YOLO neural network, OPENCV, and CUDA to detect new objects.


## Fast Object Detection

Deep learning has been proved to be a very fast and reliable manner to carry out object detection. There are different neural networks dedicated to this task such as: CNN, R-CNN, YOLO... For this project I decided to choose You Only Look Once (**YOLO**)
