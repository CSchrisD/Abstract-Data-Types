//List.h for List.c ADT

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

//Constructors-Destructors --------------------------------------------------- 
List newList(void);   //creates a new list of nodes and other parameters
void freeList(List* pL); //frees a list and its nodes and resets parameters

// Access functions ----------------------------------------------------------- 
int length(List L);   //returns number of nodes in a list
int getIndex(List L); //returns the current cursor index of a list, -1 otherwise
int front(List L);   //returns the front element of a list
int back(List L);   //returns the back element of a list
int getElement(List L);   //returns the element cursor is currently pointing at in a list
int equals(List A, List B); //determines if two lists are the same

// Manipulation procedures ---------------------------------------------------- 
void clear(List L); //frees all nodes from a list
void moveTo(List L, int i);  //moves cursor node to point at ith index
void movePrev(List L);   //moves the cursor to point at node directly before current index
void moveNext(List L);   //moves the cursor to point at node directly after current index
void prepend(List L, int data); //inserts a node to the front of the list
void append(List L, int data);  //inserts a node at the back of the list
void insertBefore(List L, int data);   //inserts a node before the node cursor is pointing at
void insertAfter(List L, int data);   //inserts a node after the node cursor is pointing at
void deleteFront(List L);   //deletes the front element of a list
void deleteBack(List L);   //deletes the back element of a list
void delete(List L);    //deletes current cursor node

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); //prints the elements of a list in order from front to back
List copyList(List L); //enters the same elements and order of elements of a list into a new one

#endif