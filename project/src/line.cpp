#include "../include/line.hpp"
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

            if (train_direction == 0)
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << "velocity of train: " << train_velocity_km_min << std::endl;
                    if (i == 1)
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
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(not_approx_times.size() - i)->get_distance() - stations.at(not_approx_times.size() - i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << "velocity of train: " << train_velocity_km_min << std::endl;
                    if (i == 1)
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

            if (train_direction == 0)
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(i))->get_distance() - stations.at(main_indexes.at(i - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << std::endl;
                    if (i == 1)
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
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(not_approx_times.size() - i))->get_distance() - stations.at(main_indexes.at(not_approx_times.size() - i - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    std::cout << not_approx_times.at(i) << "  approx: " << approx_time << std::endl;
                    if (i == 1)
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
            std::shared_ptr<Train> tr{new Slow_Train(train_direction, train_number, not_approx_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Slow train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else if (train_type == 2)
        {
            std::shared_ptr<Train> tr{new Medium_Train(train_direction, train_number, not_approx_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Medium train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else
        {
            std::shared_ptr<Train> tr{new Fast_Train(train_direction, train_number, not_approx_times)};
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
    std::shared_ptr<Station> foo{new Main_Station(s, 0)};
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

            std::shared_ptr<Station> foo{new Main_Station(station_name, station_distance)};
            stations.push_back(std::move(foo));
            remove++;
        }
        else if (station_type == 1)
        {
            std::shared_ptr<Station> foo{new Local_Station(station_name, station_distance)};
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

    for (int i = 0; i < trains.size(); i++)
    {
        key = trains.at(i)->get_expected_time(0) + trains.at(i)->get_late();
        j = i - 1;

        while (j >= 0 && trains.at(j)->get_expected_time(0) + trains.at(j)->get_late() > key)
        {
            swap(trains.at(j + 1), trains.at(j));
            j = j - 1;
        }
    }
}

void Line::departure_next_train(int index)
{
    while (line.front()->get_expected_time(0) + line.front()->get_late() == index)
    {
        if (!line.empty())
        {
            if (cmp_distance_start(line.front()) > 10)
            {
                trains.push_back(std::move(line.front()));
                std::cout << "departed train " << trains.back()->get_train_name() << " in late of " << trains.back()->get_late() << std::endl;
                trains.back()->set_velocity(1.3);
                line.erase(line.begin());
            }
            else
            {
                line.front()->set_late(line.front()->get_late() + 1);
                std::swap(line.front(), line.back());
                sort_trains();
            }
        }
        else
            break;
    }
}

double Line::cmp_distance_start(const std::shared_ptr<Train> &a)
{
    if (a->get_direction() == 0)
    {
        if (!trains.empty())
            return trains.back()->get_distance() - a->get_distance();
    }
    else if (!trains.empty())
        return trains.back()->get_distance() - a->get_distance();

    return 11;
}

void Line::update_velocity()
{
    // controlla posizione rispetto a prossimo treno e prossima stazione
    for (int i = 0; i < trains.size(); i++)
    {
        if (trains.at(i)->get_distance() - stations.at(trains.at(i)->get_stations_done())->get_distance() >= 5) // se maggiore 5 accelera a v max
            trains.at(i)->set_velocity(trains.at(i)->get_velocity_max());

        if (trains.at(i - 1)->get_velocity_curr() != 0 && i != 0)
            if (trains.at(i - 1)->get_distance() - trains.at(i)->get_distance() <= 10) // se minore 10 abbassi velocita'
                trains.at(i)->set_velocity(trains.at(i - 1)->get_velocity_curr());

        if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 5) // se minore 5 abbassi velocita'
            trains.at(i)->set_velocity(1.3);                                                                        // 1.3 = 80/60
    }
}

void Line::update_position()
{
    if (true == true)                                                                                          //can update
        trains.at(true)->set_distance(trains.at(true)->get_distance() + trains.at(true)->get_velocity_curr()); //update position
}

void Line::reverse_stations()
{
    //n     -> distance(n - (n - 0))
    //n - 1 -> distance(n - (n - 1))
    //n - 2 -> distance(n - (n - 2))

    std::vector<double> dis;

    for (int i = 0; i < stations.size(); i++)
        dis.push_back(stations.at(stations.size() - 1)->get_distance() - stations.at(stations.size() - 1 - i)->get_distance());

    reverse(stations.begin(),stations.end());

    for (int i = 0; i < stations.size(); i++)
        stations.at(i)->set_distance(dis.at(i));
}

void Line::divide_trains()
{
    while (!trains.empty())
    {
        if (trains.front()->get_direction() == 0)
        {
            line.push_back(std::move(trains.front()));
            trains.erase(trains.begin());
        }
        else
        {
            tmp.push_back(std::move(trains.front()));
            trains.erase(trains.begin());
        }
    }
}

void Line::sim()
{
    sort_trains();

    divide_trains();

    for (int minute = 0; minute < 1440; minute++)
    {
        //update position and velocity train --
        update_velocity();
        //------------------------

        //departure ---------------
        departure_next_train(minute);
        sort_trains();
        //-------------------------
    }

    trains.clear(); // treni partiti
    reverse_stations();
    line.clear(); // treni in attesa di partire
    line = tmp;

    for (int minute = 0; minute < 1440; minute++)
    {
        //update position and velocity train --
        update_velocity();
        //------------------------

        //departure ---------------
        departure_next_train(minute);
        sort_trains();
        //-------------------------
    }
}

//
//    1. controllo fermate & stop
//
//    2. controllo rallentamenti pre stazione
//
//    3. controllo sorpassi
//
//
//    0 1 2 3 4 5 6 7 8 9
//    1 2 3 4 5 6
//
//    stations : LR
//    trains : LR
//    sim() : trains, stations
//
//    stations : RL
//    trains : RL
//    sim() : trains, stations
//
