#include <iostream>
#include "Alchemize.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid run arguments; run the game with board size.\n";
        exit(-1);
    }
    int size = std::stoi(argv[1]);
    auto *game = new Alchemize(size);
    game->init();
    delete game;
    return 0;
}
