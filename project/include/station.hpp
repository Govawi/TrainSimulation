#ifndef station
    #define station

#include "deposit.hpp"
#include "train.hpp"
#include <string>
#include <queue>

class Station
{
protected:
    std::string name;
    double distance;
    const bool local;
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
    bool is_local() const { return local; }
};

class Main_Station : public Station
{
public:
    Main_Station(std::string n, double d) : Station(n, d), local{false} {}
};

class Local_Station : public Station
{
public:
    Local_Station(std::string n, double d) : Station(n, d), local{true} {}
};

#endif