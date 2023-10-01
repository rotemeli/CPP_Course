#include "Alchemize.h"
#include <iostream>

Alchemize::Alchemize(int size) {
    this->blue_count = 0;
    this->red_count = 0;
    this->size = size;
    this->counter = this->size * this->size;
    this->board = new Cell*[this->size];
    for(int i = 0; i < this->size; i++) {
        this->board[i] = new Cell[this->size];
        for(int j = 0; j < this->size; j++) {
            this->board[i][j] = Cell();
        }
    }
}

Alchemize::Alchemize(const Alchemize &other) {
    this->size = other.size;
    this->counter = other.counter;
    this->red_count = other.red_count;
    this->blue_count = other.blue_count;
    this->board = new Cell*[other.size];
    for(int i = 0; i < other.size; i++) {
        this->board[i] = new Cell[other.size];
        for(int j = 0; j < other.size; j++) {
            this->board[i][j] = other.board[i][j];
        }
    }
}

Alchemize::~Alchemize() {
    for(int i = 0; i < this->size; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

Alchemize &Alchemize::operator=(const Alchemize &other) {
    if(this == &other) {
        return *this;
    }
    for(int i = 0; i < other.size; i++) {
        if(this->board[i]) {
            delete[] board[i];
        }
    }
    delete[] this->board;

    this->size = other.size;
    this->red_count = other.red_count;
    this->blue_count = other.blue_count;

    this->board = new Cell*[this->size];
    for(int i = 0; i < other.size; i++) {
        this->board[i] = new Cell[other.size];
        for(int j = 0; j  <  other.size; j++) {
            this->board[i][j] = other.board[i][j];
        }
    }
    return *this;
}

Alchemize::Alchemize(Alchemize &&other) noexcept {
    this->size = other.size;
    this->counter = other.counter;
    this->blue_count = other.blue_count;
    this->red_count = other.red_count;
    this->board = other.board;
    for(int i = 0; i < other.size; i++) {
        other.board[i] = nullptr;
    }
    other.board = nullptr;
}

Alchemize &Alchemize::operator=(Alchemize &&other) noexcept {
    this->size = other.size;
    this->counter = other.counter;
    this->blue_count = other.blue_count;
    this->red_count = other.red_count;
    this->board = other.board;
    for(int i = 0; i < other.size; i++) {
        other.board[i] = nullptr;
    }
    other.board = nullptr;
    return *this;
}

void Alchemize::printBoard() {
    std::cout << "Red count: " << this->red_count;
    std::cout << "\tBlue count: " << this->blue_count << std::endl;
    for(int i = 0; i < this->size; i++) {
        for(int j = 0; j < this->size; j++) {
            std::cout << this->board[i][j].getValue() << "\t";
        }
        std::cout << std::endl;
    }
}

bool Alchemize::check_index(int row, int col) {
    if(row < 0 || col < 0 || row >= this->size || col >= this->size) {
        return true;
    }
    if(this->board[row][col].getValue() != 'O') {
        return true;
    }
    return false;
}

void Alchemize::red_turn(int i, int j) {
    if(this->board[i][j].isRedFlag() && this->board[i][j].getValue() == 'O') {
        this->counter--;
        this->board[i][j].setValue('X');
    }
    if(!this->board[i][j].isRedFlag()) {
        this->board[i][j].setRedFlag(true);
    }
    if(this->board[i][j].isRedFlag() && (this->board[i][j].getValue() == 'r' || this->board[i][j].getValue() == 'b')) {
        if(this->board[i][j].getValue() == 'b') {
            this->blue_count--;
        }
        else if(this->board[i][j].getValue() == 'r'){
            this->red_count--;
        }
        this->board[i][j].setValue('X');
    }
    else if(this->board[i][j].isBlueFlag() && this->board[i][j].isRedFlag() && this->board[i][j].getValue() == 'O') {
        this->board[i][j].setValue('r');
        this->counter--;
        this->red_count++;
    }
}

void Alchemize::blue_turn(int i, int j) {
    if(this->board[i][j].isBlueFlag() && this->board[i][j].getValue() == 'O') {
        this->counter--;
        this->board[i][j].setValue('X');
    }
    if(!this->board[i][j].isBlueFlag()) {
        this->board[i][j].setBlueFlag(true);
    }
    if(this->board[i][j].isBlueFlag() && (this->board[i][j].getValue() == 'r' || this->board[i][j].getValue() == 'b')) {
        if(this->board[i][j].getValue() == 'b') {
            this->blue_count--;
        }
        else if(this->board[i][j].getValue() == 'r'){
            this->red_count--;
        }
        this->board[i][j].setValue('X');
    }
    else if(this->board[i][j].isBlueFlag() && this->board[i][j].isRedFlag() && this->board[i][j].getValue() == 'O') {
        this->board[i][j].setValue('b');
        this->counter--;
        this->blue_count++;
    }
}

void Alchemize::locality(int row, int col, bool turn) {
    int rows[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int cols[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    for(int k = 0; k < 8; k++) {
        int i = row + rows[k];
        int j = col + cols[k];

        if(i < 0 || j < 0 || i > this->size-1 || j > this->size-1) {
            continue;
        }
        if(turn) {
            red_turn(i, j);
        }
        else {
            blue_turn(i, j);
        }
    }
}

void Alchemize::init() {
    bool turn = true;
    int num1, num2;
    printBoard();
    while(this->counter > 0) {
        if(turn) {
            std::cout << "R:\n";
        }
        else {
            std::cout << "B:\n";
        }
        std::cin >> num1;
        std::cin >> num2;
        num1--;
        num2--;
        if(check_index(num1, num2)) {
            std::cerr << "Invalid row/col index or non free cell\n";
            continue;
        }
        if(turn) {
            this->board[num1][num2].setValue('R');
            this->counter--;
            locality(num1, num2, turn);
        }
        else {
            this->board[num1][num2].setValue('B');
            this->counter--;
            locality(num1, num2, turn);
        }
        turn = !turn;
        printBoard();
    }
    if(this->red_count > this->blue_count) {
        std::cout << "Red won\n";
    }
    else if (this->red_count < this->blue_count) {
        std::cout << "Blue won\n";
    }
    else {
        std::cout << "The game ended with a tie\n";
    }
}
