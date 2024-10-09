#ifndef LAB03_H
#define LAB03_H

#include <iostream>
using namespace std;

// In this programme, we give the following name to elements in a link list:
// Head -> first node(index 0) -> second node(index 1) ... -> null

class myList {

    public:

    myList(); // Constructor

    ~myList(); // Destructor

    myList(myList&& other); // Move constructor(assign values to an empty list)

    myList(const myList& other); // Copy constructor(assign values to an empty list)

    void deleteEveryNode(); // Delete every node in the list except for the head node
       

    myList& operator= (myList&& other); // Move assginment operator(consideration needs to be given to the release of the current list resources) 

    myList& operator= (const myList& other); // Copy assignment operator(Deep Copy)


  
    void insert(int addValue); // Adds a value to the list (in sorted order)

    void removebyValue(int removeValue); // Removes a node in the list by value

    void removebyIndex(int removeIndex); // Removes a node in the list by index

    void printList() const; // Prints all the values in the list

    int at(int nodeIndex) const; // Return the value stored at a specified index

    int listLength() const; // Calculate how many nodes/values are in the list

        
    string printTest() const; // Only for test use in test.cc

    private:

    struct Node {
        int data; 
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head{}; 

};

#endif // LAB03_H

