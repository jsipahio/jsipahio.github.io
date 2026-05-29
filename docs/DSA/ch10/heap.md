<style>
    .math { font: "cambria-math", "cambria", "times-new-roman", "sans-serif", font-style: italic}
</style>
# Heap, Priority Queue, and Heap Sort

A heap is a data structure (not to be confused with the heap memory discussed in Chapter 3) that stores weighted objects in a tree. Most of the time when discussing heaps, we are referring to a binary heap that is implemented as a binary tree. Heaps need to satisfy two properties:
1. Heap Order: The first property is that the for every node, that node's weight is greater than (or less than) the weight of its parent. The choice of whether to order based on less than or greater than is arbitrary. From now on, we'll assume that we've chosen to implement the heap with the minimum element as the root, and higher weight elements will appear lower in the tree. 
2. Complete Binary Tree: The other property it must satisfy is its shape property: a heap must be a complete binary tree. Figure 1 displays a complete binary tree. Mathematically, a complete binary tree satisfies this condition:
- Let <span class="math">h</span> be the height of the tree.
- For <span class="math">i = 0, ..., h - 1</span> there are <span class="math">2<sup>i</sup></span> nodes of depth i
- For nodes at depth <span class="math">h - 1</span> all internal nodes (nodes with values) are to the left of external nodes (nodes that are null)

As you can see from figure 1, this means that a complete binary tree fills out each row from left to right before starting a new row of nodes. This is another strategy to create a balanced tree, like the AVL and red-black trees discussed in the last chapter.

## Data
A heap uses a binary tree to store weighted values. The values may be weighted themselves, or the values may actually be (key, value) pairs that use the key for a weight. The heap must also have a way to compare the values (or keys) being inserted. First, let's discuss a total order.
### Total Order
A total order is a mathematic formalization for relationships that behave like less than or equal to. Total order relationships are represented by the less than or equal to sign &le;, although the actual relationship between to elements can be anything that satisfies the following four properties:
1. Reflexive: x &le; x
2. Symmetric: If x &le; y and y &le; x, then x = y
3. Transitive: If x &le; y and y &le; z, then x &le; z
4. Totality: For all x, y in the collection of elements, x &le; y or y &le; x

## Operations
For external clients of the heap, the heap should support insertion of a new element of the heap. Heaps are like stacks and queues where you can only remove one item at a time. Since heaps are ordered by the weight of its elements, the element that is removed from the heap first is the one with the lowest weight. Of course, the general `size()`, `empty()`, and comparison functions we've been implementing for the other data structures should be included for heap as well.  
Internally, the heap requires two operations to to ensure the tree stays balanced when inserting or removing an element. When inserting an element to the heap, we initially ignore where the element should go. We simply place it into the next open node location in the heap. Then, we perform an operation that swaps nodes until the newly inserted element is in its correct location. This is called `upheap()` or `reheapup()`. This is since every element is placed into the bottom of the tree initially, and needs to move up to its correct location. Next, remember that we can only ever remove the root of the heap. When removing the root, we swap it with the last element in the tree to ensure that the tree stays balanced and maintains its completeness. However, this is likely not the smallest element in the heap. Therefore, we need to perform an operation to swap nodes until the lowest weight element is in the root. To do so, we compare the new root with its children, and swap it with any child that has a lower weight than it. This continues until the new root has moved to its correct location. Due to the heap order property, the first swap will put the correct element into the root. Since the element that initially replaced the root is moving down the tree, this operation is commonly referred to as `downheap()` or `reheapdown()`. 

## Rules
As stated in the section on the data stored by a heap, the data type of the elements (or the elements' weights) must have a comparison defined for it that will satisfy a total order. Like all other containers, you cannot perform a removal operation on an empty heap. Internally, the heap must satisfy the two heap properties, although this is an internal implementation detail and not a concern to clients. As far as clients are concerned, the `remove()` or `pop()` method will always return the lowest weight element in the heap. 

## Pseudocode and Complexity Analysis
The main operations that take time for heap are `insert()` and `remove()` (and really, it's the `upheap()` and `downheap()` that take time). The other operations can all be implemented in constant time. First, we'll look at the pseudocode for `insert()` and `upheap()`. We are going to assume that we maintain a pointer to the next available node to insert an element at.

```
operation insert(value):
    last_inserted = get_next_available_node(value)
    upheap(last_inserted)

operation upheap(node):
    if !(node.parent.value < node.value):
        swap(node, node.parent)
        upheap(node)
    else:
        return

operation get_next_available_node(value):
    # first, last inserted is a left child
    # if it is, the right of the parent node is open
    # and is the next available node to be inserted
    # this is the easy case
    if last_inserted.parent.left == last_inserted
        last_inserted.parent.right = Node(value, last_inserted.parent, null, null)
        return last_inserted.parent.right

    # another easy case is if the last_inserted is the root
    if last_inserted == root:
        return root.left

    # now is where it gets tricky
    # we know that we are a right node at this point
    # it is relatively easy to find the next open location if
    # the last inserted node's parent is a left node
    # due to the complete tree property, the next open location
    # is the left child of the parent's sibling
    if last_inserted.parent.parent.left == last_inserted.parent
        last_inserted.parent.parent.right.left = Node(value, last_inserted.parent.parent.right, null, null)
        return last_inserted.parent.parent.right.left

    # at this point we've exhausted all of our simple checks an we have to go hunting
    # while we are a right node, we need to check the parent node
    # while we are internal (both children are not null), we go to the left child
    # once we find a null child, we've found the next node
    Node temp = last_inserted.parent
    while temp != null:
        if temp.parent.right = temp:
            temp = temp.parent
        elif temp.left != null and temp.right != null:
            temp = temp.left
        elif temp.left == null:
            temp.left = Node(value, temp, null, null)
            temp = temp.left
            break
        elif temp.right == null:
            temp.right = Node(value, temp, null, null)
            temp = temp.right
            break

    return temp
```

```
operation remove():
    value = root.value
    swap(root, last_inserted)
    delete_last_inserted()
    downheap(root)
    return value

operation downheap(node.value):
    if node.left.value < node.value:
        swap(node, node.left)
        downheap(node)
    elif node.right.value <= node.value:
        swap(node, node.right)
        downheap(node)
    else:
        return

operation delete_last_inserted():
    if last_inserted.parent.right != null
```

## Priority Queues
A priority queue is a modified queue that orders elements based on their priority. Rather than the oldest element being removed first, the highest priority element is removed first. 
