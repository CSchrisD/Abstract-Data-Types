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
int getSource(Graph G);   //returns the current source element if BFS has been ran previously
int getParent(Graph G, int u);   //returns the parent vertex of inputed vertex if BFS was ran previously
int getDist(Graph G, int u);   //returns the distance between the source and inputed vertex if BFS was ran preveously
void getPath(List L, Graph G, int u);   //prints the vertecies between inputed vertex and the source vertex if BFS was ran preveously

/*** Manipulation procedures ***/
void makeNull(Graph G);   //sets graph to have no edges between vertecies
void addEdge(Graph G, int u, int v);   //adds an edge inbetween two inputed vertecies and increases the size of graph
void addArc(Graph G, int u, int v);   //add a directed edge outgoing from u to v and increases the size of graph
void BFS(Graph G, int s);   //sets source of graph and finds parents of vertecies and tree of the graph

/*** Other operations ***/
void printGraph(FILE* out, Graph G); //prints the list of adjacent vertecies for each vertex in the graph on each line

#endif