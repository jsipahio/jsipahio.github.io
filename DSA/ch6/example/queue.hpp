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

template <typename T>
class Queue {
public:
    Queue() :
        maxSize(DEFAULT_MAX_QUEUE),
        foq(0),
        back(0),
        data(new T[DEFAULT_MAX_QUEUE])
    {}

    Queue(size_t max) :
        maxSize(max),
        foq(0),
        back(0),
        data(new T[max])
    {}

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
    ~Queue() {
        delete[] data;
        foq = 0;
        back = 0;
        maxSize = 0;
    }
    Queue& operator=(Queue rhs) {
        swap(rhs);
        return *this;
    }

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
    T& front() const {
        // check if queue is empty
        if (empty()) {

        }
        return data[foq];
    }
    void dequeue() {
        if (empty()) {
            throw EmptyQueueException();
        }
        foq = (foq + 1) % maxSize;
    }

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
    size_t capacity() const {
        return maxSize;
    }
    bool empty() const {
        return foq == back;
    }
    bool full() const {
        return (back + 1) % maxSize == foq;
    }
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
    void swap(Queue& other) {
        size_t tempFoq = foq;
        size_t tempBack = back;
        size_t tempMax = maxSize;
        T *tempData = data;

        foq = other.foq;
        other.foq = tempFoq;

        back = other.back;
        other.back = tempBack;

        maxSize = other.maxSize;
        other.maxSize = tempMax;

        data = other.data;
        other.data = tempData;
    }

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