# Dynamic Programming

# Lecture Notes: Introduction to Dynamic Programming (DP)

Over the last few weeks, we have explored different algorithmic strategies:

* **Divide and Conquer** (like Merge Sort), which breaks a problem into completely independent sub-problems, solves them, and combines the results.
* **Greedy Algorithms** (like Dijkstra's), which make the single best "local" choice at each step, hoping it leads to a global solution.

This week, we introduce **Dynamic Programming (DP)**.

Do not let the name intimidate you. "Dynamic Programming" was coined in the 1950s by Richard Bellman as a fancy-sounding military research phrase, but its core concept is incredibly simple: **It is Divide and Conquer, but with a memory.** Dynamic Programming is a technique used to solve complex problems by breaking them down into simpler, *overlapping* sub-problems, solving each sub-problem exactly **once**, and storing their answers so we never have to recompute them.

---

## 1. When Does Dynamic Programming Outperform the Rest?

To understand why we need Dynamic Programming, we must look at the structural differences between these three major techniques.

### The Key Requirements for DP:

An algorithm is a prime candidate for Dynamic Programming if it possesses two distinct properties:

1. **Overlapping Sub-problems:** Solving the main problem requires solving the *same* smaller sub-problems over and over again. (This is where plain Divide and Conquer fails because it wastes time recalculating them).
2. **Optimal Substructure:** An optimal overall solution can be constructed efficiently from the optimal solutions of its sub-problems.

Let's compare them side-by-side:

| Strategy | Sub-problems | Decision Making | Example |
| --- | --- | --- | --- |
| **Divide & Conquer** | **Independent** (e.g., sorting the left half of an array has nothing to do with sorting the right half). | Explores all split parts. | Merge Sort |
| **Greedy** | **Dependent**, but we only ever explore *one* choice at each step. | Commits to the local best immediately. Never backtracks or looks at other paths. | Dijkstra's Algorithm |
| **Dynamic Programming** | **Overlapping** (The same sub-calculations are needed by many different parts of the algorithm). | Evaluates all possibilities for a sub-problem, remembers the best one, and builds upward. | Fibonacci, Knapsack |

---

## 2. The Classic Case Study: The Fibonacci Sequence

The absolute best way to see the power of Dynamic Programming is through the Fibonacci sequence:

$$0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...$$

Each number is the sum of the two preceding ones: $F(n) = F(n-1) + F(n-2)$, with base cases $F(0) = 0$ and $F(1) = 1$.

### The Plain Divide & Conquer Approach (Naive Recursion)

If we write this directly as a recursive function, we get:

```cpp
int fibNaive(int n) {
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

```

This code looks clean, but it is **catastrophically slow**. Let's look at the execution tree for `fibNaive(5)`:

Notice the massive redundancy:

* `fib(3)` is computed **2 times**.
* `fib(2)` is computed **3 times**.
* `fib(1)` is computed **5 times**.

As $n$ grows, this redundancy explodes. The time complexity of this naive approach is **$O(2^n)$**—exponential time! Trying to calculate `fibNaive(50)` will literally freeze your computer.

---

### The Dynamic Programming Cure: Two Approaches

Dynamic Programming solves this by ensuring we calculate each Fibonacci number exactly **once**. We can implement this in two ways:

#### Way 1: Memoization (Top-Down)

We keep our recursive structure, but we check a lookup table (like an array or hash map) before we do any math. If the answer is already in the table, we return it instantly. If not, we calculate it and save it to the table.

```cpp
#include <vector>

// Initialize a memoization array filled with -1 (meaning uncalculated)
std::vector<int> memo;

int fibTopDown(int n) {
    if (n <= 1) return n;
    
    // If we have already solved this sub-problem, return the saved answer!
    if (memo[n] != -1) {
        return memo[n];
    }
    
    // Otherwise, calculate it and store it in our memo table
    memo[n] = fibTopDown(n - 1) + fibTopDown(n - 2);
    return memo[n];
}

```

#### Way 2: Tabulation (Bottom-Up)

Instead of recursion, we start at the very bottom (the base cases) and fill up an array iteratively.

```cpp
int fibBottomUp(int n) {
    if (n <= 1) return n;
    
    std::vector<int> table(n + 1);
    table[0] = 0;
    table[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        table[i] = table[i - 1] + table[i - 2];
    }
    
    return table[n];
}

```

### The Result:

By utilizing DP, we collapsed the time complexity from an impossible **$O(2^n)$** down to a blazing fast **$O(n)$** linear time!

---

## 3. Where DP Beats Greedy: The 0/1 Knapsack Problem

To see where DP shines over the Greedy approach, let's look at the famous **0/1 Knapsack Problem**.

Imagine you are a thief breaking into a vault with a knapsack that can hold a maximum weight of **$W = 50\text{ kg}$**. Inside, you find three items:

* **Item 1:** Value: $60, Weight: 10 kg
* **Item 2:** Value: $100, Weight: 20 kg
* **Item 3:** Value: $120, Weight: 30 kg

You cannot take a fraction of an item (it's "0/1"—you either take the whole item or leave it behind). You want to maximize the dollar value of the items you steal without breaking your bag.

### The Greedy Attempt (and why it fails)

A greedy algorithm might suggest sorting items by **value-to-weight ratio**:

* Item 1 ratio: $\frac{\$60}{10\text{ kg}} = \$6/\text{kg}$
* Item 2 ratio: $\frac{\$100}{20\text{ kg}} = \$5/\text{kg}$
* Item 3 ratio: $\frac{\$120}{30\text{ kg}} = \$4/\text{kg}$

Following the greedy approach:

1. Grab Item 1 first (best ratio). Remaining capacity: 40 kg. Current Value: $60.
2. Grab Item 2 next (second best). Remaining capacity: 20 kg. Current Value: $160.
3. Item 3 (30 kg) will no longer fit in the bag!

* **Greedy Total Value: $160** (Items 1 and 2).

But look closely! What if we had ignored the greedy ratio and taken **Item 2 and Item 3** instead?

* Combined Weight: $20\text{ kg} + 30\text{ kg} = 50\text{ kg}$ (Fits perfectly!).
* **Optimal Total Value: $220** (Items 2 and 3).

The greedy algorithm failed because it made a short-sighted decision early on (grabbing Item 1) that blocked the much more lucrative combination of Items 2 and 3.

---

### The Dynamic Programming Solution

To solve this optimally, we must evaluate the choice we face for every single item: **Do we include it, or do we exclude it?** Let $dp[i][w]$ represent the maximum value we can get using the first $i$ items with a bag of weight capacity $w$.

For each item, we evaluate:

* **If we exclude item $i$:** The value is the same as the best we could do *without* this item: $dp[i-1][w]$.
* **If we include item $i$ (if it fits):** The value is the item's value plus the best we could do with the *remaining* weight: $\text{value}[i] + dp[i-1][w - \text{weight}[i]]$.

We greedily take the maximum of these two choices:

$$dp[i][w] = \max\Big(dp[i-1][w], \, \text{value}[i-1] + dp[i-1][w - \text{weight}[i-1]]\Big)$$

#### C++ Tabulation Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int knapsack(int W, const std::vector<int>& weights, const std::vector<int>& values, int n) {
    // 2D Table: rows represent items (0 to n), columns represent weight capacities (0 to W)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    // Build the table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                // We have a choice: Include or Exclude the item
                dp[i][w] = std::max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]], // Include
                    dp[i - 1][w]                                    // Exclude
                );
            } else {
                // Item is too heavy, we must exclude it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W]; // Bottom-right corner contains the final optimal answer
}

```

### Complexity

* **Time Complexity:** **$O(n \cdot W)$**, where $n$ is the number of items and $W$ is the maximum capacity. This is vastly superior to the brute-force recursive strategy which would take $O(2^n)$ time.
* **Auxiliary Space Complexity:** **$O(n \cdot W)$** to store the 2D grid.

---

## Summary Cheat Sheet for Students

| Algorithm Technique | Ideal Problem Structure | Risk / Tradeoff |
| --- | --- | --- |
| **Divide & Conquer** | Independent sub-problems. | Redundant calculations if sub-problems overlap. |
| **Greedy** | No-regret choices; local optimum matches global optimum. | Can easily get trapped in sub-optimal paths. |
| **Dynamic Programming** | Overlapping sub-problems with optimal substructure. | Requires extra memory to store state tables ($O(n)$ or $O(n^2)$ space). |

---

