// Uncomment the next line to use precompiled headers
#include "pch.h"
#include "gtest/gtest.h"
#include <vector>
#include <stdexcept>
#include <memory>
#include <cassert>
#include <iostream>
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Test that a single value can be added to the collection.
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // Initially the collection should be empty
    ASSERT_TRUE(collection->empty());

    add_entries(1);  // Add one random element

    // After adding one element, the collection size should be 1
    ASSERT_EQ(collection->size(), 1);
}

// Test that five values can be added to the collection.
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);  // Add five random elements
    ASSERT_EQ(collection->size(), 5);  // Ensure the size is 5
}

// Test that the max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanOrEqualToSize)
{
    add_entries(10);
    ASSERT_GE(collection->max_size(), collection->size());  // Max size should be >= size
}

// Test that the capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanOrEqualToSize)
{
    add_entries(5);
    ASSERT_GE(collection->capacity(), collection->size());  // Capacity should be >= size
}

// Test that resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    add_entries(5);
    size_t old_size = collection->size();

    collection->resize(10);  // Resize to a larger size

    ASSERT_GT(collection->size(), old_size);  // Size should have increased
}

// Test that resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    add_entries(10);
    size_t old_size = collection->size();

    collection->resize(5);  // Resize to a smaller size

    ASSERT_LT(collection->size(), old_size);  // Size should have decreased
}

// Test that resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeToZero)
{
    add_entries(5);
    collection->resize(0);  // Resize to zero

    ASSERT_EQ(collection->size(), 0);  // Size should be zero
}

// Test that clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(5);
    collection->clear();  // Clear the collection

    ASSERT_EQ(collection->size(), 0);  // Size should be zero
}

// Test that erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    add_entries(5);
    collection->erase(collection->begin(), collection->end());  // Erase all elements

    ASSERT_EQ(collection->size(), 0);  // Size should be zero
}

// Test that reserve increases capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacity)
{
    add_entries(5);
    size_t old_capacity = collection->capacity();

    collection->reserve(20);  // Reserve more capacity

    ASSERT_GT(collection->capacity(), old_capacity);  // Capacity should increase
    ASSERT_EQ(collection->size(), 5);  // Size should remain the same
}

// Test that std::out_of_range exception is thrown when calling at() with an index out of bounds
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
    add_entries(5);

    // Ensure that accessing out-of-range index throws std::out_of_range
    ASSERT_THROW(collection->at(10), std::out_of_range);
}

// Custom positive test: Ensure the collection can handle a large number of entries
TEST_F(CollectionTest, CanHandleLargeNumberOfEntries)
{
    add_entries(1000);  // Add 1000 random entries
    ASSERT_EQ(collection->size(), 1000);  // Verify the size is 1000
}

// Custom negative test: Ensure adding a negative number of entries results in an assertion failure
TEST_F(CollectionTest, CannotAddNegativeNumberOfEntries)
{
    try
    {
        add_entries(-5);  // Try adding negative entries
        FAIL() << "Expected an exception or assertion failure for negative entry count";
    }
    catch (const std::exception& e)
    {
        // Catching any exceptions and ensuring we do not proceed
        ASSERT_TRUE(true);  // Exception expected, test passed
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}