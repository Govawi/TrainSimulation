#include "../include/deposit.hpp"

bool Deposit::is_empty()
{
    // checks size of every queue
    return !fast.size() && !medium.size() && !slow.size();
}

void Deposit::push(Train &t)
{
    // push train in correct queue
    if (t.get_velocity_max() == 300)
        fast.push(&t);
    else if (t.get_velocity_max() == 240)
        medium.push(&t);
    else
        slow.push(&t);

    // stop the train
    t.set_velocity(0);
}

Train *Deposit::pop()
{
    // checks if deposit is mt
    if (is_empty())
        throw std::length_error("** Deposit is mt **"); // https://www.youtube.com/watch?v=S2ihdoT2noo

    // 1. empty fast queue
    if (fast.size())
    {
        fast.front()->set_velocity(80);
        Train *ret = fast.front();
        fast.pop();
        return ret;
    }
    // 2. empty medium queue
    else if (medium.size())
    {
        medium.front()->set_velocity(80);
        Train *ret = medium.front();
        medium.pop();
        return ret;
    }
    // 3. empty slow queue
    slow.front()->set_velocity(80);
    Train *ret = slow.front();
    slow.pop();
    return ret;
}