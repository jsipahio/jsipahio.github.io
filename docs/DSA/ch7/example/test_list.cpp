#include <gtest/gtest.h>
#include <string>
#include "list.hpp" // Assuming the declaration is in List.h

// Helper struct to test the Iterator's arrow (->) operator
struct Point {
    int x;
    int y;
};

// ==========================================
// 1. Constructor and Initial State Tests
// ==========================================

TEST(ListBasicTest, DefaultConstructorInitializesEmpty) {
    List<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    // On an empty list with sentinels, begin() should equal end()
    EXPECT_TRUE(list.begin() == list.end());
    EXPECT_FALSE(list.begin() != list.end());
}

// ==========================================
// 2. Insertion and Iterator Mechanics
// ==========================================

TEST(ListInsertionTest, InsertFrontMaintainsCorrectOrder) {
    List<int> list;
    list.insertFront(10);
    list.insertFront(20);
    list.insertFront(30);

    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());

    // Should be ordered: 30 -> 20 -> 10
    List<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_TRUE(it == list.end());
}

TEST(ListInsertionTest, InsertBackMaintainsCorrectOrder) {
    List<int> list;
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_EQ(list.size(), 3);

    // Should be ordered: 10 -> 20 -> 30
    List<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_TRUE(it == list.end());
}

TEST(ListIteratorTest, BiDirectionalIteration) {
    List<int> list;
    list.insertBack(1);
    list.insertBack(2);

    List<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    
    // Test decrement operator
    --it;
    EXPECT_EQ(*it, 1);
}

TEST(ListIteratorTest, ArrowOperatorOnStructure) {
    List<Point> list;
    list.insertBack(Point{5, 10});

    List<Point>::Iterator it = list.begin();
    // Test operator->
    EXPECT_EQ(it->x, 5);
    EXPECT_EQ(it->y, 10);

    // Test modification via dereference
    (*it).x = 99;
    EXPECT_EQ(it->x, 99);
}

// ==========================================
// 3. Search and Removal Operations
// ==========================================

TEST(ListSearchRemoveTest, FindReturnsCorrectIterator) {
    List<std::string> list;
    list.insertBack("apple");
    list.insertBack("banana");
    list.insertBack("cherry");

    // Successfully find item
    List<std::string>::Iterator it = list.find("banana");
    EXPECT_NE(it, list.end());
    EXPECT_EQ(*it, "banana");

    // Attempt to find non-existent item (should return end())
    List<std::string>::Iterator missingIt = list.find("dragonfruit");
    EXPECT_TRUE(missingIt == list.end());
}

TEST(ListSearchRemoveTest, RemoveMiddleElement) {
    List<int> list;
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    List<int>::Iterator it = list.find(20);
    list.remove(it);

    EXPECT_EQ(list.size(), 2);
    
    // Verify structural continuity: 10 -> 30
    List<int>::Iterator checkIt = list.begin();
    EXPECT_EQ(*checkIt, 10);
    ++checkIt;
    EXPECT_EQ(*checkIt, 30);
    ++checkIt;
    EXPECT_TRUE(checkIt == list.end());
}

TEST(ListSearchRemoveTest, RemoveOnlyElement) {
    List<int> list;
    list.insertFront(42);

    list.remove(list.begin());
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.begin() == list.end());
}

// ==========================================
// 4. Rule of Three & Mutator Safety (Deep Copy)
// ==========================================

TEST(ListCopyAssignmentTest, CopyConstructorPerformsDeepCopy) {
    List<int> original;
    original.insertBack(1);
    original.insertBack(2);

    List<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_TRUE(copy == original);

    // Deep copy confirmation: modifying copy shouldn't change original
    copy.insertBack(3);
    EXPECT_EQ(original.size(), 2);
    EXPECT_EQ(copy.size(), 3);
}

TEST(ListCopyAssignmentTest, AssignmentOperatorPerformsDeepCopy) {
    List<int> original;
    original.insertBack(100);

    List<int> assigned;
    assigned.insertBack(5); // old garbage data
    
    assigned = original; // triggers copy-and-swap
    EXPECT_EQ(assigned.size(), 1);
    EXPECT_EQ(*assigned.begin(), 100);

    // Verify isolation
    assigned.insertFront(200);
    EXPECT_FALSE(original == assigned);
}

TEST(ListCopyAssignmentTest, SwapExchangesInternalState) {
    List<int> list1;
    list1.insertBack(1);

    List<int> list2;
    list2.insertBack(10);
    list2.insertBack(20);

    list1.swap(list2);

    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(*list1.begin(), 10);

    EXPECT_EQ(list2.size(), 1);
    EXPECT_EQ(*list2.begin(), 1);
}

// ==========================================
// 5. Logical Operators
// ==========================================

TEST(ListEqualityTest, EqualityOperatorComparesElements) {
    List<int> list1;
    List<int> list2;

    // Empty matches empty
    EXPECT_TRUE(list1 == list2);

    list1.insertBack(1);
    list1.insertBack(2);

    list2.insertBack(1);
    EXPECT_FALSE(list1 == list2);

    list2.insertBack(2);
    EXPECT_TRUE(list1 == list2);
}