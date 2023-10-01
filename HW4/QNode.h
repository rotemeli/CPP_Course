#ifndef CPP_TRAININGS_QNODE_H
#define CPP_TRAININGS_QNODE_H

template <typename T>
class QNode {
private:
    T data;
    QNode* next;

public:
    QNode() = delete;

    /**
     * Creates empty node with generic element
     * @param element
     */
    explicit QNode(const T& element) : data(element), next(nullptr) {}

    /**
     * Returns the node data
     * @return
     */
    T* getData() {
        return &data;
    }

    /**
     * Returns the next node
     * @return
     */
    QNode *getNext() const {
        return next;
    }

    /**
     * Set the data
     * @param ele
     */
    void setData(T ele) {
        QNode::data = ele;
    }

    /**
     * Set the next node
     * @param n
     */
    void setNext(QNode *n) {
        QNode::next = n;
    }
};


#endif //CPP_TRAININGS_QNODE_H
