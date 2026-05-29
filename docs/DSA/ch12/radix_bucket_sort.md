# Radix and Bucket Sort

The fastest generalizable sorting algorithms are O(nlog(n)), like quicksort and merge sort. However, it is possible to come up with faster algorithms for specific types of input. The key to creating a faster algorithm is to avoid comparisons. In this section, we discuss radix sort and bucket sort, which are non-comparative sorting algorithms.

## Radix Sort
Radix sort compares 

## Bucket Sort
Let's consider this list of numbers. For our example, we'll only consider a list of unique, positive integers. 
```
13, 2, 5, 3, 1, 4, 7, 10
```
The maximum value is 13, so we need an array with 
```
index: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 
value: f | t | t | t | t | t | f | t | f | f | t  | f  | f  | t
```
```
1, 2, 3, 4, 5, 7, 10, 13
```

