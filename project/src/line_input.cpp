#include "../include/line.hpp"
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>

//                                                     //
//  _                   _   _             _            //
// (_)_ __  _ __  _   _| |_| |_ _ __ __ _(_)_ __  ___  //
// | | '_ \| '_ \| | | | __| __| '__/ _` | | '_ \/ __| //
// | | | | | |_) | |_| | |_| |_| | | (_| | | | | \__ \ //
// |_|_| |_| .__/ \__,_|\__|\__|_|  \__,_|_|_| |_|___/ //
//         |_|                                         //
//                                                     //
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
            train_velocity_km_min = 2.7; // 160/60
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
                not_approx_times.push_back(train_times.at(i));
            }

            if (train_direction == 0)
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    if (i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = ceil(approx_time);
                    }
                }
            }
            else
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(not_approx_times.size() - i)->get_distance() - stations.at(not_approx_times.size() - i - 1)->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    if (i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = ceil(approx_time);
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
                not_approx_times.push_back(train_times.at(i));
            }

            if (train_direction == 0)
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(i))->get_distance() - stations.at(main_indexes.at(i - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    if (i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = ceil(approx_time);
                    }
                }
            }
            else
            {
                for (int i = 1; i < not_approx_times.size(); i++)
                {
                    double approx_time = not_approx_times.at(i - 1) + 5 + 7.5 + (stations.at(main_indexes.at(not_approx_times.size() - i))->get_distance() - stations.at(main_indexes.at(not_approx_times.size() - i - 1))->get_distance() - 10) / train_velocity_km_min; // 7.5 = 10/80/60
                    if (i == 1)
                        approx_time = approx_time - 5;
                    if (not_approx_times.at(i) < approx_time)
                    {
                        std::cout << "Modified time for station: " << i << " from " << not_approx_times.at(i) << " to " << approx_time << std::endl;
                        not_approx_times.at(i) = ceil(approx_time);
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
        std::cout << std::endl;
    }
}

//                                                              //
//  _                   _       _        _   _                  //
// (_)_ __  _ __  _   _| |_ ___| |_ __ _| |_(_) ___  _ __  ___  //
// | | '_ \| '_ \| | | | __/ __| __/ _` | __| |/ _ \| '_ \/ __| //
// | | | | | |_) | |_| | |_\__ \ || (_| | |_| | (_) | | | \__ \ //
// |_|_| |_| .__/ \__,_|\__|___/\__\__,_|\__|_|\___/|_| |_|___/ //
//         |_|                                                  //
//                                                              //
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
    std::cout << std::endl
              << "     _        _   _                     " << std::endl
              << " ___| |_ __ _| |_(_) ___  _ __  ___     " << std::endl
              << "/ __| __/ _` | __| |/ _ \\| '_ \\/ __|  " << std::endl
              << "\\__ \\ || (_| | |_| | (_) | | | \\__ \\" << std::endl
              << "|___/\\__\\__,_|\\__|_|\\___/|_| |_|___/" << std::endl
              << std::endl;

    for (int i = 0; i < stations.size(); i++)
        stations.at(i)->print();
}

void Line::print_trains() const
{
    std::cout << std::endl
              << " _             _               " << std::endl
              << "| |_ _ __ __ _(_)_ __  ___     " << std::endl
              << "| __| '__/ _` | | '_ \\/ __|   " << std::endl
              << "| |_| | | (_| | | | | \\__ \\  " << std::endl
              << " \\__|_|  \\__,_|_|_| |_|___/  " << std::endl
              << std::endl;

    for (int i = 0; i < trains.size(); i++)
        trains.at(i)->print();
}

//                                                           //
//      ____                                            __   //
//     / __/___ _____  _______  __    _________  __  __/ /_  //
//    / /_/ __ `/ __ \/ ___/ / / /   / ___/ __ \/ / / / __/  //
//   / __/ /_/ / / / / /__/ /_/ /   / /__/ /_/ / /_/ / /_    //
//  /_/  \__,_/_/ /_/\___/\__, /____\___/\____/\__,_/\__/    //
//                       /____/_____/                        //
//                                                           //
void Line::fancy_cout() const
{
    std::ofstream of("output.txt", std::ios_base::app);

    // s: 0--------1------------2------------3-----------------------------------------------------------4
    // t:       3                  2                        1                                      0

    of << std::endl;

    // stations
    of << "s: " << '0';
    for (int i = 1; i < stations.size(); i++)
    {
        for (int j = 0; j < (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance()) / 5; j++)
            of << '-';
        of << i;
    }
    of << std::endl;

    // trains
    of << "t: ";
    // mt
    if (trains.size())
    {
        // first train
        for (int i = 0; i < (trains.at(trains.size() - 1)->get_distance()) / 5; i++)
            of << ' ';
        of << trains.at(trains.size() - 1)->get_train_name();

        // other trains
        if (trains.size() > 1)
            for (int i = trains.size() - 2; i >= 0; i--)
            {
                for (int j = 0; j < (trains.at(i)->get_distance() - trains.at(i + 1)->get_distance()) / 5; j++)
                    of << ' ';
                of << trains.at(i)->get_train_name();
            }
    }
    of << std::endl;

    // parked
    of << "p: " << ' ';
    for (int i = 1; i < stations.size(); i++)
    {
        for (int j = 0; j < (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance()) / 5; j++)
            of << ' ';
        if (!stations.at(i)->get_size())
            of << ' ';
        for (int j = 0; j < stations.at(i)->get_size(); j++)
            of << 'p';
    }
    of << std::endl;

    of.close();
}
