//Graph.h for Graph.c ADT.

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

typedef struct GraphObj* Graph;

// Constructors-Destructors --------------------------------------------------- 
Graph newGraph(int n);   //creates a new graph from an array of lists and other constructor elements
void freeGraph(Graph* pG);   //frees array of lists and resets or frees other contructor elements

/*** Access functions ***/
int getOrder(Graph G);   //returns the number of vertecies of a graph
int getSize(Graph G);   //returns the number of edges between vertecies a graph has
int getParent(Graph G, int u);   /*Pre: 1<=u<=getOrder(G)*/
int getDiscover(Graph G, int u); /* Pre: 1<=u<=getOrder(G)*/
int getFinish(Graph G, int u); /* Pre: 1<=u<=getOrder(G)*/

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);   //adds an edge inbetween two inputed vertecies and increases the size of graph
void addArc(Graph G, int u, int v);   //add a directed edge outgoing from u to v and increases the size of graph
void DFS(Graph G, List s);   //pre:getLength(S)==getOrder(G). finds parents of vertecies and tree of the graph

/*** Other operations ***/
Graph transpose(Graph G); //returns the transpose of the graph G in a new graph
Graph copyGraph(Graph G); //make a new graph that is the same as graph G
void printGraph(FILE* out, Graph G); //prints the list of adjacent vertecies for each vertex in the graph on each line

#endif