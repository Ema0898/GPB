#include <iostream>
#include "genetic/Population.h"
#include "camera/Camera.h"

using namespace std;
using namespace cv;

int main()
{
    Camera camera;
    //camera.useCamera();

    cv::Mat3b hola = cv::imread("MGSPW.png");
    //cv::Mat3b hola = cv::imread("capture.png");

    Population population(hola);

    while (population.getBestHigh()->get_fitness() < 25)
    {
        population.calculate_population_fitness();
        population.new_generation();

        imshow("hijo1", *population.getBestHigh()->getShowImage());
        imshow("hijo2", *population.getBestMedium()->getShowImage());
        imshow("hijo3", *population.getBestLow()->getShowImage());
        waitKey(0);
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

    return 0;
}

