#include "src/train.cpp"
//#include "src/station.cpp"
#include "src/line.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // base operations


    // read line_description.txt


    // read timetables.txt


    // test
    /*
    vector<int> b {1, 12,14,16,20};
    Fast_Train t( 1, 1124 ,b);
    Slow_Train k(2, 2345 ,b);
    Medium_Train l(3, 3456 ,b);
    Slow_Train p(4, 1234 ,b);
    vector<Train*> prova {&t, &k, &l};
    prova.push_back(&p);
    for(int i = 0 ; i < prova.size() ; i++ )
    {
        cout << "Train "<< i << endl;
        cout << "velocity: "<< prova[i]->get_velocity_max() << endl;
        cout << "direction: "<< prova[i]->get_direction() << endl;
        cout << "name: "<< prova[i]->get_train_name() << endl;
    }
    */

    Line test;

    return 0;
}

