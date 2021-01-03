#include "../include/line.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

Line::Line()
{
    vector_stations();

    vector_trains();
}

void Line::vector_trains()
{
    // file -> string
    std::ifstream file("timetables.txt");
    std::string t;
    while (!file.eof())
    {
        std::getline(file, t);
        std::cout<<t<<std::endl;
        int train_number = stoi(t.substr(0, t.find(' ')));
        std::cout<<train_number<<std::endl;
        int train_direction = (int)(t.at(t.find(' ') + 1));
        std::cout<<train_direction<<std::endl;
        int train_type = (int)(t.at(t.find(' ') + 3));
        std::cout<<train_type<<std::endl;

        t = t.substr(t.at(t.find(' ')+5)); // only times
        std::vector<int> train_times;
            
        //check if only times
        std::cout<<t<<std::endl;

        int j = 0 ;
        for (int i = 0; i < stations.size() && !t.empty() ; i++)     //time_to_remove { 1 , 3 , 7 }   
        {   
            std::cout<<"ciclo "<< i <<std::endl;
            if(i == time_to_remove.at(j))
            {
                j++;
                t = t.substr(0,t.at(t.find(' ')));
            }
            else
            {
                train_times.push_back(stoi(t.substr(0,t.at(t.find(' ')))));
                std::cout<<"insert: " << stoi(t.substr(0,t.at(t.find(' ')))) <<std::endl;
                t = t.substr(t.at(t.find(' ')));
            }
        }

        // check times
        double train_velocity_km_min;
        switch (train_type)
        {
            case 1: train_velocity_km_min = 160/60; break;
            case 2: train_velocity_km_min = 240/60; break;
            case 3: train_velocity_km_min = 300/60; break;
        }
        if (train_type == 1)
        {
            int approx_time = 0;
            for (int i = 1; i < train_times.size(); i++)
            {
                approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations[i]->get_distance() - stations[i - 1]->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                if (train_times.at(i) < approx_time) 
                {
                    train_times.at(i) = approx_time;
                    std::cout << "modified time for " << stations[i]->get_name() << std::endl;
                }
            }
        }
        else if (train_type == 2 || train_type == 3)
        {
            std::vector<int> main_indexes; // assumiamo sia della stessa lunghezza di train_times
            for (int i = 0; i < stations.size(); i++)
                if (!stations[i]->is_local())
                    main_indexes.push_back(i);
                
            int approx_time = 0;
            int j = 0;
            for (int i = 1; i < train_times.size(); i++)
            {
                approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations[main_indexes.at(j)]->get_distance() - stations[main_indexes.at(j - 1)]->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                if (train_times.at(i) < approx_time) 
                {
                    train_times.at(i) = approx_time;
                    std::cout << "modified time for " << stations[main_indexes.at(j)]->get_name() << std::endl;
                }
            }
        }

        //Creazione treni
        
        if(train_type==1)
        {
            Slow_Train s(train_direction, train_number, train_times);
            trains.push_back(&s);    
        }                                    
        if(train_type==2)
        {
            Medium_Train m(train_direction, train_number, train_times);
            trains.push_back(&m);
        }
        if(train_type==3)
        {
            Fast_Train f(train_direction, train_number, train_times);
            trains.push_back(&f);
        }

        std::cout << "end fo train" << std::endl;
    }
}

void Line::vector_stations()
{
    std::string l;
    std::ifstream file("line_description.txt");
    getline(file, l);
    //creare stazione origine e push_back
    Main_Station m(l,0);
    stations.push_back(&m);
    int distance_old = 0;
    int count = 0;
        

    while (!file.eof())
    {
        getline(file, l);
        int distance = stoi(l.substr(l.rfind(' ')));

        if(distance - distance_old < 20)
        {
            time_to_remove.push_back(count++);
            std::cout << "Station at " << distance << " km removed...distance from previous was less than 20 km" << std::endl;
        }
        
        distance_old = distance;

        int type = stoi(l.substr(l.rfind(' ') - 1, 1));
        std::string name = l.substr(0, l.rfind(' ') - 2);
        //creare stazioni
        if(type == 0)
        {
    
            Main_Station ms(name,distance);
            stations.push_back(&ms);
            std::cout << "Added Main station " << name << " at " << distance << "km from original station" <<std::endl;
            count++;
        }
        else if(type == 1)
        {
            Local_Station ls(name,distance);
            stations.push_back(&ls);
            std::cout << "Added Local station " << name << " at " << distance << "km from original station" << std::endl;
            count++;
        }
        else
        {
            std::cout << "Missing station type in line : " << count << std::endl;
            throw std::exception();
        }
        
        
    }
}