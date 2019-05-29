#include "../headers/menu.h"

/** Affiche le menu **/
char printMenu()
{
	clrscr();
	color(CYAN), printf("\n\n\t\t\t=== MENU ===\n\n"), resetColor;
	printf("["), color(YELLOW), printf("1"), resetColor, puts("] Print the graph");
	printf("["), color(YELLOW), printf("2"), resetColor, puts("] Calculate the shortest path between two positions");
	printf("["), color(YELLOW), printf("3"), resetColor, puts("] Print optimal zone");
	printf("["), color(YELLOW), printf("4"), resetColor, puts("] Find max minimal distance");
	printf("["), color(YELLOW), printf("5"), resetColor, puts("] Knight's Tour");
	printf("["), color(YELLOW), printf("Q/q"), resetColor, puts("] Exit");
	puts("Make your choice !");
	return getchar();
}

/** Demande avec seuil **/
void askWithTreshold(int * asked, int ** adjacencyMatrix, Graph g)
{
	do {
		color(RED), printf("Enter a number between 1 and 64: ");
		if(scanf("%d", asked) != 1)
		{
			fprintf(stderr, "[!] You may enter a number\n");
			free2D(adjacencyMatrix, NUM_TILES);
			eraseGraph(g);
			exit(EXIT_FAILURE);
		}
	}while(*asked < 1 || *asked > 64);
	resetColor;
}

/** Quitte le programme **/
void exitProg(int ** adjacencyMatrix, Graph g)
{
	clrscr();
	color(GREEN), puts("Byebye :)"), resetColor;
	free2D(adjacencyMatrix, NUM_TILES);
	eraseGraph(g);
	resetColor, exit(EXIT_SUCCESS);
}

/** Coeur du programme **/
void buildProg(void)
{
	Graph g = buildKnightGraph();
	int ** adjacencyMatrix = getAdjacencyMatrix(g);
	char choice;
	do {
		choice = printMenu();
		switch(choice)
		{
			case '1':
				printGraph(g);
			break;
			case '2':
			{
				int src, dest;
				askWithTreshold(&src, adjacencyMatrix, g);
				askWithTreshold(&dest, adjacencyMatrix, g);				
				dijkstra(adjacencyMatrix, src - 1, dest - 1);
			}
			break;
			case '3':
				printOptimalZone(g);
			break;
			case '4':
				findMaxMinDist(adjacencyMatrix);
			break;
			case '5':
			{
				int startingCase;
				puts("Enter the number for the starting case");
				askWithTreshold(&startingCase, adjacencyMatrix, g);
				knightTour(adjacencyMatrix, startingCase);
			}
			break;
			case 'Q':
			case 'q':
				exitProg(adjacencyMatrix, g);
			break;
			default:
			break;
		}
		color(MAGENTA), printf("\nReturning to main menu..."), resetColor;
		getchar();
		getchar();
	} while(choice != 'q');
}