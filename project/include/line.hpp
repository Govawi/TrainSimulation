#include <string>
#include <vector>
#include "station.hpp"
#include "train.hpp"

class Line
{
public:
    std::vector<Train> trains;
    std::vector<Station> stations;

    Line(const std::vector<std::string> &t, const std::vector<std::string> &l);
    ~Line();

    int train_number(int n);
    int station_name(std::string n);
};