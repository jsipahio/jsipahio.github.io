# Graphs and Graph Representations

# Lecture Notes: Introduction to Graphs & Implementation Strategies

So far in this course, we have looked at linear data structures (like arrays and linked lists) and hierarchical data structures (like trees). While trees are excellent for representing parent-child relationships, they have a strict rule: a node can only have one parent, and there can be no cycles.

But what if we need to represent data that is interconnected in a more complex, web-like way?

* A social network where friends are connected to multiple other friends.
* A map of cities connected by highways.
* The internet, where webpages link back and forth to each other.

To model these systems, we use a highly flexible and powerful data structure called a **Graph**.

---

## 1. Core Graph Concepts and Vocabulary

Before we write any code, we need to speak the language of graphs. A graph is mathematically defined as a collection of two sets: $G = (V, E)$.

* **Vertices ($V$):** The individual data nodes or points in the graph (singular: **Vertex**). These are often also called **nodes**.
* **Edges ($E$):** The connections or links between the vertices.

### Key Properties of Graphs

Depending on the problem you are solving, edges can have different behaviors:

#### Directed vs. Undirected

* **Undirected Graph:** Edges have no direction. If there is a connection between Vertex A and Vertex B, you can travel freely in both directions. (Example: A Facebook friendship is mutual).
* **Directed Graph (Digraph):** Edges have arrows indicating a one-way direction. An edge from A to B does *not* mean you can travel from B to A. (Example: A Twitter/X follow, or a hyperlink from one webpage to another).

#### Weighted vs. Unweighted

* **Unweighted Graph:** Edges simply represent the existence of a connection. All connections are equal.
* **Weighted Graph:** Edges have a numerical "weight" or "cost" associated with them. (Example: On a map graph, the weight of an edge might represent the physical distance in miles or travel time between two cities).

#### Cyclic vs. Acyclic

* **Cycle:** A path that starts at a vertex, travels along edges, and ends up back at the same vertex.
* **Acyclic Graph:** A graph that contains absolutely no cycles.

---

## 2. The Graph Abstract Data Type (ADT)

If we were to design a generic interface (or abstract class) for a Graph in C++, what essential operations must it support? At a minimum, a Graph ADT must allow us to manipulate vertices and edges:

### Core Operations:

* `addVertex(value)`: Inserts a new vertex into the graph.
* `addEdge(u, v)`: Creates an edge connecting vertex `u` to vertex `v`.
* `removeVertex(v)`: Removes a vertex and all edges connected to it.
* `removeEdge(u, v)`: Removes the edge between `u` and `v`.
* `isAdjacent(u, v)`: Returns `true` if there is an edge pointing from `u` to `v`.
* `getNeighbors(v)`: Returns a list of all vertices directly connected to `v`.

---

## 3. Graph Implementation Strategies

How do we actually store this web of nodes and connections in computer memory using C++? There are three classic implementation strategies: **Adjacency Matrix**, **Adjacency List**, and **Edge List**.

To compare them, let's assume we have a graph with **$V$** vertices and **$E$** edges.

---

### Strategy A: Adjacency Matrix

An **Adjacency Matrix** is a 2D grid (a matrix) of size $V \times V$.

