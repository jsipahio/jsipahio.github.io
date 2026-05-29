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

    bool contains(T data) {
        // call the internal, recursive contains
        return contains(data, root);
    }

    void printPreorder(std::ostream &out) {
        printPreorder(out, root);
    }
    void printInorder(std::ostream &out) {
        printInorder(out, root);
    }
    void printPostorder(std::ostream &out) {
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
        // if the node is null, we've reached the 
        // boundary of the tree and can create a new node 
        if (n == nullptr) {
            n = new TreeNode<T>;
            n->data = data;
            n->left = nullptr;
            n->right = nullptr;
            return;
        }
        // if the data is equal, don't do anything (no duplicate keys)
        if (n->data == data) return;
        // if the data is less than the current node's data
        // insert to the left of the current node
        if (data < n->data) insert(data, n->left);
        // otherwise, it goes to the right
        else insert(data, n->right);
    }
    // internal recursive function to delete a node
    void remove(T data, TreeNode<T> *n) {
        // value not found, return
        if (n == nullptr) return;

        // we need to be aware of the parent
        
    }
    // internal recursive function to determine if a value exists in the tree
    bool contains(T data, TreeNode<T> *n) {
        if (n == nullptr) return false;
        if (n->data == data) return true;
        if (data < n->data) return contains(data, n->left);
        else return contains(data, n->right);
    }
    // internal recursive function to perform preorder traversal
    void printPreorder(std::ostream& out, TreeNode<T> *n) {
        if (n == nullptr) return;

        out << n->data << std::endl;
        printPreorder(n->left);
        printPreorder(n->right);
    }
    // internal recursive function to perform inorder traversal
    void printInorder(std::ostream& out, TreeNode<T> *n) {
        if (n == nullptr) return;

        printPreorder(n->left);
        printPreorder(n->right);
        out << n->data << std::endl;
    }
    // internal recursive function to perform postorder traversal
    void printPostorder(std::ostream& out, TreeNode<T> *n) {
        if (n == nullptr) return;

        printPreorder(n->left);
        printPreorder(n->right);
        out << n->data << std::endl;
    }
};

#endif