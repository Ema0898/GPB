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

    cv::Mat3b originalImage;
    ImageHandler* imageHandler;

private:
    void reproduce(std::vector<cv::Mat3b>& father, std::vector<cv::Mat3b>& mother, std::vector<bool>& fit_father, std::vector<bool>& fit_mother);

public:
    Individual(cv::Mat3b image);
    Individual(std::vector<cv::Mat3b>& father, std::vector<cv::Mat3b>& mother, std::vector<bool>& fit_father, std::vector<bool>& fit_mother);
    ~Individual();

    void calculate_fitness();
    int get_fitness();
    void randomize();
    void init_fit_vector(std::vector<cv::Mat3b> &imageVector);

    std::vector<bool>* get_fitness_vector();
    std::vector<cv::Mat3b>* get_genes();
};

#endif //_INDIVIDUAL_H
