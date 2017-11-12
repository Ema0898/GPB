#include <iostream>
#include "genetic/Population.h"

using namespace std;
using namespace cv;

int main()
{
    cv::Mat3b hola = cv::imread("MGSPW.png");
    cv::Mat3b croppedImage = Mat3b(hola.rows, hola.cols, cv::Vec3b(0, 0, 0));

    ImageHandler* handler = new ImageHandler(5, 5, 1024, 640);
    vector<Mat3b> images;

    handler->split_image(images, hola);

    handler->concat_image(images, croppedImage);

    Population population(hola);
    Individual father;
    Individual mother;


    while (population.getBestHigh()->get_fitness() < 25)
    {
        population.calc_population_fitness();
        population.new_generation();

        imshow("hijo1", *population.getBestHigh()->getShowImage());
    }


    //vector<Individual> ind = *population.get_population();
    //vector<bool> fit = *ind[0].get_fitness_vector();
    //vector<bool> fit = *population.getBestHigh()->get_fitness_vector();

    /*father = *population.getBestHigh();
    mother = *population.getBestMedium();

    Individual* son = new Individual(*father.get_genes(), *mother.get_genes(), *father.get_fitness_vector() , *mother.get_fitness_vector(), hola);

    std::cout << father.get_fitness() << std::endl;
    std::cout << mother.get_fitness() << std::endl;
    son->init_fit_vector(images);
    son->calculate_fitness();
    std::cout << son->get_fitness() << std::endl;

    vector<bool> fit = *son->get_fitness_vector();

    for (int i = 0; i < fit.size(); ++i)
    {
        cout << fit[i] << endl;
    }

    imshow("hijo1", *population.getBestHigh()->getShowImage());
    imshow("hijo2", *population.getBestMedium()->getShowImage());
    imshow("hijo", *son->getShowImage());
    imshow("original", hola);
    //imshow("original", croppedImage);
     */

    waitKey(0);

    return 0;
}

