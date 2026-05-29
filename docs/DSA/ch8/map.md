# Maps

A map is, at a high level, an associative array. Rather than needing to use integral numbers to index the array, we can use any type of value as the "keys" to the array to access the value at that key. From a lower level, maps are like sets where the data being stored is important. You'll recall that in a set, we defined the `contains()` member to check if the data is present. We didn't need a function to return any data, since the key and value are the same thing in a set. For map, we use the keys to look up a value. So, accessing a value in a map is a two-step process: first we we need to find the key in the hash table, then find the data stored by that key. Rather than storing a single element `T` as we did in sets, each element in a map is a pair: `Key, Value`. 

## Data
Maps, like sets, are best implemented using a hash table. 
