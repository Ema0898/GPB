#include "Population.h"

Population::Population(cv::Mat3b image)
{
    originalImage = image;

    perfect = Individual(image);

    for (int i = 0; i < POPULATION; ++i)
    {
        population.push_back(Individual(image));
        population[i].randomize();
    }
}

Population::~Population()
{

    delete bestHigh;
    bestHigh = nullptr;

    delete bestMedium;
    bestMedium = nullptr;

    delete bestLow;
    bestLow = nullptr;

}

Individual* Population::getBestHigh()
{
    return &bestHigh;
}

Individual* Population::getBestMedium()
{
    return &bestMedium;
}

Individual* Population::getBestLow()
{
    return &bestLow;
}

std::vector<Individual>* Population::get_population()
{
    return &population;
}

int Population::get_best_fitnnes()
{
    return bestFitness;
}

void Population::new_generation()
{
    for (int i = 0; i < (POPULATION / 2); ++i)
    {
        population.[i] = Individual(*bestHigh.get_genes(), *bestMedium.get_genes(), *bestHigh.get_fitness_vector() , *bestMedium.get_fitness_vector());
    }

    for (int j = (POPULATION / 2); j < (POPULATION - (POPULATION / 4)); ++j)
    {
        population.[j] = Individual(*bestHigh.get_genes(), *bestLow.get_genes(), *bestHigh.get_fitness_vector() , *bestLow.get_fitness_vector());
    }

    for (int k = (POPULATION - (POPULATION / 4)); k < POPULATION; ++k)
    {
        population.[k] = Individual(*bestMedium.get_genes(), *bestLow.get_genes(), *bestMedium.get_fitness_vector() , *bestLow.get_fitness_vector());
    }
}

void Population::calc_population_fitness()
{
    int best1 = 0;
    int best2 = 0;
    int best3 = 0;

    for (int i = 0; i < POPULATION; ++i)
    {
        Individual* temp = &(population[i]);
        temp->init_fit_vector(*perfect.get_genes());
        temp->calculate_fitness();

        int fit = temp->get_fitness();

        if (fit > best1)
        {
            best3 = best2;
            best2 = best1;
            best1 = fit;
            bestLow = bestMedium;
            bestMedium = bestHigh;
            bestHigh = *temp;
        }
        else if (fit > best2)
        {
            best3 = best2;
            best2 = fit;
            bestMedium = *temp;
            bestLow = bestMedium;
        }
        else if (fit > best3)
        {
            best3 = fit;
            bestLow = *temp;
        }
    }

    bestFitness = best1;
    std::cout << std::endl;
    std::cout << "Best: " << best3 << " , " << best2 << " , " << best1 << std::endl;
}
