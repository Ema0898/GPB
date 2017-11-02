#ifndef _POPULATION_H
#define _POPULATION_H

#include "Individual.h"

class Population
{
private:
    std::vector<Individual*> population;
    std::vector<Individual*> bestIndividual;
    int bestFitness;

    const int INITIAL_POPULATION = 1;

    cv::Mat3b originalImage;

public:
    Population(cv::Mat3b image);
    ~Population();

    void new_generation();
    void reproduce(std::vector<cv::Mat>* father1, std::vector<cv::Mat>* mother, std::vector<bool>* fit_father, std::vector<bool>* fit_mother);
    void calc_population_fitness();

    std::vector<Individual*>* get_population();
    std::vector<Individual*>* get_best3();
    int get_best_fitnnes();

};


#endif //_POPULATION_H
