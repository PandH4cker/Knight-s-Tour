#include "../headers/knighttour.h"

/** Parcours en profondeur **/
void DFS(int ** adjacencyMatrix, int i, bool visited[], int * count, int ** outputMatrix)
{	
	assignToMatrix(outputMatrix, i + 1, *count);
	if(*count < 63)
		color(BLUE), printf("%s", assignCase(i + 1)), resetColor, printf("["), color(YELLOW), printf("%d", i), resetColor, printf("]"), printf("("), color(GREEN), printf("%d", (*count)++), resetColor, printf(") > ");

	else
		color(BLUE), printf("%s", assignCase(i + 1)), resetColor, printf("["), color(YELLOW), printf("%d", i), resetColor, printf("]"), printf("("), color(GREEN), printf("%d", *count), resetColor, printf(")");

	
	visited[i] = true;

	for(int j = 0; j < NUM_TILES; ++j)
		if(!visited[j] && adjacencyMatrix[i][j])
			DFS(adjacencyMatrix, j, visited, count, outputMatrix);
}
 /** Parcours du cavalier **/
void knightTour(int ** adjacencyMatrix, int startingCase)
{
	bool visited[NUM_TILES];
	for(int i = 0; i < NUM_TILES; ++i)
		visited[i] = false;

	int count = 0;
	int ** outputMatrix = (int **)calloc(NUM_TILES_PER_ROW, sizeof(int *));
	for(int i = 0; i < NUM_TILES_PER_ROW; ++i)
		outputMatrix[i] = (int *)calloc(NUM_TILES_PER_ROW, sizeof(int));

	DFS(adjacencyMatrix, startingCase - 1, visited, &count, outputMatrix);

	printf("\n\n\n");
	printf("["), color(GREEN), printf("+"), resetColor, printf("] There is the output matrix for the starting case:"), color(BLUE), printf(" %s\n", assignCase(startingCase)), resetColor;
	print2D(outputMatrix, NUM_TILES_PER_ROW, NUM_TILES_PER_ROW);
	free2D(outputMatrix, NUM_TILES_PER_ROW);
}

/** Assignation à la matrice du parcours du cavalier **/
void assignToMatrix(int ** Matrix, int index, int weight)
{
	int x,y;
	if(index == 49)
	{
		x = 6;
		y = 0;
		Matrix[x][y] = weight;
		return;
	}

	y = (index - 1) % NUM_TILES_PER_ROW;

	x = (index <= NUM_TILES_PER_ROW) ? (int)(index / 10) :
		(index <= NUM_TILES_PER_ROW * 2) ? (int)((index + 2) / 10) :
		(index <= NUM_TILES_PER_ROW * 3) ? (int)((index + 3) / 10) :
		(index <= 29) ? (int)((index + 5) / 10) :
		(index <= NUM_TILES_PER_ROW * 4) ? (int)(index / 10) :
		(index <= NUM_TILES_PER_ROW * 5) ? (int)((index + 7) / 10) :
		(index <= NUM_TILES_PER_ROW * 6) ? (int)((index + 9) / 10) :
		(index <= NUM_TILES_PER_ROW * 7) ? (int)((index + 10) / 10):
		(index <= NUM_TILES) ? (int)((index + 13) / 10) : -1;

	if(x == -1)
		exit(EXIT_FAILURE);

	Matrix[x][y] = weight;
}