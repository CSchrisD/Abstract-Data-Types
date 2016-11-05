//Christina Duran
//crduran
//cmps101
//11/21/14
//List ADT in C used by Client to alter their desired index

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structures

//Node
typedef struct NodeObj{
   int item;
   struct NodeObj* next;
   struct NodeObj* before;
} NodeObj;

typedef NodeObj* Node;

//List
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
}ListObj;

//constructors destructors
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->item = data;
   N->next = NULL;
   N->before = NULL;
   return(N);
}

void freeNode(Node* pN){
  if(pN!=NULL && *pN!=NULL){
      free(*pN);
      *pN = NULL;
  }
}

List newList(void){
   List L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL){
        while(length(*pL) != 0){
            clear(*pL);
    }
    free(*pL);
    *pL = NULL;
    }
}

// Access Functions

//Returns number of elements in this list.
int length(List L){
       return L->length;
}

//Returns the index of the cursor elemtent in this list, or returns
////-1 if the cursor element is undefined.
int getIndex(List L){
      if(L->cursor == NULL){
          return -1;
      }
     return L->index;
}

//Returns front element in this list. Pre: length()>0
int front(List L){
    if(L->length < 0 ){
         printf("List Error in front(): List does not contain any elements. \n");
         exit(1);
    }
    return L->front->item;
}

//Returns back element in this list. Pre: length()>0
int back(List L){
     if(L->length < 0){
         printf("List Error in back(): List does not contain any elments.\n");
         exit(1);
     }
     return L->back->item;
}

//Returns cursor element in this list. Pre: length()>0, getIndex()>=0
int getElement(List L){
   if(L == NULL){
      printf("List Error in getElement(): List does not exitst\n");
      exit(1);
   }
   if(L->length <= 0){
       printf("List Error in getElement(): This is an empty list. \n");
       exit(1);
    }if(getIndex(L)<0){
       printf("List Error in getElement(): Cursor is not pointing at an element.\n");
       exit(1);
    }
    return L->cursor->item;
}

//Returns true (1) if this List and L are the same integer sequence. 
////The cursor is ignored in both lists
int equals(List A, List B){
      int start = 1;
      Node N = A->front;
      Node Q = B->front;
      if(A->length == B->length){
        while(start==1 && N!=NULL){
           if(N->item != Q->item){
               start = 0;
           }
             N = N->next;
             Q = Q->next;
        }
        return start;
      }else{
       return 0;
   }
}

//Manipulation procedures

//Re-sets this List to the empty state
void clear(List L){
   Node N = L->front;
    while(N != NULL){
         L->front = N->next;
         freeNode(&N);
         N = L->front;
    }
    L->index  = -1;
    L->length = 0;
    freeNode(&N);
    N = NULL;
}

//If 0<=i<=length()-1, moves the cursor to the element at index i, otherwise
////the cursor becomes undefined
void moveTo(List L, int i){
       Node N = L->front;
       int j = 0;
       if(0<=i && i<=(L->length)-1){
         while(j != i){
             j++;
             N = N->next;
         }
         L->cursor = N;
         L->index = j;
       }else{
           L->cursor = NULL;
           L->index  = -1;
       }
}

//If 0<getIndex()<=length()-1, moves the cursor one step toward the
////front of the list. If getIndex()==0, cursor becomes undefined.
////If getIndex()==-1, cursor remains undefined. This operation is
////equivalent to moveTo(getIndex()-1).
void movePrev(List L){
     Node N = L->front;
     int j = 0;
     if(0<getIndex(L) && getIndex(L)<=(L->length)-1){
         while( j!= getIndex(L)){
              N = N->next;
              j++;
         }
     L->cursor = N->before;
         (L->index)--;
   }else{
     L->cursor = NULL;
     L->index = -1;
   }
}

//If 0<=getIndex()<length()-1, moves the cursor one step toward the
////back of the list. If getIndex()==length()-1, cursor becomes
////undefined. If index==-1, cursor remains undefined. This
////operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L){
     Node N = L->front;
     int j = 0;
     if(0<=getIndex(L) && getIndex(L)<(L->length)-1){
        while( j != getIndex(L)){
             N = N->next;
             j++;
        }
      L->cursor = N->next;
      (L->index)++;
  }else{
     L->cursor = NULL;
     L->index = -1;
  }
}

