#include "line.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <utility>

Line::Line()
{
    // station initialization
    vector_stations();
    std::cout << "> Stations Input OK" << std::endl;

    // train initialization
    vector_trains();
    std::cout << "> Trains Input OK" << std::endl;

    // print more, more, more!
    std::cout << std::endl;
    print_stations();
    print_trains();
    print_departure();
    sort_trains();
    print_departure();
}

void Line::vector_trains()
{
    // fancy stuff :)
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**   TRAINS INPUT   **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;
    // --------------

    // input stream
    std::ifstream filett("timetables.txt");
    std::string t;
    while (!filett.eof())
    {
        std::getline(filett, t);

        int train_number = stoi(t.substr(0, t.find(' ')));
        int train_direction = stoi(t.substr(t.find(' ') + 1, 1));
        int train_type = stoi(t.substr(t.find(' ') + 3, 1));

        t = t.substr(t.find(' ') + 5); // only times
        std::vector<double> train_times;

        // need to distinguish train velocity
        double train_velocity_km_min;
        switch (train_type)
        {
        case 1:
            train_velocity_km_min = 2.67; // 160/60
            break;
        case 2:
            train_velocity_km_min = 4; // 240/60
            break;
        case 3:
            train_velocity_km_min = 5; // 300/60
            break;
        }

        while (!t.empty()) // pushing all times
        {
            if (t.find(' ') == std::string::npos)
            {
                std::cout << "sono entrato nell npos e la stringa e' " << t << std::endl;
                train_times.push_back(stod(t));
                break;
            }
            train_times.push_back(stod(t.substr(0, t.find(' '))));
            t = t.substr(t.find(' ') + 1);
        }

        for (int i = train_times.size(); i < stations.size() + time_to_remove.size(); i++)
            train_times.push_back(0);

        std::vector<double> not_approx_times;

        if (train_type == 1) // slow
        {
            int j = 0;

            for (int i = 0; i < j + stations.size() && i <= train_times.size(); i++)
            {
                if (j < time_to_remove.size())
                {
                    if (i == time_to_remove.at(j))
                    {
                        j++;
                        continue;
                    }
                }
                std::cout << "time added: " << i << std::endl;
                not_approx_times.push_back(train_times.at(i));
            }

            std::cout << "All times saved" << std::endl;
            
            if(train_direction == 0)
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i-1) + 5 + 7.5 + (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << "velocity of train: " << train_velocity_km_min << std::endl;
                    if(i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = approx_time;
                    }
                }
            }
            else
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i-1) + 5 + 7.5 + (stations.at(not_approx_times.size() - i)->get_distance() - stations.at(not_approx_times.size() - i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << "velocity of train: " << train_velocity_km_min << std::endl;
                    if(i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = approx_time;
                    }
                }
            }
        }
        else // medium and fast
        {
            std::vector<int> main_indexes;
            for (int i = 0; i < stations.size(); i++)
                if (!stations[i]->is_local())
                    main_indexes.push_back(i);

            int j = 0;

            for (int i = 0; i < main_indexes.size() && i <= train_times.size(); i++)
            {
                if (j < time_to_remove_main.size())
                {
                    if (i == time_to_remove_main.at(j))
                    {
                        j++;
                        continue;
                    }
                }
                std::cout << "time added: " << i << std::endl;
                not_approx_times.push_back(train_times.at(i));
            }

            std::cout << "All times saved" << std::endl;

            if(train_direction == 0)
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i-1) + 5 + 7.5 + (stations.at(main_indexes.at(i))->get_distance() - stations.at(main_indexes.at(i - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << std::endl;
                    if(i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = approx_time;
                    }
                }
            }
            else 
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i-1) + 5 + 7.5 + (stations.at(main_indexes.at(not_approx_times.size() - i))->get_distance() - stations.at(main_indexes.at(not_approx_times.size() - i - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << std::endl;
                    if(i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = approx_time;
                    }
                }
            }
        }

        if (train_type == 1)
        {
            std::unique_ptr<Train> tr{new Slow_Train(train_direction, train_number, not_approx_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Slow train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else if (train_type == 2)
        {
            std::unique_ptr<Train> tr{new Medium_Train(train_direction, train_number, not_approx_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Medium train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else
        {
            std::unique_ptr<Train> tr{new Fast_Train(train_direction, train_number, not_approx_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Fast train: " << train_number << " - dir: " << train_direction << std::endl;
        }
    }
}

void Line::vector_stations()
{
    // fancy stuff :)
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**  STATIONS INPUT  **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;
    // --------------

    std::ifstream fileld("line_description.txt");
    std::string s;
    int remove = 1;

    std::getline(fileld, s);
    std::unique_ptr<Station> foo{new Main_Station(s, 0)};
    stations.push_back(std::move(foo));
    double distance_old = 0.0;

    while (!fileld.eof())
    {
        std::getline(fileld, s);

        double station_distance = stod(s.substr(s.rfind(' ')));
        int station_type = stoi(s.substr(s.rfind(' ') - 1, 1));
        std::string station_name = s.substr(0, s.rfind(' ') - 2);

        if (station_distance - distance_old < 20)
        {
            if (station_type == 0)
                time_to_remove_main.push_back(remove);
            time_to_remove.push_back(remove++);
            std::cout << "Station at " << station_distance << " km removed...distance from previous was less than 20 km" << std::endl;
            continue;
        }

        distance_old = station_distance;

        if (station_type == 0)
        {

            std::unique_ptr<Station> foo{new Main_Station(station_name, station_distance)};
            stations.push_back(std::move(foo));
            remove++;
        }
        else if (station_type == 1)
        {
            std::unique_ptr<Station> foo{new Local_Station(station_name, station_distance)};
            stations.push_back(std::move(foo));
            remove++;
        }
    }

    fileld.close();
}

void Line::print_stations() const
{
    for (int i = 0; i < stations.size(); i++)
        stations.at(i)->print();
}

void Line::print_trains() const
{
    for (int i = 0; i < trains.size(); i++)
        trains.at(i)->print();
}

void Line::sort_trains()
{
    double key;
    int j;

    for(int i = 0; i < trains.size(); i++)
    {
        key = trains.at(i)->get_expected_time(0) + trains.at(i)->get_late();
        j = i - 1;

        while( j >= 0 && trains.at(j)->get_expected_time(0) + trains.at(j)->get_late() > key )
        {
            swap(trains.at(j+1),trains.at(j));
            j = j - 1;
        }
    }
}

void Line::print_departure()
{
    for(int i=0; i<trains.size(); i++)
    {
        std::cout << "Train "<<trains.at(i)->get_train_name()<<" departure at : "<<trains.at(i)->get_expected_time(0) + trains.at(i)->get_late()<<std::endl;
    }
}

/*
void Line::departure_next_train(int index)
{
    int dir;
    while(trains.front()->get_expected_time(0) + trains.front()->get_late() == index)
    {
        if(trains.front()->get_direction() == 0)
        {
            line_left_right.push_back(std::move(trains.front()));
            std::cout<<"departed train "<<line_left_right.back()->get_train_name()<< " in late of "<<line_left_right.back()->get_late()<<std::endl;
            line_left_right.back()->set_velocity(1.3);
            trains.erase(trains.begin());
            dir = line_left_right.back()->get_direction();
        }
        else
        {
            line_right_left.push_back(std::move(trains.front()));
            std::cout<<"departed train "<<line_right_left.back()->get_train_name() << " in late of "<<line_right_left.back()->get_late()<<std::endl;
            line_right_left.back()->set_velocity(1.3);
            trains.erase(trains.begin());
            dir = line_right_left.back()->get_direction();
        }
        if(trains.empty())
            break;
        if(trains.front()->get_direction() == dir)
        {
            trains.front()->set_late(trains.front()->get_late() + 1);
            break;
        }
    }
}
*/

void Line::departure_next_train(int index)
{
    while(trains.front()->get_expected_time(0) + trains.front()->get_late() == index)
    {
        if(!trains.empty())
        {
            if(cmp_distance(trains.front()) < 10)
            {
                if(trains.front()->get_direction() == 0)
                {
                    line_left_right.push_back(std::move(trains.front()));
                    std::cout<<"departed train "<<line_left_right.back()->get_train_name()<< " in late of "<<line_left_right.back()->get_late()<<std::endl;
                    line_left_right.back()->set_velocity(1.3);
                    trains.erase(trains.begin());
                }
                else
                {
                    line_right_left.push_back(std::move(trains.front()));
                    std::cout<<"departed train "<<line_right_left.back()->get_train_name() << " in late of "<<line_right_left.back()->get_late()<<std::endl;
                    line_right_left.back()->set_velocity(1.3);
                    trains.erase(trains.begin());
                }
            }
            else
            {
                trains.front()->set_late(trains.front()->get_late() + 1);
            }
        }
        else
            break;
    }
}

double Line::cmp_distance(const std::unique_ptr<Train> &a)
{
    if(a->get_direction() == 0)
    {
        if(!line_left_right.empty())
            return line_left_right.back()->get_distance() - a->get_distance();
    }
    else if(!line_right_left.empty())
        return line_right_left.back()->get_distance() - a->get_distance();

    return 10;
}

void Line::sim()
{
    for(int i=0; i<30; i++)
    {
        departure_next_train(i);
        sort_trains();
        print_departure();
    }
    std::cout<<"Train "<<trains.back()->get_train_name() << " not departed with a late of "<<trains.back()->get_late();
}

