#ifndef LAB03_H
#define LAB03_H

#include <string>

// TODO: Complementary work: Do not open namespaces in header files 
// (using namespace). -- CHECK

// TODO: Complementary work: Function implementations should not be 
// done in the header file. -- CHECK

// TODO: Functions that exist solely for testing should only exist in test files. -- CHECK

class myList {

private:
    struct Node {
        int data; 
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head{};
    int length; // New member variable, save the length of list initially
    
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
    std::string printTest() const; // Prints all the values in the list
    int at(int nodeIndex) const; // Return the value stored at a specified index
    int listLength() const; // Calculate how many nodes/values are in the list
    void deleteEveryNode(); // Delete every node in the list except for the head node
        
};

#endif // LAB03_H

