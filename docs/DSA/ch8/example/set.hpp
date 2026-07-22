#ifndef SET_HPP
#define SET_HPP
#include <functional>
#include "../../ch7/example/list.hpp"

template <typename T, typename Hash = std::hash<T>, size_t BUCKETS=127>
class Set {
public:
    Set() : buckets(BUCKETS), hashTable(new List<T>[BUCKETS]), hash(Hash()) {}
    ~Set() { delete[] hashTable; }
    Set(const Set&);
    Set& operator=(Set);
    void swap(Set&);

    // container methods
    bool insert(const T&);
    bool remove(const T&);
    bool contains(const T&) const;

    // accessors
    size_t size() const { return currentSize; }
    bool empty() const { return currentSize == 0; }
    bool operator==(const Set&) const;

    // member implementations of set operations
    Set unionWith(const Set&) const;
    Set intersectWith(const Set&) const;
    Set differenceWith(const Set&) const;
    Set symmetricDifferenceWith(const Set&) const;

    // operator implementations of set operations
    // union
    Set operator|(const Set&) const;
    // intersection
    Set operator&(const Set&) const;
    // difference
    Set operator-(const Set&) const;
    // symmetric difference
    Set operator^(const Set&) const;
private:
    // called if the number of elements
    // gets too high, creating too many collisions
    void resize();
    // current number of buckets (indexes for the hash table)
    size_t buckets;
    // current number of elements in the set
    size_t currentSize;
    // a dynamic array of lists
    List<T> *hashTable;
    // hash object
    Hash hash;
};

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS>::Set(const Set& other) {
    buckets = other.buckets;
    currentSize = other.currentSize;
    hashTable = new List<T>[buckets];

    for (size_t i = 0; i < currentSize; ++i) {
        hashTable[i] = other.hashTable[i];
    }
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS>& Set<T, Hash, BUCKETS>::operator=(Set rhs) {
    swap(rhs);
    return *this;
}

template <typename T, typename Hash, size_t BUCKETS>
void Set<T, Hash, BUCKETS>::swap(Set &other) {
    size_t tempBuckets = buckets;
    size_t tempSize = currentSize;
    size_t tempTable = hashTable;

    buckets = other.buckets;
    other.buckets = tempBuckets;

    currentSize = other.currentSize;
    other.currentSize = tempSize;

    hashTable = other.hashTable;
    other.hashTable = hashTable;
}


template <typename T, typename Hash, size_t BUCKETS>
bool Set<T, Hash, BUCKETS>::insert(const T& data) {
    size_t hashValue = hash(data);
    size_t index = hashValue % buckets;
    if (hashTable[index].find(data) != hashTable[index].end()) {
        hashTable[index].insertBack(data);
        ++currentSize;
        // if the size grows too much, increase the buckets
        if (currentSize > 4 * buckets) resize();
        return true;
    }
    else {
        return false;
    }
}

template <typename T, typename Hash, size_t BUCKETS>
bool Set<T, Hash, BUCKETS>::remove(const T& data) {
    size_t hashValue = hash(data);
    size_t index = hashValue % buckets;
    auto it = hashTable[index].find(data);  
    if (it != hashTable[index].end()) {
        hashTable[index].remove(it);
        return true;
    }
    else {
        return false;
    }
}

template <typename T, typename Hash, size_t BUCKETS>
bool Set<T, Hash, BUCKETS>::contains(const T& data) const {
    size_t hashValue = hash(data);
    size_t index = hashValue % buckets;
    if (hashTable[index].find(data) != hashTable[index].end()) {
        return true;
    }
    else {
        return false;
    }
}

template <typename T, typename Hash, size_t BUCKETS>
bool Set<T, Hash, BUCKETS>::operator==(const Set &rhs) const {
    if (
        buckets != rhs.buckets || 
        currentSize != rhs.currentSize ||
        hash != rhs.hash
    ) 
        return false;
    for (size_t i = 0; i < buckets; ++i) {
        if (!(hashTable[i] == rhs.hashTable[i])) return false; 
    }
    return true;
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::unionWith(const Set &rhs) const {
    Set<T, Hash, BUCKETS> unionedSet;
    for (size_t i = 0; i < buckets; ++i) {
        if (!hashTable[i].empty()) {
            for (const auto& e: hashTable[i]) {
                unionedSet.insert(e);
            }
        }
    }
    for (size_t i = 0; i < rhs.currentSize; ++i) {
        if (!rhs.hashTable[i].empty()) {
            for (const auto& e: rhs.hashTable[i]) {
                unionedSet.insert(e);
            }
        }
    }
    return unionedSet;
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::intersectWith(const Set &rhs) const {
    Set<T, Hash, BUCKETS> intersectedSet;
    for (size_t i = 0; i < buckets; ++i) {
        if (!hashTable[i].empty()) {
            for (const auto& e: hashTable[i]) {
                if (rhs.contains(e)) intersectedSet.insert(e);
            }
        }
    }
    // we only have to check the one set, since items have to be in both
    // for an intersection
    return intersectedSet;
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::differenceWith(const Set &rhs) const {
    Set<T, Hash, BUCKETS> differencedSet;
    for (size_t i = 0; i < buckets; ++i) {
        if (!hashTable[i].empty()) {
            for (const auto& e: hashTable[i]) {
                if (!rhs.contains(e)) differencedSet.insert(e);
            }
        }
    }
    return differencedSet;
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::symmetricDifferenceWith(const Set &rhs) const {
    Set<T, Hash, BUCKETS> unionedSet = unionWith(rhs);
    Set<T, Hash, BUCKETS> intersecedSet = intersectWith(rhs);
    
    return unionedSet.differenceWith(intersectedSet);
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::operator|(const Set &rhs) const {
    return unionWith(rhs);
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::operator&(const Set &rhs) const {
    return intersectWith(rhs);
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::operator-(const Set &rhs) const {
    return differenceWith(rhs);
}

template <typename T, typename Hash, size_t BUCKETS>
Set<T, Hash, BUCKETS> Set<T, Hash, BUCKETS>::operator^(const Set &rhs) const {
    return symmetricDifferenceWith(rhs);
}

template <typename T, typename Hash, size_t BUCKETS>
void Set<T, Hash, BUCKETS>::resize() {
    // first, we need to save the old set
    T *tempData = new T[currentSize];
    size_t j = 0;
    for (size_t i = 0; i < buckets; ++i) {
        for (const auto& e: hashTable[i]) {
            tempData[j++] = e;
        }
    }
    buckets *= 4;
    // we need to reset the currentSize so we can
    // insert the elements again
    currentSize = 0;
    for (size_t i = 0; i < j; ++i) {
        insert(tempData[i]);
    }
    delete[] tempData;
}

#endif