#ifndef EX04_CPP_QUEUE_H
#define EX04_CPP_QUEUE_H

#include <iostream>
#include "QNode.h"
#include <typeinfo>
#include "Papilloma.h"


template <typename T>
class Queue {
private:
    QNode<T>* head;
    QNode<T>* tail;
    int count;

    /**
     * Help function to check if all viruses are of the papilloma type
     * @return
     */
    bool check_types();

    /**
     * Help function to print the queue
     * @param node
     */
    void printReverse(QNode<T>* node);

public:
    /**
     * Creates an empty queue
     */
    Queue();

    /*
     * Big five
     */
    Queue(const Queue& other);

    Queue& operator=(const Queue& other);

    ~Queue();

    Queue(Queue&& other) noexcept;

    Queue& operator=(Queue&& other) noexcept;

    /**
     * Enqueue a generic element into the tail of the queue
     * @param element
     */
    void enqueue(T element);

    /**
     * Enqueue a generic element in a sorted form
     * @param element
     */
    void sort_enqueue(T element);

    /**
     * Returns the head of the queue by reference
     * @return
     */
    T& peek();

    /**
     * Remove an element from the head of the queue
     * @return
     */
    bool dequeue();

    /**
     * Clear the queue
     */
    void clear();

    /**
     * Return the size of the queue
     * @return
     */
    int size();

    /**
     * Sorts the elements in the queue
     */
    void sort_queue();

    /**
     * Prints the queue
     */
    void print();

    /**
     * Returns the tail of the queue
     * @return
     */
    QNode<T>* getTail() const;

    /**
     * Returns the head of the queue
     * @return
     */
    QNode<T>* getHead();

    /**
     * Group update to the elements in the queue
     * @param x
     */
    void operator++(int x);
};
#include "Queue_imp.h"


#endif //EX04_CPP_QUEUE_H
