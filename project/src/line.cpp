#include "../include/line.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>

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

/*
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

        t = t.substr(t.find(' ') + 5);
        std::vector<double> train_times;
        train_times.push_back(stod(t.substr(0, t.find(' '))));
        t = t.substr(t.find(' ') + 1);

        // need to distinguish train velocity
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

        int k = 0; // counter for removed stations
        int x = 1;

        // need a time for all stations
        if (train_type == 1)
        {
            for (int i = 1; x < stations.size() && !t.empty(); i++)
            {
                if (k < time_to_remove.size())
                {
                    if (i == time_to_remove.at(k))
                    {
                        std::cout << "Removed time" << std::endl;
                        t = t.substr(t.find(' ') + 1);
                        k++;
                        continue;
                    }
                }
                double tmp = stod(t.substr(0, t.find(' ')));
                double approx_time = train_times.back() + 5 + 7.5 + (stations.at(x)->get_distance() - stations.at(x - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                x++;

                if (tmp < approx_time)
                {
                    std::cout << "Modified time for station" << x << "from" << tmp << " to " << approx_time << std::endl;
                    tmp = approx_time;
                }

                train_times.push_back(tmp);
                t = t.substr(t.find(' ') + 1);
            }

            // fill all remaining stations
            for (int i = train_times.size(); i < stations.size(); i++)
            {
                double approx_time = train_times.back() + 5 + 7.5 + (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min;
                train_times.push_back(approx_time);
                std::cout << "Missing time , insert : " << approx_time << std::endl;
            }
        }

        // need a time for main stations only
        if (train_type == 2 || train_type == 3)
        {
            std::vector<int> main_indexes;
            for (int i = 0; i < stations.size(); i++)
                if (!stations[i]->is_local())
                    main_indexes.push_back(i);

            int j = 1;
            for (int i = 1; j < main_indexes.size() && !t.empty(); i++)
            {
                if (k < time_to_remove_main.size())
                {
                    if (i == time_to_remove_main.at(k))
                    {
                        std::cout << "Removed time" << std::endl;
                        k++;
                        t = t.substr(t.find(' ') + 1);
                        continue;
                    }
                }
                if (!stations.at(i)->is_local())
                {
                    double tmp = stod(t.substr(0, t.find(' ')));
                    double approx_time = train_times.back() + 5 + 7.5 + (stations.at(main_indexes.at(j))->get_distance() - stations.at(main_indexes.at(j - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60

                    if (tmp < approx_time)
                    {
                        std::cout << "Modified time for station" << j << " from " << tmp << " to " << approx_time << std::endl;
                        tmp = approx_time;
                    }
                    train_times.push_back(tmp);
                    t = t.substr(t.find(' ') + 1);
                    std::cout << "main station" << j << std::endl;
                    j++;
                }
            }

            // fill remaining main stations
            for (int i = train_times.size(); i < main_indexes.size(); i++)
            {
                double approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(j))->get_distance() - stations.at(main_indexes.at(j - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                train_times.push_back(approx_time);
                std::cout << "Missing time , insert : " << approx_time << std::endl;
                j++;
            }
        }

        if (train_type == 1)
        {
            std::unique_ptr<Train> tr{new Slow_Train(train_direction, train_number, train_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Slow train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else if (train_type == 2)
        {
            std::unique_ptr<Train> tr{new Medium_Train(train_direction, train_number, train_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Medium train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else
        {
            std::unique_ptr<Train> tr{new Fast_Train(train_direction, train_number, train_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Fast train: " << train_number << " - dir: " << train_direction << std::endl;
        }
    }

    filett.close();
}
*/