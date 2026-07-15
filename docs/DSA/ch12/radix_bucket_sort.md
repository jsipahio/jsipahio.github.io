# Radix and Bucket Sort

# Lecture Notes: Non-Comparison Sorting Algorithms ($O(n)$)

Up until now, every sorting algorithm we have looked at (Bubble, Selection, Insertion, Merge, Quick, and Heap Sort) has been a **comparison-based sort**. This means the algorithm decides the order of elements by comparing them to each other (asking: "Is $A < B$?").

There is a mathematical rule in computer science: **No comparison-based sorting algorithm can ever run faster than $O(n \log n)$ in the worst case.** But what if we didn't compare numbers at all? What if we sorted them by taking advantage of *properties* of the data itself, like their digits or their range?

This week, we explore **Counting Sort**, **Radix Sort**, and **Bucket Sort**. Under the right conditions, these algorithms can sort data in **$O(n)$ (linear) time**!

---

## 1. Counting Sort: The Tally Strategy

Imagine you are a teacher grading quizzes. The scores are all whole numbers between 0 and 5. To sort a stack of 100 quizzes, you wouldn't use Merge Sort. Instead, you would make 6 piles on your desk (one pile for 0s, one for 1s, etc.), tally how many quizzes are in each pile, and then rebuild the stack in order.

This is exactly how **Counting Sort** works.

### How it Works

1. Find the maximum value in the input array to determine the range of numbers.
2. Create a "Count Array" of size $\text{Max} + 1$, initialized to all 0s. This array acts as our tally board.
3. Traverse the input array. For each number you see, increment its corresponding index in the Count Array.
4. Iterate through the Count Array and overwrite the original array with the tallied numbers.

### C++ Code Implementation (Basic Version)

```cpp
void countingSort(int arr[], int n) {
    // 1. Find the maximum element in the array
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // 2. Create and initialize the Count Array with 0s
    // (Size must be maxVal + 1 to include the max number as an index)
    int* count = new int[maxVal + 1](); 

    // 3. Tally the frequencies of each number
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 4. Overwrite the original array using the tallies
    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }

    // Clean up dynamic memory
    delete[] count;
}

```

### Complexity & The "Gotcha"

* **Time Complexity:** **$O(n + k)$**, where $n$ is the number of elements, and $k$ is the range of the input data (the maximum value). If $k$ is small, this runs in essentially $O(n)$ linear time!
* **Auxiliary Space Complexity:** **$O(k)$** to allocate the Count Array.
* **The Catastrophic Worst-Case:** Counting Sort is incredibly fast *only* if the range of numbers ($k$) is relatively small. If you have an array of just 5 elements: `[1, 2, 1, 3, 1000000]`, Counting Sort will allocate a temporary array of size **1,000,001** to sort just five numbers! This wastes a massive amount of memory and CPU cycles.

---

## 2. Radix Sort: The Digit-by-Digit Strategy

If Counting Sort breaks down when numbers get large, how do we sort larger numbers without comparisons? We use **Radix Sort**.

Instead of looking at a whole number, Radix Sort breaks numbers down digit by digit, starting from the **Least Significant Digit (ones place)** and moving toward the **Most Significant Digit (tens, hundreds, etc.)**.

### How it Works

1. Find the maximum number to see how many digits it has (e.g., 457 has 3 digits).
2. Use a stable sorting algorithm (usually **Counting Sort**) to sort the array based on the **1s place**.
3. Sort the resulting array based on the **10s place**.
4. Sort it again based on the **100s place**, and so on, until you run out of digits.

Because the underlying sort (Counting Sort) is *stable*, the relative order of numbers sorted in previous steps is preserved.

### C++ Code Implementation

