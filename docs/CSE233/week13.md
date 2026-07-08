# CSE233 Week 13: Recursion
Recursion is a process by which a function calls itself. A function that does so is said to call itself recursively. Not all languages support recursion, but C++ does. Recursion is a powerful tool that can replace loops with simpler, cleaner code. However, it can also cause problems if you are not careful.

## Basic Example: Summing Numbers
Let's consider a function that sums numbers from n to 1, where n is the number input. If n = 5, then we'd sum 5 + 4 + 3 + 2 + 1 = 15. 
```cpp
int sumDown(int n) {
    int sum = 0;
    for (int i = n; i > 0; --i) {
        sum += n;
    }

    return sum;
}
```
We can also define this function recursively. Whenever we are defining a recursive function, we need to have a base case. A base case is an input to the function that causes the recursion to stop. In this case, if n == 1, the function will always return 1. If n is less than 1, the function returns 0. These two comprise the base cases of the function. The recursive step is the step that causes the function to call itself. Note that `addDown(2)` is equal to `2 + addDown(1)` which is equal to `2 + 1`. Similiarly, `addDown(3) == 3 + addDown(2) == 3 + 2 + addDown(1) == 3 + 2 + 1`. Therefore, the recursive step for addDown is `n + addDown(n - 1)`. Now that we've specified the base and recursive steps, we can define the recursive function:
```cpp
int addDown(int n) {
    // base step for n = 0 or n being negative
    if (n <= 0) return 0;
    // base step for n = 1
    else if (n == 1) return 1;
    // recursive step
    else return n + addDown(n - 1);
}
```

