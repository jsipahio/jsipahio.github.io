# Maps

A map is, at a high level, an associative array. Maps are also called dictionaries in some programming languages. Rather than needing to use integral numbers to index the array, we can use any type of value as the "keys" to the array to access the value at that key. From a lower level, maps are like sets where the data being stored is important. You'll recall that in a set, we defined the `contains()` member to check if the data is present. We didn't need a function to return any data, since the key and value are the same thing in a set. For map, we use the keys to look up a value. So, accessing a value in a map is a two-step process: first we need to find the key in the hash table, then find the data stored by that key. Rather than storing a single element `T` as we did in sets, each element in a map is a pair: `Key, Value`. 

## Data
Maps, like sets, are best implemented using a hash table. The keys in a map are unique, so the only difference is the hash table must store a pair of values, and only use the key portion of the pair to compute the hash and find the correct location.

## Operations
The operations for a map largely mirror those of most containers: mechanisms to insert and delete elements, and to check if an element is present. These share time complexities with the set variants, since maps are using a hash table as well.  
  
A difference between sets and maps is that maps support random access via the subscript operator. Since maps are used to store values with their keys, we need a way to access these values. We can implement member functions to return the value at a key. But, many languages also allow access to map elements via array-like indexing. In C++, we can implement the subscript operator to use the   
  
The complexities for insertion and removal are the same as sets. The complexity for random access is the same as "contains" for a set, so we will skip the efficiency section for maps. 

## Implementation
An implementation of a generic Map class is provided with this week's examples in the `Map.hpp` file.

## Applications
Maps are used for a variety of tasks in programming. A lot of data formats, such as JSON, store data in a (key, value) format. Maps can also be used for counting, by making the object being counted a key and the value the number of occurrences of that object. Each time a new object is found, it is added to the map. A relational database can also be represented using a Map, if you have a way to convert the values to their true data types. 

## Example Application
This program will use the Map defined in `Map.hpp` to count the number of times a word appears in a text file.
```cpp
#include "map.hpp"
#include <fstream>
#include <iostream>
#include "string.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: Expected filepath via command line argument\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    if (fin.fail()) {
        std::cerr << "Error: Could not open file: " << argv[1] << "\n";
        return 2;
    }

    String input;
    Map<String, unsigned> wordCounts;
    while (fin >> input) {
        if (!wordCounts.contains(input)) {
            wordCounts[input] = 1;
        }
        else {
            ++wordCounts[input];
        }
    }

    fin.close();

    for (const auto& pair: wordCounts.pairs()) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    return 0;
}
```
