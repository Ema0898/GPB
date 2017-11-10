#include "Individual.h"

Individual::Individual(cv::Mat3b image)
{
    rows = 5;
    cols = 5;

    originalImage = image;
    imageHandler = new ImageHandler(rows, cols, originalImage.rows, originalImage.cols);
    fitness = 0;

    imageHandler->split_image(genes, originalImage);
}

Individual::Individual(std::vector<cv::Mat3b>& father, std::vector<cv::Mat3b>& mother, std::vector<bool>& fit_father, std::vector<bool>& fit_mother)
{
    reproduce(father, mother, fit_father, fit_mother);
}

Individual::~Individual()
{
    delete imageHandler;
    imageHandler = nullptr;
}

void Individual::reproduce(std::vector<cv::Mat3b> &father, std::vector<cv::Mat3b> &mother, std::vector<bool> &fit_father, std::vector<bool> &fit_mother)
{
    for (int i = 0; i < (rows * cols); ++i)
    {
        if (fit_father[i] && !fit_mother[i])
        {
            genes[i] = father[i];
        }

        if (fit_mother[i] && !fit_father[i])
        {
            genes[i] = mother[i];
        }

        if (!fit_father[i] && !fit_mother[i])
        {
            cv::Mat3b blackRect(originalImage.rows, originalImage.cols, cv::Scalar(0, 0, 0));
            genes[i] = blackRect;
        }
    }

    std::vector<cv::Mat3b> missingImages;

    for (int i = 0; i < father.size(); ++i)
    {
        bool isMarked = false;

        for (int j = 0; j < genes.size(); ++j)
        {
            if (imageHandler->areEqual(genes[j], father[i]))
            {
                isMarked = true;
            }
        }

        if (!isMarked)
        {
            missingImages.push_back(father[i]);
        }
    }

    imageHandler->randomize(missingImages);

    int iterator = 0;

    for (int i = 0; i < (rows * cols); ++i)
    {
        if (!(fit_father[i]) && !(fit_mother[i]))
        {
            genes[i] = missingImages.[iterator];
            ++iterator;
        }
    }
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

void Individual::init_fit_vector(std::vector<cv::Mat3b> &imageVector)
{
    for (int i = 0; i < genes.size(); ++i)
    {
        if (imageHandler->areEqual(imageVector[i], genes[i]))
        {
            fitnessVector.push_back(1);
        }
        else
        {
            fitnessVector.push_back(0);
        }
    }
}

void Individual::randomize()
{
    imageHandler->randomize(genes);
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
