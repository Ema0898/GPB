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

        if (cv::waitKey(10) == 's')
        {
            cv::Mat frame2;
            frame2 = frame.clone();
            cv::imshow("Captura Frame", frame2);
        }

        if (cv::waitKey(10) == 'd')
            break;
    }
}
