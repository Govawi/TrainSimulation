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

    std::ifstream filett("timetables.txt");
    std::string t;
    while (!filett.eof())
    {
        std::getline(filett, t);
        std::stringstream st(t);

        int train_number;
        int train_direction;
        int train_type;
        std::vector<double> train_times;

        st >> train_number;
        st >> train_direction;
        st >> train_type;
        double tmp;
        st >> tmp;
        train_times.push_back(tmp);

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
        int k = 0;
        if (train_type == 1)
        {
            for (int i = 1; i < stations.size() && st.gcount(); i++)
            {
                if (i == time_to_remove.at(k))
                {
                    st >> tmp;
                    k++;
                    continue;
                }
                st >> tmp;
                double approx_time = train_times.back() + 5 + 7.5 + (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60

                if (tmp < approx_time)
                    tmp = approx_time;

                train_times.push_back(tmp);
            }
            for (int i = train_times.size(); i < stations.size(); i++)
            {
                double approx_time = train_times.back() + 5 + 7.5 + (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min;
                train_times.push_back(approx_time);
            }
        }

        else if (train_type == 2 || train_type == 3)
        {
            std::vector<int> main_indexes;
            for (int i = 0; i < stations.size(); i++)
                if (!stations[i]->is_local())
                    main_indexes.push_back(i);

            int j = 1;
            for (int i = 1; i < train_times.size(); i++)
            {
                if (i == time_to_remove.at(k))
                {
                    st >> tmp;
                    k++;
                    continue;
                }
                st >> tmp;
                double approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(j))->get_distance() - stations.at(main_indexes.at(j - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60

                if (tmp < approx_time)
                    tmp = approx_time;

                train_times.push_back(tmp);
                j++;
            }
            for (int i = train_times.size(); i < main_indexes.size(); i++)
            {
                double approx_time = train_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(j))->get_distance() - stations.at(main_indexes.at(j - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                train_times.push_back(approx_time);
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
    int remove = 0;

    std::getline(fileld, s);
    std::unique_ptr<Station> foo{new Main_Station(s, 0)};
    stations.push_back(std::move(foo));
    double distance_old = 0.0;

    while (!fileld.eof())
    {
        std::getline(fileld, s);

        double station_distance = (double)stoi(s.substr(s.rfind(' ')));
        int station_type = stoi(s.substr(s.rfind(' ') - 1, 1));
        std::string station_name = s.substr(0, s.rfind(' ') - 2);

        if (station_distance - distance_old < 20)
        {
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
