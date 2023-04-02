#include "Check1.h"

int Max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int Min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

bool nextcheck(CELL_1** board, int p1, int p2, int q1, int q2) 
{
    if ((p1 == q1 + 1 || p1 == q1 - 1) && (p2 == q2)) 
    {
        if (board[p1][p2].c == board[q1][q2].c)
            return true;
    }
    if ((p2 == q2 + 1 || p2 == q2 - 1) && (p1 == q1))
    {
        if (board[p1][p2].c == board[q1][q2].c)
            return true;
    }
    return false;
}

bool linecheck(CELL_1** board, int p1, int p2, int q1, int q2) 
{
    if (p1 == q1) 
    {
        int y, x, dem = 0;
        x = Min(p2, q2);
        y = Max(p2, q2);
        for (int i = x; i <= y; i++) 
        {
            if (board[p1][i].isValid) 
            {
                dem++;
                if (dem == 2) return false;
            }
        }
        return true;
    }
    if (p2 == q2)
    {
        int x, y, dem = 0;
        x = Min(p1, q1);
        y = max(p1, q1);
        for (int i = x; i <= y; i++)
        {
            if (board[i][p2].isValid) 
            {
                dem++;
                if (dem == 2) return false;
            }
        }
        return true;
    }
    return false;
}

bool Icheck_1(CELL_1** board, int p1, int p2, int q1, int q2) 
{
    if (p1 == q1) 
    {
        int y, x, dem = 0;
        x = Min(p2, q2);
        y = Max(p2, q2);
        for (int i = x + 1; i < y; i++)
        {
            if (board[p1][i].isValid) 
            {
                return false;
            }
        }
        return true;
    }
    if (p2 == q2)
    {
        int x, y, dem = 0;
        x = Min(p1, q1);
        y = Max(p1, q1);
        for (int i = x + 1; i < y; i++)
        {
            if (board[i][p2].isValid)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Lcheck(CELL_1** board, int p1, int p2, int q1, int q2)
{
    bool c1, c2;
    if (!board[p1][q2].isValid) 
    {
        c1 = linecheck(board, p1, p2, p1, q2);
        c2 = linecheck(board, q1, q2, p1, q2);
        if (c1 && c2) 
        {
            return true;
        }
    }
    if (!board[q1][p2].isValid) 
    {
        c1 = linecheck(board, p1, p2, q1, p2);
        c2 = linecheck(board, q1, q2, q1, p2);
        if (c1 && c2) 
        {
            return true;
        }
    }
    return false;
}

bool Zcheck(CELL_1** board, int p1, int p2, int q1, int q2)
{
    bool c1, c2, c3;
    int x, y;
    x = Min(q2, p2);
    y = Max(q2, p2);
    for (int i = x + 1; i < y; i++)
    {
        c3 = linecheck(board, p1, i, q1, i);
        if (c3)
        {
            c1 = linecheck(board, p1, p2, p1, i);
            c2 = linecheck(board, q1, q2, q1, i);
            if (c1 && c2)
                return true;
        }
    }
    x = Min(q1, p1);
    y = Max(q1, p1);
    for (int i = x + 1; i < y; i++) 
    {
        c3 = linecheck(board, i, p2, i, q2);
        if (c3)
        {
            c1 = linecheck(board, p1, p2, i, p2);
            c2 = linecheck(board, q1, q2, i, q2);
            if (c1 && c2)
                return true;
        }
    }
    return false;
}

bool Ucheck(CELL_1** board, int p1, int p2, int q1, int q2, int boardLength, int boardWidth)
{
    if (((p1 == q1) && (p1 == 0 || p1 == boardWidth - 1) || ((p2 == q2) && (p2 == 0 || q2 == boardLength - 1))))
    {
        return true;
    }
    bool c1, c2, c3;
    int x, y;
    x = Min(q2, p2);
    y = Max(q2, p2);
    for (int i = 0; i < boardLength; i++) 
    {
        if (i <= x || i >= y)//xet ve 2 ben trai hoac phai 
        {
            c3 = linecheck(board, p1, i, q1, i);
            if (c3) 
            {
                c1 = linecheck(board, p1, p2, p1, i);
                c2 = linecheck(board, q1, q2, q1, i);
                if (c1 && c2)
                {
                    return true;
                }
            }
            else if (i == 0 || i == (boardLength - 1)) //neu o bien
            {
                c1 = linecheck(board, p1, p2, p1, i);
                c2 = linecheck(board, q1, q2, q1, i);
                if ((c1 && c2) || (c1 && q2 == i) || (p2 == i && c2))
                {
                    return true;
                }
            }
        }
    }

    x = Min(q1, p1);
    y = Max(q1, p1);
    for (int i = 0; i < boardWidth; i++) 
    {
        if (i <= x || i >= y) 
        {
            c3 = linecheck(board, i, p2, i, q2);
            if (c3) 
            {
                c1 = linecheck(board, p1, p2, i, p2);
                c2 = linecheck(board, q1, q2, i, q2);
                if (c1 && c2)
                {
                    return true;
                }
            }
            else if (i == 0 || i == (boardWidth - 1)) 
            {
                c1 = linecheck(board, p1, p2, i, p2);
                c2 = linecheck(board, q1, q2, i, q2);
                if ((c1 && c2) || (c1 && q1 == i) || (p1 == i && c2)) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool allcheck(CELL_1** board, int p1, int p2, int q1, int q2, int boardLength, int boardWidth) 
{
    if (nextcheck(board, p1, p2, q1, q2)) 
    {
        return true;
    }
    else if (Icheck_1(board, p1, p2, q1, q2)) 
    {
        return true;
    }
    else if (Lcheck(board, p1, p2, q1, q2)) 
    {
        return true;
    }
    else if (Zcheck(board, p1, p2, q1, q2)) 
    {
        return true;
    }
    else if (Ucheck(board, p1, p2, q1, q2, boardLength, boardWidth))
    {
        return true;
    }
    return false;
}

bool checkValidPairs(CELL_1** board, int boardLength, int boardWidth) //Kiem tra cac cap co hop le k
{
    char check = 'A';
    while (check >= 'A' && check <= 'Z') 
    {
        int cnt = 0;
        int* pos = new int[boardWidth * boardLength];
        for (int i = 0; i < boardWidth; i++)
        {
            for (int j = 0; j < boardLength; j++) 
            {
                if (board[i][j].c == check && board[i][j].isValid)
                {
                    pos[cnt++] = i;
                    pos[cnt++] = j;
                }
            }
        }
        for (int i = 0; i < cnt - 2; i += 2) 
        {
            for (int j = i + 2; j < cnt; j += 2)
            {
                if (allcheck(board, pos[i], pos[i + 1], pos[j], pos[j + 1], boardLength, boardWidth))
                {
                    delete[] pos;
                    return true;
                }
            }
        }
        check++;
        delete[] pos;
    }
    return false;
}