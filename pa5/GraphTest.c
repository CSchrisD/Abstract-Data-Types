//Christina Duran
//crduran
//cmps101
//12/08/14
//Personal GraphTest.c to test functions in Graph.c to see if they 
//comply with the expectations of current programing assignment
//so that all funtions of Graph.c work properly

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
   //create new graphs and lists
   Graph A = newGraph(8);
   List L = newList();
   int a,b;

   //add arcs to graphs
   addArc(A,1,2);
   addArc(A,2,3);
   addArc(A,2,5);
   addArc(A,2,6);
   addArc(A,3,4);
   addArc(A,3,7);
   addArc(A,4,3);
   addArc(A,4,8);
   addArc(A,5,1);
   addArc(A,5,6);
   addArc(A,6,7);
   addArc(A,7,6);
   addArc(A,7,8);
   addArc(A,8,8);

   for(int i = 1; i<=getOrder(A);i++){
       append(L,i);
   }

   printGraph(stdout,A);
   printList(stdout,L);
   fprintf(stdout,"\n");
   DFS(A,L);
   printList(stdout,L);
   fprintf(stdout, "\n\n\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=getOrder(A); i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));
   }

   Graph B = copyGraph(A);
   printGraph(stdout,B);

   Graph C = transpose(A);
   printGraph(stdout,C);

   List S = copyList(L);
   printList(stdout,S);

   DFS(C,L);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=getOrder(C); i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(C, i), getFinish(C, i), getParent(C, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, L);
   fprintf(stdout, "\n");

   for(int i=1; i<=getOrder(C);i++){
      if(getParent(C,i) == -10){
         int index = 0;
         moveTo(L,index);
         a = getElement(L);
         while(index<length(L) && a!=i){
           index++;
           moveNext(L);
           a = getElement(L);
         }
         fprintf(stdout,"connected components of %d: %d ",i,i);
         index++;
         if(index<length(L)){
            moveNext(L);
            b = getElement(L);
         }
         while(index<length(L) && getParent(C,b) != -10){
           fprintf(stdout,"%d ",b);
           index++;
           if(index<length(L)){
              moveNext(L);
              b = getElement(L);
           }
         }
         fprintf(stdout,"\n");
      }
   }

   //free all graphs and lists
   freeGraph(&A);
   freeGraph(&B);
   freeGraph(&C);
   freeList(&S);
   freeList(&L);

   return(0);
}