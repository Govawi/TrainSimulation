#include "../include/line.hpp"

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

void Line::update_position(int index)
{
    if (trains.empty())
        return;

    for (int i = 0; i < trains.size(); i++)
    {
        trains.at(i)->set_distance(trains.at(i)->get_distance() + trains.at(i)->get_velocity_curr()); //update position
        if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 0)
        {
            std::cout << "Train: " << trains.at(i)->get_train_name();
            if (stations.at(trains.at(i)->get_stations_done() + 1)->is_local() && trains.at(i)->get_velocity_max() > 2.7) //transita
            {
                std::cout << " - Transit in " << stations.at(trains.at(i)->get_stations_done() + 1)->get_name() << std::endl;
                trains.at(i)->increase_stations_done();
            }
            else //si ferma
            {
                std::cout << " - Stopping in " << stations.at(trains.at(i)->get_stations_done() + 1)->get_name() << " - Arrived: " << index << " - Delay: " << trains.at(i)->get_delay() << std::endl;
                trains.at(i)->increase_stations_done();
                trains.at(i)->set_velocity(0);
                trains.at(i)->set_stop(5);
                stations.at(trains.at(i)->get_stations_done())->add_rail(trains.at(i));
                trains.erase(trains.begin() + i);
            }
        }
        else if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 5)
        {
            if (trains.at(i)->get_deposit())
            {
                std::cout << "Train: " << trains.at(i)->get_train_name() << " Deposit" << std::endl;
                trains.at(i)->set_deposit(false);
                trains.at(i)->set_velocity(0);
                stations.at(trains.at(i)->get_stations_done() + 1)->get_deposit()->push(trains.at(i));
                trains.erase(trains.begin() + i);
            }
        }
        else if (stations.at(trains.at(i)->get_stations_done() + 1)->get_distance() - trains.at(i)->get_distance() <= 20)
        {
            if (!stations.at(i)->get_deposit()->is_empty())
                trains.at(i)->set_deposit(true);
            if (!stations.at(trains.at(i)->get_stations_done() + 1)->is_local() || trains.at(i)->get_velocity_max() == 2.7)
                if (stations.at(trains.at(i)->get_stations_done() + 1)->is_full())
                    trains.at(i)->set_deposit(true);
        }
    }
}

void Line::departure_next_train(int index)
{
    if (!line.size())
        return;

    if (line.front()->get_expected_time(0) + line.front()->get_delay() == index)
    {
        if (!trains.empty())
            std::cout << "Distanza appena partito " << trains.back()->get_distance() << " vel " << trains.back()->get_velocity_curr() << std::endl;

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
}