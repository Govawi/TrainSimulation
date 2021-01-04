#ifndef line
#define line

#include <vector>
#include "station.hpp"
#include "train.hpp"

class Line_Storage
{
private:
    std::vector<Main_Station> main_stations;
    std::vector<Local_Station> local_stations;

    std::vector<Fast_Train> fast_train;
    std::vector<Medium_Train> medium_train;
    std::vector<Slow_Train> slow_train;

public:
    inline void add_main(std::string name, double distance) { main_stations.push_back(Main_Station(name,distance)); }
    inline void add_local(std::string name, double distance) { local_stations.push_back(Local_Station(name,distance)); } 
    inline Station* get_main_at(int index) { return &main_stations.at(index); }
    inline Station* get_local_at(int index) { return &local_stations.at(index); }
    inline int get_num_main() { return main_stations.size(); }
    inline int get_num_local() { return local_stations.size(); }

    inline void add_fast(int direction, int name, std::vector<int> times) {fast_train.push_back(Fast_Train(direction,name,times)); }
    inline void add_medium(int direction, int name, std::vector<int> times) {medium_train.push_back(Medium_Train(direction,name,times)); }
    inline void add_slow(int direction, int name, std::vector<int> times) {slow_train.push_back(Slow_Train(direction,name,times)); }
    inline Train* get_fast_at(int index) { return &fast_train.at(index); }
    inline Train* get_medium_at(int index) { return &medium_train.at(index); }
    inline Train* get_slow_at(int index) { return &slow_train.at(index); }
    inline int get_num_fast() { return fast_train.size(); }
    inline int get_num_medium() { return medium_train.size(); }
    inline int get_num_slow() { return slow_train.size(); }
};

class Line
{
private:
    std::vector<Train*> trains;
    std::vector<Station*> stations;
    std::vector<int> time_to_remove;
    Line_Storage line_st;

public:
    Line();
    //~Line();
    
    void vector_trains();
    void vector_stations();
};

#endif
