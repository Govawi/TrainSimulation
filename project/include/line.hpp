#ifndef line
#define line

#include <fstream>
#include <string>
#include <vector>
#include "station.hpp"
#include "train.hpp"

class Line
{
private:
    std::vector<Train> trains;
    std::vector<Station> stations;

public:
    Line()
    {
        vector_trains();
        vector_stations();
    }
    ~Line();

    void vector_trains()
    {
        // file -> string
        ifstream file("timetable.txt");
        std::string t;
        while (!file.eof())
        {
            getline(file, t);
            int train_number = stoi(t.substr(0, t.find(' ')));
            int train_direction = stoi(t.at(t.find(' ') + 1));
            int train_type = stoi(t.at(t.find(' ') + 3)); //  xx 0 3
            std::vector<int> train_times;
            while ()
            {
                train_times.push_back(stoi(t.substring()));
            }
        }
        // controllo orari
        // string -> trains
    }

    void vector_stations()
    {
        std::string l;
        std::ifstream file("line_description.txt");
        int i = 0;
        while (!file.eof())
        {
            getline(file, l);
            std::string name = l.substr(0, l.find(' '));
            int type = (int)(l.at(l.find(' ') + 1));
            int distance = stoi(l.substr(l.find(' ') + 3, l.size()));
            if (type == 0)
                stations.at(i++) = Main_Station(name, distance);
            else
                station.at(i++) = Local_Staion(name, distance);
        }
    }

    int train_number(int n);
    int station_name(std::string n);
};

#endif