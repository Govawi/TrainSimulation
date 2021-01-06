#include "../include/simulation.hpp"

Simulation::Simulation()
{
    Line line;
    for(int i=0; i<1439; i++)
    {
        line.departure_next_train(i);
        /*
        fai partire treno che deve partire
        ogni treno aggiorna posizione, controlla se deve rallentare,o entare in un deposito, aggiorna stazione successiva se a 20 km
        elimina treni arrivati

        */
    }
}

