# HODAR - Viewer

The Lidar Viewer is a very lightweight tool that can be used to plot the points in real time as HODAR acquires them. It uses Serial communication to retrieve the data from the HODAR.

## Installation

This viewer was built using Java and the framework Processing. It is very simple and easy to scale. To run it, you only too download [Processing](https://processing.org/) and extract it somewhere in your computer. I recommend putting it in some place stable, as the .xyz files will be saved in this directory.

Next, open the LidarViewer file using the Processing executable. Similarly to the Arduino IDE, in the top under SKETCH you will find the option to Import a Library. Click on it and select Add Library. Then, using the search bar look for the PeasyCam library and install it.

## Usage

Before running the viewer you need to make sure the file is under a folder with the same name. If you cloned the repository, this is already taken care off.

When you click run on the interface, a blank prompt will appear. You need to minimize it and under it you will find **another prompt asking you to enter which serial port to use**. This is a known bug that always happen; however, I have not been to fix it yet. 

Additionally, I have implemented the option to save the points into .xyz file under the Processing directory. You can do this by pressing the key 'S'. On the other hand, you can erase all current points by pressing 'X'. As mentioned above, if you need additional features, it is extremely easy to scale. 
