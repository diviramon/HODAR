#include "yolo.hpp"


int main() {
    
    detect("webcam", 0.7); //first is the method to connect to the camera, second is the accuracy threshold

    return 0;
}
