#ifndef line_hpp
#define line_hpp

#include <memory>
#include <vector>
#include "station.hpp"
#include "train.hpp"

class Line
{
private:
    /** @brief Vector containing all stations. */
    std::vector<std::unique_ptr<Station>> stations;
    /** @brief Vector containing all trains. */
    std::vector<std::unique_ptr<Train>> trains;
    /** @brief Vector contatining train in line from left to right */
    std::vector<std::unique_ptr<Train>> line_left_right;
    /** @brief Vector contatining train in line from right to left */
    std::vector<std::unique_ptr<Train>> line_right_left;
    /** @brief Vector containing indexes of removed stations. */
    std::vector<int> time_to_remove;
    std::vector<int> time_to_remove_main;

public:
    /**
     * @brief Constructs a new line and trains & checks times.
     */
    Line();

    /**
     * @brief Manages train initialization.
     */
    void vector_trains();
    /**
     * @brief Manages station initialization.
     */
    void vector_stations();

    /**
     * @brief Prints all stored stations in a nicely formatted way :)
     */
    void print_stations() const;
    /**
     * @brief Prints all stored trains in a nicely formatted way :)
     */
    void print_trains() const;
    /**
     * @brief Sort in order of departure the train
     * 
     */
    void push_train();
    void sort_trains();
    void print_departure();
};

#endif
