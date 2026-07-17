#ifndef HEAP_HPP
#define HEAP_HPP

#include <sys/types.h>

template <typename T>
struct Node {
    T data;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;
};

template <typename T>
class Heap {
public:
    Heap() : root(nullptr) {}
    ~Heap() {}
    Heap(const Heap& other) {

    }
    Heap& operator=(Heap rhs);
    void swap(Heap &other) {
        
    }

    void insert(T data) {
        if (root == nullptr) {
            root = new Node<T>;
            root->data = data;
            root->left = nullptr;
            root->right = nullptr;
            root->parent = nullptr;
            lastInserted = root;
            return;
        }
        else {

        }

    }
    T peek() const {
        if (root != nullptr) 
            return root->data;
        else 
            throw;
    }
    T pop() {
        T data = root->data;

        return data;
    }

    bool empty() const { return root == nullptr; }
private:
    Node<T> *root;
    Node<T> *lastInserted;
    size_t size;

    Node<T>* getNextNode(T data) {
        if (lastInserted->parent->left == lastInserted) {
            lastInserted->parent->right = new Node<T>;
            lastInserted->parent->right->data = data;
            lastInserted->parent->right->left = nullptr;
            lastInserted->parent->right->right = nullptr;
            lastInserted->parent->right->parent = lastInserted->parent;
            return lastInserted->parent->right;
        }
    }

    void upHeap(Node<T> *node) {
        if (node != nullptr && node->parent != nullptr) {
            if (node->parent->value < node->value) {
                Node<T> *temp = node;
                node = node->parent;
                node->parent = node;
            }
        }
    }
};

#endif