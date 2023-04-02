#pragma once
#ifndef _CHECK2_H_
#define _CHECK2_H_

#include "Struct.h"
#include "Utility.h"

CELL_2* findTheNode(CELL_2**, int, int, int boardLength, int boardWidth);
bool Icheck(CELL_2**, int, int, int, int, int boardLength, int boardWidth);
bool Lcheck(CELL_2**, int, int, int, int, int boardLength, int boardWidth);
bool UandZcheck(CELL_2**, int, int, int, int, int boardLength, int boardWidth);
bool allCheck(CELL_2**, int, int, int, int, int boardLength, int boardWidth);
void deleteNode(CELL_2**, int, int, char[][86], int boardLength, int boardWidth);
void deleteNode2(CELL_2**, int, int, char[][86], int boardLength, int boardWidth);
void DifMode(CELL_2**, int, int, int, int, char[][86], int boardLength, int boardWidth);
void DifMode2(CELL_2**, int, int, int, int, char[][86], int boardLength, int boardWidth);
bool checkValidPairs(CELL_2**, int boardLength, int boardWidth);

#endif