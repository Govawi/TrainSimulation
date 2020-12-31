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
        std::ifstream file("timetable.txt");
        std::string t;
        while (!file.eof())
        {
            std::getline(file, t);
            int train_number = stoi(t.substr(0, t.find(' ')));
            int train_direction = (int)(t.at(t.find(' ') + 1));
            int train_type = (int)(t.at(t.find(' ') + 3)); //  xx 0 3
            std::vector<int> train_times;
            while (/*condizione*/)
            {
                train_times.push_back(stoi(t.substr()));
            }
        }
        // controllo orari
        // string -> trains
    }

    void vector_stations()
    {
        std::string l;
        std::ifstream file("line_description.txt");
        getline(file, l);
        //creare stazione origine e push_back
        stations.push_back(Main_Station(l,0));

        while (!file.eof())
        {
            getline(file, l);
            int distance = stoi(l.substr(l.rfind(' ')));
            int type = stoi(l.substr(l.rfind(' ') - 1, 1));
            std::string name = l.substr(0, l.rfind(' ') - 2);
            //creare stazioni
            if(type == 0)
                stations.push_back(Main_Station(name,distance));
            else if(type == 0)
                stations.push_back(Local_Station(name,distance));
            else
            {
                cout << "Missing station type in line : " << stations.size() << endl;
                throw std::exception();
            }

        }
    }

    int train_number(int n);
    int station_name(std::string n);
};

#endif
