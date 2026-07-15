# Lecture Notes: Advanced Sorting Algorithms ($O(n \log n)$)

Last week, we explored naive sorting algorithms that operate in $O(n^2)$ time. While those algorithms are intuitive, they scale poorly when dealing with massive datasets.

This week, we introduce three highly efficient, industrial-grade sorting algorithms: **Merge Sort**, **Quick Sort**, and **Heap Sort**. These algorithms achieve an average time complexity of **$O(n \log n)$** by leveraging clever strategies: dividing the problem into smaller pieces, or utilizing specialized data structures.

---

## 1. Merge Sort: The Ultimate Divide and Conquer

Merge Sort is a classic example of a **Divide and Conquer** algorithm. It continuously splits an array in half until it can no longer be divided, sorts the tiny pieces, and then merges them back together in the correct order.

### How it Works

1. **Divide:** Split the unsorted array into two halves at the midpoint.
2. **Conquer:** Recursively split those halves further until you are left with individual elements (an array of size 1 is naturally sorted).
3. **Combine (Merge):** Merge the sorted sub-arrays back together into a single, fully sorted array.

The magic happens in the **Merge step**. Imagine you have two piles of sorted cards face up. You compare the top card of each pile, take the smaller one, and place it into your new sorted pile. You repeat this until both piles are empty.

### The Merging Process in C++

```cpp
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary auxiliary arrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of L[] or R[]
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }

    // Clean up dynamic memory
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return; // Base case: 1 or 0 elements
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);      // Sort left half
    mergeSort(arr, mid + 1, right);  // Sort right half
    merge(arr, left, mid, right);    // Merge them together
}

```

### Complexity & Worst Case

* **Time Complexity:** **$O(n \log n)$** across all cases (best, worst, average). Splitting the array takes $\log n$ steps, and merging elements at each level takes $O(n)$ steps.
* **Auxiliary Space Complexity:** **$O(n)$**. Because it relies on temporary arrays (`L[]` and `R[]`) to hold elements during the merge process, it requires extra memory proportional to the size of the input data.
* **Worst-Case Trigger:** There is no structural worst-case for time. Merge Sort is entirely predictable and performs the exact same way regardless of whether the data is random, sorted, or reversed.

---

## 2. Quick Sort: The Pivot Strategy

Quick Sort also uses Divide and Conquer, but instead of splitting the array blindly down the middle, it selects a specific element called a **pivot** and rearranges the array around it.

### How it Works

1. **Pick a Pivot:** Choose an element from the array (common strategies include picking the first element, the last element, or a random element).
2. **Partitioning:** Rearrange the array so that all elements *smaller* than the pivot move to its left, and all elements *larger* than the pivot move to its right. The pivot is now in its exact, final sorted position.
3. **Recursion:** Apply the exact same process to the left partition and the right partition.

### C++ Code Implementation (Last Element as Pivot)

```cpp
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1); // Return the final index of the pivot
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Pivot index
        
        quickSort(arr, low, pi - 1);  // Recursively sort left of pivot
        quickSort(arr, pi + 1, high); // Recursively sort right of pivot
    }
}

```

### Complexity & Worst Case

* **Average Time Complexity:** **$O(n \log n)$**. If the pivot splits the array roughly in half each time, it scales beautifully.
* **Worst-Case Time Complexity:** **$O(n^2)$**.
* **Worst-Case Trigger:** This happens when the pivot repeatedly choices the absolute smallest or largest element in the sub-array. If you always pick the last element as the pivot, and the array is **already sorted** or **completely reversed**, Quick Sort degrades into an $O(n^2)$ nightmare. Instead of splitting the work in half, it strips off just one element at a time, resulting in a nested-loop behavior.
* **Auxiliary Space Complexity:** **$O(\log n)$** on average due to the recursive call stack. In the absolute worst-case scenario, the call stack can grow to **$O(n)$**.

---

## 3. Heap Sort: The Structural Strategy

Since we recently covered binary heaps, Heap Sort will feel like a natural extension of that structure. It utilizes the innate sorting mechanics of a **Max-Heap** to process data.

### How it Works

1. **Build a Max-Heap:** Rearrange the unsorted input array into a valid Max-Heap structure. The largest element is now sitting right at index 0.
2. **Extract:** Swap the root element (index 0) with the very last element in the array.
3. **Shrink & Reheapify:** Reduce the effective size of the heap by 1 (so the maximum element we just moved to the end is locked in place). Call `heapify()` on the root to fix the broken heap structure.
4. Repeat this extraction loop until the entire array is sorted.

### C++ Code Implementation

```cpp
void heapify(int arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    // If largest is not root, swap and keep heapifying downwards
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Step 1: Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Step 2: One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); // Move current root to end
        heapify(arr, i, 0);        // call max heapify on the reduced heap
    }
}

```

### Complexity & Worst Case

* **Time Complexity:** **$O(n \log n)$** across all cases (best, worst, average). Building the heap takes $O(n)$ time, and extracting the root $n$ times takes $n \times \log n$ steps.
* **Auxiliary Space Complexity:** **$O(1)$** if implemented iteratively, or **$O(\log n)$** if implemented via recursive `heapify` calls due to the stack frames. Unlike Merge Sort, it rearranges elements directly **in-place** inside the existing array.
* **Worst-Case Trigger:** Like Merge Sort, Heap Sort has no catastrophic worst-case scenarios. It guarantees $O(n \log n)$ performance regardless of the initial order of the data.

---

## Summary Comparison: Choosing the Right Tool

When we stack these three advanced algorithms against each other, we can see exactly why different languages choose different defaults for their standard libraries.

| Algorithm | Best Time | Avg Time | Worst Time | Aux. Space | Stability | When does the worst case happen? |
| --- | --- | --- | --- | --- | --- | --- |
| **Merge Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | **$O(n)$** | **Stable** | Never. Performance is rock-solid and highly consistent. |
| **Quick Sort** | $O(n \log n)$ | $O(n \log n)$ | **$O(n^2)$** | $O(\log n)$ | Unstable | When the array is already sorted/reversed and a poor pivot strategy is used. |
| **Heap Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | **$O(1)$** | Unstable | Never. Guarantees top performance with zero extra memory overhead. |

> **Note on Stability:** A sorting algorithm is **stable** if it preserves the original relative order of duplicate elements. For example, if you sort a list of students by grade, a stable sort ensures that students with identical grades remain in the exact order they appeared originally. Merge Sort preserves this, while Quick Sort and Heap Sort do not.
