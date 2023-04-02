#pragma once
#include "Check1.h"
#include<conio.h>
#include<time.h>
#include "ConsoleSettings.h"
#include "Utility.h"

void initBoard(CELL_1**, int boardLength, int boardWidth);
void renderBoard(CELL_1**, int boardLength, int boardWidth);
void renderBoard2(CELL_1**, int boardLength, int boardWidth);
void deleteBoard(CELL_1**, int boardLength, int boardWidth);
void deleteBoard2(CELL_1**, int boardLength, int boardWidth);
void move(CELL_1**, position&, int&, player&, position[], int&, int boardLength, int boardWidth);
void move2(CELL_1**, position&, int&, player&, position[], int&, int boardLength, int boardWidth);
void normalMode(player&, int boardLength, int boardWidth);