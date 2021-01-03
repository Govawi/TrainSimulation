#ifndef deposit
#define deposit

#include "train.hpp"
#include <queue>
#include <stdexcept>

class Deposit
{
private:
    std::queue<Train *> fast;
    std::queue<Train *> medium;
    std::queue<Train *> slow;

public:
    Deposit() : fast{}, medium{}, slow{} {}
    //~Deposit();
    bool is_empty();
    void push(Train &t); //insert a train in the correct queue
    Train *pop();        //pop a Train*
};

#endif