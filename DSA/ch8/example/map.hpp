#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <vector>
#include "../../ch7/example/list.hpp"

/**
 * Map
 * 
 * A container for storing (key, value) pairs with random access.
 * @param Key - the data type of the keys (unique identifiers)
 * @param Value - the data type of the values associated with the keys
 * @param BUCKETS - the number of hash table buckets to use
 * @param Hash - the type of the hash functor
 */
template <typename Key, typename Value, size_t BUCKETS = 127, typename Hash = std::hash<Key>>
class Map {
public:
    /**
     * Map
     * 
     * Default constructor
     * 
     * Assigns default parameter values to fields.
     */
    Map(): buckets(BUCKETS), hash{}, currentSize(0), hashTable(new List<std::pair<Key,Value>>[buckets]) {}

    /**
     * ~Map
     * 
     * Destructor
     * 
     * Deletes the hash table (dynamic array of lists)
     */
    ~Map() {
        // delete will call the List destructor
        delete[] hashTable;
    }

    /**
     * Map(const Map&)
     * 
     * Copy constructor
     * 
     * Deep copies a map object to the new object
     * 
     * @param other - Map to be copied from
     */
    Map(const Map& other): buckets(other.buckets), hash(other.hash), currentSize(other.currentSize) {
        // allocate and initialize hash table as array of lists
        hashTable = new List<std::pair<Key, Value>>[buckets];

        // iterate through the hash tables and copy each list
        for (size_t i = 0; i < buckets; ++i) {
            hashTable[i] = other.hashTable[i];
        }
    }

    /**
     * operator=(Map)
     * 
     * Copy assignment operator
     * 
     * Deep copies parameter into l-value
     * 
     * @param rhs - the Map being assigned from
     */
    Map& operator=(Map rhs) {
        // uses C++ copy-swap idiom
        swap(rhs);
        return *this;
    }

    /**
     * swap(Map&)
     * 
     * Constant time swap of two maps
     * 
     * Swaps pointers of calling Map and parameter
     * 
     * @param other - the map being swapped
     */
    void swap(Map& other) {
        Hash tempHash = hash;
        size_t tempBuckets = buckets;
        size_t tempSize = currentSize;
        List<std::pair<Key, Value>> *tempTable = hashTable;

        hashTable = other.hashTable;
        hash = other.hash;
        currentSize = other.currentSize;
        buckets = other.buckets;

        other.hashTable = tempTable;
        other.hash = tempHash;
        other.currentSize = tempSize;
        other.buckets = buckets;
    }

    // members

    /**
     * insert(const Key&, const Value&)
     * 
     * Inserts a key non-destructively
     * 
     * @param key - the Key to insert
     * @param value - the Value to associate with that key
     * 
     * @returns true - the (key, value) pair is inserted
     * @returns false - the (key, value) pair is not inserted (the key is already in use) 
     */
    bool insert(const Key& key, const Value& value) {
        // hash the key
        auto hashValue = hash(key) % buckets;

        // check if the key is already used
        if (findKey(hashTable[hashValue], key) != hashTable[hashValue].end()) {
            return false;
        }

        // insert the new key, value pair to the correct chain
        hashTable[hashValue].insertBack(std::make_pair(key, value));
        ++currentSize;

        return true;
    }
    /**
     * insert(const std::pair<Key, Value>&)
     * 
     * Inserts a key non-destructively
     * 
     * @param kvPair - the (key, value) pair to insert
     * 
     * @returns true - the (key, value) pair is inserted
     * @returns false - the (key, value) pair is not inserted (the key is already in use) 
     */
    bool insert(const std::pair<Key, Value>& kvPair) {
        // hash the key
        auto hashValue = hash(kvPair.first) % buckets;

        // check if the key is already present
        if (findKey(hashTable[hashValue], kvPair.first) != hashTable[hashValue].end()) {
            return false;
        }

        // insert the key, value pair
        hashTable[hashValue].insertBack(kvPair);
        ++currentSize;

        return true;
    }

    /**
     * remove(const Key&)
     * 
     * Removes a key (and its associated value) from the map
     * 
     * @param key - the Key to remove
     * 
     * @returns true - the key was found and removed
     * @returns false - the key was not found and no removal occured
     */
    bool remove(const Key& key) {
        // hash the key
        auto hashValue = hash(key) % buckets;

        // if the chain is empty for that hash, immediately we know there is no key
        if (hashTable[hashValue].empty()) return false;

        // find the key
        auto it = findKey(hashTable[hashValue], key);

        // if the key is found, remove it and return true
        if (it != hashTable[hashValue].end()) {
            hashTable[hashValue].remove(it);
            --currentSize;
            return true;
        }
        // otherwise, return false
        return false;
    }

    /**
     * contains(const Key&)
     * 
     * Checks if the map contains a key
     * 
     * @param key - the Key to search for
     * 
     * @returns true - the key is present
     * @returns false - the key is not present
     */
    bool contains(const Key& key) const {
        // hash the key
        auto hashValue = hash(key) % buckets;

        // if the chain is empty, we know the key is not present
        if (hashTable[hashValue].empty()) return false;

        // try to find the key in the list
        auto it = findKey(hashTable[hashValue], key);
        // if found, return true
        if (it != hashTable[hashValue].end()) {
            return true;
        }
        // otherwise, return false
        return false;
    }
    
