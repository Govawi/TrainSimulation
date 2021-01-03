#include "../include/line.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

Line::Line()
{
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**  STATIONS INPUT  **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;
    vector_stations();
    std::cout << "> Stations Input OK" << std::endl;
    
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**   TRAINS INPUT   **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;
    vector_trains();
    std::cout << "> Trains Input OK" << std::endl;
}

void Line::vector_trains()
{
    // file -> string
    std::ifstream file("timetables.txt");
    std::string t;
    while (!file.eof())
    {
        std::getline(file, t);
        std::cout << t << std::endl;
        int train_number = stoi(t.substr(0, t.find(' ')));
        std::cout << "  train number: " << train_number << std::endl;

        std::cout << t << std::endl;

        int train_direction = stoi(t.substr(t.find(' ') + 1), 0);
        std::cout << "  train direction: " << train_direction << std::endl;

        std::cout << t << std::endl;

        int train_type = stoi(t.substr(t.find(' ') + 3), 0);
        std::cout << "  train type: " << train_type << std::endl;

        t = t.substr(t.find(' ') + 5); // only times
        std::vector<int> train_times;

        int j = 0;
        for (int i = 0; i < stations.size() && t.size() != 0; i++) //time_to_remove { 1 , 3 , 7 }
        {
            //check if only times
            std::cout << t << std::endl;

            std::cout << "  ciclo " << i << std::endl;
            if (i == time_to_remove.at(j))
            {
                j++;
                if(t.find(' ') != std::string::npos)
                    t = t.substr(t.find(' ') + 1);
                else
                    t = "";

            }
            else
            {
                train_times.push_back(stoi(t.substr(0, t.find(' '))));
                std::cout << "  insert: " << stoi(t.substr(0, t.find(' '))) << std::endl;
                if(t.find(' ') != std::string::npos)
                    t = t.substr(t.find(' ') + 1);
                else
                    t = "";
            }
        }

        // check times
        double train_velocity_km_min;
        switch (train_type)
        {
        case 1:
            train_velocity_km_min = 160 / 60;
            break;
        case 2:
            train_velocity_km_min = 240 / 60;
            break;
        case 3:
            train_velocity_km_min = 300 / 60;
            break;
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
                    std::cout << "  modified time for " << stations.at(i)->get_name() << std::endl;
                }
            }
        }
        else if (train_type == 2 || train_type == 3)
        {
            std::vector<int> main_indexes; // assumiamo sia della stessa lunghezza di train_times
            for (int i = 0; i < stations.size(); i++)
                if (!stations[i]->is_local())
                    main_indexes.push_back(i);

            double approx_time = 0;
            int j = 1;
            for (int i = 1; i < train_times.size(); i++)
            {
                approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(j))->get_distance() - stations.at(main_indexes.at(j - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60

                std::cout<< "time from table: "<< train_times.at(i) << " estimated time: " << approx_time << std::endl;

                if (train_times.at(i) < approx_time)
                {
                    train_times.at(i) = approx_time;
                    std::cout << "  modified time for " << stations.at(main_indexes.at(j))->get_name() << std::endl;
                }
                j++;
            }
        }

        //Creazione treni

        if (train_type == 1)
        {
            Slow_Train s(train_direction, train_number, train_times);
            trains.push_back(&s);
        }
        if (train_type == 2)
        {
            Medium_Train m(train_direction, train_number, train_times);
            trains.push_back(&m);
        }
        if (train_type == 3)
        {
            Fast_Train f(train_direction, train_number, train_times);
            trains.push_back(&f);
        }

        std::cout << "  end fo train" << std::endl;
    }
}

void Line::vector_stations()
{
    std::string l;
    std::ifstream file("line_description.txt");
    getline(file, l);
    //creare stazione origine e push_back
    Main_Station m(l, 0);
    stations.push_back(&m);
    int distance_old = 0;
    int count = 0;

    while (!file.eof())
    {
        getline(file, l);
        int distance = stoi(l.substr(l.rfind(' ')));

        if (distance - distance_old < 20)
        {
            time_to_remove.push_back(count++);
            std::cout << "  Station at " << distance << " km removed...distance from previous was less than 20 km" << std::endl;
        }

        distance_old = distance;

        int type = stoi(l.substr(l.rfind(' ') - 1, 1));
        std::string name = l.substr(0, l.rfind(' ') - 2);
        //creare stazioni
        if (type == 0)
        {
            main_stations.push_back(Main_Station(name, distance));
            stations.push_back(&main_stations.back());
            std::cout << "  Added Main station " << name << " at " << distance << "km from original station" << std::endl;
            count++;
        }
        else if (type == 1)
        {
            local_stations.push_back(Local_Station(name, distance));
            stations.push_back(&local_stations.back());
            std::cout << "      Added Local station " << name << " at " << distance << "km from original station" << std::endl;
            count++;
        }
        else
        {
            std::cout << "Missing station type in line : " << count << std::endl;
            throw std::exception();
        }
    }
}