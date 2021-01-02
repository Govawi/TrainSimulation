#include "../include/train.hpp"

Train::Train(int i, int d, int n, std::vector<int> t)
    : velocity_max{i}, direction{d}, train_name{n}
{
    velocity_curr = 0;
    distance = 0;
    expected_times = t;
}