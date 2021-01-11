#ifndef station_hpp
#define station_hpp

#include "deposit.hpp"
#include <string>

class Station
{
protected:
    std::string name;
    double distance;
    const bool local;
    std::vector<std::shared_ptr<Train>> rail;
    std::shared_ptr<Deposit> deposit;

public:
    Station(std::string n, double d, bool type);

    inline void set_distance(double dis) { distance = dis; }
    inline std::string get_name() const { return name; }
    inline double get_distance() const { return distance; }
    inline bool is_local() const { return local; }
    void print() const;

    //controllo se ho binari pieni
    inline bool is_full() const { if (rail.size() == 2) return true; return false; }

    //gestione binari
    inline void add_rail(const std::shared_ptr<Train> p) { rail.push_back(p); }
    inline void remove_train() { rail.erase(rail.begin()); }
    inline int get_size() { return rail.size(); }
    inline std::shared_ptr<Train> get_front() { return rail.front(); }
    inline std::shared_ptr<Train> get_back() { return rail.back(); }
    void swap_train();

    //deposit
    inline std::shared_ptr<Deposit> get_deposit() { return deposit; }
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