#ifndef _IMAGESPLITTER_H
#define _IMAGESPLITTER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>


class ImageHandler
{
private:
    long seed;

    int rowNum;
    int colNum;

    int WIDTH;
    int HEIGHT;

    int xMax;
    int yMax;

public:
    ImageHandler(int rowNumber, int colNumber, int width, int height);
    ~ImageHandler();

    void randomize(std::vector<cv::Mat3b> &imageVector); //
    void split_image(std::vector<cv::Mat3b>& src, cv::Mat3b& image); //
    void concat_image(std::vector<cv::Mat3b>& imageVector, cv::Mat3b& dest);
    bool areEqual(const cv::Mat& a, const cv::Mat& b); //
};


#endif //_IMAGESPLITTER_H
