#ifndef _IMAGESPLITTER_H
#define _IMAGESPLITTER_H

#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"


class ImageHandler
{
private:
    std::vector<cv::Mat3b> smallImages;
    std::vector<cv::Mat3b> shuffleImages;
    std::vector<int> seeds;

    int rowNum;
    int colNum;

    int WIDTH;
    int HEIGHT;

    int xMax;
    int yMax;

    cv::Mat3b image;
    cv::Mat3b croppedImg;

private:
    void init_seed();
    void shuffle_image();

public:
    ImageHandler(int rowNumber, int colNumber, int width, int height, std::string src);
    ~ImageHandler();

    std::vector<cv::Mat3b>* get_original_images();
    std::vector<cv::Mat3b>* get_shuffle_images();

    void split_image();
    void concat_image();
    bool areEqual(const cv::Mat& a, const cv::Mat& b);
    void show_image();
};


#endif //_IMAGESPLITTER_H
