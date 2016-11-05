//Christina Duran
//crduran
//cmps101
//11/21/14
//Graph ADT in C that creates and array of lists to be used by client

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"
#define INF -2   //used for vertecies that have no path from one to another to represent distance
#define NIL -10  //used for vertecies that have no parent and undecided source vertex

//structures

//structure of Graph
typedef struct GraphObj{
   List* row; //array of lists
   int* color; //WHITE = 0, GRAY = 1, BLACK = 2
   int* parent;
   int* dist;
   int order; //number of vertices
   int size;  //number of edges
   int source; //current BFS source
}GraphObj;

typedef GraphObj* Graph;

//Graph constructor
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->row = calloc(n+1, sizeof(List*));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->dist = calloc(n+1, sizeof(int));
   G->order = n;
   G->size = 0;
   G->source = NIL;
   for(int i=1; i<n+1; i++){
        G->row[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->dist[i] = INF;
   }
   return G;
}

//frees Graph and other calloc/malloc uses
void freeGraph(Graph* pG){
   if(pG != NULL && *pG != NULL){
      while(getSize(*pG)!=0){
         makeNull(*pG);
      }
   }
   free((*pG)->row);
   free((*pG)->color);
   free((*pG)->parent);
   free((*pG)->dist);
   free(*pG);
   *pG = NULL;
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

//returns the current source used in most recent BFS
//run, if BFS has not been run it returns NIL
int getSource(Graph G){
    return G->source;
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

//returns the distance from vertex u to the source
//if BFS has been run, if there is no path from u to 
//source there is an infinite distance and returns
//INF. Or returns INF if BFS has not been run yet
//vertex must exist in the order of vertecies
//pre:1<=u<=getOrder(G)
int getDist(Graph G, int u){
   if(1<=u && u<=getOrder(G)){
      return G->dist[u];
   }
   return NIL;
}

//uses recursion to add to a list the vertecies that 
//are connected by edges that make the shortest path
//from u to the source
//pre:getSource(G)!=NIL, 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u){
 if(1<=u && u<=getOrder(G)){
   if(getSource(G) != NIL){
     if(u == G->source){
        append(L,G->source);
     }else if(G->parent[u] == NIL){
        append(L, INF);
     }else{
        getPath(L,G,G->parent[u]);
        append(L,u);
     }
   }
  }
}

//Manipulation procedures

//sets graph as a null graph deleting all edges
//connecting vertecies
void makeNull(Graph G){
   for(int i=1; i<=G->order;i++){
       freeList(&G->row[i]);
       G->color[i] = 0;
       G->parent[i] = NIL;
       G->dist[i] = INF;
   }
   G->size = 0;
}

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

//searches through graph for white (0) vertecies in
//increasing order if they are undiscovered white vertecies
//to determine their parent vertecies and distances
//based on current inserted source vertex
void BFS(Graph G, int s){
   int i = 1;
   int x;
   G->source = s;
   List Q = newList();
   while(i<=G->order){
       if(i != s){
           G->color[i] = 0;
           G->dist[i] = INF;
           G->parent[i] = NIL;
       }
       i++;
   }
   G->color[s] = 1;
   G->dist[s] = 0;
   G->parent[s] = NIL;
   append(Q,s);
   while(length(Q) > 0){
       x = front(Q);
       moveTo(G->row[x],0);
       while(getIndex(G->row[x]) != -1){
            int y = getElement(G->row[x]);
            if(G->color[y] == 0){
                 G->color[y] = 1;
                 G->dist[y] = G->dist[x]+1;
                 G->parent[y] = x;
                 append(Q,y);
            }
            moveNext(G->row[x]);
       }
       G->color[x] = 2;
       deleteFront(Q);
    }
    freeList(&Q);
}

//Other operations

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