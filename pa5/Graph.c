//Christina Duran
//crduran
//cmps101
//12/08/14
//Graph ADT in C that creates and array of lists to be used by client

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"
#define UNDEF -2   //used for vertecies that have no path from one to another to represent distance
#define NIL -10  //used for vertecies that have no parent and undecided source vertex
int time = 0;

//structures

//structure of Graph
typedef struct GraphObj{
   List* row; //array of lists
   int* color; //WHITE = 0, GRAY = 1, BLACK = 2
   int* parent;   //parent of specified decendant vertex
   int* discTime;   //discover time of DFS
   int* finishTime; //finish time of DES
   int order; //number of vertices
   int size;  //number of edges
}GraphObj;

typedef GraphObj* Graph;

//Graph constructor
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->row = calloc(n+1, sizeof(List*));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->discTime = calloc(n+1, sizeof(int));
   G->finishTime = calloc(n+1, sizeof(int));
   G->order = n;
   G->size = 0;
   for(int i=1; i<n+1; i++){
        G->row[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
   }
   return G;
}

//frees Graph and other calloc/malloc uses
void freeGraph(Graph* pG){
 if(pG!=NULL && *pG!=NULL){
   for(int i = 0;i<=(*pG)->order;i++){
       freeList(&(*pG)->row[i]);
   }
   free((*pG)->row);
   (*pG)->size = 0;
   free((*pG)->color);
   free((*pG)->parent);
   free((*pG)->discTime);
   free((*pG)->finishTime);
   free(*pG);
   *pG = NULL;
 }
}

//recursive function for DFS
void visit(Graph G, int x, List S){
   G->color[x] = 1;
   time = time+1;
   G->discTime[x] = time;
   for(int y = 0; y<length(G->row[x]); y++){
      moveTo(G->row[x],y);
      int g = getElement(G->row[x]);
      if(G->color[g] == 0){
          G->parent[g] = x;
          visit(G,g,S);
      }
   }
   G->color[x] = 2;
   time = time+1;
   G->finishTime[x] = time;
   prepend(S,x);
}

//Access functions

//returns the number of vertices
int getOrder(Graph G){
   return G->order;
}

//returns the number of edges
int getSize(Graph G){
   return G->size;
}

//returns the parent of a specific vertex u
//after BFS has been run, returns NIL if it
//has no parent or BFS has not been ran yet
//vertex must exist in the order of vertecies
//pre:1<=u<=getOrder(G)
int getParent(Graph G, int u){
   if(1<=u && u<=getOrder(G)){
      return G->parent[u];
   }
   return NIL;
}

/* Pre: 1<=u<=getOrder(G)*/
int getDiscover(Graph G, int u){
   if(1<=u && u<=getOrder(G)){
      return G->discTime[u];
   }
   return UNDEF;
}

/* Pre: 1<=u<=getOrder(G)*/
int getFinish(Graph G, int u){
   if(1<=u && u<=getOrder(G)){
      return G->finishTime[u];
   }
   return UNDEF;
}

//Manipulation procedures

//adds and edge between two vertecies to build a graph
//by adding each other to the others adjacency list
//in increasing order
//pre: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v){
  if((1<=u && u<=getOrder(G)) && (1<=v && v<=getOrder(G))){
      int i =0;
      int j =0;
      if(length(G->row[u]) == 0 && length(G->row[v]) == 0){
         append(G->row[u],v);
         append(G->row[v],u);
         (G->size)++;
      }else if(length(G->row[u]) == 0 && length(G->row[v]) > 0){
         append(G->row[u],v);
         while(j < length(G->row[v])){
           moveTo(G->row[v],i);
           if(u != getElement(G->row[v])){
              if(u < getElement(G->row[v])){
                insertBefore(G->row[v],u);
                (G->size)++;
                break;
              }if(j == length(G->row[v])-1 && u > getElement(G->row[v])){
                append(G->row[v],u);
                (G->size)++;
                break;
            }
           }else{
             break;
           }
           j++;
         }
      }else if(length(G->row[v]) == 0 && length(G->row[u]) > 0){
         append(G->row[v],u);
         while(i < length(G->row[u])){
            moveTo(G->row[u],i);
             if(v != getElement(G->row[u])){
              if(v < getElement(G->row[u])){
                insertBefore(G->row[u],v);
                (G->size)++;
                break;
              }if(i == length(G->row[u])-1 && v > getElement(G->row[u])){
                append(G->row[u],v);
                (G->size)++;
                break;
            }
           }else{
              break;
           }
           i++;
         }
      }else if(length(G->row[u]) > 0 && length(G->row[v]) > 0){
         while(i < length(G->row[u])){
           moveTo(G->row[u],i);
           if(v != getElement(G->row[u])){
              if(v < getElement(G->row[u])){
                insertBefore(G->row[u],v);
                (G->size)++;
                break;
              }if(i == length(G->row[u])-1 && v > getElement(G->row[u])){
                append(G->row[u],v);
                (G->size)++;
                break;
            }
           }else{
              break;
           }
           i++;
         }
         while(j < length(G->row[v])){
           moveTo(G->row[v],j);
           if(u != getElement(G->row[v])){
              if(u < getElement(G->row[v])){
                insertBefore(G->row[v],u);
                break;
              }if(j == length(G->row[v])-1 && u > getElement(G->row[v])){
                append(G->row[v],u);
                break;
            }
           }else{
             break;
           }
           j++;
         }
      }
   }
}

