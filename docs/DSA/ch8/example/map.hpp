#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "../ch7/example/list.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>, size_t BUCKETS = 127>
class Map {
public:
    Map(): buckets(BUCKETS), hash{}, currentSize(0), hashTable(new List<std::pair<Key,Value>>[buckets]) {}

    ~Map() {
        delete[] hashTable;
    }

    Map(const Map& other): buckets(other.buckets), hash(other.hash), currentSize(other.currentSize) {
        hashTable = new List<std::pair<Key, Value>>[buckets];

        for (size_t i = 0; i < buckets; ++i) {
            hashTable[i] = other.hashTable[i];
        }
    }

    Map& operator=(Map rhs) {
        swap(rhs);
        return *this;
    }

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
    bool insert(const Key& key, const Value& value) {
        auto hashValue = hash(key);
        hashTable[hashValue].insertBack(std::make_pair(key, value));
        ++currentSize;
    }

    bool insert(const std::pair<Key, Value>& kvPair) {
        auto hashValue = hash(kvPair.first);
        hashTable[hashValue].insertBack(kvPair);
        ++currentSize;
    }

    bool remove(const Key& key) {
        auto hashValue = hash(key);
        if (hashTable[hashValue].empty()) return false;

        auto it = hashTable[hashValue].find(key);
        if (it != hashTable[hashValue].end()) {
            hashTable[hashValue].remove(it);
            return true;
        }
        else {
            return false;
        }
    }

    bool contains(const Key& key) {
        auto hashValue = hash(key);
        if (hashTable[hashValue].empty()) return false;

        auto it = hashTable[hashValue].find(key);
        if (it != hashTable[hashValue].end()) {
            return true;
        }
        else {
            return false;
        }
    }
    
    const Value& at(const Key& key) const {
        if (!contains(key)) {
            std::cerr << "Cannot find requested key\n";
            exit(1);
        }

        auto hashValue = hash(key);
        return hashTable[hashValue].find(key)->second;
    }

    Value& at(const Key& key) {
        if (!contains(key)) {
            std::cerr << "Cannot find requested key\n";
            exit(1);
        }

        auto hashValue = hash(key);
        return hashTable[hashValue].find(key)->second;
    }

    // operators
    bool operator==(const Map& rhs) {
        if (rhs.size() != size()) return false;
        if (rhs.buckets != buckets) return false;

        for (size_t i = 0; i < buckets; ++i) {
            if (hashTable[i] != rhs.hashTable[i]) return false;
        }

        return true;
    }

    const Value& operator[](const Key& key) const {
        return at(key);
    }

    Value& operator[](const Key& key) {
        if (contains(key)) return at(key);
        else {
            insert(std::make_pair(key, Value{}));
            return at(key);
        }
    }

    // accessors
    size_t numBuckets() const { return buckets; }
    size_t size() const { return currentSize; }
    size_t empty() const { return currentSize == 0; }
private:
    size_t buckets;
    size_t currentSize;
    List<std::pair<Key,Value>> *hashTable;
    Hash hash;
};

#endif