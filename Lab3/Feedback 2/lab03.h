#ifndef LAB03_H
#define LAB03_H

#include <string>

// TODO: Complementary work: Function implementations should not be 
// done in the header file.
// The member initialization list in the node constructor counts as implementation. -- CHECK

// TODO: Complementary work: print() should not return a string.   
// Therefore, you wont need to test the function. If you really want to be able to test
// printing the list or something similar you can do a to_sting() function. However, you
// still need a print function. -- CHECK

// TODO: Comment: The public part should be first, and the  
// private part should be below. There should only be one private part. -- CHECK

class myList {

public:
    myList(); // Constructor
    ~myList(); // Destructor
    myList(const myList& other); // Copy constructor(assign values to an empty list)
    myList(myList&& other); // Move constructor(assign values to an empty list)
    myList& operator= (const myList& other); // Copy assignment operator(Deep Copy)
    myList& operator= (myList&& other); // Move assginment operator(consideration needs to be given to the release of the current list resources) 
    
    void copyList(const myList& other); // The code reused in Copy constuctor and Copy assignment operator
    void moveList(myList& other); // The code reused in Move constuctor and Move assignment operator
    
    void insert(int addValue); // Adds a value to the list (in sorted order)
    void removebyValue(int removeValue); // Removes a node in the list by value
    void removebyIndex(int removeIndex); // Removes a node in the list by index
    void print() const; // Print all the values in the list
    int at(int nodeIndex) const; // Return the value stored at a specified index
    int listLength() const; // Calculate how many nodes/values are in the list
    void deleteEveryNode(); // Delete every node in the list except for the head node
    std::string to_string() const; // Return a string format of the list (for test)

private:
    struct Node {
        int data; 
        Node* next;
        Node(); // Default constructor
        Node(int value); // Constructor that initializes the node with a given value
    };

    void copyList(Node *&thisNode, Node* otherNode); // Recursively copy nodes from another list

    Node* head{};
    int length; // New member variable, save the length of list initially 

};

#endif // LAB03_H

