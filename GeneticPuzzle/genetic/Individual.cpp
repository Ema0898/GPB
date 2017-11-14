#include "Individual.h"

Individual::Individual()
{
    rows = 5;
    cols = 5;
    fitness = 0;
    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

Individual::Individual(std::vector<cv::Mat3b>& father, std::vector<cv::Mat3b>& mother, std::vector<bool>& fit_father, std::vector<bool>& fit_mother, cv::Mat3b& originalImage)
{
    rows = 5;
    cols = 5;
    fitness = 0;
    setImage(originalImage);
    init();
    reproduce(father, mother, fit_father, fit_mother);

    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void Individual::setImage(cv::Mat3b image)
{
    originalImage = image;
}

void Individual::init()
{
    WIDTH = originalImage.cols;
    HEIGHT = originalImage.rows;

    xMax = (WIDTH / rows);
    yMax = (HEIGHT / cols);

    showImage = cv::Mat3b(originalImage.rows, originalImage.cols, cv::Vec3b(0,0,0));
    split_image(originalImage);

    /*split_image(originalImage);
    randomize();
    concat_image();

    cv::imshow("Showing Image", showImage);
    cv::waitKey(0);
    */
}

Individual::~Individual()
{
}

void Individual::reproduce(std::vector<cv::Mat3b> &father, std::vector<cv::Mat3b> &mother, std::vector<bool> &fit_father, std::vector<bool> &fit_mother)
{

    for (int i = 0; i < (rows * cols); ++i)
    {
        if (fit_father[i] && !fit_mother[i])
        {
            genes[i] = father[i];
        }
        else if (fit_mother[i] && !fit_father[i])
        {
            genes[i] = mother[i];
        }
        else if (!fit_father[i] && !fit_mother[i])
        {
            cv::Mat3b blackRect(yMax - 1, xMax - 1, cv::Vec3b(0, 0, 0));
            genes[i] = blackRect;
        }
    }

    std::vector<cv::Mat3b> missingImages;

    for (int i = 0; i < father.size(); ++i)
    {
        bool isMarked = false;

        for (int j = 0; j < genes.size(); ++j)
        {
            if (areEqual(genes[j], father[i]))
            {
                isMarked = true;
            }
        }

        if (!isMarked)
        {
            missingImages.push_back(father[i]);
        }
    }

    std::shuffle(missingImages.begin(), missingImages.end(), std::default_random_engine(seed));

    int iterator = 0;

    for (int i = 0; i < (rows * cols); ++i)
    {
        if (!(fit_father[i]) && !(fit_mother[i]))
        {
            genes[i] = missingImages[iterator];
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

void Individual::split_image(cv::Mat3b& image)
{
    int i = 1;
    int j = 1;

    for (int r = 0; r < image.rows - 1; r += yMax)
    {
        for (int c = 0; c < image.cols - 1; c += xMax)
        {
            cv::Mat3b tile = image(cv::Range(r, yMax * i - 1), cv::Range(c, xMax * j - 1));
            genes.push_back(tile);

            if (j == cols)
            {
                break;
            }
            ++j;
        }

        j = 1;
        ++i;
    }
}

void Individual::init_fit_vector(std::vector<cv::Mat3b>& imageVector)
{
    fitnessVector.clear();

    for (int i = 0; i < (rows * cols); ++i)
    {
        if (areEqual(imageVector[i], genes[i]))
        {
            fitnessVector.push_back(true);
        }
        else
        {
            fitnessVector.push_back(false);
        }
    }

}

void Individual::concat_image()
{
    int index = 0;
    for (int y = 0; y < showImage.rows; y += yMax)
    {
        for (int x = 0; x < showImage.cols - xMax; x += xMax)
        {
            cv::Rect roi(x, y, genes[index].cols, genes[index].rows);
            genes[index].copyTo(showImage(roi));
            index++;
        }
    }
}

void Individual::randomize()
{
    std::shuffle(genes.begin(), genes.end(), std::default_random_engine(seed));
}

bool Individual::areEqual(const cv::Mat &a, const cv::Mat &b)
{
    cv::Mat temp;
    cv::Mat tempA;
    cv::Mat tempB;

    cvtColor(a, tempA, CV_BGR2GRAY);
    cvtColor(b, tempB, CV_BGR2GRAY);

    cv::bitwise_xor(tempA, tempB, temp);
    return !((bool) cv::countNonZero(temp));
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

cv::Mat3b* Individual::getShowImage()
{
    concat_image();
    return &showImage;
}
