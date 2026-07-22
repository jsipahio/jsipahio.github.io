# Linked List ADT

Linked lists are an alternative container to arrays. While arrays allow random access to any of their elements via a subscript, the size of an array must be known when it is created. This can lead to wasted space by making the array to large, insufficient space if the original size is too small, or expensive copies when the array needs to be resized to accommodate more elements. Lists, on the other hand, only allocate as much space as is needed to store the current amount of elements it holds. While conceptual diagrams of lists often show them as sequential, remember that the elements of a list can appear in any location in memory. In this lecture, we'll mention iterators. Iterators are an abstraction that allow us to traverse a container. Iterators are covered in detail in the next lecture. 

## Data
A linked list consists of nodes that reference each other. There are two types of linked list, singly linked and doubly linked. A singly linked list only keeps track of the next element in the list. A doubly-linked list keeps track of both the previous and next node.  
The actual data of a linked list is the root node(s). For a singly linked list, there is one root, which is the first element of the list. While not needed, doubly-linked lists typically track the front and back of the list. This allows for searches for the last occurrence of an element to start from the back instead of the front. 

## Operations
We'll look at the operations for a doubly-linked list, since the singly-linked list is a subset of doubly-linked list operations. Doubly-linked lists support the ability to insert elements at the front and end of the list. They also allow for elements to be inserted in the middle of the list. This typically requires a pointer to where the element should be inserted, which is why iterators are commonly implemented for lists. Lists are also searched for if they contain an element. Doubly-linked lists support the ability to search from the front to find the instance of an element, or the back to find the last instance. Lists do not provide random access, so iterators are also needed to start searching from a certain point in the list. 

## Rules
The only limit on the size of a list is the amount of memory the computer has available to store it. Accessing or removing data from an empty list is not allowed. An empty doubly-linked list has the property that the `front == end` since they are both null. 

## Efficiency
Insertion and removal from the front and back of a doubly linked list is O(1). It only consists of creating a new node and assigning a few pointers. None of those operations are dependent on the number of nodes in the list. Insertion and removal from the front is a significant improvement over vectors and arrays, since they require shifting all elements to compensate, an O(n) operations.  
  
Finding an element is O(n), since in the worst case every node must be checked to see if it has the value being searched for. Insertion at the middle of a list is technically O(1), since it is still shifting pointers around, but is practically O(n) since the location to insert the element must be found first. 

## Implementing Stack Using a Singly Linked List
A singly-linked list with no search, find, or remove operations is automatically a stack. Elements are always added to and removed from the back of the list, since the root pointer always referencing the most recently inserted element. 
```c++
template <typename T>
struct Node {
    Node<T> *next;
    T data;
    Node(Node<T> *n = nullptr): next(n) {}
    Node(T d, Node<T> *n = nullptr): data(d), next(n) {}
};

template <typename T>
class Stack {
public:
    Stack(): tos(nullptr) {}
    Stack(const Stack<T> &other) {
        Stack<T> temp;
        // since we only have a reference to the top of stack,
        // we need to copy it (it will be in reverse order),
        // then copy it again
        Node<T> *tempNode = other.tos;
        while (tempNode != nullptr) {
            temp.push(tempNode->data);
            tempNode = tempNode->next;
        }

        // copy temp's elements into the actual stack
        while (temp.tos != nullptr) {
            push(temp.top());
            temp.pop();
        }
    }
    ~Stack() {
        while (tos != nullptr) {
            pop();
        }
    }
    Stack& operator=(Stack rhs) {
        swap(rhs);
        return *this;
    }
    void swap(Stack& other) {
        Node<T> *temp = tos;
        tos = other.tos;
        other.tos = temp;
    }
    void push(const T& data) {
        if (tos == nullptr) {
            tos = new Node<T>;
        }
        Node<T> newNode = new Node<T>(data);
        newNode->next = tos->next;
        tos->next = newNode;
    }
    T top() const {
        if (tos == nullptr) {
            std::cerr << "Stack is empty\n";
            exit(1);
        }
        return tos->next->data;
    }
    void pop() {
        if (tos == nullptr) {
            std::cerr << "Stack is empty\n";
            exit(1);
        }
        Node<T> *temp = tos->next;
        tos->next = tos->next->next;
        delete temp;
    }
    bool empty() const { return tos == nullptr; }
private:
    // tos = top of stack
    Node<T> *tos;
};
```

## Implementing Queue Using a Singly Linked List
```C++
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
```
