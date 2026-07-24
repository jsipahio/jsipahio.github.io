#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <algorithm>
#include "../../ch7/example/list.hpp"

template <typename T, typename Hash = std::hash<T>, size_t BUCKETS=127>
class HashTable {
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable&);
    HashTable<T, Hash, BUCKETS>& operator=(HashTable<T, Hash, BUCKETS>);

    bool insert(T& data);
    bool remove(T& data);
    bool exists(T& data) const;
private:
    List<T> *table;
};

#endif