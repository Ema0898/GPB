#ifndef _INDIVIDUAL_H
#define _INDIVIDUAL_H

#include <vector>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "../imageshandler/ImageHandler.h"


class Individual
{
private:
    std::vector<cv::Mat3b> genes;
    std::vector<bool> fitnessVector;
    int fitness;

    int rows;
    int cols;
    long seed;
    int WIDTH;
    int HEIGHT;
    int xMax;
    int yMax;

    cv::Mat3b originalImage;
    cv::Mat3b showImage;

private:
    void reproduce(std::vector<cv::Mat3b>& father, std::vector<cv::Mat3b>& mother, std::vector<bool>& fit_father, std::vector<bool>& fit_mother);

public:
    Individual();
    Individual(std::vector<cv::Mat3b>& father, std::vector<cv::Mat3b>& mother, std::vector<bool>& fit_father, std::vector<bool>& fit_mother, cv::Mat3b& originalImage);
    ~Individual();

    void setImage(cv::Mat3b image);
    void init();
    void calculate_fitness();
    int get_fitness();
    void randomize();
    void init_fit_vector(std::vector<cv::Mat3b>& imageVector);

    bool areEqual(const cv::Mat& a, const cv::Mat& b);
    void split_image(cv::Mat3b& image);
    void concat_image();

    std::vector<bool>* get_fitness_vector();
    std::vector<cv::Mat3b>* get_genes();
    cv::Mat3b* getShowImage();
};

#endif //_INDIVIDUAL_H
