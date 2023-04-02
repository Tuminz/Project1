#include "DifficultMode.h"
#include<iostream>
using namespace std;

char BG[23][86];

void push(CELL_2*& head, CELL_2* p) 
{
    if (head == NULL) 
    {
        head = p;
    }
    else 
    {
        CELL_2* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = p;
    }
}

void initList(CELL_2** arr, int boardLength, int boardWidth) 
{
    for (int i = 0; i < boardWidth; i++) //ve bang
    {
        arr[i] = NULL;
        for (int j = 0; j < boardLength; j++) 
        {
            CELL_2* p = new CELL_2;
            p->i = i;
            p->j = j;
            p->next = NULL;
            push(arr[i], p);
        }
    }
    //random ki tu bat ki vao cac o trong bang
    int flagNum = (boardWidth * boardLength) / 2;
    while (flagNum) 
    {
        int i, time = 2;
        char c = 65 + rand() % 26;
        while (time)
        { //gan 1 ki tu vao 2 o
            i = rand() % boardWidth;
            int j = rand() % boardLength;
            CELL_2* p = findTheNode(arr, i, j, boardLength, boardWidth);
            if (p->c == ' ') 
            {
                p->c = c;
                time--;
            }
        }
        flagNum--;
    }
}

void deleteList(CELL_2** arr, int boardWidth)
{
    for (int i = 0; i < boardWidth; i++) 
    {
        CELL_2* temp;
        while (arr[i] != NULL)
        {
            temp = arr[i];
            arr[i] = arr[i]->next;
            temp->deleteBox();
            if (temp->j < 9) displayBackground(BG, temp->j, i);
            Sleep(500);
            delete temp;
        }
    }
    delete[]arr;
}

void deleteList2(CELL_2** arr, int boardWidth)
{
    for (int i = 0; i < boardWidth; i++)
    {
        CELL_2* temp;
        while (arr[i] != NULL)
        {
            temp = arr[i];
            arr[i] = arr[i]->next;
            temp->deleteBox2();
            if (temp->j < 15) displayBackground2(BG, temp->j, i);
            Sleep(500);
            delete temp;
        }
    }
    delete[]arr;
}

void renderList(CELL_2** arr, int boardWidth) 
{
    for (int i = 0; i < boardWidth; i++) 
    {
        CELL_2* temp = arr[i];
        while (temp != NULL)
        {
            temp->drawBox(112);
            temp = temp->next;
        }
    }
}

void renderList2(CELL_2** arr, int boardWidth)
{
    for (int i = 0; i < boardWidth; i++)
    {
        CELL_2* temp = arr[i];
        while (temp != NULL)
        {
            temp->drawBox2(112);
            temp = temp->next;
        }
    }
}

