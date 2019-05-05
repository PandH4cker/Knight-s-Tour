#ifndef MENU_H
#define MENU_H

#include "generate.h"
#include "pathway.h"
#include "knighttour.h"

char printMenu();
void askWithTreshold(int * asked, int ** adjacencyMatrix, Graph g);
void exitProg(int ** adjacencyMatrix, Graph g);
void clrscr(void);
void buildProg(void);

#endif