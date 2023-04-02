#pragma once
#include "Check2.h"
#include<conio.h>
#include<time.h>
#include "ConsoleSettings.h"
#include "Utility.h"

void push(CELL_2*&, CELL_2*);
void initList(CELL_2**, int boardLength, int boardWidth);
void deleteList(CELL_2**, int boardWidth);
void deleteList2(CELL_2**, int boardWidth);
void renderList(CELL_2**, int boardWidth);
void renderList2(CELL_2**, int boardWidth);
void move(CELL_2**, position&, int&, player&, position[], int&, int boardLength, int boardWidth);
void difficultMode(player&, int boardLength, int boardWidth);