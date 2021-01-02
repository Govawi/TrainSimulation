#ifndef line
#define line

#include <queue>
#include <iostream>
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
    std::queue<int> time_to_remove;

public:
    Line()
    {
        vector_stations();

        vector_trains();
    }
    ~Line();

    int schedule(int num_station,int type)
    {
        int velocity = 0;
        int time = 0;
        if(type == 1)
            velocity = 160;
        if(type == 2)
            velocity = 240;
        else
            velocity = 300;
        
        time = times[num_station-1] + 10*80 + velocity * (stations[num_station].get_distance() - stations[num_station-1].get_distance());
    }

    void check_times(vector<int>& times,int type)
    {
        for(int i=0; i<times.size(); i++)
        {
            if(times[i] < schedule(i,type))
        }

        while(times.size() < stations.size())
        {

        }
        
    }

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
            int train_type = (int)(t.at(t.find(' ') + 3));

            t = t.substr(t.at(t.find(' ') + 5));
            std::vector<int> train_times;
            
            int remove = time_to_remove.front();
            time_to_remove.pop();
            int i = 0 ;

            while (i < stations.size() && !t.empty())     //time_to_remove { 1 , 3 , 7 }   
            {   
                if(i == remove)
                {
                    remove = time_to_remove.front();
                    time_to_remove.pop();
                    t = t.substr(0,t.at(t.find(' ')));
                    i++;
                }
                train_times.push_back(stoi(t.substr(0,t.at(t.find(' ')))));
                i++;
            }
        }
        
        check_times(vector<int> train_times,train_type);
        
        if(train_type==1)
            trains.push_back(Slow_Train(train_direction, train_number, train_times));                                          
        if(train_type==2)
            trains.push_back(Medium_Train(train_direction, train_number, train_times));
        if(train_type==3)
            trains.push_back(Fast_Train(train_direction, train_number, train_times));
        
    }

    void vector_stations()
    {
        std::string l;
        std::ifstream file("line_description.txt");
        getline(file, l);
        //creare stazione origine e push_back
        stations.push_back(Main_Station(l,0));
        int distance_old = 0;
        int count = 0;
        

        while (!file.eof())
        {
            getline(file, l);
            int distance = stoi(l.substr(l.rfind(' ')));

            if(distance - distance_old < 20)
            {
                time_to_remove.push(count++);
                std::cout << "Station at " << distance << " km removed...distance from previous was less than 20 km" << std::endl;
                continue;
            }

            distance_old = distance;

            int type = stoi(l.substr(l.rfind(' ') - 1, 1));
            std::string name = l.substr(0, l.rfind(' ') - 2);
            //creare stazioni
            if(type == 0)
            {
                stations.push_back(Main_Station(name,distance));
                count++;
            }
            else if(type == 1)
            {
                stations.push_back(Local_Station(name,distance));
                count++;
            }
            else
            {
                std::cout << "Missing station type in line : " << count << std::endl;
                throw std::exception();
            }

        }
    }

    int train_number(int n);
    int station_name(std::string n);
};

#endif
