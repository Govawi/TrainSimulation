#ifndef station
    #define station

#include "deposit.hpp"
#include "train.hpp"
#include <string>
#include <queue>

class Station
{
private:
    std::string name;
    double distance;
    std::vector<Train> rail_left;
    std::vector<Train> rail_right;
    Deposit dep_left;
    Deposit dep_right;

public:
    Station(std::string n, double d)
    {
        name = n;
        distance = d;

        dep_right();
        dep_left();
    }
    ~Station();

    std::string get_name() const { return name; }
    double get_distance() const { return distance; }
};

class Main_Station : public Station
{
public:
    Main_Station(std::string n, double d) : Station(n, d)
    {
    }
};

class Local_Station : public Station
{
public:
    Local_Station(std::string n, double d) : Station(n, d)
    {
    }
};

#endif