# Time and Space Complexity of Algorithms

When we write software, it isn't enough for a program to just work. It also needs to be efficient. If your program takes three days to process a single file, it isn't very useful.

In computer science, we measure efficiency using two metrics:

1. **Time Complexity:** How fast does the algorithm run as the amount of input data grows?
2. **Auxiliary Space Complexity:** How much extra memory does the algorithm need as the amount of input data grows?

Rather than measuring this in exact seconds or megabytes (which change depending on whether you are running the code on a smartphone or a supercomputer), we use a framework called Big O Notation.

---

## Basics of Time Complexity

Imagine you are looking for a specific name in a physical phone book.

* **Strategy A:** You start at page 1 and look at every single name in order until you find it.
* **Strategy B:** You open to the exact middle, see if your name comes before or after that page, flip to the middle of the remaining section, and repeat.

If the phone book only has 10 pages, both methods are fast. But if the phone book has 1,000,000 pages, Strategy A will take forever, while Strategy B will take only a few seconds.

In data structures, we represent the size of the input data as **$n$**. (For example, $n$ could be the number of elements in an array). We want to know: As $n$ gets massive, how does the number of operations our CPU has to perform grow?

### Counting Steps

For our purposes, a "step" (or a primitive operation) is any basic action that takes a constant amount of time:

* Assigning a value to a variable (`int x = 5;`)
* Arithmetic operations (`x + y`, `x * 2`)
* Comparing two values (`x < y`)
* Accessing an element in an array (`arr[0]`)

## Big O Notation

Big O notation provides an approximation of an algorithm's time complexity. When $n$ becomes incredibly large (like 10 million), smaller terms and constant multipliers stop mattering.

### Drop the Constants

If an algorithm takes $3n$ steps, we say it is $O(n)$. Why? Because if $n$ goes from 1 million to 2 million, the time it takes doubles. The factor of 3 doesn't change the rate of growth.

### Drop Non-Dominant Terms

If an algorithm takes $n^2 + 5n + 100$ steps, we say it is $O(n^2)$.  
Let's look at why the $5n$ and $100$ become irrelevant when $n$ is large:

* If $n = 1,000$: $n^2 = 1,000,000$, while $5n = 5,000$.
* The 5,000 term makes almost no difference in the amount of time the algorithm takes.
* The $n^2$ term completely dominates the execution time.
* At this point, the 100 term in contributing practically nothing to execution time.

## 3. Analyzing Time Complexity of C++ Code

Let's look at common code structures your students will encounter and learn how to count their complexities.

### Constant Time: $O(1)$

An algorithm is $O(1)$ if its execution time does not depend on the size of the input data ($n$).

```cpp
void printFirstElement(int arr[], int n) {
    std::cout << arr[0] << std::endl; // 1 step
}

```

Even if the array has 5 elements or 5 million elements, this function only ever looks at the first element. It takes the exact same amount of time no matter what the size of the input is.

### Linear Time: $O(n)$

If you have a single loop that visits every item in a collection of size $n$, the code runs in linear time.

```cpp
int findSum(int arr[], int n) {
    int sum = 0;                  // 1 step
    for (int i = 0; i < n; i++) { // Loop runs n times
        sum += arr[i];            // 1 step per iteration
    }
    return sum;                   // 1 step
}

```

* **Exact Step Count:** $1 + n(1) + 1 = n + 2$.
* **Big O:** Drop the constant $2$. We are left with $O(n)$.

### Quadratic Time: $O(n^2)$

This usually occurs when you nest a loop inside another loop, and both loops depend on $n$.

```cpp
void printPairs(int arr[], int n) {
    for (int i = 0; i < n; i++) {         // Outer loop runs n times
        for (int j = 0; j < n; j++) {     // Inner loop runs n times
            std::cout << arr[i] << ", " << arr[j] << std::endl;
        }
    }
}

```

* For every single iteration of the outer loop ($n$ times), the inner loop runs completely ($n$ times).
* Total iterations = $n \times n = n^2$.
* **Big O:** $O(n^2)$.

#### More Complex Nested Loops

What happens if the inner loop doesn't go up to $n$, but instead changes based on $i$?

