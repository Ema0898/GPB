#include "Individual.h"

Individual::Individual()
{
    fitness = 0;
}

Individual::~Individual()
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
