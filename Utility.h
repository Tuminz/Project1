#pragma once
#ifndef _UTILITY_H_ //kiem tra xem _UTILITY_H_ da dc dinh nghia chua ? Neu chua thi chay tiep cau lenh ben duoi, neu roi thi nhay xuong cau lenh #endif
#define _UTILITY_H_ //dinh nghia cai ten _UTILITY_H_ 

#include<fstream>
#include<string>
#include "ConsoleSettings.h"
#include "Struct.h"
using namespace std;

void readLeaderBoard();
void writeLeaderBoard(player);
void getPlayerInfo(player&);
void displayStatus(bool);
void getBackground(char[][86]);
void displayBackground(char[][86], int, int);
void displayBackground2(char[][86], int, int);
int mainMenu();
#endif // !_UTILITY_H_