    /**
     * at(const Key&) const
     * 
     * Returns a constant reference to the value at Key
     * 
     * @param key - the Key to search for
     * 
     * @return const Value& - the Value associated with that key
     * 
     * On error (key is not present) it forcibly ends the program
     */
    const Value& at(const Key& key) const {
        // check if the key is present
        if (!contains(key)) {
            std::cerr << "Cannot find requested key\n";
            exit(1);
        }

        // hash the key
        auto hashValue = hash(key) % buckets;
        // find the key and return
        return findKey(hashTable[hashValue], key)->second;
    }

    /**
     * at(const Key&)
     * 
     * Returns a mutable reference to the value at Key
     * 
     * @param key - the Key to search for
     * 
     * @return Value& - the Value associated with that key
     * 
     * On error (key is not present) it forcibly ends the program
     */
    Value& at(const Key& key) {
        // check if the key is present
        if (!contains(key)) {
            std::cerr << "Cannot find requested key\n";
            exit(1);
        }

        // hash the key
        auto hashValue = hash(key) % buckets;
        // find the key and return
        return findKey(hashTable[hashValue], key)->second;
    }

    // operators

    /**
     * operator==(const Map&) const
     * 
     * Equvilence operator
     * 
     * Checks if the two maps contain identical elements and hashes
     * 
     * @param rhs - the Map being compared with
     * 
     * @returns true - the Maps are the same
     * @returns false - the Maps are different
     */
    bool operator==(const Map& rhs) const {
        // return false if the maps differ in size or buckets
        if (rhs.size() != size()) return false;
        if (rhs.buckets != buckets) return false;

        // compare each list
        for (size_t i = 0; i < buckets; ++i) {
            if (hashTable[i] != rhs.hashTable[i]) return false;
        }

        // if we haven't returned false yet, they must be the same
        return true;
    }

    /**
     * operator[](const Key&) const
     * 
     * Overloaded subscript operator
     * 
     * Returns a constant reference to the value associated with a key
     * 
     * @param key - the Key to search for
     * 
     * @returns const Value& - a reference to the value associated with that key
     * 
     * If the key is not present, this function will abort the program
     */
    const Value& operator[](const Key& key) const {
        return at(key);
    }

    /**
     * operator[](const Key&)
     * 
     * Overloaded subscript operator
     * 
     * Returns a mutable reference to the value associated with a key
     * If the key is not present, it adds that key to the Map.
     * 
     * @param key - the Key to search for
     * 
     * @returns Value& - mutable reference to key's associated value
     */
    Value& operator[](const Key& key) {
        // if the key is present, return it's value
        if (contains(key)) return at(key);
        // otherwise, insert it and return the value
        else {
            insert(std::make_pair(key, Value{}));
            return at(key);
        }
    }

    // accessors
    /**
     * numBuckets() const
     * 
     * Returns the number of buckets the Map is using
     */
    size_t numBuckets() const { return buckets; }

    /**
     * size() const
     * 
     * Returns the number of elements the Map is storing
     */
    size_t size() const { return currentSize; }

    /**
     * empty() const
     * 
     * Returns true if the map has 0 elements, false otherwise
     */
    bool empty() const { return currentSize == 0; }

    /**
     * keys() const
     * 
     * Returns vector of keys in the map
     */
    std::vector<Key> keys() const {
        // preallocate memory for vector
        std::vector<Key> keyVec;
        keyVec.reserve(currentSize);

        for (size_t i = 0; i < buckets; ++i) {
            if (!hashTable[i].empty()) {
                for (const auto& pair: hashTable[i]) {
                    keyVec.push_back(pair.first);
                }
            }
        }

        return keyVec;
    }

    /**
     * pairs() const
     * 
     * Returns vector of pairs in the map
     */
    std::vector<std::pair<Key, Value>> pairs() const {
        // preallocate memory for vector
        std::vector<std::pair<Key, Value>> pairVec;
        pairVec.reserve(currentSize);

        for (size_t i = 0; i < buckets; ++i) {
            if (!hashTable[i].empty()) {
                for (const auto& pair: hashTable[i]) {
                    pairVec.push_back(pair);
                }
            }
        }

        return pairVec;
    }
private:
    // helper to find key
    static List<std::pair<Key, Value>>::Iterator findKey(const List<std::pair<Key, Value>>& list, const Key& key) {
        auto it = list.begin();
        // check every element in the list
        while (it != list.end()) {
            // if the first of "it" is equal to the target, return "it"
            if (it->first == key) return it;
            else ++it;
        }
        // if key is not found, "it" will be list.end()
        return it;
    }

    // the number of buckets
    size_t buckets;
    // the number of elements being stored
    size_t currentSize;
    // dynamic array of Lists (hash table using chaining)
    List<std::pair<Key,Value>> *hashTable;
    // hash functor
    Hash hash;
};

#endif
