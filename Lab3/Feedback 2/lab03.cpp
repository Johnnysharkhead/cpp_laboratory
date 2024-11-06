#include "lab03.h"
#include <iostream>
using namespace std;

// TODO: Complementary work: The list should not print anything unless
// explicitly told to. You only need to throw exceptions
// and not print an error message. -- CHECK

// TODO: Comment: One function should be implemented recursively. -- CHECK (The 'copyList' function now is recursively implemented. Please see line 15 to 28 for more details.)

myList::myList() : head {nullptr}, length(0) {}
myList::Node::Node() : data(0), next(nullptr) {}
myList::Node::Node(int value) : data(value), next(nullptr) {} 

void myList::copyList(Node* &thisNode, Node* otherNode){
    if(otherNode == nullptr){
        thisNode = nullptr;
    }
    else{
        thisNode = new Node();
        thisNode->data = otherNode->data;
        copyList(thisNode->next, otherNode->next); // recursively call 
    }
}

void myList::copyList(const myList& other) { // outer function that calls the recursive function 'copyList'
    copyList(head, other.head);
}


// Optimize the code duplication, reuse this function. Called by 'Move constructor' and 'Move assginment opearator'
void myList::moveList(myList& other){
    this->deleteEveryNode();
    head = other.head; // Head node point to the first node of the list that being moved
    other.head = nullptr; // Free other's head node, avoid memory leak
}


// Copy constructor(deep copy)
myList::myList(const myList& other){
    copyList(other);
}

// Copy assginment opearator(deep copy) 
myList& myList::operator= (const myList& other){
    if (this == &other) {return *this;}
    else{
        copyList(other); // reuse the code 
        return *this;
    }
}

// Move constructor
myList::myList(myList&& other){
    moveList(other);
}

// Move assginment operator
myList& myList::operator= (myList&& other){
    if(this == &other){
        return *this; // Judge whether they are same
    }
    else{
        moveList(other); 
        return *this;
    }
}

// Call by Destructor and Move assignment operator
void myList:: deleteEveryNode(){
    Node* tempNode = head;
    while (tempNode != nullptr)
    {
        Node* next = tempNode -> next;
        delete tempNode;
        tempNode = next;
    }
    head = nullptr;
}

myList:: ~myList() {
    deleteEveryNode(); 
}

void myList::insert(int addValue){

    // "newNode" is a pointer that point to the Node in Heap momory
    // "tempNode" is a pointer we use it as a searcher that can navigate any location of the list
    Node* newNode = new Node{addValue} ; 

    // Condition 1: insert the Node at the first place
    if (head == nullptr || head->data > newNode->data ) { 
        newNode->next = head;
        head = newNode;
        newNode = nullptr;
    }
    else{
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
    length++; // update the length of list           
}

void myList::removebyValue(int removeValue){
    Node* tempNode = head;
    
    // if the the node we want to delete is the first node
    while (tempNode != nullptr && tempNode->data == removeValue)
    {
        head = tempNode->next;
        delete tempNode;
        length--; // update of the length of list
        return;
    }

    // if the the node we want to delete is other node except the first node
    while (tempNode != nullptr && tempNode->next != nullptr)
    {
        if(tempNode->next->data == removeValue){
            Node* k = tempNode->next;
            tempNode->next = k->next;
            delete k; // prevent memory leak
            length--; // update of the length of list
            return;
        }
        else{
            tempNode = tempNode -> next;
        }
    }

    // handle the exception
    throw std::out_of_range("Value out of range");
    return;  
}

void myList::removebyIndex(int removeIndex){

    // Ensure the index is reasonable
    if (removeIndex < 0 || removeIndex > (listLength()-1) ){ // handle the exception
        throw std::out_of_range("Index out of range");
        return;
    }

    else{
        Node* tempNode = head;
        // if we want to delete the first Node of the list
        if (removeIndex == 0){
            head = tempNode -> next;
            delete tempNode;
            length--; // update of the length of list
            return;
        }
        // if we want to delete the other Node of the list
        for (int i = 1; i < (removeIndex) ; i++){
            tempNode =  tempNode -> next; // move the pointer to the Node before the Node we want to delete;
        }
        Node* k = tempNode->next; // Now, pointer k point to the node we want to delete
        tempNode -> next = k -> next; // if we want to delete the last node, then k->next = null
        delete k; 
        length--; // update of the length of list
        return;  
    }
}

int myList::at(int nodeIndex) const{
    // handle the exception
    if ( nodeIndex < 0 || nodeIndex > (listLength()-1) ){
        throw std::out_of_range("The index you input is invalid, please try again.");
    }

    Node* tempNode = head ;

    if ( nodeIndex == 0 ){
        return head->data;
    }
    for (int i = 1; i <= nodeIndex; i++){
        tempNode = tempNode->next;
    }
    return tempNode->data;        
}

// User gets the length of list via calling this function
int myList::listLength() const{ 
    if (head == nullptr) return 0;
    else return length;
}

void myList::print() const {
    Node* tempNode = head;
    while (tempNode != nullptr) {
        std::cout << tempNode->data << " ";
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}
