#include "Mimivirus.h"

#include <utility>

Mimivirus::Mimivirus(std::string name, int *values) : Virus(std::move(name), values) {
    this->setPm(4);
    this->setType("M");
}
