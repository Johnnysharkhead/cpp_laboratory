#include "lab03.h"
#include <iostream>
using namespace std;

int main(){

    myList list;

    // Test insert function
    list.insert(3);
    list.insert(2);
    list.insert(5);
    list.insert(9);
    list.insert(8);
    list.printList();

    // Test remove by value 
    list.removebyValue(9);
    list.printList();

    // Test remove by index
    list.removebyIndex(0);
    list.printList();
 
    // Test retrieving a node
    list.at(0);
    list.at(2);

    // // Test copy assginment operator
    // myList deep;
    // deep.insert(12);
    // deep.insert(24);
    // deep.printList();

    // deep = list;
    // std::cout << "Deep copy list: " << std::endl;
    // deep.printList();
    
    // list.insert(100);
    // std::cout << "Orignal list: " << std::endl;
    // list.printList();
    // std::cout << "Deep copy list: " << std::endl;
    // deep.printList();

    // // Test copy construtor
    // myList listcopy = list; // listcopt is an empty list
    // std::cout << "Orignal list: " << std::endl;
    // list.printList();
    // std::cout << "Deep copy list: " << std::endl;
    // listcopy.printList();

    // // Test move constructor
    // myList listmove (std::move(list)); 
    // listmove.printList();

    // // Test move assginment operator
    // myList list_1;
    // list_1.insert(2);
    // list_1.insert(4);
    // list_1.insert(8);
    // list_1.insert(6);
    // list_1.insert(0);
    // list_1.printList();
    // std::cout << "list_1: ";
    // list_1.printList();
    // list = std::move(list_1);
    // std::cout << "list: ";
    // list.printList();
    
    return 0;

}