// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
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

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_TRUE(collection->size() == 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    ASSERT_TRUE(collection->empty()); // Verify collection is empty

    add_entries(5); // Add 5 entires to the vector

    ASSERT_TRUE(collection->size() == 5); // Verify vector equals 5
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CheckVectorMaxSize){

    // Verify collection is empty
    ASSERT_TRUE(collection->empty());

    // 0 entries in vector
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // 1 entry in vector
    add_entries(1);
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // 5 entries in vector
    add_entries(4);
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // 10 entries in vector
    add_entries(5);
    ASSERT_TRUE(collection->max_size() >= collection->size());
}
// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CheckVectorCapacity) {

    // 0 entries in vector
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // 1 entry in vector
    add_entries(1);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // 5 entries in vector
    add_entries(4);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // 10 entries in vector
    add_entries(5);
    ASSERT_TRUE(collection->capacity() >= collection->size());
}
// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, CheckResizingIncrease) {

    int beforeResize = collection->size(); // Store vector initial size
    int afterResize = NULL;

    collection->resize(5); // Resize vector to 5
    afterResize = collection->size(); // Store vector final size

    ASSERT_TRUE(beforeResize < afterResize); // Confirm initial size was smaller than current size
}
// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, CheckResizingDecrease) {

    int beforeResize = NULL;
    int afterResize = NULL;

    ASSERT_TRUE(collection->empty()); // Confirm vector is empty

    add_entries(5); // Add 5 entries to vector
    beforeResize = collection->size(); // Store vector initial size

    collection->resize(1); // Resize vector to 1
    afterResize = collection->size(); // Store vector final size

    ASSERT_TRUE(beforeResize > afterResize); // Confirm initial size was larger than current size
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, CheckResizingZero) {

    ASSERT_TRUE(collection->empty()); // Verify vector is empty

    add_entries(5); // Add 5 entries to vector
    ASSERT_FALSE(collection->empty()); // Verify vector is not empty

    collection->resize(0); // Resize vector to 0
    ASSERT_TRUE(collection->empty()); // Confirm current vector is empty
}
// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, CheckClearErases) {

    ASSERT_TRUE(collection->empty()); //Confirm vector is empty
   
    add_entries(5); // Add 5 entries to vector
    ASSERT_FALSE(collection->empty()); // Confirm vector is not empty

    collection->clear();  // Clear vector
    ASSERT_TRUE(collection->empty()); // Confirm vector is empty
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CheckEraseErases) {

    std::vector<int>::iterator begin;
    std::vector<int>::iterator end;

    ASSERT_TRUE(collection->empty()); //Confirm vector is empty

    add_entries(5); // Add 5 entries to vector
    ASSERT_FALSE(collection->empty()); // Confirm vector is not empty

    // Initilize iterators for erase function
    begin = collection->begin();
    end = collection->end();

    collection->erase(begin, end);  // Clear vector
    ASSERT_TRUE(collection->empty()); // Confirm vector is empty
}
// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CheckReserveCapacityIncrease) {

    int size = 5;
    int capacity = NULL;

    ASSERT_TRUE(collection->empty()); // Confirm vector is empty

    add_entries(size); //Add size entries to vector
    capacity = collection->capacity(); // Store capacity

    ASSERT_TRUE(collection->size() == size); // Confirm vector size equals variable size
    ASSERT_TRUE(collection->capacity() == capacity); // Confirm vector capacity equals variable capacity

    collection->reserve(capacity + size); // Reserve double the space of variable size
    ASSERT_TRUE(collection->size() == size); // Verify size remained the same
    ASSERT_TRUE(collection->capacity() == capacity + size); //Verify capacity equals capacity + size
}
// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, CheckOutOfRangeException) {

    int size = 5;

    add_entries(size); // Add size nunber of entries
    ASSERT_TRUE(collection->size() == size); // Verify vector equals size

    ASSERT_THROW({
        collection->at(size + 1); // Try to access vector at one entry past the last
        }, std::out_of_range); // Verify out of range exception is thrown

}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, CheckValueChange) {

    int value = 6;

    add_entries(10); //Add 10 entries

    collection->at(3) = 5;
    ASSERT_FALSE(collection->at(3) == value); // Verify location 3 does not equal value

    collection->at(3) = value;
    ASSERT_TRUE(collection->at(3) == value); // Verify location 3 now equals value
}

TEST_F(CollectionTest, CheckAssignValues) {

    int numberOfAssigned = 50;
    int intToBeAssigned = 66;

    ASSERT_TRUE(collection->empty()); // Verify vector is empty
    collection->assign(numberOfAssigned, intToBeAssigned);

    for (int i = 0; i < collection->size(); i++) {
        ASSERT_TRUE(collection->at(i) == intToBeAssigned); // Verify each assigned entry is equal to the assigned variable
    }
}