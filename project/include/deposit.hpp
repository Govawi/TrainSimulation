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
    Deposit();
    ~Deposit();

    bool is_empty()
    { return !fast.size() && !medium.size() && !slow.size(); }

    void push(Train t)
    {
        if(t.get_velocity_max() == 300)
            fast.push(t);
        else if(t.get_velocity_max() == 240)
            medium.push(t);
        else
            slow.push(t);

        t.set_velocity(0);
    }
    
    int pull()
    {
        if (is_empty())
            throw std::length_error("** Deposit is mt **"); // https://www.youtube.com/watch?v=S2ihdoT2noo

        if (fast.size())
        {
            int ret = fast.front().get_train_name();
            fast.front().set_velocity(80);
            fast.pop();
            return ret;
        }
        else if(medium.size())
        {
            int ret = medium.front().get_train_name();
            medium.front().set_velocity(80);
            medium.pop();
            return ret;
        }
        int ret = slow.front().get_train_name();
        slow.front().set_velocity(80);
        slow.pop();
        return ret;        
    }

};

#endif