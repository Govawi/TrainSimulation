#ifndef train_hpp
#define train_hpp

#include <iostream>
#include <vector>

class Train
{
protected:
    const int train_number;
    double velocity_curr;
    const double velocity_max;
    double distance;
    const int direction;
    int delay = 0;
    std::vector<double> expected_times;
    int stations_done = 0;

    //contatore per stop alla stazione
    int stop = 0;
    bool deposit = false;

public:
    Train(double i, int d, int n, std::vector<double> t);

    inline int get_train_name() const { return train_number; }
    inline double get_velocity_curr() const { return velocity_curr; }
    inline double get_velocity_max() const { return velocity_max; }
    inline double get_distance() const { return distance; }
    inline void set_velocity(double v) { velocity_curr = v; }
    inline void set_distance(double d) { distance = d; }
    inline int get_direction() const { return direction; }
    inline int get_delay() const { return delay; }
    inline void increase_delay(int l) { delay += l; }
    inline double get_expected_time(int index) const { return expected_times.at(index); }
    inline void increase_stations_done() { stations_done++; }
    inline int get_stations_done() const { return stations_done; }
    void print() const;

    inline int get_stop() const { return stop; }
    inline void set_stop(int s) { stop = s; }
    inline void decrease_stop() { (stop <= 1) ? stop = 0 : stop--; }
    inline bool get_deposit() { return deposit; }
    inline void set_deposit(bool b) { deposit = b; }
};

class Fast_Train : public Train
{
public:
    Fast_Train(int d, int n, std::vector<double> t) : Train(5, d, n, t) {}
};

class Medium_Train : public Train
{
public:
    Medium_Train(int d, int n, std::vector<double> t) : Train(4, d, n, t) {}
};

class Slow_Train : public Train
{
public:
    Slow_Train(int d, int n, std::vector<double> t) : Train(2.7, d, n, t) {}
};

#endif
