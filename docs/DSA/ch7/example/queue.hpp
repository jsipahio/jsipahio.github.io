#ifndef QUEUE_HPP
#define QUEUE_HPP

// a Node struct that stores each queue element's
// data, along with a reference to the next node
template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node(const T& d, Node<T>* n = nullptr) {
        data = d;
        next = n;
    }
};

// an implementation of queue that uses a singly
// linked list, rather than an array
template <typename T>
class Queue {
public:
    Queue() {
        foq = back = nullptr;
    }
    ~Queue() {
        while (foq != nullptr) {
            Node<T> *temp = foq;
            foq = foq-next;
            delete temp;
        }
    }
    Queue(const Queue& other) {
        foq = back = nullptr;
        Node<T> *temp = other.foq;
        while (temp != nullptr) {
            enqueue(temp->data);
        }
    }
    Queue<T>& operator=(Queue rhs) {
        swap(rhs);
        return *this;
    }

    void swap(Queue& other) {
        Node<T> *tempFront = foq;
        Node<T> *tempBack = back;

        foq = other.foq;
        other.foq = tempFront;

        back = other.back;
        other.back = tempBack;
    }

    void enqueue(const T& data) {
        if (foq == nullptr) {
            foq = new Node<T>(data);
            back = foq;
        }
        else {
            Node<T> *next = new Node<T>(data);
            foq->next = next;
            back = next;
        }
    }

    void dequeue() {
        if (foq == nullptr && back == nullptr) {
            throw;
        }
        Node<T> *temp = foq;
        foq = foq->next;
        delete temp;
    }

    T front() const {
        if (foq == nullptr) {
            throw;
        }
        return foq->data;
    }

    bool empty() const {
        return foq == nullptr && back == nullptr;
    }
private:
    Node<T> *foq;
    Node<T> *back;
};

#endif