//adds a directed edge between two vertecies but only
//add vertex v to the outgoing edge adjacency list
//of u in increasing order, and nothing to v
//pre:1<=u<=getOrder(G) and 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v){
   if((1<=u && u<=getOrder(G)) && (1<=v && v<=getOrder(G))){
      int i = 0;
      if(length(G->row[u]) == 0){
         append(G->row[u],v);
         (G->size)++;
      }else if(length(G->row[u]) > 0){
         while(i < length(G->row[u])){
            moveTo(G->row[u],i);
             if(v != getElement(G->row[u])){
              if(v < getElement(G->row[u])){
                insertBefore(G->row[u],v);
                (G->size)++;
                break;
              }if(i == length(G->row[u])-1 && v > getElement(G->row[u])){
                append(G->row[u],v);
                (G->size)++;
                break;
            }
           }else{
              break;
           }
           i++;
         }
      }
   }
}

//uses recursion to discover vertecies and 
//find their discovery and finish times
//and find the strongly connected components
//pre:length(S)==getOrder(G)
void DFS(Graph G, List S){
   if(length(S)==getOrder(G)){
      for(int i = 1; i<=getOrder(G); i++){
         G->color[i] = 0;
         G->parent[i] = NIL;
      }
      int k = length(S);
      time = 0;
      moveTo(S,0);
      for(int j = 0; j<k; j++){
         int g = getElement(S);
         if(G->color[g] == 0){
             visit(G,g,S);
         }
         moveNext(S);
      }
      int g = length(S);
      for(int x = 0; x<(g/2);x++){
         deleteBack(S);
      }
   }
}

//Other operations

//alters the adjacency list so the new Graph has the ij elements of Graph G in its ji elements
Graph transpose(Graph G){
       Graph H = newGraph(getOrder(G));
       for(int i = 1; i<=getOrder(G); i++){
           for(int j = 0; j<length(G->row[i]); j++){
                moveTo(G->row[i],j);
                int k = getElement(G->row[i]);
                addArc(H,k,i);
           }
       }
       return H;
}

//makes a new graph identicle to Graph G
Graph copyGraph(Graph G){
       Graph H = newGraph(getOrder(G));
       for(int i = 1; i<=getOrder(G); i++){
          for(int j=0; j<length(G->row[i]);j++){
            moveTo(G->row[i],j);
            int v = getElement(G->row[i]);
            addArc(H,i,v);
          }
      }
      for(int k = 1; k <= getOrder(G); k++){
        H->color[k] = G->color[k];
        H->parent[k] = G->parent[k];
        H->discTime[k] = G->discTime[k];
        H->finishTime[k] = G->finishTime[k];
   }
      return H;
}

//prints to out file the vertex number followed by a colon
//then the  adjacency list of each vertex in a graph
//one line for each vertex, if a vertex has no adjacent
//vertecies it will print a blank list
void printGraph(FILE* out, Graph G){
   for(int i = 1; i<=G->order; i++){
     fprintf(out,"%d %c ",i,':');
     printList(out, G->row[i]);
     fprintf(out,"%s","\n");
   }
}