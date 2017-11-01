#include "Camera.h"

void Camera::useCamera()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
        return;

    cv::Mat frame;

    while (true)
    {
        cap.read(frame);
        cv::imshow("Camera", frame);
        cv::Mat frame2;

        if (cv::waitKey(10) == 's')
        {
            frame2 = frame.clone();
            cv::imwrite("capture.png", frame2);
            std::cout << "Foto tomada" << std::endl;
            //cv::imshow("Captura Frame", frame2);
        }

        if (cv::waitKey(10) == 'd')
        {
            break;
        }

    }
}
