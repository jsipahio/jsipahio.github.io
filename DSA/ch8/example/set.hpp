#ifndef SET_HPP
#define SET_HPP
#include <functional>
#include <vector>
#include <iostream>
#include "../../ch7/example/list.hpp"

template <typename T, size_t BUCKETS=127, typename Hash = std::hash<T>>
class Set {
public:
    /**
     * Set()
     * 
     * Default constructor
     */
    Set() : buckets(BUCKETS), hashTable(new List<T>[BUCKETS]), hash(Hash()), currentSize(0) {}
    /**
     * ~Set()
     * 
     * Destructor
     */
    ~Set() { 
        // delete[] will call the List destructor on each list
        delete[] hashTable; 
    }
    /**
     * Set(const Set&)
     * 
     * Copy constructor
     * 
     * Performs a deep copy
     * 
     * @param other - the Set to copy
     */
    Set(const Set& other);
    /**
     * operator=(Set)
     * 
     * Overloaded copy assignment operator
     * 
     * Performs a deep copy
     * 
     * @param rhs - the Set to copy
     */
    Set& operator=(Set rhs);
    /**
     * swap(Set&)
     * 
     * Constant time swap function
     * 
     * @param other - the Set to swap with
     */
    void swap(Set& other);

    // container methods

    /**
     * insert(const T& key)
     * 
     * Inserts a key into the set
     * 
     * @param key - the key to insert
     * 
     * @returns true - the key was inserted
     * @returns false - the key was present, and not inserted
     */
    bool insert(const T& key);

    /**
     * Remove(const T& key)
     * 
     * Removes a key from the set
     * 
     * @param key - the key to remove
     * 
     * @returns true - the key was remove
     * @returns false - the key was not present, and not removed
     */
    bool remove(const T& key);

    /**
     * Contains(const T& key)
     * 
     * Checks if the set contains a key
     * 
     * @param key - the key to check
     * 
     * @returns true - the key is present
     * @returns false - the key is not present
     */
    bool contains(const T& key) const;

    // accessors

    /**
     * size() const
     * 
     * Returns the number of elements in the set
     */
    size_t size() const { return currentSize; }

    /**
     * empty() const
     * 
     * Returns true if the size of the set is 0, false otherwise
     */
    bool empty() const { return currentSize == 0; }
    
    /**
     * operator==(const Set&) const
     * 
     * Returns true if the two sets are the same
     * 
     * @param rhs - the Set being compared to 
     */
    bool operator==(const Set& rhs) const;

    /**
     * keys() const
     * 
     * Returns a vector containing all the keys in the set
     */
    std::vector<T> keys() const;

    // member implementations of set operations

    /**
     * unionWith(const Set&) const
     * 
     * Returns a new set that is the union of "this" Set with "other"
     * 
     * @param other - the set to be unioned with
     */
    Set unionWith(const Set&) const;

    /**
     * intersectWith(const Set&) const
     * 
     * Returns a new set that is the intersection of "this" Set with "other"
     * 
     * @param other - the set to be intersected with
     */
    Set intersectWith(const Set&) const;

    /**
     * differenceWith(const Set&) const
     * 
     * Returns a new set that is the difference of "this" Set with "other"
     * 
     * @param other - the set to be differenced with
     */
    Set differenceWith(const Set&) const;

    /**
     * symmetricDifferenceWith(const Set&) const
     * 
     * Returns a new set that is the symmetric difference of "this" Set with "other"
     * 
     * @param other - the set to be symmetric differenced with
     */
    Set symmetricDifferenceWith(const Set&) const;

    // operator implementations of set operations
    
    /**
     * operator|(const Set) const
     * 
     * Union operator
     * 
     * Unions "this" with "rhs", returns new set with result
     * 
     * @param rhs - the set to be unioned with
     */
    Set operator|(const Set&) const;
    
    /**
     * operator&(const Set) const
     * 
     * Intersection operator
     * 
     * Intersects "this" with "rhs", returns new set with result
     * 
     * @param rhs - the set to be intersected with
     */
    Set operator&(const Set&) const;
    
    /**
     * operator-(const Set) const
     * 
     * Difference operator
     * 
     * Differences "this" with "rhs", returns new set with result
     * 
     * @param rhs - the set to be differenced with
     */
    Set operator-(const Set&) const;
    
