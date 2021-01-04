#include "../include/line.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

Line::Line()
    : line_st{}
{
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**  STATIONS INPUT  **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;
    vector_stations();
    std::cout << std::endl;
    print_line();
    std::cout << "> Stations Input OK" << std::endl;
    
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**   TRAINS INPUT   **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;
    vector_trains();
    std::cout << std::endl;
    print_train();
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
        int train_number = stoi(t.substr(0, t.find(' ')));
        int train_direction = stoi(t.substr(t.find(' ') + 1), 0);
        int train_type = stoi(t.substr(t.find(' ') + 3), 0);
        t = t.substr(t.find(' ') + 5); // only times
        std::vector<int> train_times;

        int j = 0;
        for (int i = 0; i < stations.size() && t.size() != 0; i++) //time_to_remove { 1 , 3 , 7 }
        {
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
                
                std::cout<< "time from table: "<< train_times.at(i) << " estimated time: " << approx_time << std::endl;
                
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
            line_st.add_slow(train_direction,train_number,train_times);
            trains.push_back(line_st.get_slow_at(line_st.get_num_slow()-1));
        }
        if (train_type == 2)
        {
            line_st.add_medium(train_direction,train_number,train_times);
            trains.push_back(line_st.get_medium_at(line_st.get_num_medium()-1));
        }
        if (train_type == 3)
        {
            line_st.add_fast(train_direction,train_number,train_times);
            trains.push_back(line_st.get_fast_at(line_st.get_num_fast()-1));
        }

        std::cout<<"Train Done"<<std::endl<<std::endl;

    }
}

void Line::vector_stations()
{
    std::string l;
    std::ifstream file("line_description.txt");
    getline(file, l);

    //creare stazione origine e push_back
    line_st.add_main(l,0);
    stations.push_back(line_st.get_main_at(0));
    std::cout << "Added Origin station " << l << std::endl;

    int distance_old = 0;
    int count = 0;

    while (!file.eof())
    {
        getline(file, l);
        int distance = stoi(l.substr(l.rfind(' ')));

        if (distance - distance_old < 20)
        {
            time_to_remove.push_back(count++);
            std::cout << "Station at " << distance << " km removed...distance from previous was less than 20 km" << std::endl;
        }

        distance_old = distance;

        int type = stoi(l.substr(l.rfind(' ') - 1, 1));
        std::string name = l.substr(0, l.rfind(' ') - 2);
        //creare stazioni
        if (type == 0)
        {
            line_st.add_main(name,distance);
            stations.push_back(line_st.get_main_at(line_st.get_num_main()-1));
            std::cout << "Added Main station " << name << " at " << distance << "km" << std::endl;
            count++;
        }
        else if (type == 1)
        {
            line_st.add_local(name,distance);
            stations.push_back(line_st.get_local_at(line_st.get_num_local()-1));
            std::cout << "Added Local station " << name << " at " << distance << "km" << std::endl;
            count++;
        }
        else
        {
            std::cout << "Missing station type in line : " << count << std::endl;
            throw std::exception();
        }
    }

}

void Line::print_line()
{
    std::cout<<"Origin Station : " << line_st.get_main_at(0)->get_name() << std::endl;

    for(int i=1; i<stations.size(); i++)
    {
        if(stations.at(i)->is_local())
            std::cout<<"Local Station  : ";
        else
            std::cout<<"Main Station   : ";
        std::cout << stations.at(i)->get_name() << std::endl;
        
    }
}

void Line::print_train()
{
    for(int i=0; i<trains.size(); i++)
    {
        std::cout<<"Times for ";
        if(trains.at(i)->get_velocity_max() == 300)
            std::cout<<"Fast ";
        else if(trains.at(i)->get_velocity_max() == 240)
            std::cout<<"Medium ";
        else
            std::cout<<"Slow ";
        std::cout << "train number : "<< trains.at(i)->get_train_name() << std::endl;

        trains.at(i)->print_times();
    }
}