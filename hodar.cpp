#include "yolo.hpp"


int main() {
    
    detect("webcam", 0.7); //first is the input method (videofile, webcam...), the second parameter is the accuracy threshold

    return 0;
}
