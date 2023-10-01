#include "World.h"


int World::dim;
Virus* World::target = nullptr;

World::World(const std::string& file1, const std::string& file2) {
    std::string line;
    std::ifstream outfile(file1);
    if(outfile.is_open()) {
        std::getline(outfile, line);
        dim = stoi(line);
        std::getline(outfile, line);
        outfile.close();
    }
    else {
        std::cerr << "File not found." << std::endl;
    }
    std::string targetName = "target";
    target = new Virus(targetName, strToArray(line));
    target->setApproximation(0);
    this->population = new Queue<Virus>();
    std::string line2;
    std::ifstream outfile2(file2);

    if(outfile2.is_open()) {
        std::getline(outfile2, line2);
        this->popSize = stoi(line2);
        std::string name;
        std::string virusType;
        std::stringstream ss;
        while(std::getline(outfile2, line2)) {
            ss.str(line2);
            ss >> virusType;
            ss >> name;
            std::string temp;
            temp.append(virusType).append(" ").append(name);
            name = temp;
            if(virusType == "L") {
                Virus* l = new Lentivirus(name, strToArray(ss.str().erase(0, name.size()+1)));
                l->setApproximation(l->approximationCalc());
                this->population->sort_enqueue(*l);
            }
            else if(virusType == "M") {
                Virus* m = new Mimivirus(name, strToArray(ss.str().erase(0, name.size()+1)));
                m->setApproximation(m->approximationCalc());
                this->population->sort_enqueue(*m);
            }
            else if(virusType == "P") {
                Virus* p = new Papilloma(name, strToArray(ss.str().erase(0, name.size()+1)));
                p->setApproximation(p->approximationCalc());
                this->population->sort_enqueue(*p);
            }
        }
        outfile2.close();
    }
    else {
        std::cerr << "File not found." << std::endl;
    }
    this->best = new Virus(*population->getTail()->getData());
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
        if(population->getTail()->getData()->getApproximation() == 0) {
            break;
        }
        (*population)++;
        individualUpdate();
        population->sort_queue();
    }
    population->print();
    printBest();
}

void World::RecIndividualUpdate(QNode<Virus>* node, Queue<Virus>* pop) {
    if(node == nullptr) {
        return;
    }
    RecIndividualUpdate(node->getNext(), pop);
    Virus *v = node->getData();
    *(*v);
    pop->sort_enqueue(*v);
    population = pop;
}

void World::individualUpdate() {
    Queue<Virus>* new_pop = new Queue<Virus>();
    QNode<Virus>* temp = population->getHead();
    RecIndividualUpdate(temp, new_pop);
    population->sort_queue();
    if(population->getTail()->getData()->getApproximation() < best->getApproximation()) {
        best = new Virus(*population->getTail()->getData());
    }
}

void World::printBest() {
    std::cout << "\n" << this->best->getName();
    if(best->getVersion() != 0) {
        std::cout << "_" + std::to_string(best->getVersion());
    }
    std::cout << " ";
    for(int i = 0; i < this->best->getDim(); i++) {
        std::cout << this->best->getValues()[i] << " ";
    }
    std::cout << std::endl;
}
