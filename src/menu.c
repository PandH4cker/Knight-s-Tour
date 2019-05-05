#include "../headers/menu.h"

char printMenu()
{
	clrscr();
	printf("\n\n\t\t\t=== MENU ===\n\n");
	puts("[1] Print the graph");
	puts("[2] Calculate the shortest path between two positions");
	puts("[3] Print optimal zone");
	puts("[4] Find max minimal distance");
	puts("[5] Knight's Tour");
	puts("[Q/q] Exit");
	puts("Make your choice !");
	return getchar();
}

void askWithTreshold(int * asked, int ** adjacencyMatrix, Graph g)
{
	do {
		printf("Enter a number between 1 and 64: ");
		if(scanf("%d", asked) != 1)
		{
			fprintf(stderr, "[!] You may enter a number\n");
			free2D(adjacencyMatrix, NUM_TILES);
			eraseGraph(g);
			exit(EXIT_FAILURE);
		}
	}while(*asked < 1 || *asked > 64);
}

void exitProg(int ** adjacencyMatrix, Graph g)
{
	clrscr();
	puts("Byebye :)");
	free2D(adjacencyMatrix, NUM_TILES);
	eraseGraph(g);
	exit(EXIT_SUCCESS);
}

void buildProg(void)
{
	Graph g = buildKnightGraph();
	int ** adjacencyMatrix = getAdjacencyMatrix(g);
	//print2D(adjacencyMatrix, NUM_TILES, NUM_TILES);
	//exitProg(adjacencyMatrix, g);
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
		printf("\nReturning to main menu...");
		getchar();
		getchar();
	} while(choice != 'q');
}

void clrscr(void)
{
	system("@cls||clear");
}