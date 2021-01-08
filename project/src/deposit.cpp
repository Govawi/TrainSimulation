#include "../include/deposit.hpp"

bool Deposit::is_empty()
{
    // checks size of every queue
    return !fast.size() && !medium.size() && !slow.size();
}

void Deposit::push(std::shared_ptr<Train> p)
{
    // push train in correct queue
    if (p->get_velocity_max() == 300)
        fast.push(p);
    else if (p->get_velocity_max() == 240)
        medium.push(p);
    else
        slow.push(p);

    // stop the train
    p->set_velocity(0);
}

std::shared_ptr<Train> Deposit::pop()
{
    // checks if deposit is mt
    if (is_empty())
        throw std::length_error("** Deposit is mt **"); // https://www.youtube.com/watch?v=S2ihdoT2noo

    // 1. empty fast queue
    if (fast.size())
    {
        fast.front()->set_velocity(1.3);
        std::shared_ptr<Train> ret = fast.front();
        fast.pop();
        return ret;
    }
    // 2. empty medium queue
    else if (medium.size())
    {
        medium.front()->set_velocity(1.3);
        std::shared_ptr<Train> ret = medium.front();
        medium.pop();
        return ret;
    }
    // 3. empty slow queue
    slow.front()->set_velocity(1.3);
    std::shared_ptr<Train> ret = slow.front();
    slow.pop();
    return ret;
}