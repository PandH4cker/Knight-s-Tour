#ifndef PATHWAY_H
#define PATHWAY_H

/** Définition de l'infini **/
#define IN 99

#include "generate.h"
#include <string.h>
#include <limits.h>

/** Prototypes **/
int minDistance(int dist[], bool sptSet[]);
int dijkstra(int ** adjacencyMatrix, int src, int dest);
void findMaxMinDist(int ** adjacencyMatrix);
void printPath(int parent[], int j, int dest);
void printSolution(int src, int dest, int dist[], int parent[]);
void printAllPaths(Graph g, int source, int dest);
void printAllPathsUtil(Graph g, int source, int dest, 
					   bool visited[], int path[], int path_index);
#endif