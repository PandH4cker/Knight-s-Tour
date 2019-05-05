#ifndef GENERATE_H
#define GENERATE_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_TILES 64
#define NUM_TILES_PER_ROW 8

/** Définition d'un noeud (sommet) / Une case de l'échiquier **/
typedef struct NodeListElement
{
	int 		  			 value;
	struct NodeListElement * next;
}NodeListElement, * NodeList;

/** Définition d'une liste d'adjacence **/
typedef struct AdjacencyListElement
{
	NodeListElement * begin;
}AdjacencyListElement, * AdjacencyList;

/** Définition d'un graphe / Notre échiquier **/
typedef struct GraphElement
{
	int 		nbVertices;
	AdjacencyList tabNeighbours;
}GraphElement, * Graph;

Graph newChessboardForKnight();
Graph buildKnightGraph();
NodeList addNode(int x);
NodeList swapNode(NodeList n1, NodeList n2);
int getLength(NodeList n);
int * calculateLegalMoves(int position);
int ** getAdjacencyMatrix(Graph g);
bool isEmptyGraph(Graph g);
bool isOutOfBounds(int x);
bool isOnSameLine(int position, int candidate);
bool isExclusionChessboard(int position, int candidate);
bool isValidMove(int position, int candidate);
void addEdge(Graph g, int src, int dest);
void assignEdges(Graph g, int position);
void printGraph(Graph g);
void printOptimalZone(Graph g);
void eraseGraph(Graph g);
void free2D(int ** matrix, int nbLine);
void print2D(int ** matrix, int nbLine, int nbCol);
void bubbleSort(NodeList * head, int count);
void graphSort(Graph g);
const char * assignCase(int x);

#endif