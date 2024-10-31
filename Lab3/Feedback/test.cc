#define CATCH_CONFIG_MAIN
#include "lab03.h"
#include "catch.hpp"

// TODO: Complementary work: Test cases insufficient, what if a list is 
// empty for all functions? -- CHECK

// TODO: Complementary work: unnecessary include  -- CHECK 

// In this programme, we give the following name to elements in a link list:
// Head -> first node(index 0) -> second node(index 1) ... -> null

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE( "CRUD of link list" ) { // No memory leak detected
    
    myList list;

    list.insert(3), list.insert(2), list.insert(5), list.insert(9), list.insert(8);
    CHECK(list.listLength() == 5);
    CHECK(list.printTest() == "23589");
    
    list.removebyValue(3);
    CHECK(list.printTest() == "2589");
    CHECK_THROWS_AS(list.removebyValue(999), std::out_of_range); // Test Throws Exceptions

    list.removebyIndex(0);
    CHECK(list.printTest() == "589");
    list.removebyIndex(2);
    CHECK(list.printTest() == "58");
    // Currently, the length of list are 2 and the index range of list is from 0 to 1
    CHECK_THROWS_AS(list.removebyIndex(2), std::out_of_range); // Test Throws Exceptions

    CHECK(list.at(0) == 5);
    CHECK(list.at(1) == 8); 
    CHECK(list.at(2) == -1); // Test Throws Exceptions
}

TEST_CASE( "All about empty list"){
    myList emptyList;
    CHECK(emptyList.listLength() == 0); // test the length of an empty list
    CHECK_THROWS_AS(emptyList.removebyValue(0), std::out_of_range); // remove a node by value in an empty list
    CHECK_THROWS_AS(emptyList.removebyIndex(0), std::out_of_range); // remove a node by index in an empty list

    // test Copy Constructor of an empty list
    myList a = emptyList;
    CHECK(a.printTest() == "NULL");

    // test Move Constructor of an empty list
    myList b (std::move(emptyList));  
    CHECK(b.printTest() == "NULL");

    // test Move Operator Assignment ( List c = move(empty list) )
    myList c; 
    c.insert(1), c.insert(2), c.insert(3);
    c = std::move(emptyList);
    CHECK(c.printTest() == "NULL");
    
    // test Copy Operator Assignment ( List c = empty list )
    emptyList.deleteEveryNode();
    c = emptyList;
    CHECK(c.printTest() == "NULL");
    emptyList.insert(4);
    CHECK(c.printTest() == "NULL");
}


TEST_CASE( "COPY Constructor of link list" ) { // No memory leak detected

    myList list;
    list.insert(8), list.insert(4), list.insert(2), list.insert(6);

    myList listcopy = list;
    CHECK(listcopy.printTest() == "2468");

    list.removebyValue(2);
    CHECK(list.printTest() == "468");
    CHECK(listcopy.printTest() == "2468"); // listcopy does not change with list

}

TEST_CASE( "COPY assignment operator of link list" ) { // No memory leak detected

    myList a;
    a.insert(1), a.insert(2), a.insert(3), a.insert(4);

    myList b;
    b.insert(6), b.insert(7), b.insert(8);

    a = b;
    CHECK(a.printTest() == "678");

    b.insert(9);
    CHECK(b.printTest() == "6789");
    CHECK(a.printTest() == "678"); // Confirm list a does not change with b

} 

TEST_CASE( "MOVE assignment operator of link list" ) { // No memory leak detected
    myList a;
    a.insert(1), a.insert(2), a.insert(3), a.insert(4);

    myList b;
    b.insert(6), b.insert(7), b.insert(8);

    a = std::move(b);

    CHECK(a.printTest() == "678");
    CHECK(b.listLength() == 0); // Confirm that we release all resources of list b
} 

TEST_CASE( "MOVE Constructor of link list" ) { // No memory leak detected

    myList list;
    list.insert(8), list.insert(4), list.insert(2), list.insert(6);

    myList listmove (std::move(list));
    CHECK(listmove.printTest() == "2468");
    CHECK(list.listLength() == 0); // Confirm that we release all resources of list

} 