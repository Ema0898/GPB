#include "ImageHandler.h"

ImageHandler::ImageHandler(int rowNumber, int colNumber, int width, int height)
{
    rowNum = rowNumber;
    colNum = colNumber;

    WIDTH = width;
    HEIGHT = height;

    xMax = WIDTH / rowNum;
    yMax = HEIGHT / colNum;

    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

ImageHandler::~ImageHandler()
{

}

void ImageHandler::randomize(std::vector<cv::Mat3b> &imageVector)
{

    std::shuffle(imageVector.begin(), imageVector.end(), std::default_random_engine(seed));
}

void ImageHandler::split_image(std::vector<cv::Mat3b>& src, cv::Mat3b& image)
{
    int i = 1;
    int j = 1;

    for (int r = 0; r < image.rows - 1; r += yMax)
    {
        for (int c = 0; c < image.cols - 1; c += xMax)
        {
            cv::Mat3b tile = image(cv::Range(r, yMax * i - 1), cv::Range(c, xMax * j - 1));
            src.push_back(tile);

            if (j == colNum)
            {
                break;
            }
            ++j;
        }

        j = 1;
        ++i;
    }
}

void ImageHandler::concat_image(std::vector<cv::Mat3b> &imageVector, cv::Mat3b& dest)
{
    int index = 0;
    for (int k = 0; k < dest.rows; k += yMax)
    {
        for (int l = 0; l < dest.cols - xMax; l += xMax)
        {
            cv::Rect roi(l, k, imageVector[index].cols, imageVector[index].rows);
            imageVector[index].copyTo(dest(roi));
            index++;
        }
    }
}

bool ImageHandler::areEqual(const cv::Mat& a, const cv::Mat& b)
{
    cv::Mat temp;
    cv::Mat tempA;
    cv::Mat tempB;

    cvtColor(a, tempA, CV_BGR2GRAY);
    cvtColor(b, tempB, CV_BGR2GRAY);

    cv::bitwise_xor(tempA, tempB, temp);
    return !((bool) cv::countNonZero(temp));
}
