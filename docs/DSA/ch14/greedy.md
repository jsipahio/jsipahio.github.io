# Lecture Notes: Greedy Algorithms & Dijkstra's Algorithm

When we face complex computational problems, finding the absolute best (optimal) solution can sometimes take an astronomical amount of time. One of the most intuitive and powerful strategies we can use to solve these problems is the **Greedy Approach**.

This week, we will demystify greedy algorithms, look at a few simple examples of where they succeed (and where they fail), and then dive deep into one of the most famous greedy algorithms in computer science: **Dijkstra's Algorithm** for finding the shortest path in a weighted graph.

---

## 1. What is a Greedy Algorithm?

The core philosophy of a greedy algorithm can be summarized in one sentence:

> **Make the choice that looks best right now, and never look back.**

At every step of the algorithm, you make a **locally optimal choice** in the hope that these step-by-step choices will lead to a **globally optimal solution**.

### The Pros:

* **Simple to design and write:** You don't have to look ahead or plan for multiple future scenarios.
* **Highly efficient:** Greedy algorithms usually run incredibly fast (often $O(n)$ or $O(n \log n)$) because they make a single pass through the data.

### The Catch:

* **They don't always work:** Because greedy algorithms are short-sighted, they can easily get trapped. They make a choice that is great in the short term, but completely locks them out of the best possible overall solution later on.

---

## 2. Classic Greedy Examples: Success vs. Failure

To understand how greedy algorithms work—and when they break down—let's look at two classic problems.

### Example A: The Coin Change Problem

Suppose you are a cashier and need to give a customer **48 cents** in change using the fewest number of coins possible.

#### The Greedy Strategy:

Always grab the largest denomination coin that is less than or equal to the remaining amount you need to make.

* **Remaining: 48¢** $\rightarrow$ Largest coin $\le 48¢$ is a **Quarter (25¢)**. (Remaining: 23¢)
* **Remaining: 23¢** $\rightarrow$ Largest coin $\le 23¢$ is a **Dime (10¢)**. (Remaining: 13¢)
* **Remaining: 13¢** $\rightarrow$ Largest coin $\le 13¢$ is a **Dime (10¢)**. (Remaining: 3¢)
* **Remaining: 3¢** $\rightarrow$ Largest coin $\le 3¢$ is a **Penny (1¢)**. (Remaining: 2¢)
* Repeat for two more Pennies.
* **Total Coins:** 1 Quarter, 2 Dimes, 3 Pennies = **6 coins**.

For standard US currency, this greedy approach is **guaranteed** to always give the optimal (fewest) number of coins.

#### Where Greedy Fails:

Imagine a fictional country where the coin denominations are **1¢, 10¢, and 12¢**. You need to make **15¢** in change.

* **Greedy Path:** 1. Take a 12¢ coin (Remaining: 3¢).
2. Take three 1¢ coins.
3. **Total: 4 coins** (`12, 1, 1, 1`).
* **The Actual Optimal Path:** * Take one 10¢ coin and five 1¢ coins? No, that's 6 coins.
* Wait, what if we didn't take the 12¢ coin? We could take no 12¢, but instead take... wait, is there a better way?
* What if we needed to make **20¢**?
* **Greedy Path:** Take a 12¢ coin $\rightarrow$ Remaining 8¢ $\rightarrow$ Take eight 1¢ coins. **Total: 9 coins** (`12` + eight `1`s).
* **Optimal Path:** Take two 10¢ coins. **Total: 2 coins** (`10, 10`).





Because the greedy algorithm blindly took the 12¢ coin first (because 12 is larger than 10), it missed the incredibly clean combination of two 10¢ coins.

---

### Example B: Activity Selection (Interval Scheduling)

Imagine you have a single classroom and 5 student clubs want to use it for meetings. Because their times overlap, you can't host all of them. You want to schedule the **maximum number of non-overlapping meetings**.

Each activity has a start time and an end time:

* Activity A: 9:00 AM - 10:30 AM
* Activity B: 10:00 AM - 11:00 AM
* Activity C: 10:30 AM - 11:30 AM
* Activity D: 11:00 AM - 12:00 PM

#### The Greedy Strategy:

To maximize the number of meetings, **always choose the next available meeting that finishes the earliest**. Why? Because finishing early leaves the room free for as long as possible for future meetings.

#### C++ Concept Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Activity {
    int start;
    int end;
};

// Sort activities based on their end times
bool compareActivities(Activity a, Activity b) {
    return a.end < b.end;
}

void selectActivities(std::vector<Activity>& activities) {
    // Step 1: Sort activities by end time
    std::sort(activities.begin(), activities.end(), compareActivities);

    std::cout << "Selected Activities: " << std::endl;

    // Step 2: The first activity always gets selected
    int i = 0;
    std::cout << "(" << activities[i].start << ", " << activities[i].end << ")\n";

    // Step 3: Loop through the rest of the activities
    for (size_t j = 1; j < activities.size(); j++) {
        // If this activity starts after or when the last selected activity ends, select it
        if (activities[j].start >= activities[i].end) {
            std::cout << "(" << activities[j].start << ", " << activities[j].end << ")\n";
            i = j; // Update the index of the last selected activity
        }
    }
}

