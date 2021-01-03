#ifndef line
#define line

#include <vector>
#include "station.hpp"
#include "train.hpp"

class Line
{
private:
    std::vector<Train*> trains;
    std::vector<Station*> stations;
    std::vector<int> time_to_remove;

public:
    Line();
    //~Line();
    
    void vector_trains();
    void vector_stations();
};

#endif
