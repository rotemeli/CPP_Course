#include "Lentivirus.h"

#include <utility>

Lentivirus::Lentivirus(std::string name, int *values) : Virus(std::move(name), values) {
    this->setPm(2);
    this->setType("L");
}
