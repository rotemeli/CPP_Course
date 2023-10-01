#ifndef EX03_CPP_SLINKEDLIST_H
#define EX03_CPP_SLINKEDLIST_H
#include "Virus.h"


class SLinkedList {
private:
    /*
     * Node in the linked list
     */
    struct Node {
        Virus* data;
        Node* next;

        Node(Virus* data, Node* next);
    };

    Node* head;
    int count;

public:
    /**
     * Create an empty sorted linked list of viruses
     */
    SLinkedList();

    /*
     * Big three
     * I didn't implement the big five because the default is enough for me
     */
    SLinkedList(const SLinkedList& other);                  // Constructor

    SLinkedList& operator=(const SLinkedList& other);       // Operator=

    ~SLinkedList();                                         // Destructor

    /*
     * Group update to the viruses that's in the linked list
     */
    void operator++(int t);

    /**
     * Adds a virus to the data
     * @param v
     */
    void add(Virus* v);

    /**
     * Removes virus from the linked list
     * @param v
     * @return
     */
    bool remove(Virus* v);

    /**
     * Returns a virus found in the received index
     * @param index
     * @return
     */
    Virus* get(int index);

    /**
     * Returns the linked list size
     * @return
     */
    int size() const;

    /**
     * Removes all the viruses in the linked list
     */
    void clear();

    /**
     * Return if the linked list is empty
     * @return
     */
    bool isEmpty() const;

    /**
     * Print the current linked list
     */
    void print();
};


#endif //EX03_CPP_SLINKEDLIST_H
