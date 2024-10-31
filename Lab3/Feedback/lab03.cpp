#include "lab03.h"
#include <iostream>
using namespace std;


// In this programme, we give the following name to elements in a link list:
// Head -> first node(index 0) -> second node(index 1) ... -> null 

myList::myList() : head{ nullptr } {}

// Move constructor
myList::myList(myList&& other) noexcept {
    head = other.head;// Head node point to the first node of the list that being moved
    other.head = nullptr; // Free other's head node, avoid memory leak
}

// Copy constructor(deep copy)
myList::myList(const myList& other) {
    // Copy an empty list
    if (other.head == nullptr) {
        head = nullptr;
    }
    else {
        // Copy the first node
        head = new Node{ other.head->data };
        // Copy other nodes
        Node* tempNode = head; // Initialize pointer tempNode which point to the first node of "this"
        Node* k_ptr = other.head->next; // Initialize pointer k_ptr which point to the second node of "other"

        while (k_ptr != nullptr)
        {
            tempNode->next = new Node{ k_ptr->data };
            k_ptr = k_ptr->next;
            tempNode = tempNode->next;
        }
        tempNode = nullptr;
    }
}

// Move assginment operator
myList& myList::operator= (myList&& other) noexcept {
    std::cout << "Shallow copy called" << std::endl;
    if (this == &other) {
        return *this; // Judge whether they are same
    }
    else {
        this->deleteEveryNode(); // Release all values of the current list except for the head node
        head = other.head;
        other.head = nullptr; // Avoid memory leak
    }
    return *this;
}

// Copy assginment opearator(deep copy) 
myList& myList::operator= (const myList& other) {

    std::cout << "Deep copy called" << std::endl;
    // Handle the exception
    if (this == &other) {
        return *this;
    }

    if (other.head == nullptr) {
        head = nullptr;
        return *this;
    }
    else {
        // Copy the first node
        this->deleteEveryNode(); // Avoid memory leaks
        head = new Node{ other.head->data };

        // Copy rest of nodes
        Node* current = head; // Pointer current point to the first node of newList
        Node* k_ptr = other.head->next; // Pointer k_ptr point to the second node of "other" list

        while (k_ptr != nullptr) {
            current->next = new Node{ k_ptr->data }; // Create from the second node to the last node
            current = current->next;
            k_ptr = k_ptr->next;
        }
        current = nullptr;
        return *this;
    }
}


// Call by Destructor and Move assignment operator
void myList::deleteEveryNode() {
    Node* tempNode = head;
    while (tempNode != nullptr)
    {
        Node* next = tempNode->next;
        delete tempNode;
        tempNode = next;
    }
    head = nullptr;
}

myList:: ~myList() {
    deleteEveryNode();
    std::cout << "\n***The list has been destroyed by the destructor*** \n" << std::endl;
}


void myList::insert(int addValue) {

    // "newNode" is a pointer that point to the Node in Heap momory
    // "tempNode" is a pointer we use it as a searcher that can navigate any location of the list
    Node* newNode = new Node{ addValue };

    // Condition 1: insert the Node at the first place
    if (head == nullptr || head->data > newNode->data) {
        newNode->next = head;
        head = newNode;
        newNode = nullptr;
    }
    else {
        // Condition 2: insert the Node either at the end of the list or between any two Node in the list
        Node* tempNode = head;

        // move the tempNode to the location we want
        // stop moving the tempNode until the Node after the Node which tempNote point to is bigger than insert Node
        while (tempNode->next != nullptr && tempNode->next->data < newNode->data) {
            tempNode = tempNode->next;
        }
        // although tempNode->next is null, set newNode->next as null and it will be the last Node of the list
        newNode->next = tempNode->next;
        tempNode->next = newNode;
        newNode = nullptr;
    }
}

void myList::removebyValue(int removeValue) {
    Node* tempNode = head;

    // if the the node we want to delete is the first node
    while (tempNode != nullptr && tempNode->data == removeValue)
    {
        head = tempNode->next;
        delete tempNode;
        return;
    }

    // if the the node we want to delete is other node except the first node
    while (tempNode != nullptr && tempNode->next != nullptr)
    {
        if (tempNode->next->data == removeValue) {
            Node* k = tempNode->next;
            tempNode->next = k->next;
            delete k; // prevent memory leak
            return;
        }
        else {
            tempNode = tempNode->next;
        }
    }

    // handle the exception
    std::cout << "Sorry, there is no match node with the value you input in the list. \n" << std::endl;
    throw std::out_of_range("Value out of range");
    return;

}

void myList::removebyIndex(int removeIndex) {

    // Ensure the index is reasonable
    if (removeIndex < 0 || removeIndex >(listLength() - 1)) { // handle the exception
        std::cout << "The index you input is invalid, please try again. \n" << std::endl;
        throw std::out_of_range("Index out of range");
        return;
    }

    else {
        Node* tempNode = head;
        // if we want to delete the first Node of the list
        if (removeIndex == 0) {
            head = tempNode->next;
            delete tempNode;
            return;
        }
        // if we want to delete the other Node of the list
        for (int i = 1; i < (removeIndex); i++) {
            tempNode = tempNode->next; // move the pointer to the Node before the Node we want to delete;
        }
        Node* k = tempNode->next; // Now, pointer k point to the node we want to delete
        tempNode->next = k->next; // if we want to delete the last node, then k->next = null
        delete k;
        return;
    }
}

void myList::printList() const {

    Node* tempNode = head;
    std::cout << "The current list: ";

    if (tempNode == nullptr)
    {
        std::cout << "NULL";
    }

    while (tempNode != nullptr)
    {
        std::cout << tempNode->data << " -> ";
        tempNode = tempNode->next;
    }
    std::cout << "null" << std::endl;

    std::cout << "The amount of nodes in the current list is: " << this->listLength() << "\n" << std::endl;
}

std::string myList::printTest() const {
    string test{};
    Node* tempNode = head;

    if (tempNode == nullptr) {
        test = "NULL";
        return test;
    }

    while (tempNode != nullptr)
    {
        test.append(std::to_string(tempNode->data));
        tempNode = tempNode->next;
    }
    return test;
}

int myList::at(int nodeIndex) const {
    // handle the exception
    if (nodeIndex < 0 || nodeIndex >(listLength() - 1)) {
        std::cout << "The index you input is invalid, please try again. \n" << std::endl;
        return -1;
    }

    Node* tempNode = head;

    if (nodeIndex == 0) {
        std::cout << "The value of the NO.1 node is: " << head->data << std::endl;
        return head->data;
    }
    for (int i = 1; i <= nodeIndex; i++) {
        tempNode = tempNode->next;
    }
    std::cout << "The value of the NO." << nodeIndex << " node is: " << tempNode->data << " \n" << std::endl;
    return tempNode->data;
}

// If there is an empty list, the length of the list is 0.
int myList::listLength() const {
    Node* listLength = head;
    if (head == nullptr) { // an empty list
        return 0;
    }

    int count{ 0 };
    while (listLength->next != nullptr) {
        ++count; // the amount of nodes in the list is count+1
        listLength = listLength->next;
    }
    return count + 1;
}