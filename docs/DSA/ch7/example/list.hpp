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
        bool operator==(const Iterator &rhs) const {
            return rhs.ref == ref;
        }
        bool operator!=(const Iterator &rhs) const {
            return rhs.ref != ref;
        }
    private:
        Node<T> *ref;
    };

    List() {
        front = new Node<T>;
        back = new Node<T>(front, nullptr);
        front->next = back;
        currentSize = 0;
    }

    ~List() {
        while (front != nullptr) {
            Node<T> *temp = front;
            front = front->next;
            delete temp;
        }
        front = back = nullptr;
        currentSize = 0;
    }

    List(const List &other) {
        // initialize front and back of this list
        front = new Node<T>;
        back = new Node<T>(front, nullptr);
        front->next = back;
        currentSize = 0;

        // walk the other list from front to back
        // inserting each element at the back
        // will create a new list with the same
        // elements in the same order
        Node<T> *temp = other.front->next;
        while (temp != other.back) {
            insertBack(temp->data);
            temp = temp->next;
        }
    }

    Iterator begin() const {
        if (currentSize == 0) return end();
        return Iterator(front->next);
    }

    Iterator end() const {
        return Iterator(back);
    }

    void swap(List &other) {
        if (this == &other) return;
        Node<T> *tempFront = front;
        Node<T> *tempBack = back;
        size_t tempSize = currentSize;

        front = other.front;
        other.front = tempFront;

        back = other.back;
        other.back = tempBack;

        currentSize = other.currentSize;
        other.currentSize = tempSize;
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
        ++currentSize;
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
        ++currentSize;
    }

    Iterator find(T data) const {
        if (front == nullptr) {
            return Iterator(back);
        }
        Node<T> *temp = front->next;
        while (temp != nullptr) {
            if (temp->data == data) {
                return Iterator(temp);
            }
            temp = temp->next;
        }
        return Iterator(back);
    }

    Iterator findLast(T data) const {
        if (back == nullptr) {
            return Iterator(back);
        }
        Node<T> *temp = back->prev;
        while (temp != nullptr) {
            if (temp->data == data) {
                return Iterator(temp);
            }
            temp = temp->prev;
        }
        return Iterator(back);
    }

    void remove(Iterator pos) {
        // we need to find the node this iterator points to
        Node<T> *node = front;
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

    bool operator==(const List& rhs) const {
        if (currentSize != rhs.currentSize) return false;

        auto thisIterator = begin();
        auto rhsIterator = rhs.begin();
        while (thisIterator != end()) {
            if (!(*thisIterator == *rhsIterator)) return false;
            ++thisIterator;
            ++rhsIterator;
        }
        return true;
    }

    size_t size() const { return currentSize; }

    bool empty() const { return currentSize == 0; }
private:
    void remove(Node<T> *node) {
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
        --currentSize;
    }
    Node<T> *front;
    Node<T> *back;
    size_t currentSize;
};

#endif
