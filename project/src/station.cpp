#include "station.hpp"

Station::Station(std::string n, double d, bool type)
    : local{type}
{
    name = n;
    distance = d;

    Deposit dep_right;
    Deposit dep_left;
}

void Station::print() const
{
    std::cout << "name:     " << name << std::endl;
    std::cout << "local:    " << local << std::endl;
    std::cout << "distance: " << distance << "km" << std::endl;
    std::cout << std::endl;
}