```

This greedy approach is mathematically proven to always find the optimal schedule for this problem!

---

## 3. Dijkstra's Algorithm

Now let’s apply the greedy philosophy to graphs.

Suppose you are at Vertex $A$ in a weighted graph, and you want to find the **shortest path to every other vertex** in the network. This is known as the **Single-Source Shortest Path** problem. **Dijkstra's Algorithm** solves this using a greedy strategy.

### Why is Dijkstra's Algorithm "Greedy"?

Dijkstra maintains a list of "tentative" distances from the start node to all other nodes.
At each step, **it greedily grabs the unvisited vertex with the absolute smallest tentative distance**, locks it in as "visited," and updates the distances of its neighbors. It makes this choice because it assumes that if this is the closest unvisited node, there is no possible longer path through other nodes that could somehow wind up being shorter.

> **Crucial Rule:** Dijkstra's algorithm only works if the graph has **no negative edge weights**. If a road can have a "negative" travel time, the greedy assumption breaks down completely.

---

### How the Algorithm Works (Step-by-Step)

1. Create a `distances` array where the distance to the starting vertex is set to `0`, and the distance to all other vertices is initialized to **Infinity** ($\infty$).
2. Create a min-priority queue (min-heap) to store vertices and their current tentative distances.
3. Push the starting vertex into the priority queue with a distance of `0`.
4. While the priority queue is not empty:
* Pop the vertex $u$ with the minimum distance.
* If $u$ has already been processed, skip it. Otherwise, mark it as processed/visited.
* **Relaxation Step:** For each neighbor $v$ of $u$:
* Calculate the distance to $v$ *through* $u$:

$$\text{New Distance} = \text{Distance}(u) + \text{Weight}(u, v)$$


* If this $\text{New Distance}$ is **smaller** than the current recorded distance to $v$, update $v$'s distance and push $v$ into the priority queue with this new, shorter distance.





---

### C++ Code Implementation (Adjacency List & Priority Queue)

To implement this efficiently, we use a **Min-Priority Queue** (`std::priority_queue`). By default, C++'s priority queue is a max-heap, so we have to configure it with custom parameters to act as a min-heap.

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>

const int INF = 1e9; // Represent infinity with a very large number

// Structure to represent an edge: {destination, weight}
typedef std::pair<int, int> Edge; 

// Structure to represent an item in our Priority Queue: {distance, vertex_ID}
typedef std::pair<int, int> PQItem; 

void dijkstra(int startVertex, const std::vector<std::list<Edge>>& adjList, int V) {
    // Step 1: Initialize distances to Infinity
    std::vector<int> dist(V, INF);
    std::vector<bool> visited(V, false);

    // Min-heap Priority Queue setup
    // Greater comparison makes the smallest values bubble to the top
    std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;

    // Step 2: Initialize the start vertex
    dist[startVertex] = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        // Step 3: Greedily extract the vertex with the minimum distance
        int u = pq.top().second;
        pq.pop();

        // If we've already locked in this vertex, skip it
        if (visited[u]) continue;
        visited[u] = true;

        // Step 4: Relaxation Step
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;

            // If we found a shorter path to v through u
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v}); // Push updated distance to min-heap
            }
        }
    }

    // Print the final shortest distances
    std::cout << "Shortest distances from source vertex " << startVertex << ":\n";
    for (int i = 0; i < V; i++) {
        std::cout << "To Vertex " << i << " -> Distance: ";
        if (dist[i] == INF) std::cout << "INF (Unreachable)\n";
        else std::cout << dist[i] << "\n";
    }
}

```

---

## 4. Complexity Analysis

By utilizing a binary min-heap (via `std::priority_queue`), we make Dijkstra's algorithm incredibly performant.

* **Time Complexity:** **$O((V + E) \log V)$**
* Extracting the minimum element from the priority queue takes $O(\log V)$ time, and we do this for every vertex.
* When we relax an edge, we may need to insert a new distance into the priority queue, which also takes $O(\log V)$ time. Since we check every edge, this happens at most $E$ times.
* This is vastly superior to a naive implementation using a simple array lookup, which would run in $O(V^2)$ time.


* **Auxiliary Space Complexity:** **$O(V)$** to maintain the distances array, visited array, and the priority queue (which holds at most $V$ elements at any given time).

---

## 5. Summary: The Greedy Landscape

As we wrap up our study of graphs, keep this mental checklist of when to deploy these routing algorithms:

| Algorithm | Type | Edge Weights Allowed? | Primary Use Case | Time Complexity |
| --- | --- | --- | --- | --- |
| **BFS** | Graph Traversal | **No** (Unweighted only) | Shortest path based *strictly* on number of hops. | $O(V + E)$ |
| **Dijkstra** | Greedy | **Yes** (Non-negative weights only) | Shortest physical path (GPS, network routing). | $O((V + E) \log V)$ |

---
