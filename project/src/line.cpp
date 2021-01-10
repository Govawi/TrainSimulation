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

void Line::sort_trains()
{
    double key;
    int j;

    for (int i = 0; i < trains.size(); i++)
    {
        key = trains.at(i)->get_expected_time(0) + trains.at(i)->get_delay();
        j = i - 1;

        while (j >= 0 && trains.at(j)->get_expected_time(0) + trains.at(j)->get_delay() > key)
        {
            swap(trains.at(j + 1), trains.at(j));
            j = j - 1;
        }
    }
}

void Line::departure_next_train(int index)
{
    switch (line.size())
    {
    case 0:
        break;

    default:
        if (line.front()->get_expected_time(0) + line.front()->get_delay() == index)
        {
            if (trains.empty() || trains.back()->get_distance() >= 10)
            {
                trains.push_back(std::move(line.front()));
                std::cout << "Train: " << trains.back()->get_train_name() << " - Departure: " << index << " - Delay: " << trains.back()->get_delay() << std::endl;
                trains.back()->set_velocity(1.3);
                line.erase(line.begin());
            }
            // delay update
            if (!line.empty())
                for (int i = 0; i < line.size() && line.at(i)->get_expected_time(0) + line.at(i)->get_delay() == index; i++)
                    line.at(i)->increase_delay(1);
        }
        break;
    }
}

void Line::update_velocity()
{
    // controlla posizione rispetto a prossimo treno e prossima stazione
    for (int i = 0; i < trains.size(); i++)
    {
        if (trains.at(i)->get_distance() - stations.at(trains.at(i)->get_stations_done())->get_distance() >= 5) // se maggiore 5 accelera a v max
            trains.at(i)->set_velocity(trains.at(i)->get_velocity_max());

        if (i != 0)
            if (trains.at(i - 1)->get_velocity_curr() != 0)
                if (trains.at(i - 1)->get_distance() - trains.at(i)->get_distance() <= 10) // se minore 10 abbassi velocita'
                    trains.at(i)->set_velocity(trains.at(i - 1)->get_velocity_curr());

        if (trains.at(i)->get_stations_done() != stations.size() - 1)                                                   //TEST PER PROBLEMI
            if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 5) // se minore 5 abbassi velocita'
                trains.at(i)->set_velocity(1.3);                                                                        // 1.3 = 80/60
    }
}

void Line::update_position()
{
    for (int i = 0; i < trains.size(); i++)
    {
        if (trains.at(i)->get_stop() != 0) //can't update
            continue;

        trains.at(i)->set_distance(trains.at(i)->get_distance() + trains.at(i)->get_velocity_curr()); //update position

        if (trains.at(i)->get_stations_done() != stations.size() - 1) //TEST PER PROBLEMI
        {
            if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 20) //se vicino a stazione
            {
                if (stations.at(trains.at(i)->get_stations_done() + 1)->is_local() && trains.at(i)->get_velocity_max() > 160) //se locale e treno principale
                    std::cout;                                                                                                //nothing happens

                else if (stations.at(trains.at(i)->get_stations_done() + 1)->is_full()) //controlla se i binari di una principale sono pieni
                    trains.at(i)->set_deposit(true);
            }

            if (trains.at(i)->get_deposit() && stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 5)
            {
                //deve entrare nel deposito
                std::cout << "Train: " << trains.at(i)->get_train_name() << " Deposit" << std::endl;
                stations.at(trains.at(i)->get_stations_done() + 1)->get_deposit()->push(trains.at(i));
                trains.erase(trains.begin() + i);
                continue;
            }

            if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 0)
            {
                std::cout << "Train: " << trains.at(i)->get_train_name();
                //transita e basta
                if (stations.at(trains.at(i)->get_stations_done() + 1)->is_local() && trains.at(i)->get_velocity_max() > 160)
                {
                    trains.at(i)->increase_stations_done();
                    std::cout << " - Transit in " << stations.at(trains.at(i)->get_stations_done() + 1)->get_name() << std::endl;
                }
                //entra nella stazione e si ferma
                else
                {
                    std::cout << " - Stopping in " << stations.at(trains.at(i)->get_stations_done() + 1)->get_name() << " - Arrived: ";
                    if (trains.at(i)->get_velocity_max() == 160)
                        std::cout << trains.at(i)->get_expected_time(trains.at(i)->get_stations_done() + 1) + trains.at(i)->get_delay();
                    else
                    {
                        int exp = 0;
                        for (int j = 0; j < trains.at(i)->get_stations_done() + 1; j++)
                            if (stations.at(j)->is_local())
                                exp++;
                        std::cout << trains.at(i)->get_expected_time(exp) + trains.at(i)->get_delay();
                    }
                    std::cout << " - Delay: " << trains.at(i)->get_delay() << std::endl;

                    trains.at(i)->set_stop(5);
                    trains.at(i)->set_velocity(0);
                    trains.at(i)->increase_stations_done();
                    stations.at(trains.at(i)->get_stations_done())->add_rail(trains.at(i)); //errore caso finale
                    trains.erase(trains.begin() + i);
                }
            }
        }
    }
}

