#ifndef station_hpp
#define station_hpp

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
    std::vector<std::shared_ptr<Train>> rail;
    Deposit dep_left;
    Deposit dep_right;

public:
    Station(std::string n, double d, bool type);

    inline void set_distance(double dis) { distance = dis; }
    inline std::string get_name() const { return name; }
    inline double get_distance() const { return distance; }
    inline bool is_local() const { return local; }
    void print() const;

    //controllo se ho binari pieni
    inline bool is_full() const { rail.size() == 2 ? true : false; }

    //gestione binari
    
};

class Main_Station : public Station
{
public:
    Main_Station(std::string n, double d) : Station(n, d, false) {}
};

class Local_Station : public Station
{
public:
    Local_Station(std::string n, double d) : Station(n, d, true) {}
};

#endif