
## List (and Forward List)
The STL List class is used to create a linked list. Similar to an array/vector, lists store a collection of elements while preserving their order. Linked lists are different from arrays/vectors in that the elements can no longer be accessed by an index and are not stored contiguously in memory. This can be an advantage or disadvantage depending on the usage. Below is a table that compares lists and vectors.
| Scenario | Array | Vector | List |
| -------- | ----- | ------ | ---- |
| Insertion at End | Impossible | May be instant, unless vector must be resized | Fast |
| Insertion at Middle | Impossible | Requires shifting all elements that follow the insertion point, Slow | Fast |
| Insertion at Front | Impossible | Requires shifting all elements, Slow | Fast |
| Deletion | Impossible | Requires shifting of elements, Slow | Fast, and preserves iterators |
| Random Access (index) | Fast | Fast | Impossible |
| Space | Must be known at compile time - empty indices are wasted space | Does not need to be known at compile time, but resizing is expensive and can result in massive amounts of wasted space | Does not need to be known at compile time, and there is never wasted space | 

### Unique Operations
`std::list` provides `push_front()` to add elements to the front of the list, and `push_back()` to add elements to the end of the list. Similarly, it offers `pop_front()` and `pop_back()` to remove elements from the front and end of the list, respectively. The `std::forward_list` class only supports `push_front()` and `pop_front()`.  
Lists provide a few unique member functions for common list operations. First is `splice()`, which expects an iterator and 
