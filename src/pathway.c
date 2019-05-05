#include "../headers/pathway.h"

int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;
	for(int i = 0; i < NUM_TILES; ++i)
		if(sptSet[i] == false && dist[i] <= min)
			min = dist[i], min_index = i;
	return min_index;
}

void printPath(int parent[], int j, int dest)
{
	if(parent[j] == -1)
		return;

	printPath(parent, parent[j], dest);
	if(j != dest)
		printf("%s > ", assignCase(j + 1));
	else
		printf("%s\n", assignCase(j + 1));
}

void printSolution(int src, int dest, int dist[], int parent[])
{
	printf("Vertex\t\t Distance\t\t Path");
	printf("\n%s --> %s \t\t %d \t\t %s > ", 
		   assignCase(src + 1), assignCase(dest + 1), 
		   dist[dest], assignCase(src + 1));
	printPath(parent, dest, dest);
}

int dijkstra(int ** adjacencyMatrix, int src, int dest)
{
	printf("[+] Calculating the shortest path for %s --> %s\n", assignCase(src + 1), assignCase(dest + 1));
	int dist[NUM_TILES];
	int parent[NUM_TILES];
	bool sptSet[NUM_TILES];

	parent[src] = -1;

	printf("[+] Initializing the distances\n");
	for(int i = 0; i < NUM_TILES; ++i)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false; 
	}

	dist[src] = 0;

	printf("[+] Calculating the distances\n");
	for(int count = 0; count < NUM_TILES - 1; ++count)
	{
		int u = minDistance(dist, sptSet);
		sptSet[u] = true;
		for(int v = 0; v < NUM_TILES; ++v)
		{
			if(!sptSet[v] && adjacencyMatrix[u][v] &&
				dist[u] + adjacencyMatrix[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + adjacencyMatrix[u][v];
			}
		}

	}

	printf("[+] Printing solution: \n");
	printSolution(src, dest, dist, parent);

	return dist[dest];
}

void findMaxMinDist(int ** adjacencyMatrix)
{
	int maxMinDist = 0;
	int tempMax;
	for(int i = 0; i < NUM_TILES; ++i)
		for(int j = 0; j < NUM_TILES; ++j)
		{
			if(i == j) 
				continue;

			tempMax = dijkstra(adjacencyMatrix, i, j);
			if(tempMax > maxMinDist)
				maxMinDist = tempMax;
		}

	printf("[+] The max minimal distance is %d\n", maxMinDist);
}