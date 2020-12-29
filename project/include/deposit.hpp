#ifndef deposit
    #define deposit

#include "train.hpp"
#include <queue>

class Deposit
{
private:
    std::queue<Train> fast;
    std::queue<Train> medium;
    std::queue<Train> slow;

public:
    Deposit(int p, int s);
    ~Deposit();

    void push(Train t);
    Train pull();


};

#endif