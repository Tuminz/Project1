#include "NormalMode.h"
#include<iostream>
using namespace std;

char bg[23][86];

void initBoard(CELL_1** board, int boardLength, int boardWidth) //bang ban dau
{
    for (int i = 0; i < boardWidth; i++) 
    { // gan vi tri cho tung o mot
        board[i] = new CELL_1[boardLength];
        for (int j = 0; j < boardLength; j++) 
        {
            board[i][j].j = j;
            board[i][j].i = i;
        }
    }

    int flagNum = (boardWidth * boardLength) / 2;
    while (flagNum) 
    { // gan ky tu cho tung o mot
        int index, time = 2;
        char c = 65 + rand() % 26;
        while (time) 
        { // gan 1 ky tu cho 2 o
            index = rand() % (boardLength * boardWidth);
            if (board[index / boardLength][index % boardLength].c == ' ')
            {
                board[index / boardLength][index % boardLength].c = c;
                time--;
            }
        }
        flagNum--;
    }
}

void deleteBoard(CELL_1** board, int boardLength, int boardWidth) //xoa bang
{
    for (int i = 0; i < boardWidth; i++) 
    {
        for (int j = 0; j < boardLength; j++) 
        {
            if (board[i][j].isValid) 
            {
                board[i][j].deleteBox();
                if (j < 9) displayBackground(bg, j, i);//hien hinh nen
                Sleep(200);
            }
        }
    }

    for (int i = 0; i < boardWidth; i++) 
    {
        delete[]board[i];
    }
    delete[]board;
}

void deleteBoard2(CELL_1** board, int boardLength, int boardWidth) //xoa bang voi box nho
{
    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardLength; j++)
        {
            if (board[i][j].isValid)
            {
                board[i][j].deleteBox2();
                if (j < 15) displayBackground2(bg, j, i);//hien hinh nen
                Sleep(200);
            }
        }
    }

    for (int i = 0; i < boardWidth; i++)
    {
        delete[]board[i];
    }
    delete[]board;
}

void renderBoard(CELL_1** board, int boardLength, int boardWidth) //ket xuat bang
{
    for (int i = 0; i < boardWidth; i++) 
    {
        for (int j = 0; j < boardLength; j++) 
        {
            board[i][j].drawBox(112);
        }
    }
}

void renderBoard2(CELL_1** board, int boardLength, int boardWidth) //ket xuat bang voi box nho
{
    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardLength; j++)
        {
            board[i][j].drawBox2(112);
        }
    }
}
// di chuyen
void move(CELL_1** board, position& pos, int& status, player& p, position selectedPos[], int& couple, int boardLength, int boardWidth) 
{
    int temp, key;
    temp = _getch();//bat lay 1 ky tu phim nhan va gan vao bien temp
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
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                Sleep(500);

                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
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
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                if (couple == 0) 
                { // neu da chon 1 cap
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) 
                    {  // neu cap nay hop nhau
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, boardLength, boardWidth))
                        {
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            Sleep(500);

                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                            if (selectedPos[0].x < 9) displayBackground(bg, selectedPos[0].x, selectedPos[0].y);

                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                            if (selectedPos[1].x < 9) displayBackground(bg, selectedPos[1].x, selectedPos[1].y);
                        }
                        else 
                        {
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else 
                    {
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // tra ve noi san xuat
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < boardWidth; i++) 
                    {
                        for (int j = pos.x; j < boardLength; j++) 
                        {
                            if (board[i][j].isValid) 
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
                            if (board[i][j].isValid) 
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
            board[pos.y][pos.x].isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < boardLength; i++) 
            {
                for (int j = pos.y - 1; j >= 0; j--) 
                {
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[j][i].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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
                    if (board[i][j].isValid) 
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

void move2(CELL_1** board, position& pos, int& status, player& p, position selectedPos[], int& couple, int boardLength, int boardWidth)
{
    int temp, key;
    temp = _getch();//bat lay 1 ky tu phim nhan va gan vao bien temp
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
                board[selectedPos[0].y][selectedPos[0].x].drawBox2(70);
                Sleep(500);

                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
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
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                if (couple == 0)
                { // neu da chon 1 cap
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c)
                    {  // neu cap nay hop nhau
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, boardLength, boardWidth))
                        {
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            board[selectedPos[0].y][selectedPos[0].x].drawBox2(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox2(40);
                            Sleep(500);

                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox2();
                            if (selectedPos[0].x < 15) displayBackground2(bg, selectedPos[0].x, selectedPos[0].y);

                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox2();
                            if (selectedPos[1].x < 15) displayBackground2(bg, selectedPos[1].x, selectedPos[1].y);
                        }
                        else
                        {
                            board[selectedPos[0].y][selectedPos[0].x].drawBox2(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox2(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else
                    {
                        board[selectedPos[0].y][selectedPos[0].x].drawBox2(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox2(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // tra ve noi san xuat
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < boardWidth; i++)
                    {
                        for (int j = pos.x; j < boardLength; j++)
                        {
                            if (board[i][j].isValid)
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
                            if (board[i][j].isValid)
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
            board[pos.y][pos.x].isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < boardLength; i++)
            {
                for (int j = pos.y - 1; j >= 0; j--)
                {
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[j][i].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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
                    if (board[i][j].isValid)
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

void normalMode(player& p, int boardLength, int boardWidth) 
{
    srand(time(0));
    getBackground(bg);

    CELL_1** board = new CELL_1* [boardWidth];
    initBoard(board, boardLength, boardWidth);

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
        board[curPosition.y][curPosition.x].isSelected = 1;

        if (boardLength <= 10 && boardWidth <= 6)
        {
            renderBoard(board, boardLength, boardWidth);
            move(board, curPosition, status, p, selectedPos, couple, boardLength, boardWidth);
        }
        else
        {
            renderBoard2(board, boardLength, boardWidth);
            move2(board, curPosition, status, p, selectedPos, couple, boardLength, boardWidth);
        }
        if ((!checkValidPairs(board, boardLength, boardWidth))) status = 1;
    }

    if (boardLength <= 10 && boardWidth <= 6)
    {
        renderBoard(board, boardLength, boardWidth);
        deleteBoard(board, boardLength, boardWidth);
    }
    else
    {
        renderBoard2(board, boardLength, boardWidth);
        deleteBoard2(board, boardLength, boardWidth);
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
        if (c == 'y' || c == 'Y') normalMode(p, boardLength, boardWidth);
        else writeLeaderBoard(p);
    }
    else if (p.life == 0) 
    {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(2000);
    }
    system("cls");
}