#include "Individual.h"

Individual::Individual()
{
    fitness = 0;
}

Individual::~Individual()
{

}

Individual* Individual::reproduce(std::vector<cv::Mat>* father1, std::vector<cv::Mat>* mother, std::vector<int>* fit_father, std::vector<int>* fit_mother)
{

}

void Individual::calculate_fitness()
{
    int counter = 0;

    for (int i = 0; i < fitnessVector.size(); ++i)
    {
        if (fitnessVector[i])
        {
            counter++;
        }
    }

    fitness = counter;
}

int Individual::get_fitness()
{
    return fitness;
}

std::vector<bool>* Individual::get_fitness_vector()
{
    return &fitnessVector;
}

std::vector<cv::Mat3b>* Individual::get_genes()
{
    return &genes;
}
