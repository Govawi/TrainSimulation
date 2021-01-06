#ifndef train_hpp
#define train_hpp

#include <string>
#include <vector>
#include <iostream>

class Train
{
protected:
    const int train_number;
    int velocity_curr;
    const int velocity_max;
    double distance;
    const int direction;
    int late = 0;
    std::vector<double> expected_times;
    int stations_done = 0;

public:
    Train(int i, int d, int n, std::vector<double> t);

    inline int get_train_name() const { return train_number; }
    inline int get_velocity_curr() const { return velocity_curr; }
    inline int get_velocity_max() const { return velocity_max; }
    inline double get_distance() const { return distance; }
    inline void set_velocity(int v) { velocity_curr = v; }
    inline void set_distance(double d) { distance = d; }
    inline int get_direction() const { return direction; }
    inline double get_expected_time(int index) const { return expected_times.at(index); }
    inline int get_stations_done() const { return stations_done; }
    void print() const;
};

class Fast_Train : public Train
{
public:
    Fast_Train(int d, int n, std::vector<double> t) : Train(300, d, n, t) {}
};

class Medium_Train : public Train
{
public:
    Medium_Train(int d, int n, std::vector<double> t) : Train(240, d, n, t) {}
};

class Slow_Train : public Train
{
public:
    Slow_Train(int d, int n, std::vector<double> t) : Train(160, d, n, t) {}
};

#endif
