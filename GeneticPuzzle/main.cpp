#include <iostream>
#include "camera/Camera.cpp"
#include "imageshandler/ImageHandler.h"

int main()
{

    //Camera camera;

    //camera.useCamera();

    //ImageHandler imageSplitter(5, 5, 640, 480, "capture.png");
    /*cv::Mat3b hola = cv::imread("MGSPW.png");
    std::vector<cv::Mat3b> images;
    cv::Mat3b croppedImg = cv::Mat3b(hola.rows, hola.cols, cv::Vec3b(0,0,0));

    ImageHandler* imageSplitter = new ImageHandler(5, 5, 1024, 640);

    imageSplitter->split_image(images, hola);

    imageSplitter->randomize(images);

    imageSplitter->concat_image(images, croppedImg);

    cv::imshow("Split", croppedImg);

    cv::waitKey(0);

    delete imageSplitter;
    imageSplitter = nullptr;
    */

    bool h1;
    bool h2;

    std::cout << "Father" << std::endl;
    std::cin >> h1;

    std::cout << "Mother" << std::endl;
    std::cin >> h2;

    if (h1 && h2)
    {
        std::cout << "Both Parent" << std::endl;
    }
    else if (h1 || h2)
    {
        std::cout << "One Parent" << std::endl;
    }
    else
    {
        std::cout << "No Parent" << std::endl;
    }

    return 0;
}
