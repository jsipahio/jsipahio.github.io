#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>, size_t BUCKETS>
class Map {
public:
private:
    size_t buckets;
    size_t currentSize;
    List<std::pair<Key,Value>> *hashTable;
    Hash hash;
};

#endif