#include <gtest/gtest.h>
#include "stack.hpp"
#include <string>

// --- Group 1: Constructor and Initial State Tests ---

TEST(StackTest, DefaultConstructorInitializesCorrectly) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s.full());
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.capacity(), DEFAULT_MAX_STACK);
}

TEST(StackTest, CustomCapacityConstructorInitializesCorrectly) {
    size_t custom_capacity = 42;
    Stack<double> s(custom_capacity);
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s.full());
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.capacity(), custom_capacity);
}

// --- Group 2: Core Stack Operations (Push, Pop, Top) ---

TEST(StackTest, PushAndPopModifySizeAndElements) {
    Stack<int> s(5);
    
    s.push(10);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 10);

    s.push(20);
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.top(), 20);

    s.pop();
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 10);

    s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, TopReturnsModifiableReference) {
    Stack<int> s(5);
    s.push(50);
    
    // Modify the element directly via the reference returned by top()
    s.top() = 100; 
    EXPECT_EQ(s.top(), 100);
}

// --- Group 3: Exception Handling Boundary Conditions ---

TEST(StackTest, AccessingEmptyStackThrowsException) {
    Stack<std::string> s;
    
    // Verify top() and pop() throw EmptyStackAccess on an empty stack
    EXPECT_THROW(s.top(), EmptyStackAccess);
    EXPECT_THROW(s.pop(), EmptyStackAccess);
}

TEST(StackTest, ExceedingCapacityThrowsException) {
    Stack<char> s(2);
    s.push('A');
    s.push('B');
    
    EXPECT_TRUE(s.full());
    // Verify pushing onto a full stack throws FullStackAccess
    EXPECT_THROW(s.push('C'), FullStackAccess);
}

// --- Group 4: Copy Semantics (Deep Copy & Assignment) ---

TEST(StackTest, CopyConstructorPerformsDeepCopy) {
    Stack<int> original(5);
    original.push(1);
    original.push(2);

    Stack<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.capacity(), original.capacity());
    EXPECT_EQ(copy.top(), 2);

    // Modify the copy and check that the original is unaffected (Deep Copy check)
    copy.pop();
    EXPECT_EQ(copy.top(), 1);
    EXPECT_EQ(original.top(), 2); 
}

TEST(StackTest, AssignmentOperatorPerformsDeepCopy) {
    Stack<int> s1(5);
    s1.push(100);

    Stack<int> s2(2);
    s2.push(5);
    s2.push(10);

    s2 = s1; // Assignment operation
    
    EXPECT_EQ(s2.size(), 1);
    EXPECT_EQ(s2.top(), 100);
    
    // Mutate s2 to guarantee absolute isolation from s1
    s2.push(200);
    EXPECT_EQ(s1.size(), 1); 
}

// --- Group 5: Logical Operations and Modifiers ---

TEST(StackTest, EqualityOperatorComparesPairwiseRegardlessOfCapacity) {
    Stack<int> s1(5);
    Stack<int> s2(10);

    // Empty stacks should be equal
    EXPECT_TRUE(s1 == s2);

    s1.push(10);
    s1.push(20);
    EXPECT_FALSE(s1 == s2);

    s2.push(10);
    s2.push(20);
    // Same elements and order, different capacities -> Should be equal
    EXPECT_TRUE(s1 == s2);

    s2.pop();
    s2.push(99);
    // Mismatched elements -> Should not be equal
    EXPECT_FALSE(s1 == s2);
}

TEST(StackTest, SwapExchangesInternalState) {
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);

    Stack<int> s2(5);
    s2.push(10);

    s1.swap(s2);

    // s1 should now have s2's old properties
    EXPECT_EQ(s1.capacity(), 5);
    EXPECT_EQ(s1.size(), 1);
    EXPECT_EQ(s1.top(), 10);

    // s2 should now have s1's old properties
    EXPECT_EQ(s2.capacity(), 3);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.top(), 2);
}

TEST(StackTest, ResizeAdjustsCapacityAndTruncatesIfNecessary) {
    Stack<int> s(5);
    s.push(10);
    s.push(20);
    s.push(30);

    // Case 1: Upsizing
    s.resize(10);
    EXPECT_EQ(s.capacity(), 10);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.top(), 30);

    // Case 2: Downsizing below current element count (truncation expected)
    s.resize(2);
    EXPECT_EQ(s.capacity(), 2);
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.top(), 20); // The 30 should have been dropped
}
