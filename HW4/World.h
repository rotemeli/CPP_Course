#ifndef EX03_CPP_WORLD_H
#define EX03_CPP_WORLD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Virus.h"
#include "Queue.h"
#include "Lentivirus.h"
#include "Papilloma.h"
#include "Mimivirus.h"


class World {
private:
    Queue<Virus>* population;
    int popSize;
    Virus* best;

    /**
     * Function that gets string and return pointer to integer array with the values
     * @param values
     * @return
     */
    static int* strToArray(const std::string& values);

    /**
     * A recursive helper function for the individual update
     * @param node
     * @param pop
     */
    void RecIndividualUpdate(QNode<Virus>* node, Queue<Virus>* pop);

    /**
     * Individual update to the population of viruses
     */
    void individualUpdate();

    /**
     * Prints the best virus of all times (lowest error)
     */
    void printBest();

public:
    /*
     * static fields
     */
    static Virus* target;

    static int dim;

    World(const std::string& file1, const std::string& file2);      // constructor

    /*
     * Big three
     * I didn't implement the big five because the default is enough for me
     */
    World(const World& other);

    World& operator=(const World& other);

    ~World();

    /**
     * Starts the program
     */
    void init();
};


#endif //EX03_CPP_WORLD_H
