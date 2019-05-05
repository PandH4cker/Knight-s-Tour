#ifndef KNIGHTTOUR_H
#define KNIGHTTOUR_H

#include "generate.h"

void knightTour(int ** adjacencyMatrix, int startingCase);
void DFS(int ** adjacencyMatrix, int i, bool visited[], int * count, int ** outputMatrix);
void assignToMatrix(int ** Matrix, int index, int weight);
#endif