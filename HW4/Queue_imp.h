#ifndef EX04_CPP_QUEUE_IMP_H
#define EX04_CPP_QUEUE_IMP_H

#include "Queue.h"

template <typename T>
Queue<T>::Queue() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &other) {
    head = nullptr;
    tail = nullptr;
    count = 0;
    QNode<T>* temp = other.head;
    while(temp) {
        enqueue(temp->data);
        temp = temp->next;
    }
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &other) {
    if(this == &other) {
        return *this;
    }
    clear();
    QNode<T>* temp = other.head;
    while(temp) {
        enqueue(head->data);
        temp = temp->next;
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
Queue<T>::Queue(Queue<T> &&other) noexcept {
    head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept {
    if(this == &other) {
        return *this;
    }
    head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    return *this;
}

template <typename T>
void Queue<T>::enqueue(T element) {
    QNode<T>* node = new QNode<T>(element);
    count++;
    if(head == nullptr) {
        head = node;
        tail = node;
        return;
    }
    tail->setNext(node);
    tail = node;
}

template <typename T>
void Queue<T>::sort_enqueue(T element) {
    QNode<T>* node = new QNode<T>(element);
    count++;
    if(head == nullptr) {
        head = node;
        tail = node;
        return;
    }
    else if(*head->getData() <= element) {
        node->setNext(head);
        head = node;
    }
    else {
        QNode<T>* current = head;
        while(current->getNext() && *current->getNext()->getData() > element) {
            current = current->getNext();
        }
        if(current == tail) {
            tail->setNext(node);
            tail = node;
            return;
        }
        node->setNext(current->getNext());
        current->setNext(node);
    }
}

template <typename T>
T& Queue<T>::peek() {
    return *head->getData();
}

template <typename T>
bool Queue<T>::dequeue() {
    if(count == 0) {
        std::cerr << "Queue is empty!" << std::endl;
        return false;
    }
    head = head->getNext();
    count--;
    return true;
}

template <typename T>
void Queue<T>::clear() {
    while(head) {
        QNode<T>* temp = head;
        head = head->getNext();
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <typename T>
int Queue<T>::size() {
    return count;
}

template <typename T>
void Queue<T>::sort_queue() {
    Queue<T>* sorted = new Queue<T>();
    while(head) {
        QNode<T>* temp = head;
        head = head->getNext();
        sorted->sort_enqueue(*temp->getData());
        delete temp;
    }
    head = sorted->head;
    tail = sorted->tail;
    count = sorted->count;
}

template <typename T>
void Queue<T>::print() {
    printReverse(head);
}

template <typename T>
void Queue<T>::printReverse(QNode<T>* node) {
    if(node == nullptr) {
        return;
    }
    printReverse(node->getNext());
    std::cout << *node->getData();
}

template <typename T>
QNode<T> *Queue<T>::getTail() const {
    return tail;
}

template <typename T>
QNode<T> *Queue<T>::getHead() {
    return head;
}

template <typename T>
void Queue<T>::operator++(int x) {
    if(check_types()) {
        return;
    }
    else if(head->getData()->getType() == "P") {
        QNode<T>* h = getHead();
        dequeue();
        enqueue(*h->getData());
        (*this)++;
        return;
    }
    Virus* v = new Virus(*getTail()->getData());
    getTail()->getData()->incrementId();
    v->setVersion(*getTail()->getData()->getId());
    dequeue();
    v->setApproximation(v->approximationCalc());
    enqueue(*v);
    sort_queue();
}

template <typename T>
bool Queue<T>::check_types() {
    QNode<T>* temp = head;
    while(temp) {
        if(temp->getData()->getType() != "P") {
            return false;
        }
        temp = temp->getNext();
    }
    return true;
}


#endif //EX04_CPP_QUEUE_IMP_H
