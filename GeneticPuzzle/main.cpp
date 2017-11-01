#include <iostream>
#include "camera/Camera.cpp"
#include "imageshandler/ImageHandler.h"

int main() {

    Camera camera;

    camera.useCamera();

    ImageHandler imageSplitter(5, 5, 640, 480, "capture.png");

    imageSplitter.split_image();
    imageSplitter.concat_image();
    imageSplitter.show_image();

    cv::waitKey(0);

    return 0;
}