    /**
     * operator^(const Set) const
     * 
     * Symmetric Diference operator
     * 
     * Symmetric differences "this" with "rhs", returns new set with result
     * 
     * @param rhs - the set to be symmetric differenced with with
     */
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

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash>::Set(const Set& other): hash{}, currentSize(0) {
    // copy properities and allocate hash table
    buckets = other.buckets;
    hashTable = new List<T>[buckets];

    // copy elements
    for (const auto& key: other.keys()) {
        insert(key);
    }
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash>& Set<T, BUCKETS, Hash>::operator=(Set rhs) {
    // C++ copy-swap idiom
    swap(rhs);
    return *this;
}

template <typename T, size_t BUCKETS, typename Hash>
void Set<T, BUCKETS, Hash>::swap(Set &other) {
    // temps
    size_t tempBuckets = buckets;
    size_t tempSize = currentSize;
    List<T>* tempTable = hashTable;

    // swap buckets
    buckets = other.buckets;
    other.buckets = tempBuckets;

    // swap sizes
    currentSize = other.currentSize;
    other.currentSize = tempSize;

    // swap hash table pointers
    hashTable = other.hashTable;
    other.hashTable = tempTable;

    // swapping hashes is not needed, since it is a functor
    // provided by the template parameter
    // if they were different, this function would not work in the first place
}


template <typename T, size_t BUCKETS, typename Hash>
bool Set<T, BUCKETS, Hash>::insert(const T& data) {
    // hash the key
    size_t hashValue = hash(data);
    size_t index = hashValue % buckets;

    // if the chain is empty, just insert it
    if (hashTable[index].empty()) {
        hashTable[index].insertFront(data);
        ++currentSize;
        return true;
    }
    
    // if the key is not in the set, insert it into the correct chain
    if (hashTable[index].find(data) == hashTable[index].end()) {
        hashTable[index].insertBack(data);
        ++currentSize;
        // if the size grows too much, increase the buckets
        if (currentSize > 4 * buckets) resize();
        return true;
    }
    // otherwise, return false
    return false;
}

template <typename T, size_t BUCKETS, typename Hash>
bool Set<T, BUCKETS, Hash>::remove(const T& data) {
    // hash the key
    size_t hashValue = hash(data);
    size_t index = hashValue % buckets;

    // check if the key is present at that index
    auto it = hashTable[index].find(data);  
    // if we found the key, remove it and return true
    if (it != hashTable[index].end()) {
        hashTable[index].remove(it);
        --currentSize;
        return true;
    }
    // otherwise, return false
    return false;
}

template <typename T, size_t BUCKETS, typename Hash>
bool Set<T, BUCKETS, Hash>::contains(const T& data) const {
    // hash the key
    size_t hashValue = hash(data);
    size_t index = hashValue % buckets;
    
    // if we find the key at that index, return true
    if (hashTable[index].find(data) != hashTable[index].end()) {
        return true;
    }
    // otherwise, return false
    return false;

}

template <typename T, size_t BUCKETS, typename Hash>
bool Set<T, BUCKETS, Hash>::operator==(const Set &rhs) const {
    // if any of the non-data properties are different, it is not a valid
    // comparison so we return
    if (buckets != rhs.buckets || currentSize != rhs.currentSize)
        return false;

    // check every element for equality
    for (size_t i = 0; i < buckets; ++i) {
        // return false if any values are not equal
        if (!(hashTable[i] == rhs.hashTable[i])) return false; 
    }
    // return true if all elements are equal
    return true;
}

template <typename T, size_t BUCKETS, typename Hash>
std::vector<T> Set<T, BUCKETS, Hash>::keys() const {
    // create vector and preallocate correct size
    std::vector<T> keyVec;
    keyVec.reserve(currentSize);
    // iterate over hash table
    for (size_t i = 0; i < buckets; ++i) {
        if (!hashTable[i].empty()) {
            for (const auto& e: hashTable[i]) {
                keyVec.push_back(e);
            }
        }
    }
    return keyVec;
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::unionWith(const Set &rhs) const {
    // result set
    Set<T, BUCKETS, Hash> unionedSet;
    
    // insert every element from "this" into the result
    for (size_t i = 0; i < buckets; ++i) {
        if (!hashTable[i].empty()) {
            for (const auto& e: hashTable[i]) {
                unionedSet.insert(e);
            }
        }
    }
    // insert every element from rhs into the result
    for (size_t i = 0; i < rhs.buckets; ++i) {
        if (!rhs.hashTable[i].empty()) {
            for (const auto& e: rhs.hashTable[i]) {
                unionedSet.insert(e);
            }
        }
    }
    // insert() will take care of not inserting duplicates
    return unionedSet;
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::intersectWith(const Set &rhs) const {
    // result set
    Set<T, BUCKETS, Hash> intersectedSet;
    
    // iterate over the buckets
    for (size_t i = 0; i < buckets; ++i) {
        // check that the bucket is not empty
        if (!hashTable[i].empty()) {
            // iterate over the bucket
            for (const auto& e: hashTable[i]) {
                // only insert to the result if the element is in the other set
                if (rhs.contains(e)) intersectedSet.insert(e);
            }
        }
    }
    // we only have to check the one set, since items have to be in both
    // for an intersection
    return intersectedSet;
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::differenceWith(const Set &rhs) const {
    // result set
    Set<T, BUCKETS, Hash> differencedSet;
    
    // iterate over the buckets
    for (size_t i = 0; i < buckets; ++i) {
        // check that the bucket is not empty
        if (!hashTable[i].empty()) {
            // iterate through the bucket
            for (const auto& e: hashTable[i]) {
                // if not in the other set, insert it to the result
                if (!rhs.contains(e)) differencedSet.insert(e);
            }
        }
    }
    return differencedSet;
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::symmetricDifferenceWith(const Set &rhs) const {
    // the symmetric diffence of two sets can be thought of as either the union of
    // setA - setB and setB - setA, or the difference of setA union setB and setA intersect setB

    Set<T, BUCKETS, Hash> unionedSet = unionWith(rhs);
    Set<T, BUCKETS, Hash> intersectedSet = intersectWith(rhs);
    
    return unionedSet.differenceWith(intersectedSet);
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::operator|(const Set &rhs) const {
    return unionWith(rhs);
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::operator&(const Set &rhs) const {
    return intersectWith(rhs);
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::operator-(const Set &rhs) const {
    return differenceWith(rhs);
}

template <typename T, size_t BUCKETS, typename Hash>
Set<T, BUCKETS, Hash> Set<T, BUCKETS, Hash>::operator^(const Set &rhs) const {
    return symmetricDifferenceWith(rhs);
}

template <typename T, size_t BUCKETS, typename Hash>
void Set<T, BUCKETS, Hash>::resize() {
    // first, we need to save the old set
    // sets don't preserve order or have any structure beyond
    // the hash table, so we can just store every element in an
    // array for now
    T *tempData = new T[currentSize];
    size_t j = 0;
    // iterate over the buckets
    for (size_t i = 0; i < buckets; ++i) {
        // iterate over the elements in a bucket
        for (const auto& e: hashTable[i]) {
            tempData[j++] = e;
        }
    }
    // scale up the number of buckets
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