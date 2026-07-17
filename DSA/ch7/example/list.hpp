// implementation of doubly linked list
#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
struct Node {
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(T d, Node<T> *p = nullptr, Node<T> *n = nullptr) {
        data = d;
        prev = p;
        next = n;
    }

    Node(Node<T> *p = nullptr, Node<T> *n = nullptr) {
        prev = p;
        next = n;
    }
};

// A double linked list looks something like this
// nullptr <- front <-> node1 <-> node2 <-> node3 <-> back -> nullptr
// the list is empty when front and back are nullptr, 
// or front->next == back and back->prev == front
// front and back do not store data, 
// they just mark the front and end of the list
template <typename T>
class List {
public:
    struct Iterator {
        Iterator(Node<T> *r): ref(r) {}
        Iterator& operator--() {
            if (ref == nullptr) return *this;
            if (ref->prev != nullptr) {
                ref = ref->prev;
                return *this;
            }
            else {
                return *this;
            }
        }
        Iterator& operator++() {
            if (ref == nullptr) return *this;
            if (ref != nullptr && ref->next != nullptr) {
                ref = ref->next;
                return *this;
            }
            else {
                ref = nullptr;
                return *this;
            }
        }
        T& operator*() {
            return ref->data;
        }
        T* operator->() {
            return &ref->data;
        }
        bool operator==(const Iterator &rhs) {
            return rhs.ref == ref;
        }
        bool operator!=(const Iterator &rhs) {
            return rhs.ref != ref;
        }
    private:
        Node<T> *ref;
    };

    List() {
        front = new Node<T>(nullptr, back);
        back = new Node<T>(front, nullptr);
    }
    ~List() {
        while (front != nullptr) {
            Node<T> *temp = front;
            front = front->next;
            delete temp;
        }
        front = back = nullptr;
    }
    List(const List &other) {
        // initialize front and back of this list
        front = new Node<T>(nullptr, back);
        back = new Node<T>(front, nullptr);

        // walk the other list from front to back
        // inserting the each element at the back
        // will create a new list with the same
        // elements in the same order
        Node<T> *temp = other.front->next;
        while (temp != nullptr) {
            insertBack(temp->data);
            temp = temp->next;
        }
    
    }

    Iterator begin() {
        return Iterator(front->next);
    }

    Iterator end() {
        return Iterator(back);
    }

    void swap(List &other) {
        if (this == &other) return;
        Node<T> *tempFront = front;
        Node<T> *tempBack = back;

        front = other.front;
        other.front = tempFront;

        back = other.back;
        other.back = tempBack;
    }

    List<T>& operator=(List rhs) {
        swap(rhs);
        return *this;
    }

    void insertFront(T data) {
        // assuming the list looks like this:
        // nullptr <- front <-> node1 <-> back -> nullptr
        // we want it to look like this
        // nullptr <- front <-> newNode <-> node1 <-> back -> nullptr
        // therefore, newNode->next is the old front->next
        // node1->prev is newNode
        // newNode->prev is front
        // and front->next becomes newNode
        Node<T> *newNode = new Node<T>(data, front, front->next);
        front->next->prev = newNode;
        front->next = newNode;
    }

    void insertBack(T data) {
        // assuming the list looks like this:
        // nullptr <- front <-> node1 <-> back -> nullptr
        // we want it to look like this
        // nullptr <- front <-> node1 <-> newNode <-> back -> nullptr
        // therefore, newNode->next is back
        // node1->next is newNode
        // newNode->prev is node1, which is back->prev
        // and back->prev becomes newNode
        Node<T> *newNode = new Node<T>(data, back->prev, back);
        back->prev->next = newNode;
        back->prev = newNode;
    }

    Iterator find(T data) const {
        if (front == nullptr) {
            return end();
        }
        Node<T> *temp = front->next;
        while (temp != nullptr) {
            if (temp->data == data) {
                return Iterator(temp);
            }
        }
        return end();
    }

    void remove(Iterator pos) {
        // we need to find the node this iterator points to
        Node<T> node = front;
        // since we don't want to expose the nodes in the Iterator class
        // we need to convert node to an iterator and compare with the 
        // parameter to this function
        while (Iterator(node) != pos && node != back) {
            node = node->next;
        }
        // if we didn't find the iterator, there is nothing to do
        if (node == back) return;
        // if we do find it, call the private remove with the node
        else remove(node);
    }
private:
    void remove(Node<T> node) {
        // say we have this list
        // nullptr<-front<->node1<->node2<->node3<->back->nullptr
        // we want to remove node2
        // the list becomes
        // nullptr<-front<->node1<->node3<->back->nullptr
        // this means:
        // - node1->next needs to be node3
        //  - node1 is node2->prev
        //  - node3 is node2->next
        //  - so, node2->prev->next = node2->next
        // - node3->prev needs to be node1
        //  - so, node2->next->prev = node2->prev
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }
    Node<T> *front;
    Node<T> *back;
};

#endif
