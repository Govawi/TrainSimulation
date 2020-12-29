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
    std::queue<Train> rail_std;
    Station* left;
    Station* right;
    Deposit right;
    Deposit left;

public:
    Station(std::string n, double d)
    {
        name = n;
        distance = d;
    }
    ~Station();
    
    std::string get_name() { return name; }
    Station get_right() { return *right; }
    Station get_left() { return *left; }
    double get_distance() { return distance; }
};

class Main_Station : public Station
{
public :
    Main_Station(std::string n, double d) : Station(n, d)
    {}
};

class Local_Station : public Station
{
public :
    Local_Station(std::string n, double d) : Station(n, d)
    {}
};


#endif