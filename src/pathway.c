#include "../headers/pathway.h"

/** Récupère la plus petite distance parmis ceux visités **/
int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;
	for(int i = 0; i < NUM_TILES; ++i)
		if(sptSet[i] == false && dist[i] <= min)
			min = dist[i], min_index = i;
	return min_index;
}

/** Affiche récursivement le chemin **/
void printPath(int parent[], int j, int dest)
{
	if(parent[j] == -1)
		return;

	printPath(parent, parent[j], dest);
	if(j != dest)
		color(BLUE), printf("%s", assignCase(j + 1)), resetColor,  printf(" > ");
	else
		color(BLUE), printf("%s\n", assignCase(j + 1)), resetColor;
}

/** Affiche la solution finale **/
void printSolution(int src, int dest, int dist[], int parent[])
{
	color(MAGENTA), printf("Vertex\t\t"), color(YELLOW), printf("Distance\t\t"), color(CYAN), puts("Path"), resetColor;
	color(BLUE), printf("%s", assignCase(src + 1)), color(YELLOW), printf(" --> "), color(BLUE), printf("%s \t\t ", assignCase(dest + 1)), color(GREEN), printf("%d \t\t ", dist[dest]), color(BLUE), printf("%s ", assignCase(src + 1)), resetColor, printf("> ");
	printPath(parent, dest, dest);
}

/** Dijkstra **/
int dijkstra(int ** adjacencyMatrix, int src, int dest)
{
	printf("["), color(GREEN), printf("+"), resetColor, printf("] Calculating the shortest path for "), color(BLUE), printf("%s", assignCase(src + 1)), color(YELLOW), printf(" --> "), color(BLUE), printf("%s\n", assignCase(dest + 1)), resetColor;
	int dist[NUM_TILES];
	int parent[NUM_TILES];
	bool sptSet[NUM_TILES];

	parent[src] = -1;

	printf("["), color(GREEN), printf("+"), resetColor, puts("] Initializing the distances");
	for(int i = 0; i < NUM_TILES; ++i)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false; 
	}

	dist[src] = 0;

	printf("["), color(GREEN), printf("+"), resetColor, puts("] Calculating the distances");
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

	printf("["), color(GREEN), printf("+"), resetColor, puts("] Printing solution: \n");
	printSolution(src, dest, dist, parent);

	return dist[dest];
}

/** Affiche la distance maximale minimale entre deux cases **/
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

	printf("["), color(GREEN), printf("+"), resetColor, printf("] The max minimal distance is %d\n", maxMinDist);
}