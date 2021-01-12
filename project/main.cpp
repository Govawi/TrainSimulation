#include "include/line.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    Line test;
    return 0;
}
/*

| ------------------------------------------------------------------------------------ |
|                  _                          __  ___                                  |
|    ___ ____ ___ (_)__ ____  __ _  ___ ___  / /_|_  |                                 |
|   / _ `(_-<(_-</ / _ `/ _ \/  ' \/ -_) _ \/ __/ __/                                  |
|   \_,_/___/___/_/\_, /_//_/_/_/_/\__/_//_/\__/____/                                  |
|                 /___/                                                                |
|                                                                                      |
|                    _-====-__-======-__-========-_____-============-__                |
|                  _(                                                 _)               |
|               OO(     Alessio Cocco               Giovanni Brejc    )_               |
|              0  (_               Andrea Valentinuzzi                 _)              |
|            o0     (_                                                _)               |
|           o         '=-___-===-_____-========-___________-===-dwb-='                 |
|         .o                                _________                                  |
|        . ______          ______________  |         |      _____                      |
|      _()_||__|| ________ |            |  |_________|   __||___||__                   |
|     (BNSF 1995| |      | |            | __Y______00_| |_         _|                  |
|    /-OO----OO""="OO--OO"="OO--------OO"="OO-------OO"="OO-------OO"=P                |
|   #####################################################################              |
|                                                                                      |
| ------------------------------------------------------------------------------------ |
|                                                                                      |
|     __ _ _               _                   _                                       |
|    / _(_) | ___  ___ ___| |_ _ __ _   _  ___| |_ _   _ _ __ ___                      |
|   | |_| | |/ _ \/ __/ __| __| '__| | | |/ __| __| | | | '__/ _ \                     |
|   |  _| | |  __/\__ \__ \ |_| |  | |_| | (__| |_| |_| | | |  __/                     |
|   |_| |_|_|\___||___/___/\__|_|   \__,_|\___|\__|\__,_|_|  \___|                     |
|                                                                                      |
|                                ----------                                            |
|                               | main.cpp |                                           |
|                                ----------                                            |
|                                    ˅˅                                                |
|                                ----------                                            |
|                   ˂˂˂˂˂˂˂˂˂˂˂ | line.hpp |                                           |
|                  ˅˅            ----------                                            |
|                  ˅˅                ˅˅                                                |
|             -----------       -------------                                          |
|            | train.hpp | ˂˂˂ | station.hpp |                                         |
|             -----------       -------------                                          |
|                  ˄˄                ˅˅                                                |
|                  ˄˄           -------------                                          |
|                   ˂˂˂˂˂˂˂˂˂˂ | deposit.hpp |                                         |
|                               -------------                                          |
|                                                                                      |
| ------------------------------------------------------------------------------------ |
|                                                                                      |
|                  _      _             _                                              |
|     ___ ___   __| | ___| | ___   __ _(_) ___                                         |
|    / __/ _ \ / _` |/ _ \ |/ _ \ / _` | |/ __|                                        |
|   | (_| (_) | (_| |  __/ | (_) | (_| | | (__                                         |
|    \___\___/ \__,_|\___|_|\___/ \__, |_|\___|                                        |
|                                 |___/                                                |
|                                                                                      |
|   Creation of a Line object that contains:                                           |
|    - std::vector of std::shared_ptr to Stations.                                     |
|    - std::vector of std::shared_ptr to Trains.                                       |
|                                                                                      |
|   Filling said vectors with data from timetables.txt & line_description.txt:         |
|    - stations closer than 20km are eliminated (& corresponding times).               |
|    - times not compatible with [distance / train speed + factors] are modified.      |
|                                                                                      |
|   The simulation starts and is executed twice (one per direction):                   |
|    - it consists of 1440-loop (minutes in a day).                                    |
|    - every minute various conditions are checked in order to allow                   |
|       take-overs, entrance in deposit, wait inside deposit or station.               |
|    - train delays get updated and communication happens between trains & stations.   |
|    - the last step of a loop cycle is updating the position of each train            |
|       taking into consideration their speed.                                         |
|                                                                                      |
| ------------------------------------------------------------------------------------ |

*/