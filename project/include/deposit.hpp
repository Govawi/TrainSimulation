#ifndef deposit_hpp
#define deposit_hpp

#include "train.hpp"
#include <queue>
#include <stdexcept>

class Deposit
{
private:
    /** @brief Fast queue. */
    std::queue<Train*> fast;
    /** @brief Medium queue. */
    std::queue<Train*> medium;
    /** @brief Slow queue. */
    std::queue<Train*> slow;

public:
    /**
     * @brief Construct a mt deposit, with priority.
     */
    Deposit() : fast{}, medium{}, slow{} {}

    /**
     * @brief Checks if deposit it mt.
     */
    bool is_empty();
    /**
     * @brief Adds incoming train to the deposit.
     * 
     * @param t Train to deposit.
     */
    void push(Train &t);
    /**
     * @brief Removes highest priority train from the deposit
     * 
     * @return Train* that leaves the deposit.
     */
    Train *pop();
};

#endif