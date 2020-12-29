#ifndef train
#define train

#include <string>
#include "station.hpp"

class Train
{
protected:
    const int train_name;
    int velocity_curr;
    const int velocity_max;
    double distance;
    const std::string station_original;

public:
    Train(int i, std::string o, int n)
        : velocity_max{i}, station_original{o}, train_name{n}
    {
        velocity_curr = 0;
        distance = 0;
    }
    ~Train();

    int get_train_name() const { return train_name; }
    int get_velocity_curr() const { return velocity_curr; }
    int get_velocity_max() const { return velocity_max; }
    double get_distance() const { return distance; }
    void set_velocity(int v) { velocity_curr = v; }
    void set_distance(double d) { distance = d; }
    std::string get_station_original() const { return station_original; }
};

class Fast_Train : public Train
{
public:
    Fast_Train(std::string s, int n) : Train(300, s, n) {}
};

class Medium_Train : public Train
{
public:
    Medium_Train(std::string s, int n) : Train(240, s, n) {}
};

class Slow_Train : public Train
{
public:
    Slow_Train(std::string s, int n) : Train(160, s, n) {}
};

#endif