* The rows represent the starting vertices, and the columns represent the destination vertices.
* If there is an edge from row `i` to column `j`, we store a `1` (or the edge's weight) at `matrix[i][j]`. Otherwise, we store a `0` (or infinity/null for weighted graphs).

#### C++ Concept Code

```cpp
class GraphMatrix {
private:
    int numVertices;
    std::vector<std::vector<int>> matrix;

public:
    GraphMatrix(int vertices) : numVertices(vertices) {
        matrix.resize(vertices, std::vector<int>(vertices, 0));
    }

    void addEdge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1; // If undirected, set both directions!
    }

    bool isAdjacent(int u, int v) {
        return matrix[u][v] == 1;
    }
};

```

* **Pros:** * Incredibly fast to check if an edge exists between two specific vertices: `isAdjacent(u, v)` is a simple lookup at `matrix[u][v]`, taking **$O(1)$** constant time.
* Easy to implement.


* **Cons:**
* **Memory Waste:** It always uses **$O(V^2)$** memory. If you have 10,000 vertices but only 5,000 edges, you are allocating a $10,000 \times 10,000$ matrix (100 million entries!) just to store 5,000 connections. This is called a **sparse graph**.
* Finding the neighbors of a vertex takes **$O(V)$** time because you have to scan an entire row of the matrix.



---

### Strategy B: Adjacency List

Instead of allocating a massive grid, an **Adjacency List** associates each vertex with a list (like a dynamic array or linked list) containing only its actual neighbors.

* We use an array/vector of size $V$.
* Index `i` of this array points to a list of all vertices that vertex `i` has an edge to.

#### C++ Concept Code

```cpp
#include <vector>
#include <list>

class GraphList {
private:
    int numVertices;
    std::vector<std::list<int>> adjList; // An array of linked lists

public:
    GraphList(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // If undirected
    }

    std::list<int> getNeighbors(int u) {
        return adjList[u]; // Instant access to u's actual neighbors
    }

    bool isAdjacent(int u, int v) {
        // Must search u's neighbor list
        for (int neighbor : adjList[u]) {
            if (neighbor == v) return true;
        }
        return false;
    }
};

```

* **Pros:**
* **Highly Space-Efficient:** It only takes **$O(V + E)$** memory. We only allocate memory for actual connections.
* Finding the neighbors of a vertex is incredibly fast—we just read the existing list.


* **Cons:**
* Checking `isAdjacent(u, v)` is slower. We must traverse the list of `u`'s neighbors to see if `v` is in there, which takes **$O(degree(u))$** time (where degree is the number of neighbors `u` has). In the worst case, this is $O(V)$.



---

### Strategy C: Edge List

The simplest implementation of all is the **Edge List**. This is simply a collection (like a vector) of pairs containing the start and end of every edge in the graph.

```cpp
struct Edge {
    int source;
    int destination;
    int weight; // Optional
};

std::vector<Edge> edgeList;

```

* **Pros:** Extremely simple; uses only $O(E)$ memory.
* **Cons:** Doing almost *any* operation (finding neighbors, checking adjacency) requires a brute-force scan of the entire list, taking **$O(E)$** time. It is rarely used for general graph operations but is useful for specific algorithms we will see later in the semester (like Kruskal's algorithm).

---

## 4. Operation Complexity Comparison

When choosing how to implement a graph, you must weigh the tradeoffs based on the density of your graph.

* **Dense Graph:** The number of edges is close to the maximum possible ($E \approx V^2$).
* **Sparse Graph:** The number of edges is much smaller ($E \approx V$). Real-world graphs (like mapping roads or social networks) are almost always sparse.

| Operation | Adjacency Matrix | Adjacency List | Edge List |
| --- | --- | --- | --- |
| **Space Complexity** | $O(V^2)$ | **$O(V + E)$** | **$O(E)$** |
| **Add Vertex** | $O(V^2)$ (must resize matrix) | **$O(1)$** (push back to list) | $O(1)$ |
| **Add Edge** | **$O(1)$** | **$O(1)$** | $O(1)$ |
| **Remove Vertex** | $O(V^2)$ | $O(V + E)$ | $O(E)$ |
| **Remove Edge** | **$O(1)$** | $O(V)$ | $O(E)$ |
| **Query: `isAdjacent(u,v)**` | **$O(1)$** | $O(V)$ (average case is much faster) | $O(E)$ |
| **Query: `getNeighbors(u)**` | $O(V)$ | **$O(degree(u))$** | $O(E)$ |

> **Rule of Thumb for Students:** Unless your graph is incredibly small or so dense that almost every node connects to every other node, **prefer the Adjacency List**. It is the standard, go-to representation for most practical applications.

---

Next, we will discuss how to traverse these graph structures to find paths using Breadth-First Search (BFS) and Depth-First Search (DFS).
