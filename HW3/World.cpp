#include "World.h"
#include "Virus.h"

int World::dim;
int World::Pm;
Virus* World::target = nullptr;

World::World(const std::string& file1, const std::string& file2) {
    std::string line;
    std::ifstream outfile(file1);
    if(outfile.is_open()) {
        std::getline(outfile, line);
        dim = stoi(line);
        std::getline(outfile, line);
        Pm = stoi(line);
        std::getline(outfile, line);
        outfile.close();
    }
    else {
        std::cerr << "File not found." << std::endl;
    }
    std::string targetName = "target";
    target = new Virus(targetName, strToArray(line));
    target->setApproximation(0);
    this->population = new SLinkedList();
    std::string line2;
    std::ifstream outfile2(file2);

    if(outfile2.is_open()) {
        std::getline(outfile2, line2);
        this->popSize = stoi(line2);
        std::string name;
        std::stringstream ss;
        while(std::getline(outfile2, line2)) {
            ss.str(line2);
            ss >> name;
            auto* v = new Virus(name, strToArray(ss.str().erase(0, name.size()+1)));
            v->setApproximation(v->approximationCalc());
            this->population->add(v);
        }
        outfile2.close();
    }
    else {
        std::cerr << "File not found." << std::endl;
    }
    this->best = new Virus(*this->population->get(0));
}

World::World(const World &other) {
    this->population = other.population;
    this->popSize = other.popSize;
    this->best = other.best;
}

World &World::operator=(const World &other) {
    if(this == &other) {
        return *this;
    }
    this->population = other.population;
    this->popSize = other.popSize;
    this->best = other.best;
    return *this;
}

World::~World() {
    delete target;
    delete this->population;
    delete this->best;
}

int* World::strToArray(const std::string& values) {
    std::stringstream ss(values);
    std::string val;
    int* arr = new int[dim];
    int i = 0;
    while(ss >> val) {
        arr[i] = stoi(val);
        i++;
    }
    if(i != dim) {
        std::cerr << "Invalid input." << std::endl;
        exit(-1);
    }
    return arr;
}

void World::init() {
    int num;
    std::cin >> num;
    for(int i = 0; i < num; i++) {
        if(population->get(0)->getApproximation() == 0) {
            break;
        }
        (*population)++;
        individualUpdate();
    }
    population->print();
    printBest();
}

void World::individualUpdate() {
    auto *new_pop = new SLinkedList();
    for(int i = 0; i < population->size(); i++) {
        Virus *v = population->get(i);
        *(*v);
        new_pop->add(v);
    }
    population = new_pop;
    if(new_pop->get(0)->getApproximation() < best->getApproximation()) {
        best = new Virus(*new_pop->get(0));
    }
}

void World::printBest() {
    std::cout << "\n" << this->best->getName();
    if(best->getVersion() != 0) {
        std::cout << "_" + std::to_string(best->getVersion());
    }
    std::cout << "\t";
    for(int i = 0; i < this->best->getDim(); i++) {
        std::cout << this->best->getValues()[i] << " ";
    }
    std::cout << std::endl;
}
