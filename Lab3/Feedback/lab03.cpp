#include "lab03.h"
#include <iostream>

// TODO: Complementary work: Do not iterate through the list unnecessarily 
// Comment: When the listlength() function is called you iterate through the
// whole list, when used in a loop you do this n² times. -- CHECK

// TODO: Complementary work: Initialize variables with {} not = -- CHECK

// TODO: Complementary work: Code duplication. Can you perhaps 
// reuse the code from the copy constructor by creating a local copy 
// of other? Same goes for move. -- CHECK (partly)

// TODO: Complementary work: The list should not print anything unless
// explicitly told to. -- CHECK

// TODO: Complementary work: You have some redundant deletes.


using namespace std;
// In this programme, we give the following name to elements in a link list:
// Head -> first node(index 0) -> second node(index 1) ... -> null 
myList::myList() : head {nullptr}, length(0) {}

// Optimize the code duplication, reuse this function and called by 'Copy constructor' and 'Copy assginment opearator'
void myList::copyList(const myList& other){
    // If the list 'other' is empty
    if(other.head == nullptr){
        head = nullptr;
    }
    else{
    //Copy the first node
    head = new Node(other.head->data);
    //Copy rest of nodes in list "other"
    Node* tempNode = head; // Pointer current point to the first node of "newList"
    Node* k_ptr = other.head->next; // Pointer k_ptr point to the second node of "other" list
    while(k_ptr != nullptr){
        tempNode->next = new Node{k_ptr->data};
        k_ptr = k_ptr->next;
        tempNode = tempNode->next;
    }
    tempNode = nullptr; // the last node of "newList" point to NULL
    }
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
    head = other.head;// Head node point to the first node of the list that being moved
    other.head = nullptr; // Free other's head node, avoid memory leak
}

// Move assginment operator
myList& myList::operator= (myList&& other){
    if(this == &other){
        return *this; // Judge whether they are same
    }
    else{
        this->deleteEveryNode(); // Release all values of the current list except for the head node
        head = other.head;
        other.head = nullptr; // Avoid memory leak
    }
    return *this;
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
    //sstd::cout << "\n***The list has been destroyed by the destructor*** \n" << std::endl; 
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
    std::cout << "Sorry, there is no match node with the value you input in the list. \n" << std::endl;
    throw std::out_of_range("Value out of range");
    return;  
}

void myList::removebyIndex(int removeIndex){

    // Ensure the index is reasonable
    if (removeIndex < 0 || removeIndex > (listLength()-1) ){ // handle the exception
        std::cout << "The index you input is invalid, please try again. \n" << std::endl;
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

void myList::printList() const{

    Node* tempNode = head;
    std::cout << "The current list: ";

    if (tempNode==nullptr)
    {
        std::cout << "NULL";
    }

    while(tempNode != nullptr)
    {
        std::cout << tempNode->data << " -> ";
        tempNode = tempNode -> next;
    }
    std::cout << "null" << std::endl;
    std::cout << "The amount of nodes in the current list is: " << this->listLength() << "\n" << std::endl;   
}
std::string myList::printTest() const{
    string test{};
    Node* tempNode = head;

    if (tempNode==nullptr){
        test = "NULL";
        return test;
    }

    while (tempNode!=nullptr)
    {
      test.append(std::to_string(tempNode->data));
      tempNode = tempNode->next;
    }
    return test;
}

int myList::at(int nodeIndex) const{
    // handle the exception
    if ( nodeIndex < 0 || nodeIndex > (listLength()-1) ){
        std::cout << "The index you input is invalid, please try again. \n" << std::endl;
        return -1;
    }

    Node* tempNode = head ;

    if ( nodeIndex == 0 ){
        std::cout << "The value of the NO.1 node is: " << head->data << std::endl;
        return head->data;
    }
    for (int i = 1; i <= nodeIndex; i++){
        tempNode = tempNode->next;
    }
    std::cout << "The value of the NO."<< nodeIndex << " node is: " << tempNode->data << " \n" << std::endl;
    return tempNode->data;        
}

// User has to get the length of list by call this instead of the private member variable 'length'
int myList::listLength() const{ 
    if (head == nullptr) return 0;
    else return length;
}


