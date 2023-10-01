#ifndef EX02_CPP_ALCHEMIZE_H
#define EX02_CPP_ALCHEMIZE_H

#include "Cell.h"


class Alchemize {
private:
    int size;
    Cell **board;
    int red_count;
    int blue_count;
    int counter;

    /**
     * Board printing to standard output
     */
    void printBoard();

    /**
     * Checking if the indexes received from the user are valid
     * @param row
     * @param col
     * @return
     */
    bool check_index(int row, int col);

    /**
     * A function that runs around all neighbors of a cell
     * @param row
     * @param col
     * @param turn
     */
    void locality(int row, int col, bool turn);

    /**
     * A function that updates the board when it is the red player's turn
     * @param i
     * @param j
     */
    void red_turn(int i, int j);

    /**
     * A function that updates the board when it is the blue player's turn
     * @param i
     * @param j
     */
    void blue_turn(int i, int j);

public:
    /**
     * Delete the default constructor
     */
    Alchemize() = delete;

    /**
     * Constructor
     * @param size
     */
    explicit Alchemize(int size);

    /**
     * Copy constructor
     * @param other
     */
    Alchemize(const Alchemize& other);

    /**
     * Destructor
     */
    ~Alchemize();

    /**
     * Operator=
     * @param other
     * @return
     */
    Alchemize& operator=(const Alchemize& other);

    /**
     * Move constructor
     * @param other
     */
    Alchemize(Alchemize&& other) noexcept;

    /**
     * Move operator=
     * @param other
     * @return
     */
    Alchemize& operator=(Alchemize&& other) noexcept;

    /**
     * Starts the game with a board of size nXn
     */
    void init();
};


#endif //EX02_CPP_ALCHEMIZE_H
