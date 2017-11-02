#include "Population.h"

Population::Population(cv::Mat3b image)
{
    originalImage = image;
}

Population::~Population()
{
    for (int i = 0; i < population.size(); ++i)
    {
        delete population[i];
        population[i] = nullptr;
    }

    for (int j = 0; j < bestIndividual.size(); ++j)
    {
        delete bestIndividual[j];
        population[j] = nullptr;
    }
}

std::vector<Individual*>* Population::get_population()
{
    return &population;
}

std::vector<Individual*>* Population::get_best3()
{
    return &bestIndividual;
}

int Population::get_best_fitnnes()
{
    return bestFitness;
}

void Population::new_generation()
{

}

void Population::reproduce(std::vector<cv::Mat> *father1, std::vector<cv::Mat> *mother, std::vector<bool> *fit_father, std::vector<bool> *fit_mother)
{

}

void Population::calc_population_fitness()
{

}
