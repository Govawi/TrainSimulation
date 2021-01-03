#include "../include/deposit.hpp"

bool Deposit::is_empty()
{
    return !fast.size() && !medium.size() && !slow.size();
}

void Deposit::push(Train &t)
{
    if (t.get_velocity_max() == 300)
        fast.push(&t);
    else if (t.get_velocity_max() == 240)
        medium.push(&t);
    else
        slow.push(&t);

    t.set_velocity(0);
}

Train *Deposit::pop()
{
    if (is_empty())
        throw std::length_error("** Deposit is mt **"); // https://www.youtube.com/watch?v=S2ihdoT2noo

    if (fast.size())
    {
        fast.front()->set_velocity(80);
        Train *ret = fast.front();
        fast.pop();
        return ret;
    }
    else if (medium.size())
    {
        medium.front()->set_velocity(80);
        Train *ret = medium.front();
        medium.pop();
        return ret;
    }
    slow.front()->set_velocity(80);
    Train *ret = slow.front();
    slow.pop();
    return ret;
}