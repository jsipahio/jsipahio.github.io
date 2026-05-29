## Week 2 Quiz
### CSE238 - Data Structures and Algorithms
#### Name _____________________________________

1. Explain what is meant by code coverage in software testing. (2.5 points)
2. Explain what edge cases are in software testing. (2.5 points)
3. Write the recurrence equation, inductive reduction, and big-Oh runtime complexity of the following loops. You can assume that any function calls within the loop have an O(1) complexity. (2 points each)  
  
a.
```C++
int count = 0;
for (int i = 0; i < MAX; ++i) {
    count += i;
}
```
b.
```C++
int total = 1;
for (int i = n; i > 0; --i) {
    total *= i;
}
```
c. 
```C++
int x = 0;
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n: ++j) {
        x += j;
    }
    x *= i;
}
```
d. 
```C++
int x = 0;
while (x < (n * n)) {
    performOperation(x);
}
```
  
e. 
```C++
int x = 0;
for (int i = 1; i < n; ++i) {
    x += i;
    for (int j = n * n; j > 0; --j) {
        x /= j;
    }
    x *= i;
}
```
4. For the following functions and classes, determine their space complexity. (2 points each)  
  
a.
```C++
void reverseArray(int arr[], int length) {
    int *copy = new int[length];
    for (int i = 0; i < length; ++i) {
        copy[i] = arr[length - 1 - i];
    }
    for (int i = 0; i < length; ++i) {
        arr[i] = copy[i];
    }
}
```
b.
```C++
void reverseArray(int arr[], int length) {
    for (int i = 0; i < length / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[length - 1 - i];
        arr[length - 1 - i] = temp;
    }
}
```
c.
```C++
class IntegerArray {
public:
    IntegerArray(int s) {
        size = s;
        arr = new int[size];
    }
    // ...
private:
    int *arr;
    int size;
};
```
d.
```C++
class IntegerPointer {
public:
    IntegerPointer(int value) {
        ptr = new int;
        *ptr = value;
    }
    // ...
private:
    int *ptr;
};
```
e.
```C++
class Matrix {
public:
    Matrix(int n, int m) {
        rows = n;
        columns = m;
        matrix = new int*[n];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[columns];
        }
    }
    // ...
private:
    int rows;
    int columns;
    int **matrix;
};
```