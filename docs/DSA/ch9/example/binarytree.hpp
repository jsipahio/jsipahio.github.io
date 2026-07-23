#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>

template <typename T>
struct TreeNode {
    TreeNode<T> *left;
    TreeNode<T> *right;
    T data;
};

template <typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        deleteTree(root);
    }
    BinaryTree(const BinaryTree& other) : root(nullptr) {
        createTree(other.root);
    }
    BinaryTree& operator=(BinaryTree rhs) {
        swap(rhs);
        return *this;
    }
    void swap(BinaryTree &other) {
        TreeNode<T> *tempRoot = root;
        root = other.root;
        other.root = tempRoot;
    }

    void insert(T data) {
        // call the internal, recursive insert
        insert(data, root);
    }

    void remove(T data) {
        // call the internal, recursive remove
        remove(data, root);
    }

    bool contains(T data) const {
        // call the internal, recursive contains
        return contains(data, root);
    }

    void printPreorder(std::ostream &out) const {
        printPreorder(out, root);
    }
    void printInorder(std::ostream &out) const {
        printInorder(out, root);
    }
    void printPostorder(std::ostream &out) const {
        printPostorder(out, root);
    }


private:
    TreeNode<T> *root;
    // recursive function to create a copy of a tree 
    // using preorder traversal. required for the copy constructor
    void createTree(const TreeNode<T> *other) {
        // creating a tree requires a preorder traversal,
        // creating a copy of the left subtree, then the right

        // if the current node is null, don't do anything
        if (other == nullptr) return;
        // insert the data into tree
        insert(other->data);
        // create the left subtree
        if (other->left) createTree(other->left);
        // create the right subtree
        if (other->right) createTree(other->right);
    }
    // recursive function to delete nodes using postorder
    // traversal. needed for the destructor
    void deleteTree(TreeNode<T> *r) {
        // deleting a tree requires a postorder traversal
        // recursively delete left subtrees, then right

        // return if current node is null (nothing to do)
        if (r == nullptr) return;
        // delete the left tree first
        if (r->left) deleteTree(r->left);
        // then delete the right tree
        if (r->right) deleteTree(r->right);
        // delete the current node
        delete r;
    }
    // internal recursive function to insert a key to the tree
    void insert(T data, TreeNode<T> *n) {
        // handle the case where the root is null (empty tree)
        if (root == nullptr) {
            root = new TreeNode<T>;
            root->data = data;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
        // if the data is equal, don't do anything (no duplicate keys)
        if (n->data == data) {
            return;
        }
        // if the data is less than the current node's data
        // insert to the left of the current node
        if (data < n->data && n->left != nullptr) {
            insert(data, n->left);
        }
        else if (data < n->data) {
            n->left = new TreeNode<T>;
            n->left->data = data;
            n->left->left = nullptr;
            n->left->right = nullptr;
        }
        // otherwise, it goes to the right
        else if (data > n->data && n->right != nullptr) {
            insert(data, n->right);
        }
        else {
            n->right = new TreeNode<T>;
            n->right->data = data;
            n->right->left = nullptr;
            n->right->right = nullptr;
        }
    }
    // internal recursive function to delete a node
    void remove(T data, TreeNode<T>* &n) {
        // Case 0: Element not found in the tree
        if (n == nullptr) return;

        // Phase 1: Search for the node containing the target data
        if (data < n->data) {
            remove(data, n->left);
        } 
        else if (data > n->data) {
            remove(data, n->right);
        } 
        // Phase 2: Target found! (data == n->data)
        else {
            // Case 1 & 2: Leaf node OR Node with only one child (Right child only)
            if (n->left == nullptr) {
                TreeNode<T> *temp = n;
                n = n->right; // Modifies the actual parent pointer to point to the right child
                delete temp;
            }
            // Case 2: Node with only one child (Left child only)
            else if (n->right == nullptr) {
                TreeNode<T> *temp = n;
                n = n->left;  // Modifies the actual parent pointer to point to the left child
                delete temp;
            }
            // Case 3: Node with two children
            else {
                // Find the inorder successor (smallest node in the right subtree)
                TreeNode<T> *successor = n->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                
                // Overwrite the current node's data with the successor's data
                n->data = successor->data;
                
                // Recursively remove the successor value from the right subtree.
                // This safely unlinks the old node and handles its right child if it had one!
                remove(n->data, n->right);
            }
        }
    }

    // internal recursive function to determine if a value exists in the tree
    bool contains(T data, const TreeNode<T> *n) const {
        if (n == nullptr) return false;
        if (n->data == data) return true;
        if (data < n->data) return contains(data, n->left);
        else return contains(data, n->right);
    }
    // internal recursive function to perform preorder traversal
    void printPreorder(std::ostream& out, const TreeNode<T> *n) const {
        if (n == nullptr) return;

        out << n->data << std::endl;
        printPreorder(out, n->left);
        printPreorder(out, n->right);
    }
    // internal recursive function to perform inorder traversal
    void printInorder(std::ostream& out, const TreeNode<T> *n) const {
        if (n == nullptr) return;

        printInorder(out, n->left);
        out << n->data << std::endl;
        printInorder(out, n->right);
    }
    // internal recursive function to perform postorder traversal
    void printPostorder(std::ostream& out, const TreeNode<T> *n) const {
        if (n == nullptr) return;

        printPostorder(out, n->left);
        printPostorder(out, n->right);
        out << n->data << std::endl;
    }
};

#endif