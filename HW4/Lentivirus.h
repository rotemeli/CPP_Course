#ifndef EX04_CPP_LENTIVIRUS_H
#define EX04_CPP_LENTIVIRUS_H

#include "Virus.h"


class Lentivirus : public Virus {
public:
    Lentivirus(std::string name, int* values);          // constructor
};


#endif //EX04_CPP_LENTIVIRUS_H
