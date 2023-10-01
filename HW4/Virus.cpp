#include "Virus.h"
#include <utility>
#include "World.h"


Virus::Virus(std::string name, int* values) {
    this->name = std::move(name);
    this->dim = World::dim;
    this->values = values;
    this->approximation = 1;
    this->version = 0;
    this->counter = 0;
    this->id = &counter;
    this->Pm = 0;
    this->type = "V";
}

Virus::Virus(const Virus &other) {
    this->name = other.name;
    this->approximation = other.approximation;
    this->dim = other.dim;
    this->counter = other.counter;
    this->version = other.version;
    this->id = other.id;
    this->Pm = other.Pm;
    this->type = other.type;
    this->values = new int[dim];
    for(int i = 0; i < dim; i++) {
        this->values[i] = other.values[i];
    }
}

Virus &Virus::operator=(const Virus &other) {
    if(this == &other) {
        return *this;
    }
    this->name = other.name;
    this->approximation = other.approximation;
    this->dim = other.dim;
    this->counter = other.counter;
    this->version = other.version;
    this->id = other.id;
    delete[] this->values;
    this->type = other.type;
    this->Pm = other.Pm;
    this->values = new int[dim];
    for(int i = 0; i < dim; i++) {
        this->values[i] = other.values[i];
    }
    return *this;
}

Virus::~Virus() {
    delete[] this->values;
}

Virus::Virus(Virus &&other) noexcept {
    this->name = other.name;
    this->approximation = other.approximation;
    this->values = other.values;
    this->dim = other.dim;
    this->counter = other.counter;
    this->version = other.version;
    this->type = other.type;
    this->id = other.id;
    this->Pm = other.Pm;
}

Virus &Virus::operator=(Virus &&other) noexcept {
    if(this == &other) {
        return *this;
    }
    this->name = other.name;
    this->approximation = other.approximation;
    this->dim = other.dim;
    this->counter = other.counter;
    this->version = other.version;
    this->id = other.id;
    this->type = other.type;
    delete[] this->values;
    this->values = other.values;
    this->Pm = other.Pm;
    return *this;
}

const std::string &Virus::getName() const {
    return name;
}

int *Virus::getValues() const {
    return values;
}

double Virus::getApproximation() const {
    return approximation;
}

int Virus::getDim() const {
    return dim;
}

void Virus::setApproximation(double approximate) {
    Virus::approximation = approximate;
}

void Virus::incrementId() {
    (*this->id)++;
}

void Virus::setVersion(int v) {
    Virus::version = v;
}

int Virus::getVersion() const {
    return version;
}

int *Virus::getId() const {
    return id;
}

void Virus::setValues(int *array) {
    Virus::values = array;
}

double Virus::approximationCalc() const {
    int* targetVec = World::target->getValues();
    int* vVec = this->getValues();
    int size = this->getDim();
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(targetVec[i] == vVec[i]) {
            count++;
        }
    }
    double approximate = 1;
    approximate -= (double)count / size;
    return approximate;
}

void Virus::operator*() {
    int * arr = this->getValues();
    for(int j = 0; j < this->getPm(); j++) {
        int index1 = rand() % dim;
        int index2 = rand() % dim;
        std::swap(arr[index1], arr[index2]);
    }
    this->setValues(arr);
    this->setApproximation(this->approximationCalc());
}

bool Virus::operator>(const Virus& v) const {
    if(this->getApproximation() > v.getApproximation()) {
        return true;
    }
    return false;
}

bool Virus::operator<=(const Virus& v) const {
    if(this->getApproximation() <= v.getApproximation()) {
        return true;
    }
    return false;
}

void Virus::setPm(int pm) {
    Pm = pm;
}

int Virus::getPm() const {
    return Pm;
}

const std::string &Virus::getType() const {
    return type;
}

void Virus::setType(const std::string &t) {
    Virus::type = t;
}

std::ostream &operator<<(std::ostream &out, const Virus &v) {
    out << v.getName();
    if (v.version != 0) {
        out << "_" + std::to_string(v.version);
    }
    out << " ";
    int *arr = v.values;
    int size = v.dim;
    for (int i = 0; i < size; i++) {
        out << arr[i] << " ";
    }
    out << std::endl;
    return out;
}
