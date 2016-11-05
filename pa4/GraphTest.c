//Christina Duran
//crduran
//cmps101
//11/21/14
//Personal GraphTest.c to test functions in Graph.c to see if they 
//comply with the expectations of current programing assignment
//so that all funtions of Graph.c work properly

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   //create new graphs and lists
   Graph A = newGraph(6);
   Graph B = newGraph(4);
   Graph C = newGraph(4);
   Graph D = newGraph(7);
   List L = newList();
   List H = newList();
   List G = newList();

   //add edges or arcs to graphs
   addEdge(A,1,2);
   addEdge(A,1,4);
   addEdge(A,1,5);
   addEdge(A,2,3);
   addEdge(A,2,5);
   addEdge(A,2,6);
   addEdge(A,3,5);
   addEdge(A,3,6);
   addEdge(A,4,5);
   addEdge(A,5,6);

   addEdge(B,1,2);
   addEdge(B,1,3);
   addEdge(B,1,4);

   addArc(C,1,2);
   addArc(C,1,4);
   addArc(C,3,1);
   addArc(C,4,2);
   addArc(C,4,3);

   addEdge(D,1,3);
   addEdge(D,1,2);
   addEdge(D,3,2);
   addEdge(D,2,4);
   addEdge(D,4,5);

   //print adjacency list, order, and size of A
   //B and C
   printGraph(stdout,A);
   fprintf(stdout,"%d \n", getOrder(A));
   fprintf(stdout,"%d \n", getSize(A));

   printGraph(stdout,B);
   fprintf(stdout,"%d \n", getOrder(B));
   fprintf(stdout,"%d \n", getSize(B));

   printGraph(stdout,C);
   fprintf(stdout,"%d \n", getOrder(C));
   fprintf(stdout,"%d \n", getSize(C));

   //adds a new directed edge path in graph C
   addArc(C,2,3);
   printGraph(stdout,C);
   fprintf(stdout,"%d \n", getOrder(C));
   fprintf(stdout,"%d \n", getSize(C));

   //preforms BFS on A,B,C,D
   BFS(A,2);
   BFS(B,4);
   BFS(C,3);
   BFS(D,3);

   //prints parents and distances based on source for graphs
   fprintf(stdout,"%d\n",getParent(A,4));
   fprintf(stdout,"%d\n",getDist(A,4));

   fprintf(stdout,"%d\n",getParent(A,2));
   fprintf(stdout,"%d\n",getDist(A,2));

   fprintf(stdout,"%d\n",getParent(B,3));
   fprintf(stdout,"%d\n",getDist(B,3));

   fprintf(stdout,"%d\n",getParent(C,2));
   fprintf(stdout,"%d\n",getDist(C,3));

   //finds path from 4 to source in graph A
   getPath(L,A,4);

   //prints the path from previous call
   printList(stdout,L);
   fprintf(stdout,"\n");

   getPath(H,D,5);

   //prints path from source to 5
   printGraph(stdout,D);
   printList(stdout,H);
   fprintf(stdout,"\n");

   //adds a new edge and redoes BFS with new edge
   //making two connected components
   addEdge(D,6,7);
   BFS(D,3);
   getPath(G,D,6);

   //prints graph of D and path
   printGraph(stdout,D);
   printList(stdout,G);
   fprintf(stdout,"\n");

   //delete all edges in graph A
   makeNull(A);
   printGraph(stdout,A);

   //free all graphs and lists
   freeGraph(&A);
   freeGraph(&B);
   freeGraph(&C);
   freeGraph(&D);
   freeList(&L);
   freeList(&H);
   freeList(&G);

   return(0);
}