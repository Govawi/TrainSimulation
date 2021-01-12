#include "../include/line.hpp"
#include <fstream>
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

    sim();
}

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

    std::ofstream of("output.txt");
    of << " ---------- SIMULATION ----------\n"
       << std::endl;
    of.close();
    for (int minute = 0; minute < 1440; minute++)
    {
        //update position and velocity train --
        update_velocity();
        update_position(minute);
        //------------------------

        //stations --------------
        depart_station(minute);
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
        update_position(minute);
        //------------------------

        //stations ---------------
        depart_station(minute);
        depart_deposit();
        //-------------------------

        //departure ---------------
        departure_next_train(minute);
        sort_trains();

        //fancy_cout();
    }
    std::cout << "seconda simulazione ok" << std::endl;
}
