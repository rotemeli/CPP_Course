#include "SLinkedList.h"

SLinkedList::Node::Node(Virus *data, SLinkedList::Node *next) {
    this->data = data;
    this->next = next;
}

SLinkedList::SLinkedList() {
    this->head = nullptr;
    this->count = 0;
}

SLinkedList::SLinkedList(const SLinkedList &other) {
    this->head = nullptr;
    this->count = 0;
    Node* temp = other.head;
    while(temp) {
        add(temp->data);
        temp = temp->next;
    }
}

SLinkedList& SLinkedList::operator=(const SLinkedList &other) {
    if(this == &other) {
        return *this;
    }
    clear();
    Node* temp = other.head;
    while(temp) {
        add(temp->data);
        temp = temp->next;
    }
    return *this;
}

SLinkedList::~SLinkedList() {
    clear();
}

void SLinkedList::add(Virus *v) {
    Node* current;
    if(head == nullptr || head->data->getApproximation() > v->getApproximation()) {
        head = new Node(v, head);
    }
    else {
        current = head;
        while(current->next && current->next->data->getApproximation() <= v->getApproximation()) {
            current = current->next;
        }
        Node* new_node = new Node(v, current->next);
        current->next = new_node;
    }
    count++;
}

bool SLinkedList::remove(Virus *v) {
    if(isEmpty()) {
        return false;
    }
    Node* temp = head;
    if(temp->data->compareTo(v)) {
        head = head->next;
        delete temp;
        count--;
        return true;
    }
    while(temp->next && !temp->next->data->compareTo(v)) {
        temp = temp->next;
    }
    if(temp->next) {
        Node* temp2 = temp->next;
        temp->next = temp2->next;
        delete temp2;
        count--;
        return true;
    }
    return false;
}

Virus* SLinkedList::get(int index) {
    if (index < 0 || index >= count) {
        std::cerr << "Invalid index" << std::endl;
        exit(-1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

int SLinkedList::size() const {
    return count;
}

void SLinkedList::clear() {
    while(head) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
    }
    count = 0;
    head = nullptr;
}

bool SLinkedList::isEmpty() const {
    if(count == 0) {
        return true;
    }
    return false;
}

void SLinkedList::print() {
    Node* temp = head;
    int size = temp->data->getDim();
    while(temp) {
        std::cout << temp->data->getName();
        if(temp->data->getVersion() != 0) {
            std::cout << "_" + std::to_string(temp->data->getVersion());
        }
        std::cout << "\t";
        int* arr = temp->data->getValues();
        for(int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        temp = temp->next;
    }
}

void SLinkedList::operator++(int t) {
    auto* v = new Virus(*this->get(0));
    this->get(0)->incrementId();
    v->setVersion(*this->get(0)->getId());
    this->remove(this->get(this->size()-1));
    v->setApproximation(v->approximationCalc());
    this->add(v);
}
