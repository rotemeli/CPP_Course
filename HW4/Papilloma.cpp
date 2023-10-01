#include "Papilloma.h"

#include <utility>

Papilloma::Papilloma(std::string name, int *values) : Virus(std::move(name), values) {
    this->setPm(1);
    this->setType("P");
}
