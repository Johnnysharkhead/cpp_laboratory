
In this programme, we give the following name to elements in a link list: 

head -> first node(index 0) -> second node(index 1) ... -> null

This means：
1. If Node* temp = head, the pointer "temp" will point to the first node.
2. If head = nullptr, there is not any node in the link list.
3. The "head" is not counted when calculating the length of link list.

---------------------------------------------------------------------------------------

We wrote the test file with the file name "test.cc" and it contains five test cases:

1. CRUD of link list (including adding nodes, accessing nodes based on index, deleting nodes based on index, deleting nodes based on value, getting the length of
the list, and printing the list)
2. Move Constructor
3. Copy Consturctor
4. Move Assignment Operator
5. Copy Assignment Operator

---------------------------------------------------------------------------------------

Additionly, to make it more user-friendly for displaying print list, giving feedback on input value exceptions, we wrote the file with the name "main.cpp".

Some of the running results are as follows:
The current list: 3 -> 5 -> 8 -> null
The amount of nodes in the current list is: 3

-----------------------------------------------------------------------------------------

We tested each of the above files with the Valgrind tool and reported no memory leaks.


