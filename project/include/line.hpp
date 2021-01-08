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
    std::vector<std::shared_ptr<Station>> stations;
    /** @brief Vector containing all trains. */
    std::vector<std::shared_ptr<Train>> trains;
    /** @brief Vector contatining train in line from left to right */
    std::vector<std::shared_ptr<Train>> line;
    /** @brief Vector contatining train in line from right to left */
    std::vector<std::shared_ptr<Train>> tmp;
    /** @brief Vector containing indexes of removed stations. */
    std::vector<int> time_to_remove;
    /** @brief Vector containing indexes of removed main stations. */
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
    void sort_trains();

    //update trains velocity
    void update_velocity();
    void update_position();

    //stations
    void enqueue_next_train();
    void dequeue_next_train();

    //departure
    void departure_next_train(int index);
    double cmp_distance_start(const std::shared_ptr<Train> &a);
    
    //simulation
    void sim();
    void reverse_stations();
    void divide_trains();
};

#endif
