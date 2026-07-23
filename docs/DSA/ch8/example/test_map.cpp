#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include "map.hpp" // Assuming the declaration is in Map.h

// Helper to look up keys inside std::vector<Key>
template <typename T>
bool vectorContains(const std::vector<T>& vec, const T& element) {
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

// Helper to look up key-value pairs inside std::vector<std::pair<K, V>>
template <typename K, typename V>
bool pairsContains(const std::vector<std::pair<K, V>>& vec, const K& key, const V& value) {
    auto pair = std::make_pair(key, value);
    return std::find(vec.begin(), vec.end(), pair) != vec.end();
}

// ==========================================
// 1. Initialization and Core State
// ==========================================

TEST(MapBasicTest, DefaultConstructorState) {
    Map<std::string, int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
    EXPECT_EQ(m.numBuckets(), 127); // Default template value
    EXPECT_TRUE(m.keys().empty());
    EXPECT_TRUE(m.pairs().empty());
}

// ==========================================
// 2. Insertion, Containment, and Removal
// ==========================================

TEST(MapOperationsTest, InsertVariants) {
    Map<int, std::string> m;

    // Test standard insert(key, value)
    EXPECT_TRUE(m.insert(1, "One"));
    EXPECT_EQ(m.size(), 1);
    
    // Test duplicate insertion (should fail, non-destructive)
    EXPECT_FALSE(m.insert(1, "Uno")); 
    EXPECT_EQ(m.size(), 1);

    // Test pair overload insert(std::pair)
    std::pair<int, std::string> kvPair(2, "Two");
    EXPECT_TRUE(m.insert(kvPair));
    EXPECT_EQ(m.size(), 2);
}

TEST(MapOperationsTest, ContainsAndRemove) {
    Map<std::string, double> m;
    m.insert("pi", 3.14);
    m.insert("e", 2.71);

    EXPECT_TRUE(m.contains("pi"));
    EXPECT_FALSE(m.contains("golden_ratio"));

    // Successful removal
    EXPECT_TRUE(m.remove("pi"));
    EXPECT_FALSE(m.contains("pi"));
    EXPECT_EQ(m.size(), 1);

    // Unsuccessful removal of non-existent key
    EXPECT_FALSE(m.remove("golden_ratio"));
    EXPECT_EQ(m.size(), 1);
}

// ==========================================
// 3. Element Access via at() & Subscript []
// ==========================================

TEST(MapAccessTest, MutableAndConstAtMethod) {
    Map<int, std::string> m;
    m.insert(10, "Ten");

    // Mutable reference read/write
    m.at(10) = "Ten Modified";
    EXPECT_EQ(m.at(10), "Ten Modified");

    // Const reference check
    const Map<int, std::string>& constMap = m;
    EXPECT_EQ(constMap.at(10), "Ten Modified");
}

TEST(MapAccessTest, SubscriptOperatorBehaviors) {
    Map<std::string, int> m;
    m.insert("Existing", 100);

    // Reading/Writing existing elements
    m["Existing"] = 200;
    EXPECT_EQ(m["Existing"], 200);

    // Mutable subscript auto-inserts missing key
    EXPECT_EQ(m.size(), 1);
    m["NewKey"] = 500; // Trigger auto-insertion
    EXPECT_EQ(m.size(), 2);
    EXPECT_TRUE(m.contains("NewKey"));
    EXPECT_EQ(m["NewKey"], 500);
}

// ==========================================
// 4. Death Tests (Program Abort Verification)
// ==========================================

TEST(MapDeathTest, AtThrowsOrAbortsOnMissingKey) {
    Map<int, std::string> m;
    const Map<int, std::string>& constMap = m;

    // ".*" regex matches any error message prior to termination / crash
    EXPECT_DEATH(m.at(99), ".*");
    EXPECT_DEATH(constMap.at(99), ".*");
}

TEST(MapDeathTest, ConstSubscriptAbortsOnMissingKey) {
    Map<int, std::string> m;
    const Map<int, std::string>& constMap = m;

    EXPECT_DEATH(constMap[99], ".*");
}

// ==========================================
// 5. Deep Copy, Copy Assignment, and Swap
// ==========================================

TEST(MapCopyAssignmentTest, DeepCopyConstructor) {
    Map<std::string, int> original;
    original.insert("A", 1);
    original.insert("B", 2);

    Map<std::string, int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_TRUE(copy == original);

    // Confirm Deep Copy: altering copy does not infect the original
    copy.insert("C", 3);
    EXPECT_FALSE(original.contains("C"));
}

TEST(MapCopyAssignmentTest, DeepCopyAssignment) {
    Map<std::string, int> original;
    original.insert("KeepMe", 42);

    Map<std::string, int> assigned;
    assigned.insert("OldGarbage", 999);

    assigned = original; // Triggers pass-by-value copy and swap
    EXPECT_EQ(assigned.size(), 1);
    EXPECT_TRUE(assigned.contains("KeepMe"));
    EXPECT_FALSE(assigned.contains("OldGarbage")); // Cleaned up properly

    // Validate Isolation
    assigned.insert("Isolate", 7);
    EXPECT_FALSE(original.contains("Isolate"));
}

TEST(MapCopyAssignmentTest, ConstantTimeSwap) {
    Map<int, char> m1;
    m1.insert(1, 'X');

    Map<int, char> m2;
    m2.insert(2, 'Y');
    m2.insert(3, 'Z');

    m1.swap(m2);

    EXPECT_EQ(m1.size(), 2);
    EXPECT_TRUE(m1.contains(2));

    EXPECT_EQ(m2.size(), 1);
    EXPECT_TRUE(m2.contains(1));
}

// ==========================================
// 6. Bulk Vector Retrieval and Comparison
// ==========================================

TEST(MapBulkDataTest, KeysAndPairsExtraction) {
    Map<std::string, int> m;
    m.insert("Alpha", 10);
    m.insert("Beta", 20);

    // Extracting key vector
    std::vector<std::string> allKeys = m.keys();
    EXPECT_EQ(allKeys.size(), 2);
    EXPECT_TRUE(vectorContains(allKeys, std::string("Alpha")));
    EXPECT_TRUE(vectorContains(allKeys, std::string("Beta")));

    // Extracting pair vector
    auto allPairs = m.pairs();
    EXPECT_EQ(allPairs.size(), 2);
    EXPECT_TRUE(pairsContains(allPairs, std::string("Alpha"), 10));
    EXPECT_TRUE(pairsContains(allPairs, std::string("Beta"), 20));
}

TEST(MapComparisonTest, EqualityOperator) {
    Map<int, int> m1;
    Map<int, int> m2;

    EXPECT_TRUE(m1 == m2); // Empty matches empty

    m1.insert(1, 100);
    m1.insert(2, 200);

    m2.insert(2, 200);
    m2.insert(1, 100);

    // Order of insertion shouldn't break structural value equality
    EXPECT_TRUE(m1 == m2);

    m2.insert(3, 300);
    EXPECT_FALSE(m1 == m2);
}