//Inserts new element before front element in this list.
void prepend(List L, int data){
     if(L->length== 0){
        L->front = L->back = newNode(data);
     }else{
         Node N = L->front;
         L->front = newNode(data);
         L->front->next = N;
         L->front->before = NULL;
         N->before = L->front;
         if(L->cursor != NULL){
             (L->index)++;
         }
     }
    (L->length)++;
}

//Inserts new element after back element in this list.
void append(List L, int data){
     if(L->length == 0){
         L->back = newNode(data);
         L->front = L->back;
     }else{
          Node N = L->back;
          Node T = newNode(data);
          N->next = T;
          T->before = N;
          L->back = T;
          N = NULL;
          T = NULL;
          freeNode(&T);
          freeNode(&N);
     }
     (L->length)++;
}

//Inserts new element before cursor element in this List. Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data){
     Node G = L->cursor->before;
    if(L->length<0){
       printf("List Error in insertBefore(): cannot insert on empty list.\n");
       exit(1);
    }else if(getIndex(L)<0){
       printf("List Error in insertBefore(): cannot insert negative index.\n");
       exit(1);
    }else if(G == NULL){
       Node N = L->front;
       Node R = newNode(data);
       N->before = R;
       R->next = N;
       R->before = NULL;
       L->front = R;
       (L->index)++;
    }else{
       Node N = newNode(data);
       G->next = N;
       N->before = G;
       N->next = L->cursor;
       L->cursor->before = N;
       (L->index)++;
    }
    (L->length)++;
}

//Inserts new element after cursor element in this List. Pre: Pre: length()>0
//getIndex()>=0
void insertAfter(List L, int data){
      Node G = L->cursor->next;
    if(L->length<0){
       printf("List Error in insertBefore(): cannot insert on empty list.\n");
       exit(1);
    }else if(getIndex(L)<0){
       printf("List Error in insertBefore(): cannot insert negative index.\n");
       exit(1);
    }else if(G == NULL){
       Node N = L->back;
       L->back = newNode(data);
       L->back->next = NULL;
       L->back->before = N;
    }else{
       Node N = newNode(data);
       L->cursor->next = N;
       N->before = L->cursor;
       N->next = G;
       G->before = N;
    }
  (L->length)++;
}

//Deletes the front element in this List. Pre: length()>0
void deleteFront(List L){
   if(L->length == 0){
       printf("List Error in deleteFront(): List does not contain any elements.\n");
       exit(1);
   }
   if(L->length > 1){
      Node N = L->front->next;
      freeNode(&L->front);
      L->front = N;
      L->front->before = NULL;
      L->length--;
      if(L->cursor != NULL){
         (L->index)--;
      }
   }else{
      L->front = NULL;
      freeNode(&L->front);
      L->length--;
      if(L->cursor != NULL){
         freeNode(&L->cursor);
         L->cursor = NULL;
         L->index=-1;
      }
   }
}

//Deletes the back element in this List. Pre: length()>0
void deleteBack(List L){
   if(L->length == 0){
     printf("List Error in deleteBack(): List does not contain any elements.\n");
     exit(1);
   }
   if(L->length >1){
      Node N = L->back->before;
      freeNode(&L->back);
      L->back = N;
      L->back->next = NULL;
      L->length--;
      if(L->cursor != NULL){
          (L->index)--;
      }
   }else{
       L->back = NULL;
      freeNode(&L->back);
      L->length--;
      if(L->cursor != NULL){
         freeNode(&L->cursor);
         L->cursor = NULL;
         L->index=-1;
      }
   }
}

//Deletes cursor element in this List. Cursor is undefined after this operation.
//Pre: lenght()>0,getIndex()>=0
void delete(List L){
   if(L->length>0 && getIndex(L)>=0){
      Node N = L->cursor->before;
      Node G = L->cursor->next;
      N->next = G;
      G->before = N;
      freeNode(&L->cursor);
      L->cursor = NULL;
      L->length--;
      L->index = -1;
   }
}

//Other methods

////Overides Object's toString method. Creates a string
////consisting of a space separated sequence of integers
////with front on the left and back on the right. The
////cursor is ignored.
void printList(FILE* out, List L){
    for(Node N = L->front; N != NULL; N = N->next){
       fprintf(out,"%d ", N->item);
    }
}

List copyList(List L){
    List G = newList();//copy into this new list
    for(Node N = L->front; N != NULL; N = N->next){
       append(G,N->item);
    }
    return G;
}