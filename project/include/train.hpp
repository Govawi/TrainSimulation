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
    const int direction;
    int late = 0, departure;
    std::vector<int> expected_times;
    int stations_done = 0;

public:
    Train(int i, int d, int n, std::vector<int> t)
        : velocity_max{i}, direction{d}, train_name{n}
    {
        velocity_curr = 0;
        distance = 0;
        expected_times = t;
    }
    ~Train();

    inline int    get_train_name()       const { return train_name       ; }
    inline int    get_velocity_curr()    const { return velocity_curr    ; }
    inline int    get_velocity_max()     const { return velocity_max     ; }
    inline double get_distance()         const { return distance         ; }
    inline void   set_velocity(int v)          {        velocity_curr = v; }
    inline void   set_distance(double d)       {        distance = d     ; }
    inline int    get_direction()        const { return direction        ; }
    inline int    get_stations_done()    const { return stations_done    ; }
};

class Fast_Train : public Train
{
public:
    Fast_Train(int d, int n, std::vector<int> t) : Train(300, d, n, t) {}
};

class Medium_Train : public Train
{
public:
    Medium_Train(int d, int n, std::vector<int> t) : Train(240, d, n, t) {}
};

class Slow_Train : public Train
{
public:
    Slow_Train(int d, int n, std::vector<int> t) : Train(160, d, n, t) {}
};

#endif