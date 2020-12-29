#ifndef train
#define train

#include <string>
#include "station.hpp"

class Train
{
protected:
    int velocity_curr;
    int velocity_max;
    double distance;
    Station station_original;
    Station station_from;
    Station station_to;

public:
    Train(int i, const Station &s)
        : velocity_max{i}
    {
        velocity_curr = 0;
        station_original = s;
        station_from = s;
        if (s.get_left())
            station_to = s.get_left();
        else
            station_to = s.get_right();
        distance = 0;
    }
    ~Train();

    int get_velocity_curr() const { return velocity_curr; }
    int get_velocity_max() const { return velocity_max; }
    double get_distance() const { return distance; }
    void set_velocity(int v) { velocity_curr = v; }
    void set_distance(double d) { distance = d; }
    void set_station_from(const Station &s) { station_from = s; }
    void set_station_to(const Station &s) { station_to = s; }
    Station get_station_from() const { return station_from; }
    Station get_station_to() const { return station_to; }
    Station get_station_original() const { return station_original; }
};

class Fast_Train : public Train
{
public:
    Fast_Train(Station s) : Train(300, s) {}
};

class Medium_Train : public Train
{
public:
    Medium_Train(Station s) : Train(240, s) {}
};

class Slow_Train : public Train
{
public:
    Slow_Train(Station s) : Train(160, s) {}
};

#endif