#ifndef QUEUE_HPP
#define QUEUE_HPP 

#include <sys/types.h>

constexpr size_t DEFAULT_MAX_QUEUE = 256;

class FullQueueException {
public:
    FullQueueException() {}
    static const char* what() {
        return "Cannot add to full queue";
    }
};

class EmptyQueueException {
public:
    EmptyQueueException() {}
    static const char* what() {
        return "Cannot access front of empty queue";
    }
};

/**
 * @class Queue
 * 
 * An array based queue implementation
 * Uses dynamic array as underlying storage of the queue.
 * 
 * @invariant A new queue is always empty
 * @invariant An empty queue cannot have dequeue or front executed on it
 * @invariant A full queue cannot be pushed to
 */
template <typename T>
class Queue {
public:
    /**
     * Queue()
     * 
     * Default Constructor
     */
    Queue() :
        maxSize(DEFAULT_MAX_QUEUE),
        foq(0),
        back(0),
        data(new T[DEFAULT_MAX_QUEUE])
    {}

    /**
     * Queue(size_t)
     * 
     * Constructor
     * Creates queue with max size of `max`
     * 
     * @param max - the maximum number of elements the queue can store
     */
    Queue(size_t max) :
        maxSize(max),
        foq(0),
        back(0),
        data(new T[max])
    {}

    /**
     * Queue(const Queue&)
     * 
     * Copy constructor
     * Performs deep copy
     * 
     * @param other - Queue being copied
     */
    Queue(const Queue& other) :
        maxSize(other.maxSize),
        foq(other.foq),
        back(other.back),
        data(new T[other.maxSize])
    {
        for (size_t i = 0; i < maxSize; ++i) {
            data[i] = other.data[i];
        }
    }

    /**
     * ~Queue
     * 
     * Destructor
     */
    ~Queue() {
        delete[] data;
        foq = 0;
        back = 0;
        maxSize = 0;
    }

    /**
     * Queue& operator=
     * 
     * Overloaded assignment operator
     * Performs deep copy
     * 
     * @param rhs - Queue to copy
     * @returns reference to "this"
     */
    Queue& operator=(Queue rhs) {
        swap(rhs);
        return *this;
    }

    /**
     * void enqueue(const T&)
     * 
     * Adds element to the end of the queue
     * 
     * @invariant the Queue must not be full
     * @throw FullQueueException if the queue is full
     */
    void enqueue(const T& element) {
        // using modulus to handle wrapping of the queue
        // first, check if adding element will overfill queue
        if (full()) {
            throw FullQueueException();
        }
        // if not, insert element and move back
        data[back] = element;
        back = (back + 1) % maxSize;
    }

    /**
     * const T& front() cosnt
     * 
     * Returns reference to the least recently entered element of the queue
     * 
     * @invariant the Queue must not be empty
     * @throw EmptyQueueException if the queue is empty
     */
    const T& front() const {
        // check if queue is empty
        if (empty()) {
            throw EmptyQueueException();
        }
        // return the front of the queue
        return data[foq];
    }

    /**
     * void dequeue()
     * 
     * Removes the least-recently entered element from the queue
     * 
     * @invariant the Queue must not be empty
     * @throw EmptyQueueException if the queue is empty
     */
    void dequeue() {
        // check if the queue is empty
        if (empty()) {
            throw EmptyQueueException();
        }
        // compute the new front
        foq = (foq + 1) % maxSize;
    }

    /**
     * size_t size() const
     * 
     * Returns the current number of elements the queue stores
     * 
     * @returns current numbeer of elements in the queue
     */
    size_t size() const {
        // if foq is less than back, the elements
        // are all in order in the array and we
        // can just subtract them
        if (foq < back) {
            return back - foq + 1;
        }
        // otherwise, back has wrapped around to the front
        // to avoid including the math library, we just swap
        // the subtraction order
        else {
            return foq - back + 1;
        }
    }

    /**
     * size_t capacity() const
     * 
     * Returns the maximum number of elements the Queue can stores
     * 
     * @returns size of the queue's array
     */
    size_t capacity() const {
        return maxSize;
    }

    /**
     * bool empty() const
     * 
     * Checks if queue is empty
     * 
     * @returns true - the queue is empty
     * @returns false - the queue contains at least one element
     */
    bool empty() const {
        return foq == back;
    }
    
    /**
     * bool full() const
     * 
     * Checks if queue is full
     * 
     * @returns true - the queue is full (all indicees in use)
     * @returns false - the queue is not full
     */
    bool full() const {
        return (back + 1) % maxSize == foq;
    }

    /**
     * bool operator==(const Queue&)
     * 
     * Overloaded equality comparison operator
     * Compares if two queues contain equivilent elements in the same order
     * 
     * @param rhs - Queue to compare with
     * @returns true - Queues are the same
     * @returns false - Queues are not the same
     */
    bool operator==(const Queue& rhs) const {
        // this is a little tricky, since we are 
        // comparing elements pairwise. we need to first
        // check that the queues hold the same number 
        // of elements
        if (size() != rhs.size()) {
            return false;
        }
        // we need two indices to loop through the two arrays
        // even if the elements are not in the same physical position
        // in the two arrays, if they have the same logical order,
        // we say the queues are the same
        size_t i = foq;
        size_t j = rhs.foq;
        while (i != back) {
            if (data[i] != rhs.data[j]) return false;
            i = (i + 1) % maxSize;
            j = (j + 1) % rhs.maxSize;
        }
    }

    /**
     * void resize(size_t)
     * 
     * Resize the underlying array holding the queue
     * 
     * @param newSize - the new size to make the queue's array data
     */
    void resize(size_t newSize) {
        size_t i = foq;
        size_t j = 0;
        T *newData = new T[newSize];
        // i != back makes sure we do not copy more elements
        // than are in the current queue
        // j < newSize prevents us from overflowing the new array
        // if it is smaller than the old size
        while (i != back && j < newSize) {
            newData[j] = data[i];
            ++j;
            i = (i + 1) % maxSize;
        }
        foq = 0;
        back = j - 1;
        delete[] data;
        data = newData;
    }

    /**
     * void swap(Queue&)
     * 
     * Constant time swap of two queues
     * 
     * @param other - Queue to swap with
     */
    void swap(Queue& other) {
        // temp variables
        size_t tempFoq = foq;
        size_t tempBack = back;
        size_t tempMax = maxSize;
        T *tempData = data;

        // swap front pointers
        foq = other.foq;
        other.foq = tempFoq;

        // swap back pointers
        back = other.back;
        other.back = tempBack;
        
        // swap sizes
        maxSize = other.maxSize;
        other.maxSize = tempMax;

        // swap data pointers
        data = other.data;
        other.data = tempData;
    }

    /**
     * void print(std::ostream&)
     * 
     * Helper function to print out the contents of the queue
     * 
     * @param out - output stream to print the queue to
     */
    void print(std::ostream& out) {
        size_t i = foq;
        while (i != back) {
            out << data[i] << std::endl;
            i = (i + 1) % maxSize;
        }
    }
private:
    // "front of queue" - index of the front element
    size_t foq;
    // index after the back element
    size_t back;
    // maximum number of elements the array can hold
    size_t maxSize;
    // array to store the actual data elements
    T *data;
};

#endif 
