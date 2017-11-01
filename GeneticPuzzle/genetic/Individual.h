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

public:
    Individual();
    ~Individual();

    Individual* reproduce(std::vector<cv::Mat>* father1, std::vector<cv::Mat>* mother, std::vector<int>* fit_father, std::vector<int>* fit_mother);

    void calculate_fitness();
    int get_fitness();

    std::vector<bool>* get_fitness_vector();
    std::vector<cv::Mat3b>* get_genes();
};

#endif //_INDIVIDUAL_H