void Line::reverse_stations()
{
    //n     -> distance(n - (n - 0))
    //n - 1 -> distance(n - (n - 1))
    //n - 2 -> distance(n - (n - 2))

    std::vector<double> dis;

    for (int i = 0; i < stations.size(); i++)
        dis.push_back(stations.at(stations.size() - 1)->get_distance() - stations.at(stations.size() - 1 - i)->get_distance());

    reverse(stations.begin(), stations.end());

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

void Line::depart_station()
{
    for (int i = 1; i < stations.size(); i++)
    {
        stations.at(i)->swap_train();
        if (stations.at(i)->get_size() != 0)
        {
            if (stations.at(i)->get_front()->get_stop() == 0) //stop == 0
            {
                if (i == stations.size() - 1 && stations.at(i)->get_size() == 1)
                {
                    std::cout << "Train: " << stations.at(i)->get_front()->get_train_name() << " - Bye, Have a Great Time!" << std::endl;
                    stations.at(i)->get_front().reset();
                    stations.at(i)->remove_train();
                }
                else if (trains.empty())
                {
                    stations.at(i)->get_front()->set_velocity(1.3);
                    trains.push_back(stations.at(i)->get_front());
                    stations.at(i)->remove_train();
                }
                else
                {
                    for (int j = 0; j < trains.size(); j++)
                    {
                        if (stations.at(i)->get_front()->get_distance() < trains.at(j)->get_distance())
                        {
                            if (trains.at(j)->get_distance() - stations.at(i)->get_front()->get_distance() >= 10)
                            {
                                stations.at(i)->get_front()->set_velocity(1.3);
                                trains.insert(trains.begin() + j, stations.at(i)->get_front());
                                stations.at(i)->remove_train();
                                break;
                            }
                        }
                    }
                }
            }

            if (stations.at(i)->get_size() != 0)
            {
                if (stations.at(i)->get_back()->get_stop() == 0)
                {
                    stations.at(i)->get_back()->set_stop(1);
                    stations.at(i)->get_back()->increase_delay(1);
                }
                stations.at(i)->get_front()->decrease_stop();
                if (stations.at(i)->get_size() == 2)
                    stations.at(i)->get_back()->decrease_stop();
            }
        }
    }
}

void Line::depart_deposit() 
{
    for (int i = 1; i < stations.size(); i++)
    {
        if (!stations.at(i)->is_full() && !stations.at(i)->get_deposit()->is_empty())
        {
            std::shared_ptr<Train> tr = stations.at(i)->get_deposit()->pop();
            for (int j = 0; j < trains.size(); j++)
            {
                if (tr->get_distance() < trains.at(j)->get_distance())
                {
                    trains.insert(trains.begin() + j, tr);
                    break;
                }
            }
        }
        stations.at(i)->get_deposit()->add_delay();
    }
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
    // s: 0--------1------------2------------3-----------------------------------------------------------4
    // t:       3                  2                        1                                      0

    std::cout << std::endl;

    // stations
    std::cout << "s: " << '0';
    for (int i = 1; i < stations.size(); i++)
    {
        for (int j = 0; j < (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance()) / 5; j++)
            std::cout << '-';
        std::cout << i;
    }

    std::cout << std::endl;

    // trains
    std::cout << "t: ";
    switch (trains.size())
    {
    case 0:
        std::cout << std::endl;
        break;

    default:
        // first train
        for (int i = 0; i < (trains.at(trains.size() - 1)->get_distance()) / 5; i++)
            std::cout << ' ';
        std::cout << trains.size() - 1;

        // other trains
        if (trains.size() != 1)
            for (int i = trains.size() - 2; i >= 0; i--)
            {
                for (int j = 0; j < (trains.at(i)->get_distance() - trains.at(i + 1)->get_distance()) / 5; j++)
                    std::cout << ' ';
                std::cout << trains.size() - i;
            }
        break;
    }

    std::cout << std::endl;
}

//                                                   //
//      _                 _       _   _              //
//  ___(_)_ __ ___  _   _| | __ _| |_(_) ___  _ __   //
// / __| | '_ ` _ \| | | | |/ _` | __| |/ _ \| '_ \  //
// \__ \ | | | | | | |_| | | (_| | |_| | (_) | | | | //
// |___/_|_| |_| |_|\__,_|_|\__,_|\__|_|\___/|_| |_| //
//                                                   //
void Line::sim()
{
    std::cout << std::endl
              << "     _                 _       _   _                 " << std::endl
              << " ___(_)_ __ ___  _   _| | __ _| |_(_) ___  _ __      " << std::endl
              << "/ __| | '_ ` _ \\| | | | |/ _` | __| |/ _ \\| '_ \\  " << std::endl
              << "\\__ \\ | | | | | | |_| | | (_| | |_| | (_) | | | |  " << std::endl
              << "|___/_|_| |_| |_|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|" << std::endl
              << std::endl;

    sort_trains();
    divide_trains();

    for (int minute = 0; minute < 1440; minute++)
    {
        //update position and velocity train --
        update_velocity();
        update_position();
        //------------------------

        //stations --------------
        depart_station();
        depart_deposit();
        //-----------------------

        //departure ---------------
        departure_next_train(minute);
        sort_trains();
        //-------------------------
        //fancy_cout();
    }
    std::cout << "prima simulazione ok\n"
              << std::endl;

    trains.clear(); // treni partiti
    reverse_stations();
    line.clear(); // treni in attesa di partire
    line = tmp;

    for (int minute = 0; minute < 1440; minute++)
    {
        //update position and velocity train --
        update_velocity();
        update_position();
        //------------------------

        //departure ---------------
        departure_next_train(minute);
        sort_trains();
        //-------------------------

        //fancy_cout();
    }
    std::cout << "seconda simulazione ok" << std::endl;
}
