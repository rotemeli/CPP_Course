#include "Cell.h"

Cell::Cell() {
    this->value = 'O';
    this->red_flag = false;
    this->blue_flag = false;
}

bool Cell::isRedFlag() const {
    return red_flag;
}

void Cell::setRedFlag(bool redFlag) {
    red_flag = redFlag;
}

bool Cell::isBlueFlag() const {
    return blue_flag;
}

void Cell::setBlueFlag(bool blueFlag) {
    blue_flag = blueFlag;
}

void Cell::setValue(char val) {
    Cell::value = val;
}

char Cell::getValue() const {
    return value;
}