```cpp
void printUniquePairs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // Notice: j starts at i + 1
            std::cout << arr[i] << ", " << arr[j] << std::endl;
        }
    }
}

```

* **Iteration 1 ($i=0$):** Inner loop runs $n-1$ times.
* **Iteration 2 ($i=1$):** Inner loop runs $n-2$ times.
* **Last Iteration:** Inner loop runs $0$ times.
* The total number of iterations is the sum: $(n-1) + (n-2) + ... + 2 + 1 + 0$.
* An easy way to picture this visually is a grid cut in half diagonally (a triangle). The area of a triangle of base $n$ and height $n$ is $\frac{1}{2}n^2$.
* Using our rules: Drop the constant fraction ($\frac{1}{2}$). The complexity is still **$O(n^2)$**.
* However, in the real world, this algorithm is much faster than the previous. Big O is an approximation, and assigns algorithms to categories. It does not provide deep analysis between algorithms in the same Big O category.

### Logarithmic Time: $O(\log n)$
Logarithmic algorithms are tricky to understand without a discrete math background. At a high level, any time an algorithm splits its data in half successively, it is probably logarithmic.

```cpp
// A classic example of dividing the problem in half
void divideByTwo(int n) {
    while (n > 1) {
        n = n / 2; // The input is cut in half every single loop
        std::cout << n << std::endl;
    }
}

```

If $n = 16$, the loop executes for $16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1$ (4 iterations).
If $n = 1,000,000$, it takes only about 20 iterations! This makes $O(\log n)$ incredibly fast.

---

## 4. Auxiliary Space Complexity
The total space an algorithm uses will, of course, be dependent on the input data size. However, in algorithm analysis, we really want to know how much extra space an algorithm uses.  

* **Total Space:** The entire memory the program uses, including the original input data.
* **Auxiliary Space:** The extra or temporary memory allocated by the algorithm to solve the problem, excluding the input data. In this course, we focus almost exclusively on auxiliary space.

Just like time complexity, we measure this by seeing how our temporary allocations grow relative to $n$.

### $O(1)$ Auxiliary Space (Constant Extra Space)

If an algorithm only creates a few temporary variables that don't multiply based on the input size, it uses $O(1)$ auxiliary space.

```cpp
int findMax(int arr[], int n) {
    int maxVal = arr[0];          // Allocates 1 integer of extra space
    for (int i = 0; i < n; i++) { // 'i' is 1 integer of extra space
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

```

Whether $n$ is 10 or 10,000, this function only ever creates two integers (`maxVal` and `i`) in memory. The extra space does not grow.

### $O(n)$ Auxiliary Space (Linear Extra Space)

If an algorithm creates a copy of the data, or dynamically allocates an array that matches the size of the input, it uses $O(n)$ auxiliary space.

```cpp
int* copyArray(int arr[], int n) {
    int* newArr = new int[n];    // Allocates a new array of size n!
    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}

```

If $n = 1,000$, we allocate memory for 1,000 integers. The auxiliary space grows perfectly in parallel with the input size.

## Table of Complexities
Here is a high-level overview of common algorithm complexities. We rarely see algorithms go beyond $O(n^3)$, since at this point they become far too slow to be practical. Many algorithms are $O(2^n)$, but they are never used because exponential algorithms become impossibly slow, even for relatively small input sizes. Most modern cryptology (security) depends on the fact that finding the prime factorization of a large enough number would take centuries to compute.
  
| Big O | Common Name | How to spot it in basic code |
| --- | --- | --- |
| **$O(1)$** | Constant | No loops that depend on $n$. Just straight-through code. |
| **$O(\log n)$** | Logarithmic | Loop variables are divided or multiplied by a factor (e.g., `i /= 2` or `i *= 2`). |
| **$O(n)$** | Linear | A single loop that counts from $0$ up to $n$ (or down to $0$). |
| **$O(n \log n)$** | Linearithmic | A loop that runs $n$ times, inside of which is an operation that cuts data in half. (Seen in efficient sorting algorithms). |
| **$O(n^2)$** | Quadratic | Two nested loops that both depend on $n$. |
| **$O(n^3)$** | Hyperbolic | Three nested loops that both depend on $n$. |
| **$O(2^n)$** | Exponential | No easy tell |
