#include <iostream>
#include <string>
#include "World.h"


int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Usage: run the program with <init file name> <location file name>" << std::endl;
        exit(-1);
    }
    auto *w = new World(argv[1], argv[2]);
    w->init();

    delete w;

    return 0;
}