void move(CELL_2** arr, position& pos, int& status, player& p, position selectedPos[], int& couple, int boardLength, int boardWidth)
{
    int temp, key;
    temp = _getch();
    if (temp && temp != 224) 
    { // neu ko phai la dau mui ten
        if (temp == ESC_KEY) 
        { // neu la ESC
            status = 2;
        }
        else if (temp == ENTER_KEY) 
        { // neu la Enter
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) 
            {
                CELL_2* temp = findTheNode(arr, pos.y, pos.x, boardLength, boardWidth);
                temp->drawBox(70);
                Sleep(500);

                temp->isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                goToXY(70, 0);
                cout << "Life: " << p.life;
            } // kiem tra lap lai
            else 
            {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                findTheNode(arr, pos.y, pos.x, boardLength, boardWidth)->isSelected = 1;
                couple--;

                if (couple == 0) 
                { // neu da chon 1 cap
                    CELL_2* p1, * p2;
                    p1 = findTheNode(arr, selectedPos[0].y, selectedPos[0].x, boardLength, boardWidth);
                    p2 = findTheNode(arr, selectedPos[1].y, selectedPos[1].x, boardLength, boardWidth);
                    if (p1->c == p2->c) 
                    {  // neu cap nay hop nhau
                        if (allCheck(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, boardLength, boardWidth)) 
                        {
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            p1->drawBox(40);
                            p2->drawBox(40);
                            Sleep(500);

                            DifMode(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, BG, boardLength, boardWidth);
                        }
                        else 
                        {
                            p1->drawBox(70);
                            p2->drawBox(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else 
                    {
                        p1->drawBox(70);
                        p2->drawBox(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // tra ve noi san xuat
                    p1->isSelected = 0;
                    p2->isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < boardWidth; i++) 
                    {
                        for (int j = pos.x; j < boardLength; j++) 
                        {
                            if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                            {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++) 
                    { // chuyen den CELL_1 o tren
                        for (int j = 0; j <= pos.x; j++) 
                        {
                            if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                            {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    else //neu la dau mui ten
    {
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            findTheNode(arr, pos.y, pos.x, boardLength, boardWidth)->isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < boardLength; i++) 
            {
                for (int j = pos.y - 1; j >= 0; j--) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) 
            {
                for (int j = pos.y - 1; j >= 0; j--) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < boardLength; i++) 
            {
                for (int j = boardWidth - 1; j > pos.y; j--) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) 
            {
                for (int j = boardWidth - 1; j > pos.y; j--) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            break;
        case KEY_DOWN:
            for (int i = pos.x; i < boardLength; i++) 
            {
                for (int j = pos.y + 1; j < boardWidth; j++) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) 
            {
                for (int j = pos.y + 1; j < boardWidth; j++) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < boardLength; i++) 
            {
                for (int j = 0; j < pos.y; j++) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) 
            {
                for (int j = 0; j < pos.y; j++) 
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;
        case KEY_LEFT:
            for (int i = pos.y; i >= 0; i--) 
            {
                for (int j = pos.x - 1; j >= 0; j--) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++) 
            {
                for (int j = pos.x - 1; j >= 0; j--) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) 
            {
                for (int j = boardLength - 1; j > pos.x; j--) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++) 
            {
                for (int j = boardLength - 1; j > pos.x; j--) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;
        case KEY_RIGHT:
            for (int i = pos.y; i >= 0; i--) 
            {
                for (int j = pos.x + 1; j < boardLength; j++) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++) 
            {
                for (int j = pos.x + 1; j < boardLength; j++) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) 
            {
                for (int j = 0; j < pos.x; j++) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++) 
            {
                for (int j = 0; j < pos.x; j++) 
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            default:
            break;
        }
    }
}

void move2(CELL_2** arr, position& pos, int& status, player& p, position selectedPos[], int& couple, int boardLength, int boardWidth)
{
    int temp, key;
    temp = _getch();
    if (temp && temp != 224)
    { // neu ko phai la dau mui ten
        if (temp == ESC_KEY)
        { // neu la ESC
            status = 2;
        }
        else if (temp == ENTER_KEY)
        { // neu la Enter
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y)
            {
                CELL_2* temp = findTheNode(arr, pos.y, pos.x, boardLength, boardWidth);
                temp->drawBox2(70);
                Sleep(500);

                temp->isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                goToXY(70, 0);
                cout << "Life: " << p.life;
            } // kiem tra lap lai
            else
            {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                findTheNode(arr, pos.y, pos.x, boardLength, boardWidth)->isSelected = 1;
                couple--;

                if (couple == 0)
                { // neu da chon 1 cap
                    CELL_2* p1, * p2;
                    p1 = findTheNode(arr, selectedPos[0].y, selectedPos[0].x, boardLength, boardWidth);
                    p2 = findTheNode(arr, selectedPos[1].y, selectedPos[1].x, boardLength, boardWidth);
                    if (p1->c == p2->c)
                    {  // neu cap nay hop nhau
                        if (allCheck(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, boardLength, boardWidth))
                        {
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            p1->drawBox2(40);
                            p2->drawBox2(40);
                            Sleep(500);

                            DifMode2(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, BG, boardLength, boardWidth);
                        }
                        else
                        {
                            p1->drawBox2(70);
                            p2->drawBox2(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else
                    {
                        p1->drawBox2(70);
                        p2->drawBox2(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // tra ve noi san xuat
                    p1->isSelected = 0;
                    p2->isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < boardWidth; i++)
                    {
                        for (int j = pos.x; j < boardLength; j++)
                        {
                            if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                            {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++)
                    { // chuyen den CELL_1 o tren
                        for (int j = 0; j <= pos.x; j++)
                        {
                            if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                            {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    else //neu la dau mui ten
    {
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            findTheNode(arr, pos.y, pos.x, boardLength, boardWidth)->isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < boardLength; i++)
            {
                for (int j = pos.y - 1; j >= 0; j--)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--)
            {
                for (int j = pos.y - 1; j >= 0; j--)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < boardLength; i++)
            {
                for (int j = boardWidth - 1; j > pos.y; j--)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--)
            {
                for (int j = boardWidth - 1; j > pos.y; j--)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            break;
        case KEY_DOWN:
            for (int i = pos.x; i < boardLength; i++)
            {
                for (int j = pos.y + 1; j < boardWidth; j++)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--)
            {
                for (int j = pos.y + 1; j < boardWidth; j++)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < boardLength; i++)
            {
                for (int j = 0; j < pos.y; j++)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--)
            {
                for (int j = 0; j < pos.y; j++)
                {
                    if (findTheNode(arr, j, i, boardLength, boardWidth) != NULL)
                    {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;
        case KEY_LEFT:
            for (int i = pos.y; i >= 0; i--)
            {
                for (int j = pos.x - 1; j >= 0; j--)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++)
            {
                for (int j = pos.x - 1; j >= 0; j--)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--)
            {
                for (int j = boardLength - 1; j > pos.x; j--)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++)
            {
                for (int j = boardLength - 1; j > pos.x; j--)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;
        case KEY_RIGHT:
            for (int i = pos.y; i >= 0; i--)
            {
                for (int j = pos.x + 1; j < boardLength; j++)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++)
            {
                for (int j = pos.x + 1; j < boardLength; j++)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--)
            {
                for (int j = 0; j < pos.x; j++)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < boardWidth; i++)
            {
                for (int j = 0; j < pos.x; j++)
                {
                    if (findTheNode(arr, i, j, boardLength, boardWidth) != NULL)
                    {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
        default:
            break;
        }
    }
}

void difficultMode(player& p, int boardLength, int boardWidth)
{
    srand(time(0));
    getBackground(BG);

    CELL_2** board = new CELL_2 * [boardWidth];
    initList(board, boardLength, boardWidth);

    goToXY(10, 0);
    cout << "Name: " << p.name;
    goToXY(40, 0);
    cout << "Point: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;

    TextColor(2);
    goToXY(95, 1);
    cout << "Press arrow key to move";
    goToXY(95, 2);
    cout << "Press Enter to delete";
    goToXY(95, 3);
    cout << "Press ESC to quit";
    TextColor(7);

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };
    int status = 0; //0. dang choi game
    //1. het game
    //2. nguoi choi chon thoat

    while (!status && p.life) 
    {
        findTheNode(board, curPosition.y, curPosition.x, boardLength, boardWidth)->isSelected = 1;
        if (boardLength <= 10 && boardWidth <= 6)
        {
            renderList(board, boardWidth);
            move(board, curPosition, status, p, selectedPos, couple, boardLength, boardWidth);
        }
        else
        {
            renderList2(board, boardWidth);
            move2(board, curPosition, status, p, selectedPos, couple, boardLength, boardWidth);
        }

        if ((!checkValidPairs(board, boardLength, boardWidth))) status = 1;
    }
    if (boardLength <= 10 && boardWidth <= 6)
    {
        renderList(board, boardWidth);
        deleteList(board, boardWidth);
    }
    else
    {
        renderList2(board, boardWidth);
        deleteList2(board, boardWidth);
    }
    Sleep(500);
    system("cls");

    if (p.life && status == 1) 
    {
        displayStatus(1);
        goToXY(50, 17);
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') difficultMode(p, boardLength, boardWidth);
        else writeLeaderBoard(p);
    }
    else if (p.life == 0) 
    {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(500);
    }
    system("cls");
}