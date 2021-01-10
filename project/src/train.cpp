#include "../include/train.hpp"

Train::Train(double i, int d, int n, std::vector<double> t)
    : velocity_max{i}, direction{d}, train_number{n}
{
    velocity_curr = 0;
    distance = 0;
    expected_times = t;
}

void Train::print() const
{
    std::cout << "number:    " << train_number << std::endl;
    std::cout << "max velocity:  " << velocity_max << std::endl;
    std::cout << "direction: " << direction << std::endl;
    for (int i = 0; i < expected_times.size(); i++)
        std::cout << " - station: " << i << " - time: " << expected_times.at(i) << std::endl;
    std::cout << std::endl;
}
