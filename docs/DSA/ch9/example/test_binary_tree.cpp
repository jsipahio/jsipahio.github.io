#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "binarytree.hpp" // Assuming the declaration is in BinaryTree.h

// ==========================================
// 1. Initialization and Empty State Tests
// ==========================================

TEST(BinaryTreeBasicTest, DefaultConstructorInitializesEmpty) {
    BinaryTree<int> tree;
    
    // An empty tree should not contain elements
    EXPECT_FALSE(tree.contains(10));
    
    // Traversals on an empty tree should yield empty output
    std::stringstream ss;
    tree.printInorder(ss);
    EXPECT_EQ(ss.str(), "");
}

// ==========================================
// 2. Insertion and Search (Contains)
// ==========================================

TEST(BinaryTreeOperationsTest, InsertAndContains) {
    BinaryTree<int> tree;
    
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    // Verify presence
    EXPECT_TRUE(tree.contains(50));
    EXPECT_TRUE(tree.contains(30));
    EXPECT_TRUE(tree.contains(70));
    
    // Verify absence
    EXPECT_FALSE(tree.contains(100));
}

// ==========================================
// 3. Tree Traversal & Shape Verification
// ==========================================

// This test creates a deterministic BST structure:
//        50
//       /  \
//     30    70
//    /  \  /  \
//   20  40 60  80
TEST(BinaryTreeTraversalTest, VerifiesTreeStructureAndOrder) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Test Inorder Traversal (Should always be sorted for a BST)
    std::stringstream ssInorder;
    tree.printInorder(ssInorder);
    // Assumes your implementation separates values with spaces/newlines. 
    // Read individual tokens to keep tests agnostic to exact layout whitespace.
    int v1, v2, v3, v4, v5, v6, v7;
    ssInorder >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7;
    EXPECT_EQ(v1, 20); EXPECT_EQ(v2, 30); EXPECT_EQ(v3, 40);
    EXPECT_EQ(v4, 50); EXPECT_EQ(v5, 60); EXPECT_EQ(v6, 70); EXPECT_EQ(v7, 80);

    // Test Preorder Traversal (Root -> Left -> Right)
    std::stringstream ssPreorder;
    tree.printPreorder(ssPreorder);
    ssPreorder >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7;
    EXPECT_EQ(v1, 50); EXPECT_EQ(v2, 30); EXPECT_EQ(v3, 20);
    EXPECT_EQ(v4, 40); EXPECT_EQ(v5, 70); EXPECT_EQ(v6, 60); EXPECT_EQ(v7, 80);

    // Test Postorder Traversal (Left -> Right -> Root)
    std::stringstream ssPostorder;
    tree.printPostorder(ssPostorder);
    ssPostorder >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7;
    EXPECT_EQ(v1, 20); EXPECT_EQ(v2, 40); EXPECT_EQ(v3, 30);
    EXPECT_EQ(v4, 60); EXPECT_EQ(v5, 80); EXPECT_EQ(v6, 70); EXPECT_EQ(v7, 50);
}

// ==========================================
// 4. Node Removal Logic
// ==========================================

TEST(BinaryTreeRemovalTest, RemoveLeafNode) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    
    tree.remove(30); // Leaf node removal
    EXPECT_FALSE(tree.contains(30));
    EXPECT_TRUE(tree.contains(50));
}

TEST(BinaryTreeRemovalTest, RemoveNodeWithOneChild) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20); // 30 has only one left child (20)

    tree.remove(30); 
    EXPECT_FALSE(tree.contains(30));
    EXPECT_TRUE(tree.contains(20)); // 20 should bypass up to be connected to 50
    EXPECT_TRUE(tree.contains(50));
}

TEST(BinaryTreeRemovalTest, RemoveNodeWithTwoChildren) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Removing root node (50) which has two distinct subtrees
    tree.remove(50);
    EXPECT_FALSE(tree.contains(50));
    
    // Remaining elements must survive structurally intact
    EXPECT_TRUE(tree.contains(30));
    EXPECT_TRUE(tree.contains(70));
    EXPECT_TRUE(tree.contains(60));
    EXPECT_TRUE(tree.contains(80));
}

// ==========================================
// 5. Deep Copy, Copy Assignment, and Swap
// ==========================================

TEST(BinaryTreeCopyAssignmentTest, CopyConstructorPerformsDeepCopy) {
    BinaryTree<std::string> original;
    original.insert("M");
    original.insert("A");
    original.insert("Z");

    BinaryTree<std::string> copy(original);
    
    // Content matches
    EXPECT_TRUE(copy.contains("M"));
    EXPECT_TRUE(copy.contains("A"));
    EXPECT_TRUE(copy.contains("Z"));

    // Deep Copy Validation: mutations to the copy must not alter original state
    copy.remove("A");
    EXPECT_FALSE(copy.contains("A"));
    EXPECT_TRUE(original.contains("A")); // Original remains completely untouched
}

TEST(BinaryTreeCopyAssignmentTest, AssignmentOperatorReplacesState) {
    BinaryTree<int> original;
    original.insert(100);

    BinaryTree<int> assigned;
    assigned.insert(5);
    assigned.insert(2);

    assigned = original; // Triggers pass-by-value copy and swap pipeline

    EXPECT_TRUE(assigned.contains(100));
    EXPECT_FALSE(assigned.contains(5));  // Old values should be deleted completely
    EXPECT_FALSE(assigned.contains(2));

    // Confirm absolute pointer separation
    assigned.insert(200);
    EXPECT_FALSE(original.contains(200));
}

TEST(BinaryTreeCopyAssignmentTest, SwapSwitchesInternalRoots) {
    BinaryTree<int> t1;
    t1.insert(10);

    BinaryTree<int> t2;
    t2.insert(99);
    t2.insert(88);

    t1.swap(t2);

    // Elements swapped successfully
    EXPECT_TRUE(t1.contains(99));
    EXPECT_TRUE(t1.contains(88));
    EXPECT_FALSE(t1.contains(10));

    EXPECT_TRUE(t2.contains(10));
    EXPECT_FALSE(t2.contains(99));
}
