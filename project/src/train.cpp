#include "../include/train.hpp"

Train::Train(int i, int d, int n, std::vector<double> t)
    : velocity_max{i}, direction{d}, train_name{n}
{
    velocity_curr = 0;
    distance = 0;
    expected_times = t;
}

void Train::print_times() const
{
    for(int i=0; i<expected_times.size(); i++)
        std::cout<< "Stazione "<< i << " : " << expected_times.at(i) << std::endl;
}
