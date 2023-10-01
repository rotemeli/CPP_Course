#ifndef EX03_CPP_WORLD_H
#define EX03_CPP_WORLD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Virus.h"
#include "SLinkedList.h"


class World {
private:
    SLinkedList* population;
    int popSize;
    Virus* best;

    /**
     * Function that gets string and return pointer to integer array with the values
     * @param values
     * @return
     */
    static int* strToArray(const std::string& values);

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

    static int Pm;

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
