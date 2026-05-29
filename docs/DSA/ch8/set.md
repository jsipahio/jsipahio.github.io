# Sets

A set is a container that stores unique values where order is not important (note: C++'s standard library sets do not follow this rule). The goal of a set is to provide O(1) insertion, deletion, and find operations. Additionally, sets implement between-set operations like union, intersection, set difference, and symmetric difference. Before looking at sets, we need to discuss the internal data structure we will use to implement sets: hash tables.

## Hash Table
A hash is a mathematical algorithm that converts a data into a (sufficiently) unique, numeric output. A hash table is a table that uses hashes to key its values. 

### Chaining

### Open Addressing

## Set Data
A set stores a collection of unique values without maintaining any ordering on the elements. In theory, we could use an array if we can compute a unique index for each item we enter into the set. However, this means that the underlying array may be very large and sparse. It would need to be large to hold all the possible elements that could be entered into the set. It would likely end up being sparse, since if the overall array size is very large, and the set only contains a few elements, there would be many wasted indices. Consider this example of a set using an array to store data. Let's say the set stores integers, and an integer is transformed to a key by subtracting one from it. If the first element added to the set is 1,000,000, that means we need to reserve 1,000,000 spaces for the array to store an element in the array:
```
Index: 0 1 2 ... 999998  999999
Value: 0 0 0 ...      0 1000000 
```
Now, let's say the only other values we enter are 1 and 2:
```
Index: 0 1 2 ... 999998  999999
Value: 1 2 0 ...      0 1000000 
```
We have allocated 1,000,000 integers to store 3 values, wasting 999,997 integers worth of memory. Assuming these are 4-byte integers, that would be 3999988 bytes, or approximately 4 megabytes that is reserved, but not holding any data.  
This is why we use a hash table for the implementation of a set. While it may slow down certain operations due to chaining or probing when there are collisions, there is far less wasted memory.

## Set Operations
Like other containers, sets need to support insertion and removal. Insertion to a set entails checking if the element is already in the set, and only inserting it if the element is not already present. Removing an element from a set requires checking that the element is present before attempting to remove it. Sets also implement a find operation to check if an element is present in the set. When we discuss set applications later in this section, we'll note that sets are often used to quickly check if some data item is present in a collection.  
Beyond the typical container operations, sets also implement several operations unique to sets. Let's consider these two sets:

First, we'll discuss unions. A set union is a new set that contains all the elements present in two sets.  
Next, we'll discuss intersections. A set intersection is a set that contains only the elements shared by the two sets being intersected.  
Now, we'll discuss the set difference. If we have sets A and B, A &setminus; B contains all the elements in A that are not in B. B &setminus; A returns a set with all the elements in B that are not in A.
Finally, we'll discuss the symmetric difference of two sets. The symmetric difference are the elements that are in A or B, but not both. The symmetric difference is the union of A &setminus; B with B &setminus; A.

## Set Implementation

## Applications of Sets


