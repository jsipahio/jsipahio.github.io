#include "set.hpp"


#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Helper function to check if a vector contains an element
template <typename T>
bool vectorContains(const std::vector<T>& vec, const T& element) {
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

// ==========================================
// 1. Constructor and Basic State Tests
// ==========================================

TEST(SetBasicTest, DefaultConstructorInitializesEmpty) {
    Set<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.keys().empty());
}

// ==========================================
// 2. Core Container Operations (Insert, Remove, Contains)
// ==========================================

TEST(SetOperationsTest, InsertElements) {
    Set<int> s;
    
    // Test successful insertions
    EXPECT_TRUE(s.insert(10));
    EXPECT_TRUE(s.insert(20));
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2);
    
    // Test duplicate insertion (should fail and not change size)
    EXPECT_FALSE(s.insert(10));
    EXPECT_EQ(s.size(), 2);
}

TEST(SetOperationsTest, ContainsElements) {
    Set<std::string> s;
    s.insert("apple");
    s.insert("banana");

    EXPECT_TRUE(s.contains("apple"));
    EXPECT_TRUE(s.contains("banana"));
    EXPECT_FALSE(s.contains("cherry"));
}

TEST(SetOperationsTest, RemoveElements) {
    Set<int> s;
    s.insert(5);
    s.insert(10);

    // Remove existing
    EXPECT_TRUE(s.remove(5));
    EXPECT_FALSE(s.contains(5));
    EXPECT_EQ(s.size(), 1);

    // Remove non-existing
    EXPECT_FALSE(s.remove(99));
    EXPECT_EQ(s.size(), 1);
}

TEST(SetOperationsTest, KeysReturnsAllElements) {
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    std::vector<int> allKeys = s.keys();
    EXPECT_EQ(allKeys.size(), 3);
    EXPECT_TRUE(vectorContains(allKeys, 1));
    EXPECT_TRUE(vectorContains(allKeys, 2));
    EXPECT_TRUE(vectorContains(allKeys, 3));
}

// ==========================================
// 3. Copy, Assignment, and Swap Tests
// ==========================================

TEST(SetCopyAssignmentTest, CopyConstructorPerformsDeepCopy) {
    Set<int> original;
    original.insert(42);
    original.insert(84);

    Set<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_TRUE(copy.contains(42));
    EXPECT_TRUE(copy.contains(84));

    // Deep copy check: modifying copy must not affect original
    copy.insert(100);
    EXPECT_FALSE(original.contains(100));
}

TEST(SetCopyAssignmentTest, AssignmentOperatorPerformsDeepCopy) {
    Set<int> original;
    original.insert(1);
    
    Set<int> assigned;
    assigned.insert(2); // populate with old data
    
    assigned = original; 
    EXPECT_EQ(assigned.size(), 1);
    EXPECT_TRUE(assigned.contains(1));
    EXPECT_FALSE(assigned.contains(2)); // Old data should be cleared

    // Deep copy check
    assigned.insert(3);
    EXPECT_FALSE(original.contains(3));
}

TEST(SetCopyAssignmentTest, SwapExchangesData) {
    Set<int> s1;
    s1.insert(1);
    s1.insert(2);

    Set<int> s2;
    s2.insert(3);

    s1.swap(s2);

    EXPECT_EQ(s1.size(), 1);
    EXPECT_TRUE(s1.contains(3));

    EXPECT_EQ(s2.size(), 2);
    EXPECT_TRUE(s2.contains(1));
    EXPECT_TRUE(s2.contains(2));
}

// ==========================================
// 4. Equality and Comparisons
// ==========================================

TEST(SetComparisonTest, EqualityOperator) {
    Set<int> s1;
    Set<int> s2;
    
    // Empty sets match
    EXPECT_TRUE(s1 == s2);

    s1.insert(10);
    s1.insert(20);
    
    s2.insert(20);
    s2.insert(10);
    
    // Order of insertion shouldn't break equality logically
    EXPECT_TRUE(s1 == s2);

    s2.insert(30);
    EXPECT_FALSE(s1 == s2);
}

// ==========================================
// 5. Method-Based Set Operations
// ==========================================

TEST(SetMathematicalMethodsTest, UnionWith) {
    Set<int> A; A.insert(1); A.insert(2);
    Set<int> B; B.insert(2); B.insert(3);

    Set<int> result = A.unionWith(B); // {1, 2, 3}
    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.contains(1));
    EXPECT_TRUE(result.contains(2));
    EXPECT_TRUE(result.contains(3));
}

TEST(SetMathematicalMethodsTest, IntersectWith) {
    Set<int> A; A.insert(1); A.insert(2);
    Set<int> B; B.insert(2); B.insert(3);

    Set<int> result = A.intersectWith(B); // {2}
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(2));
    EXPECT_FALSE(result.contains(1));
}

TEST(SetMathematicalMethodsTest, DifferenceWith) {
    Set<int> A; A.insert(1); A.insert(2);
    Set<int> B; B.insert(2); B.insert(3);

    Set<int> result = A.differenceWith(B); // Elements in A NOT in B -> {1}
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(1));
    EXPECT_FALSE(result.contains(2));
}

TEST(SetMathematicalMethodsTest, SymmetricDifferenceWith) {
    Set<int> A; A.insert(1); A.insert(2);
    Set<int> B; B.insert(2); B.insert(3);

    Set<int> result = A.symmetricDifferenceWith(B); // {1, 3}
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains(1));
    EXPECT_TRUE(result.contains(3));
    EXPECT_FALSE(result.contains(2));
}

// ==========================================
// 6. Operator-Based Set Operations
// ==========================================

TEST(SetOperatorTest, OverloadedOperators) {
    Set<int> A; A.insert(1); A.insert(2);
    Set<int> B; B.insert(2); B.insert(3);

    // Bitwise OR (|) -> Union
    Set<int> unionRes = A | B;
    EXPECT_EQ(unionRes.size(), 3);

    // Bitwise AND (&) -> Intersection
    Set<int> intersectRes = A & B;
    EXPECT_EQ(intersectRes.size(), 1);
    EXPECT_TRUE(intersectRes.contains(2));

    // Minus (-) -> Difference
    Set<int> diffRes = A - B;
    EXPECT_EQ(diffRes.size(), 1);
    EXPECT_TRUE(diffRes.contains(1));

    // Bitwise XOR (^) -> Symmetric Difference
    Set<int> symDiffRes = A ^ B;
    EXPECT_EQ(symDiffRes.size(), 2);
    EXPECT_TRUE(symDiffRes.contains(1));
    EXPECT_TRUE(symDiffRes.contains(3));
}