```cpp
// A modified counting sort that sorts based on a specific digit represented by 'exp'
// (exp = 1 for 1s place, 10 for 10s place, 100 for 100s place, etc.)
void countingSortForRadix(int arr[], int n, int exp) {
    int output[n]; 
    int count[10] = {0}; // Digits are always 0-9, so count size is always 10!

    // Store count of occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Change count[i] so that it contains the actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array (going backward to maintain stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array back to arr[]
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    // Find the maximum number to know the number of digits
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // Do counting sort for every digit. 
    // Instead of passing digit number, exp is passed (10^i)
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}

```

### Complexity & Worst Case

* **Time Complexity:** **$O(d \cdot (n + k))$**, where $d$ is the number of digits in the maximum number, $n$ is the number of elements, and $k$ is the base of the numbers (base 10 for decimal numbers, so $k = 10$). Since $d$ and $k$ are usually constant properties of the system, this behaves as **$O(n)$**.
* **Auxiliary Space Complexity:** **$O(n + k)$**.
* **Worst-Case Trigger:** If you have an array where almost all numbers are small, but a single outlier is extremely long (like $1,000,000,000,000$), $d$ becomes massive. You will have to run the outer loop many unnecessary times just to handle that one outlier.

---

## 3. Bucket Sort: The Distribution Strategy

Bucket Sort is a "divide and conquer" sorting algorithm that works by distributing the elements of an array into several recursively sorted groups called **buckets**. It is exceptionally useful when the input data is **uniformly distributed** over a known range (such as decimals between 0.0 and 1.0).

### How it Works

1. Create an array of empty "buckets" (linked lists or dynamic arrays).
2. Put each input element into its corresponding bucket based on a mathematical formula (like $\text{index} = n \times \text{element}$).
3. Sort each individual bucket using a simple sorting algorithm (usually **Insertion Sort**).
4. Concatenate all the sorted buckets back together into the original array.

### C++ Code Implementation (For Floats between 0.0 and 1.0)

```cpp
#include <vector>
#include <algorithm>

void bucketSort(float arr[], int n) {
    // 1. Create n empty buckets
    std::vector<float>* buckets = new std::vector<float>[n];

    // 2. Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i]; // Index in bucket
        buckets[bucketIndex].push_back(arr[i]);
    }

    // 3. Sort individual buckets (std::sort usually defaults to QuickSort/InsertionSort)
    for (int i = 0; i < n; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // 4. Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }

    delete[] buckets;
}

```

### Complexity & Worst Case

* **Average Time Complexity:** **$O(n)$**. If the data is distributed evenly, each bucket will hold only a few elements, making the individual sorting step incredibly fast.
* **Worst-Case Time Complexity:** **$O(n^2)$**.
* **Worst-Case Trigger:** This occurs when the data is highly clustered instead of uniformly distributed. If every single item in the array hashes to the exact same bucket, Bucket Sort degrades into whatever sorting algorithm is used on that single bucket (e.g., Insertion Sort).
* **Auxiliary Space Complexity:** **$O(n + k)$**, where $k$ is the number of buckets.

---

## Summary of Non-Comparison Sorting Algorithms

| Algorithm | Best Time | Avg Time | Worst Time | Aux. Space | Best Used When... |
| --- | --- | --- | --- | --- | --- |
| **Counting Sort** | $O(n + k)$ | $O(n + k)$ | $O(n + k)$ | $O(k)$ | You have a massive array of small integers (e.g., age data, exam scores). |
| **Radix Sort** | $O(d \cdot n)$ | $O(d \cdot n)$ | $O(d \cdot n)$ | $O(n + k)$ | You are sorting keys with a fixed, known number of digits (e.g., zip codes, phone numbers). |
| **Bucket Sort** | $O(n)$ | **$O(n)$** | **$O(n^2)$** | $O(n + k)$ | Your data is uniformly distributed floats (e.g., percentage scores, probabilities between 0 and 1). |

---

This concludes our deep dive into sorting algorithms! Would you like to move on to drafting the lecture notes for the next unit of your course, or would you like to review some practice questions for these sorting modules?
