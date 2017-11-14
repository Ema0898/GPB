#ifndef _POPULATION_H
#define _POPULATION_H

#include "Individual.h"

class Population
{
private:
    std::vector<Individual> population;

    Individual bestHigh;
    Individual bestMedium;
    Individual bestLow;

    Individual perfect;

    int bestFitness;

    int POPULATION = 20;

    cv::Mat3b originalImage;

public:
    Population(cv::Mat3b image);
    ~Population();

    void new_generation();
    void calculate_population_fitness();

    std::vector<Individual>* get_population();

    Individual* getBestHigh();
    Individual* getBestMedium();
    Individual* getBestLow();

    int get_best_fitnnes();

};


#endif //_POPULATION_H
