# Binary Trees

In computer science, a tree is a data structure which has a single root node. Each node can have many children, but only one parent. The root is the only node in the tree which does not have any children. A binary tree is a type of tree where every node has at most two children. Other types of trees will be discussed in later sections. For now, we'll consider the binary tree. 

## Data
A binary tree can be implemented using an array/vector or using nodes and pointers, like a linked list. Binary trees are used to store data with some additional constraint on the tree. Binary search trees, for example, insert smaller values to the left, and higher values to the right. 

## Operations 
Binary trees support insertion and removal of elements. The other operations depend on the purpose of the tree.
### Binary Search Trees
The main goal of a binary search tree is to offer a faster find operation than is available for a list, at the cost of a more expensive insertion and removal. To achieve this, elements are inserted recursively, starting at the root. If the element is less than the root, the element is inserted to the left of the root. Otherwise, it is inserted to the right. This continues until reaching a null (empty) node. At that point, the element is inserted:
```
operation bst_insert(element, node):
    if node == null:
        node.data = element
        node.left = null
        node.right = null
        return

    if element < node.data:
        bst_insert(element, node.left)
    else:
        bst_insert(element, node.right)
```
Now, we can look at the pseudocode for the find operation:
```
operation bst_find(element, node) -> boolean:
    if node == null:
        return false
    if node.data == element:
        return true
    elif element < node.data:
        return bst_find(element, node.right)
    else:
        return bst_find(element, node.left)
```
### Complete Binary Tree
A complete binary tree satisfies the property that h.
