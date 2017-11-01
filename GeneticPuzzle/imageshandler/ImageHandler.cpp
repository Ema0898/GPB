#include "ImageHandler.h"

ImageHandler::ImageHandler(int rowNumber, int colNumber, int width, int height, std::string src)
{
    rowNum = rowNumber;
    colNum = colNumber;

    WIDTH = width;
    HEIGHT = height;

    xMax = WIDTH / rowNum;
    yMax = HEIGHT / colNum;

    image = cv::imread(src);
    croppedImg = cv::Mat3b(image.rows, image.cols, cv::Vec3b(0,0,0));
}

ImageHandler::~ImageHandler()
{

}

std::vector<cv::Mat3b>* ImageHandler::get_original_images()
{
    return &smallImages;
}

std::vector<cv::Mat3b>* ImageHandler::get_shuffle_images()
{
    return &shuffleImages;
}

void ImageHandler::init_seed()
{
    for (int index = 0; index < smallImages.size(); ++index)
    {
        seeds.push_back(index);
    }
}

void ImageHandler::shuffle_image()
{
    init_seed();

    cv::randShuffle(seeds);

    for (int current = 0; current < smallImages.size(); current++)
    {
        shuffleImages.push_back(smallImages[seeds[current]]);
    }
}

void ImageHandler::split_image()
{

    int i = 1;
    int j = 1;

    for (int r = 0; r < image.rows - 1; r += yMax)
    {
        for (int c = 0; c < image.cols - 1; c += xMax)
        {
            cv::Mat3b tile = image(cv::Range(r, yMax * i - 1), cv::Range(c, xMax * j - 1));
            //imshow("smallImages", tile);
            smallImages.push_back(tile);

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

void ImageHandler::concat_image()
{
    shuffle_image();

    int index = 0;
    for (int k = 0; k < croppedImg.rows; k += yMax)
    {
        for (int l = 0; l < croppedImg.cols - xMax; l += xMax)
        {
            // Select the roi in the grid
            cv::Rect roi(l, k, shuffleImages[index].cols, shuffleImages[index].rows);

            // Copy the image into the roi
            shuffleImages[index].copyTo(croppedImg(roi));
            index++;
        }
    }
}

bool ImageHandler::areEqual(const cv::Mat& a, const cv::Mat& b)
{
    cv::Mat temp;
    cv::Mat tempA;
    cv::Mat tempB;

    cvtColor(a, tempA, CV_BGR2GRAY );
    cvtColor(b, tempB, CV_BGR2GRAY );

    cv::bitwise_xor(tempA, tempB, temp); //It vectorizes well with SSE/NEON
    return !((bool) cv::countNonZero(temp));
}

void ImageHandler::show_image()
{
    cv::imshow("Image", croppedImg);
}
