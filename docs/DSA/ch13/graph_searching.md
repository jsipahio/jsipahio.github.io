# Lecture Notes: Graph Searching and Traversal (BFS & DFS)

Once we have represented a graph in memory (such as with an Adjacency List), the most fundamental task we need to perform is **traversal**—visiting every vertex in the graph systematically.

Unlike arrays or linked lists, which are linear and have an obvious "next" element, graphs are highly interconnected networks. If we aren't careful, we could easily get stuck in an infinite loop by traveling in a circle, or we might miss entire sections of the graph.

To prevent this, all graph traversal algorithms share one golden rule: **We must keep track of which vertices we have already visited.**

This week, we explore the two primary algorithms used to search and traverse a graph: **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**.

---

## 1. The Core Mechanism: The "Visited" Array

Whether we use BFS or DFS, we need a way to mark vertices so we don't process them more than once. The simplest way to do this is with a boolean array (or a `std::vector<bool>`) of size $V$, where `visited[i]` is set to `true` once we encounter vertex `i`.

Without this safeguard, a simple cyclic graph like `A -> B -> C -> A` would cause our program to loop infinitely until the computer runs out of memory.

---

## 2. Breadth-First Search (BFS): Exploring in Ripple Layers

Breadth-First Search explores a graph level by level, radiating outward from a starting vertex.

Imagine dropping a pebble into a calm pond. The ripples spread outward in concentric circles. BFS does the same:

1. First, it visits the starting vertex (Level 0).
2. Next, it visits all the direct neighbors of the starting vertex (Level 1).
3. Then, it visits all the neighbors of those neighbors (Level 2), and so on.

### The Tool of Choice: The Queue

Because we want to visit vertices in the exact order we discovered them (First-In, First-Out), BFS uses a **Queue** (`std::queue`) under the hood.

### BFS Step-by-Step Algorithm

1. Create a queue and a boolean `visited` array.
2. Push the starting vertex into the queue and mark it as visited.
3. While the queue is not empty:
* Dequeue (remove) the vertex at the front of the queue. This is your "current" vertex.
* Process/print the current vertex.
* For every unvisited neighbor of the current vertex:
* Mark it as visited.
* Push it into the queue.





### C++ Code Implementation (Using Adjacency List)

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <queue>

void BFS(int startVertex, const std::vector<std::list<int>>& adjList, int V) {
    std::vector<bool> visited(V, false);
    std::queue<int> q;

    // Initialize with the starting vertex
    visited[startVertex] = true;
    q.push(startVertex);

    std::cout << "BFS Traversal starting from vertex " << startVertex << ": ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::cout << current << " ";

        // Explore all neighbors of the current vertex
        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true; // Mark visited when pushing to queue
                q.push(neighbor);
            }
        }
    }
    std::cout << std::endl;
}

```

### The Key Advantage of BFS: Shortest Path

Because BFS explores the graph uniformly in layers, **it is guaranteed to find the shortest path (in terms of the minimum number of edges) between the starting vertex and any other reachable vertex in an unweighted graph.** If you want to find the fewest number of friend connections separating you from a celebrity on social media, BFS is the exact algorithm you would use.

---

## 3. Depth-First Search (DFS): Plunging Deep into the Maze

While BFS spreads out wide, Depth-First Search goes deep.

Imagine you are exploring a dark maze. Instead of systematically checking every branch near the entrance, you choose a path and walk as far down as you possibly can until you hit a dead end. Only when you hit a dead end do you backtrack to the last intersection and try a different path.

### The Tool of Choice: The Stack

Because we need to backtrack (reversing our steps to go back to the most recently seen intersection), DFS relies on a **Stack** (Last-In, First-Out).

We can implement DFS in two ways:

* **Recursively:** Using the computer's built-in call stack (simplest and most common).
* **Iteratively:** Manually managing a `std::stack` object.

### Recursive DFS Step-by-Step Algorithm

1. Start at a vertex. Mark it as visited and process/print it.
2. For every neighbor of the current vertex:
* If the neighbor is unvisited, immediately make a recursive call to DFS on that neighbor.


3. If all neighbors of the current vertex are already visited, the recursive function returns (backtracks automatically).

### C++ Code Implementation (Recursive)

```cpp
#include <iostream>
#include <vector>
#include <list>

// Helper function that carries the visited state through recursion
void DFSHelper(int vertex, const std::vector<std::list<int>>& adjList, std::vector<bool>& visited) {
    // 1. Mark the current node as visited and print it
    visited[vertex] = true;
    std::cout << vertex << " ";

    // 2. Recur for all the vertices adjacent to this vertex
    for (int neighbor : adjList[vertex]) {
        if (!visited[neighbor]) {
            DFSHelper(neighbor, adjList, visited);
        }
    }
}

void DFS(int startVertex, const std::vector<std::list<int>>& adjList, int V) {
    std::vector<bool> visited(V, false);
    
    std::cout << "DFS Traversal starting from vertex " << startVertex << ": ";
    DFSHelper(startVertex, adjList, visited);
    std::cout << std::endl;
}

```

### The Key Advantage of DFS: Connectivity and Structure

Because DFS plunges deep and backtracks, it naturally maps out the topological structure of a graph. It is highly efficient for:

* Detecting cycles in a graph.
* Finding "strongly connected components" (islands of nodes that can all reach each other).
* Solving mazes and puzzles where you must find any valid path to the end.

---

## 4. Complexity Analysis

Both algorithms are incredibly efficient because they make sure to visit each vertex and cross each edge a limited number of times.

Assuming we use an **Adjacency List** to represent a graph with $V$ vertices and $E$ edges:

* **Time Complexity:** **$O(V + E)$** for both BFS and DFS.
* Every vertex is enqueued/visited exactly once ($O(V)$).
* Every edge is checked to find neighbors exactly once (in a directed graph) or twice (in an undirected graph) ($O(E)$).


* **Auxiliary Space Complexity:** **$O(V)$** for both BFS and DFS.
* For BFS: The queue can hold at most $V$ vertices, and the `visited` array requires $V$ spots.
* For DFS: The recursion stack can grow to a depth of $V$ in the worst-case scenario (a graph that is just a straight, single line of nodes), and the `visited` array requires $V$ spots.



---

## Summary Comparison: BFS vs. DFS

| Metric | Breadth-First Search (BFS) | Depth-First Search (DFS) |
| --- | --- | --- |
| **Underlying Structure** | Queue (FIFO) | Stack (LIFO) or Recursion |
| **Search Movement** | Explores widely in concentric layers. | Explores deeply along a single path before backtracking. |
| **Shortest Path** | **Yes** (guaranteed for unweighted graphs). | No (finds *any* path, not necessarily the shortest). |
| **Memory Consumption** | Can use more memory on wide, shallow graphs (queue grows large). | Can use more memory on deep, narrow graphs (recursion stack grows large). |
| **Best Used For** | Finding shortest physical paths, peer-to-peer networks, GPS navigation. | Solving mazes, cycle detection, compiling dependencies (Topological Sort). |
