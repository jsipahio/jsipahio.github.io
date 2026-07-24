# Other Types of Trees

Up to this point, we have focused heavily on Binary Trees, where every node has a maximum of two children (Left and Right). While binary trees are incredibly useful, they have two major structural vulnerabilities:

1. Some real-world data naturally splits into more than two paths.
2. A standard Binary Search Tree (BST) can become unbalanced. If you insert sorted data (e.g., 1, 2, 3, 4, 5) into a regular BST, it grows in a single straight line, degrading from a fast $O(\log n)$ tree into a slow $O(n)$  linked list.

Today, we will expand our horizons by exploring trees that branch into multiple children, as well as specialized binary trees that automatically balance themselves to guarantee an efficiency floor.

## Ternary Trees (3 Children)

A ternary tree node contains data and up to three child pointers, usually designated as **Left**, **Middle**, and **Right**.

```cpp
struct TernaryNode {
    int data;
    TernaryNode* left;
    TernaryNode* middle;
    TernaryNode* right;
};

```
Ternary Search Trees (TSTs) are widely used in spell-checkers, auto-complete systems, and IP routing tables because they combine the space-efficiency of a binary tree with the rapid prefix-searching capabilities of string-processing trees.

### $M$-ary Trees (Generic Number of Children)

An $M$-ary tree generalizes this concept further. The $M$ represents the maximum number of children any node can have. For example, a 4-ary tree can have up to 4 children, an 8-ary tree up to 8 children, and so on.

Because hardcoding individual pointer names like `left`, `right`, `middle`, `fourth`, etc., becomes messy, we implement $M$-ary nodes using a dynamic collection (like a C++ `std::vector`) of node pointers.

```cpp
#include <vector>

struct MaryNode {
    int data;
    std::vector<MaryNode*> children; // Can hold up to M child pointers
};

```
##### Applications 

* **File Systems:** Your operating system’s directory structure is a giant $M$-ary tree. A folder (node) doesn't just have a "left" and "right" subfolder; it can contain an arbitrary vector of many subfolders and files.
* **B-Trees:** Databases use massive $M$-ary trees where $M$ can be in the hundreds. This allows them to store huge amounts of data in a very "flat" tree, minimizing disk-read operations.

---

## Self-Balancing BSTs

When dealing with standard Binary Search Trees, if the tree becomes skewed (unbalanced), lookups, insertions, and deletions degrade to an $O(n)$ worst-case runtime.

To fix this, many Self-Balancing Binary Search Trees have been proposed. These trees look at their own shape during every insertion and deletion. If they detect that one side is getting too heavy, they automatically rearrange their nodes using operations called rotations to restore balance, locking the worst-case runtime at a guaranteed $O(\log n)$. This creates a performance floor, guaranteeing that runtime will never degrade to O(n).

### AVL Trees

Invented in 1962 by Adelson-Velsky and Landis, the AVL Tree was the first self-balancing BST proposed.

The core metric of an AVL tree is the Balance Factor:

$$\text{Balance Factor} = \text{Height of Left Subtree} - \text{Height of Right Subtree}$$

#### The AVL Rule:

For every single node in an AVL tree, the Balance Factor must only ever be $-1$, $0$, or $1$.

```
     50 (BF = 0)              50 (BF = 2) --> UNBALANCED!
    /  \                     /
  30    70                 30 (BF = 1)
                          /
                        20 (BF = 0)

```

If an insertion or deletion causes a node’s Balance Factor to become $-2$ or $2$, the tree triggers a rotation (either a Single Left/Right rotation, or a Double Left-Right/Right-Left rotation) to shift the nodes and pull the heavy side back up.

* **Pros:** Highly aggressive, strict balancing. Because it is perfectly balanced, looking up data (`search`) is incredibly fast.
* **Cons:** Because the balancing rules are so strict, inserting or deleting elements requires frequent, complex node rotations to keep everything perfect.

---

### Red-Black Trees

A Red-Black Tree takes a slightly different approach to balancing. Instead of tracking exact numerical heights like an AVL tree, it assigns each node a color property: Red or Black.

By enforcing a strict set of coloring rules, the tree mathematically guarantees that no path from the root to a leaf is ever more than twice as long as any other path.

#### The Red-Black Rules:

1. Every node is colored either Red or Black.
2. The root node is always Black.
3. All null pointers (empty leaves at the bottom) are considered Black.
4. No Two Red Nodes Can Be Adjacent: A Red node cannot have a Red child (Red nodes must have Black children).
5. Black Depth Rule: Every path from the root node to an empty null pointer must contain the exact same number of Black nodes.

When you insert a new element, it is initially colored Red. If this violates Rule 4 (a Red node next to a Red node), the tree fixes itself by recoloring nodes or performing *otations.

* **Pros:** The balancing requirements are more relaxed than an AVL tree. A Red-Black tree is "balanced enough" to keep performance at $O(\log n)$, but requires far fewer rotations during insertions and deletions.
* **Cons:** Lookups are slightly slower than an AVL tree because the tree can be slightly asymmetrical.

Because it handles frequent insertions and deletions gracefully while maintaining efficient lookups, the Red-Black tree is the industry standard choice for standard libraries. In C++, the backend structures of `std::map`, `std::set`, `std::multimap`, and `std::multiset` are almost always implemented as Red-Black Trees.

**Note:** The C++ STL `set` and `map` are not true sets and maps. They are ordered. The STL `unordered_set` and `unordered_map` are the true set and map that use a hash table implementation.
