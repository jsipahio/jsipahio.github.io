# Lecture Notes: Digraphs, DAGs, and Weighted Graphs

Up to this point, we have primarily focused on simple, undirected, and unweighted graphs. While those are great for modeling basic connections like mutual friendships, real-world systems are rarely that simple.

If you are modeling a street network, some streets are one-way (directed). If you are mapping out college course prerequisites, you must take Course A *before* Course B (directed and acyclic). If you are building a GPS navigation system, some roads are longer or have slower speed limits than others (weighted).

This week, we expand our Graph toolkit to cover **Directed Graphs (Digraphs)**, **Directed Acyclic Graphs (DAGs)**, and **Weighted Graphs**, along with a critical algorithm called **Topological Sort**.

---

## 1. Directed Graphs (Digraphs)

In a **Digraph**, edges have a direction. An edge is represented as an ordered pair $(u, v)$, meaning there is a one-way path from vertex $u$ to vertex $v$.

### Impact on Graph Implementation

Our C++ implementation strategies from earlier need slight adjustments to support direction:

* **Adjacency Matrix:** If there is a directed edge $u \rightarrow v$, we set `matrix[u][v] = 1`. However, we **do not** set `matrix[v][u] = 1` unless there is also a separate return edge from $v$ to $u$. The matrix is no longer guaranteed to be symmetric.
* **Adjacency List:** When adding a directed edge $u \rightarrow v$, we only push $v$ into the neighbor list of $u$:

```cpp
void addDirectedEdge(int u, int v) {
    adjList[u].push_back(v); // Only u can reach v!
    // Do NOT add u to adjList[v]
}

```

### In-Degree vs. Out-Degree

In undirected graphs, we simply counted how many connections a node had (its degree). In a digraph, we split this into two metrics:

* **In-Degree:** The number of incoming edges pointing *to* a vertex. (How many nodes can reach this vertex?)
* **Out-Degree:** The number of outgoing edges pointing *from* a vertex. (How many nodes can this vertex reach?)

---

## 2. Directed Acyclic Graphs (DAGs)

A **DAG** is a directed graph that contains **absolutely no cycles**. If you start at any vertex in a DAG and follow the directed edges, it is mathematically impossible to ever loop back to your starting point.

DAGs are the gold standard for representing **dependencies, workflows, and hierarchies**.

### Examples of DAGs:

* **Prerequisite Sheets:** You must take CS1 before CS2, and CS2 before Algorithms. You cannot have a cycle where Algorithms is a prerequisite for CS1!
* **Build Systems (like Make or CMake):** Compiling Code File B depends on Code File A being compiled first.
* **Git Commits:** Every commit points backward to its parent commit(s), forming a history tree that never loops back on itself.

---

## 3. Topological Sort: Ordering a DAG

Suppose you want to find a valid order to take all your college classes such that you never violate a prerequisite. The process of taking a DAG and laying out its vertices in a linear sequence is called a **Topological Sort**.

> **The Topological Sort Rule:** For every directed edge $u \rightarrow v$, vertex $u$ must appear *before* vertex $v$ in the final ordering.

*Note: A graph can only have a topological sort if it is a DAG. If there is a cycle (e.g., A depends on B, B depends on C, C depends on A), no valid ordering exists.*

### How to Implement: Kahn's Algorithm (BFS-Based)

The most intuitive way to perform a topological sort is using **Kahn's Algorithm**, which works by repeatedly stripping away nodes that have no prerequisites (In-Degree = 0).

#### The Algorithm:

1. Calculate the **In-Degree** of every vertex in the graph.
2. Place all vertices with an In-Degree of `0` into a Queue. (These are classes with no prerequisites).
3. While the queue is not empty:
* Dequeue a vertex $u$ and add it to our sorted list.
* For each neighbor $v$ of $u$ (the classes that depended on $u$):
* Decrement the In-Degree of $v$ by 1.
* If $v$'s In-Degree becomes `0`, push it into the queue.




4. If the final sorted list does not contain all vertices in the graph, it means the graph has a **cycle**, and topological sorting was impossible.

### C++ Code for Kahn's Algorithm

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <queue>

bool topologicalSort(int V, const std::vector<std::list<int>>& adjList, std::vector<int>& order) {
    std::vector<int> inDegree(V, 0);

    // Step 1: Calculate In-Degrees
    for (int u = 0; u < V; u++) {
        for (int v : adjList[u]) {
            inDegree[v]++;
        }
    }

    // Step 2: Queue up all vertices with In-Degree of 0
    std::queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // Step 3: Process the queue
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adjList[u]) {
            inDegree[v]--; // u is resolved, so v has one less dependency
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Step 4: Check for cycles
    return order.size() == static_cast<size_t>(V);
}

```

* **Time Complexity:** **$O(V + E)$** because it behaves exactly like a standard BFS.
* **Auxiliary Space Complexity:** **$O(V)$** to store the in-degree array and the queue.

---

## 4. Weighted Graphs

In a **Weighted Graph**, each edge is assigned a numerical value called a **weight**. This weight can represent physical distance, cost, delay, capacity, or any other metric associated with traversing that edge.

### How to Represent Weights in C++

To represent weights, we need to transition our data structures from holding plain integers to holding pairs or custom structs.

#### Weighted Adjacency Matrix

Instead of storing `1` for an edge and `0` for no edge, we store the actual weight.

* To represent the lack of a connection, we use a special value (like `-1` or `std::numeric_limits<int>::max()`), because a `0` could be a valid edge weight.

```cpp
// Representing a grid of weights
std::vector<std::vector<int>> weightedMatrix(V, std::vector<int>(V, -1));

```

#### Weighted Adjacency List

Instead of storing a list of integers, each element in the neighbor list becomes a pair: `std::pair<int, int>`, where the first value is the destination vertex, and the second is the weight of the edge.

```cpp
#include <vector>
#include <list>
#include <utility> // For std::pair

class WeightedGraph {
private:
    int numVertices;
    // Each element in the list is a pair: {destination, weight}
    std::vector<std::list<std::pair<int, int>>> adjList;

public:
    WeightedGraph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    void addWeightedEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        // adjList[v].push_back({u, weight}); // Include this line if undirected!
    }
};

```

---

## Summary of Graph Varieties

| Graph Variant | Edge Direction | Uses Weights? | Constraints | Best Real-World Use Case |
| --- | --- | --- | --- | --- |
| **Digraph** | Directed (One-way) | No | None | Hyperlink structures, web scrapers. |
| **DAG** | Directed (One-way) | No | **No cycles allowed** | Project management schedules, compilers. |
| **Weighted Graph** | Directed or Undirected | **Yes** | None | Road networks, network routing paths. |

---

Next up, we will tackle the final set of notes in our Graph unit: **Greedy Algorithms** and how we can use them to find the absolute shortest path through a weighted graph using **Dijkstra's Algorithm**.
