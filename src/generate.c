#include "../headers/generate.h"

/** Mapping du Chessboard **/
const char * CHESSBOARD[8][8] = { 
	{ "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1" },	//0
	{ "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2" }, //2
	{ "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3" }, //14
	{ "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4" }, //16
	{ "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5" }, //18
	{ "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6" }, //20
	{ "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7" }, //22
	{ "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8" }, //24

};

/** Génération d'un graphe 64x64 **/
Graph newChessboardForKnight()
{
	GraphElement * element;
	element = malloc(sizeof(*element));
	if(!element)
	{
		printf("["), color(RED), printf("!"), resetColor, fprintf(stderr, "] Unable to allocate the chessboard, out of memory\n");
		exit(EXIT_FAILURE);
	}

	element->nbVertices = NUM_TILES;

	element->tabNeighbours = malloc(NUM_TILES * sizeof(AdjacencyListElement));
	if(!element->tabNeighbours)
	{
		printf("["), color(RED), printf("!"), resetColor, fprintf(stderr, "] Unable to allocate the neighbours, out of memory\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i < element->nbVertices + 1; ++i)
		element->tabNeighbours[i - 1].begin = NULL;
	
	return element;
}

/** Si le graphe est vide **/
bool isEmptyGraph(Graph g)
{
	return !g ? true : false;
}

/** Ajout d'un noeud **/
NodeList addNode(int x)
{
	NodeListElement * n = malloc(sizeof(NodeListElement));
	if(!n)
	{
		printf("["), color(RED), printf("!"), resetColor, fprintf(stderr, "] Unable to allocate the node, out of memory\n");
		exit(EXIT_FAILURE);
	}

	n->value = x;
	n->next = NULL;

	return n;
}

/** Assignationdes cases en fonction de la valeur de la case (i.e 0 === A1) **/ 
const char * assignCase(int x)
{
	if(x == 49)
		return "A7";
	if(x <= NUM_TILES_PER_ROW)
		return CHESSBOARD[(int)(x / 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 16)
		return CHESSBOARD[(int)((x + 2)/ 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 24)
		return CHESSBOARD[(int)((x + 3) / 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 29)
		return CHESSBOARD[(int)((x + 5) / 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 32)
		return CHESSBOARD[(int)(x/ 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 40)
		return CHESSBOARD[(int)((x + 7) / 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 48)
		return CHESSBOARD[(int)((x + 9)/ 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= 56)
		return CHESSBOARD[(int)((x + 10)/ 10)][(x - 1) % NUM_TILES_PER_ROW];
	else if(x <= NUM_TILES)
		return CHESSBOARD[(int)((x + 13)/ 10)][(x - 1) % NUM_TILES_PER_ROW];
	return "";

}

/** Ajout d'un arc **/
void addEdge(Graph g, int src, int dest)
{
	NodeList n = addNode(dest);
	n->next = g->tabNeighbours[src - 1].begin;
	g->tabNeighbours[src - 1].begin = n;
}

/** Affichage du graphe **/
void printGraph(Graph g)
{
	printf("["), color(GREEN), printf("+"), resetColor, puts("] Printing graph :");
	for(int i = 1; i < g->nbVertices + 1; ++i)
	{
		NodeList n = g->tabNeighbours[i - 1].begin;
		printf("(%d) Case ", i), color(BLUE), printf("%s", assignCase(i)), resetColor, printf(": [");

		while(n)
		{
			if(n->next)
				color(GREEN), printf("%s", assignCase(n->value)), resetColor, printf(", ");
			else
				color(GREEN), printf("%s", assignCase(n->value)), resetColor;
			n = n->next;
		}
		puts("]");
	}
}

/** Affiche la zone optimale où on peut jouer **/
void printOptimalZone(Graph g)
{
	printf("["), color(GREEN), printf("+"), resetColor, puts("] Printing Optimal Zone:");
	for(int i = 1; i < g->nbVertices + 1; ++i)
	{
		NodeList n = g->tabNeighbours[i - 1].begin;
		int length = getLength(n);
		if(length == 2)
			color(RED);
		else if(length == 3)
			color(MAGENTA);
		else if(length == 4)
			color(BLUE);
		else if(length == 6)
			color(YELLOW);
		else if(length == 8)
			color(GREEN);
		printf("%3d ", length), resetColor;
		if(!(i % 8))
			puts("");
	}
	printf("In "), color(GREEN), printf("green"), resetColor, puts(" this is the optimal zone to play with the Knight");
}

/** Efface le graphe **/
void eraseGraph(Graph g)
{
	printf("["), color(RED), printf("-"), resetColor, puts("] Erasing graph");
	if(!isEmptyGraph(g))
	{
		if(g->tabNeighbours)
		{
			for(int i = 1; i < g->nbVertices + 1; ++i)
			{
				NodeList n = g->tabNeighbours[i - 1].begin;

				while(n != NULL)
				{
					NodeList tmp = n;
					n = n->next;
					free(tmp);
				}
			}
			free(g->tabNeighbours);
		}
		free(g);
	}
}

/** Construit le graphe pour le cavalier
 * 
 *  et le tri dans l'ordre croissant pour extraire plus facilement la matrice d'adjacence 
**/
Graph buildKnightGraph()
{
	printf("["), color(GREEN), printf("+"), resetColor, puts("] Creating the Knight's Graph");
	Graph g = newChessboardForKnight();

	printf("["), color(GREEN), printf("+"), resetColor, puts("] Assigning edges to the graph");
	for(int i = 1; i < g->nbVertices + 1; ++i)
		assignEdges(g, i);

	graphSort(g);

	return g;
}

/** Si on est en dehors de l'échiquier **/
bool isOutOfBounds(int x)
{
	if(x < 0 || x > NUM_TILES)
		return true;
	return false;
}

/** Assigne les arcs pour le graphe du cavalier **/
void assignEdges(Graph g, int position)
{
	int * legalMoves = calculateLegalMoves(position);
	for(int i = 0; i < NUM_TILES_PER_ROW; ++i)
		if(!isOutOfBounds(legalMoves[i]) && legalMoves[i] != 0)
			addEdge(g, position, legalMoves[i]);

	free(legalMoves);
}

/** Calcule les moves légaux et les renvois sous forme d'un tableau **/
int * calculateLegalMoves(int position)
{
	int * legalMove = malloc(NUM_TILES_PER_ROW * sizeof(int));
	if(!legalMove)
	{
		printf("["), color(RED), printf("!"), resetColor, fprintf(stderr, "] Unable to allocate legal moves, out of memory\n");
		exit(EXIT_FAILURE);
	}

	int vectorMove[NUM_TILES_PER_ROW] = {-17, -15, -10, -6, 6, 10, 15, 17};

	for(int i = 0; i < NUM_TILES_PER_ROW; ++i)
	{
		int candidate = position + vectorMove[i];
		if(!isValidMove(position, candidate))
			legalMove[i] = -1;

		else
			legalMove[i] = candidate;
	}

	return legalMove;
}

/** Si le move est valide **/
bool isValidMove(int position, int candidate)
{
	return !isOnSameLine(position, candidate) && !isExclusionChessboard(position, candidate);
}

/** Extrait la matrice a partir des listes d'adjacences du graphe **/
int ** getAdjacencyMatrix(Graph g)
{
	int ** adjacencyMatrix = (int **)calloc(NUM_TILES, sizeof(int *));
	for(int i = 0; i < NUM_TILES; ++i)
		adjacencyMatrix[i] = (int *)calloc(NUM_TILES, sizeof(int));

	for(int i = 1; i < g->nbVertices + 1; ++i)
	{
		NodeList n = g->tabNeighbours[i - 1].begin;
		for(int j = 0; j < NUM_TILES; ++j)
		{
			if(!n)
				break;

			else if(n->value - 1 == j)
			{
				adjacencyMatrix[i - 1][j] = 1;
				n = n->next;
			}

		}
	}

	return adjacencyMatrix;
}

/** Swap deux noeuds **/
NodeList swapNode(NodeList n1, NodeList n2)
{
	NodeList n = n2->next;
	n2->next = n1;
	n1->next = n;
	return n2;
}

/** Bubblesort sur liste **/
void bubbleSort(NodeList * head, int count)
{
	NodeList * h;
	int i, j;
	bool swapped;

	for(i = 0; i <= count; ++i)
	{
		h = head;
		swapped = false;

		for(j = 0; j < count - i - 1; ++j)
		{
			NodeList n1 = *h;
			NodeList n2 = n1->next;

			if(n1->value > n2->value)
			{
				*h = swapNode(n1, n2);
				swapped = true;
			}

			h = &(*h)->next;
		}

		if(!swapped)
			break;
	}
}

/** Graph sort utilisant bubble sort **/
void graphSort(Graph g)
{
	for(int i = 1; i < g->nbVertices + 1; ++i)
	{
		int length = getLength(g->tabNeighbours[i - 1].begin);
		bubbleSort(&(g->tabNeighbours[i - 1].begin), length);
	}
}

/** Accesseur de la taille de la liste **/
int getLength(NodeList n)
{
	if(!n) return 0;
	return 1 + getLength(n->next);
}

/** Efface une matrice 2D **/
void free2D(int ** matrix, int nbLine)
{
	for(int i = 0; i < nbLine; ++i)
		free(matrix[i]);
	free(matrix);
}

/** Affice une matrice 2D **/
void print2D(int ** matrix, int nbLine, int nbCol)
{
	for(int i = 0; i < nbLine; ++i)
	{
		for(int j = 0; j < nbCol; ++j)
			printf("%3d ", matrix[i][j]);
		printf("\n");
	}
}



























bool isOnSameLine(int position, int candidate)
{
	return ((position > 0 && position <= 8) && (candidate > 0 && candidate <= 8))     ||
		   ((position > 8 && position <= 16) && (candidate > 8 && candidate <= 16))   ||
		   ((position > 16 && position <= 24) && (candidate > 16 && candidate <= 24)) ||
		   ((position > 24 && position <= 32) && (candidate > 24 && candidate <= 32)) ||
		   ((position > 32 && position <= 40) && (candidate > 32 && candidate <= 40)) ||
		   ((position > 40 && position <= 48) && (candidate > 40 && candidate <= 48)) ||
		   ((position > 48 && position <= 56) && (candidate > 48 && candidate <= 56)) ||
		   ((position > 56 && position <= 64) && (candidate > 56 && candidate <= 64));
}

bool isExclusionChessboard(int position, int candidate)
{
	return ((position == 1 && candidate == 16) || 
			(position == 7 && candidate == 17) || 
			(position == 8 && (candidate == 25 || candidate == 18)) || 
			(position == 9 && candidate == 24) || 
			(position == 15 && candidate == 25) || 
			(position == 16 && (candidate == 33 || candidate == 26 || candidate == 1)) || 
			(position == 17 && (candidate == 7 || candidate == 32)) || 
			(position == 18 && candidate == 8) || 
			(position == 23 && candidate == 33) || 
			(position == 24 && (candidate == 41 || candidate == 9 || candidate == 34)) || 
			(position == 25 && (candidate == 40 || candidate == 15 || candidate == 8)) || 
			(position == 26 && candidate == 16) || 
			(position == 31 && candidate == 41) || 
			(position == 32 && (candidate == 41 || candidate == 42 || candidate == 17 || candidate == 49)) || 
			(position == 33 && (candidate == 48 || candidate == 23 || candidate == 16)) || 
			(position == 34 && candidate == 24) || 
			(position == 39 && candidate == 49) || 
			(position == 40 && (candidate == 57 || candidate == 50 || candidate == 25)) || 
			(position == 41 && (candidate == 56 || candidate == 31 || candidate == 24)) || 
			(position == 42 && candidate == 32) || 
			(position == 47 && candidate == 57) || 
			(position == 48 && (candidate == 58 || candidate == 33)) || 
			(position == 49 && (candidate == 64 || candidate == 32 || candidate == 39)) || 
			(position == 50 && candidate == 40) || 
			(position == 56 && candidate == 41) || 
			(position == 57 && (candidate == 47 || candidate == 40)) || (position == 58 && candidate == 48) ||
			(position == 64 && candidate == 49));
}