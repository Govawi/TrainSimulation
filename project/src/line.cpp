#include "../include/line.hpp"

Line::Line()
{
    vector_stations();

    vector_trains();
}

void Line::vector_trains()
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

        t = t.substr(t.at(t.find(' ') + 5)); // only times
        std::vector<int> train_times;
            
        int j = 0 ;
        for (int i = 0; i < stations.size() && !t.empty(); i++)     //time_to_remove { 1 , 3 , 7 }   
        {   
            if(i == time_to_remove.at(j))
            {
                j++;
                t = t.substr(0,t.at(t.find(' ')));
            }
            else
            {
                train_times.push_back(stoi(t.substr(0,t.at(t.find(' ')))));
                t = t.substr(0,t.at(t.find(' ')));
                std::cout << "added time in station " << i << std::endl;
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
                approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations.at(i).get_distance() - stations.at(i - 1).get_distance() - 10) / train_velocity_km_min); // 7.5 = 10/80/60
                if (train_times.at(i) < approx_time) 
                {
                    train_times.at(i) = approx_time;
                    std::cout << "modified time for " << stations.at(i).get_name() << std::endl;
                }
            }
        }
        else if (train_type == 2 || train_type == 3)
        {
            std::vector<int> main_indexes; // assumiamo sia della stessa lunghezza di train_times
            for (int i = 0; i < stations.size(); i++)
                if (!stations.at(i).is_local())
                    main_indexes.push_back(i);
                
            int approx_time = 0;
            int j = 0;
            for (int i = 1; i < train_times.size(); i++)
            {
                approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(j)).get_distance() - stations.at(main_indexes.at(j - 1)).get_distance() - 10) / train_velocity_km_min); // 7.5 = 10/80/60
                if (train_times.at(i) < approx_time) 
                {
                    train_times.at(i) = approx_time;
                    std::cout << "modified time for " << stations.at(main_indexes.at(j)).get_name() << std::endl;
                }
            }
        }

        //Creazione treni
        
        if(train_type==1)
            trains.push_back(Slow_Train(train_direction, train_number, train_times));                                          
        if(train_type==2)
            trains.push_back(Medium_Train(train_direction, train_number, train_times));
        if(train_type==3)
            trains.push_back(Fast_Train(train_direction, train_number, train_times));
    }
}

void Line::vector_stations()
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
            time_to_remove.push_back(count++);
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