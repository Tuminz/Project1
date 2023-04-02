#include "Check2.h"

CELL_2* findTheNode(CELL_2** arr, int y, int x, int boardLength, int boardWidth) 
{
    if (y < 0 || y > boardWidth - 1 || x < 0 || x > boardLength - 1) return NULL;

    CELL_2* temp = arr[y];
    while (temp != NULL)
    {
        if (temp->j == x) 
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

bool Icheck(CELL_2** arr, int y1, int x1, int y2, int x2, int boardLength, int boardWidth)
{
    int ma, mi, i = 0;
    CELL_2* temp, * tempHead;
    if (x1 == x2) 
    {
        ma = max(y1, y2);
        mi = min(y1, y2);
        tempHead = findTheNode(arr, mi, x1, boardLength, boardWidth);
        temp = tempHead;
        while (temp == NULL) 
        {
            mi++;
            temp = findTheNode(arr, mi, x1, boardLength, boardWidth);
            tempHead = temp;
            if (mi == ma) 
            {
                return true;
            }
            if (temp != NULL) 
            {
                return false;
            }
        }
        while (temp != NULL) 
        {
            i++;
            temp = findTheNode(arr, mi + i, x1, boardLength, boardWidth);
            while (temp == NULL) 
            {
                i++;
                temp = findTheNode(arr, mi + i, x1, boardLength, boardWidth);
                if (mi + i > ma) 
                {
                    return true;
                }
            }
            if (mi + i > ma) 
            {
                return true;
            }
            if (mi + i == ma) 
            {
                if (temp == NULL) 
                {
                    return true;
                }
                if (temp->c == tempHead->c)
                {
                    return true;
                }
                return false;
            }
            if (temp != NULL) 
            {
                return false;
            }
        }
    }
    if (y1 == y2) 
    {
        i = 0;
        ma = max(x1, x2);
        mi = min(x1, x2);
        tempHead = findTheNode(arr, y1, mi, boardLength, boardWidth);
        temp = tempHead;
        while (temp == NULL) 
        {
            mi++;
            temp = findTheNode(arr, mi, x1, boardLength, boardWidth);
            tempHead = temp;
            if (mi > ma) 
            {
                return true;
            }
        }
        while (temp != NULL) 
        {
            i++;
            temp = temp->next;
            if (mi + i > ma) 
            {
                return true;
            }
            if (mi + i == ma) 
            {
                if (temp == NULL) 
                {
                    return true;
                }
                if (temp->c == tempHead->c) 
                {
                    return true;
                }
                return false;
            }
            if (temp != NULL) 
            {
                return false;
            }
        }
    }
    return false;
}

bool Lcheck(CELL_2** arr, int y1, int x1, int y2, int x2, int boardLength, int boardWidth)
{
    CELL_2* temp;
    temp = findTheNode(arr, y1, x2, boardLength, boardWidth);
    if (temp == NULL) 
    {
        int x = x2, y = y1;
        while (temp == NULL) 
        {
            if (x2 > x1) 
            {
                x--;
            }
            else 
            {
                x++;
            }
            temp = findTheNode(arr, y1, x, boardLength, boardWidth);
        }
        temp = NULL;
        while (temp == NULL) 
        {
            if (y2 > y1) 
            {
                y++;
            }
            else 
            {
                y--;
            }
            temp = findTheNode(arr, y, x2, boardLength, boardWidth);
        }
        if (Icheck(arr, y1, x1, y1, x, boardLength, boardWidth))
        {
            if (Icheck(arr, y2, x2, y, x2, boardLength, boardWidth))
            {
                return true;
            }
        }
        else if (Icheck(arr, y1, x1, y1, x, boardLength, boardWidth))
        {
            if (Icheck(arr, y2, x2, y, x2, boardLength, boardWidth))
            {
                return true;
            }
        }
    }

    temp = findTheNode(arr, y2, x1, boardLength, boardWidth);
    if (temp == NULL)
    {
        int x = x1, y = y2;
        while (temp == NULL) 
        {
            if (x2 > x1) 
            {
                x++;
            }
            else 
            {
                x--;
            }
            temp = findTheNode(arr, y2, x, boardLength, boardWidth);
        }
        temp = NULL;
        while (temp == NULL)
        {
            if (y2 > y1)
            {
                y--;
            }
            else 
            {
                y++;
            }
            temp = findTheNode(arr, y, x1, boardLength, boardWidth);
        }
        if (Icheck(arr, y1, x1, y1, x, boardLength, boardWidth))
        {
            if (Icheck(arr, y2, x2, y, x2, boardLength, boardWidth))
            {
                return true;
            }
        }
        else if (Icheck(arr, y2, x2, y2, x, boardLength, boardWidth))
        {
            if (Icheck(arr, y1, x1, y, x1, boardLength, boardWidth))
            {
                return true;
            }
        }
    }

    return false;
}


bool UandZcheck(CELL_2** arr, int y1, int x1, int y2, int x2, int boardLength, int boardWidth)
{
    if ((findTheNode(arr, y1 - 1, x1, boardLength, boardWidth) == NULL && findTheNode(arr, y2 - 1, x2, boardLength, boardWidth) == NULL || findTheNode(arr, y1 + 1, x1, boardLength, boardWidth) == NULL && findTheNode(arr, y2 + 1, x2, boardLength, boardWidth) == NULL) && (y1 == y2))
    {
        return true;
    }

    if ((x1 == 0 && x2 == 0) || (findTheNode(arr, y1, x1, boardLength, boardWidth)->next == NULL && findTheNode(arr, y2, x2, boardLength, boardWidth)->next == NULL))
    {
        return true;
    }

    CELL_2* tempTail, *tempHead;
    if ((Icheck(arr, y1, x1, 0, x1, boardLength, boardWidth) || Icheck(arr, y1, x1, 4, x1, boardLength, boardWidth)) && (y1 != y2))
    {
        tempTail = findTheNode(arr, y1, x2, boardLength, boardWidth);
        if (tempTail == NULL) 
        {
            int y = y1;
            if ((Icheck(arr, y1, x1, 0, x1, boardLength, boardWidth)))
            {
                while (tempTail == NULL) 
                {
                    y++;
                    tempTail = findTheNode(arr, y, x2, boardLength, boardWidth);
                }
            }
            if (Icheck(arr, y, x2, y2, x2, boardLength, boardWidth))
            {
                return true;
            }
            y = y1;
            if (Icheck(arr, y1, x1, 4, x1, boardLength, boardWidth))
            {
                tempTail = NULL;
                while (tempTail == NULL) 
                {
                    y--;
                    tempTail = findTheNode(arr, y, x2, boardLength, boardWidth);
                }
            }
            if (Icheck(arr, y, tempTail->j, y2, x2, boardLength, boardWidth))
            {
                return true;
            }
        }
        if (Icheck(arr, tempTail->i, tempTail->j, y2, x2, boardLength, boardWidth))
        {
            return true;
        }
    }
    if ((Icheck(arr, y2, x2, 0, x2, boardLength, boardWidth) || Icheck(arr, y2, x2, 4, x2, boardLength, boardWidth)) && (y1 != y2))
    {
        tempTail = findTheNode(arr, y2, x1, boardLength, boardWidth);
        if (tempTail == NULL) 
        {
            int y = y2;
            if (Icheck(arr, y2, x2, 0, x2, boardLength, boardWidth))
            {
                while (tempTail == NULL) 
                {
                    y++;
                    tempTail = findTheNode(arr, y, x1, boardLength, boardWidth);
                }
            }
            if (Icheck(arr, y, x1, y1, x1, boardLength, boardWidth))
            {
                return true;
            }
            y = y2;
            if (Icheck(arr, y2, x2, 4, x2, boardLength, boardWidth))
            {
                while (tempTail == NULL) 
                {
                    y--;
                    tempTail = findTheNode(arr, y, x1, boardLength, boardWidth);
                }
            }
            if (Icheck(arr, y, x1, y1, x1, boardLength, boardWidth))
            {
                return true;
            }
        }
        else 
        {
            if (Icheck(arr, tempTail->i, tempTail->j, y1, x1, boardLength, boardWidth))
            {
                return true;
            }
        }
    }

    int ma, mi;
    ma = max(y1, y2);
    mi = min(y1, y2);
    if (x1 != x2) 
    {
        for (int i = 0; (i < boardWidth); i++) 
        {
            tempHead = findTheNode(arr, i, x1, boardLength, boardWidth);
            int x = x1;
            tempTail = findTheNode(arr, i, x2, boardLength, boardWidth);
            x = x2;
            if (Icheck(arr, i, x1, i, x2, boardLength, boardWidth))
            {
                if (Icheck(arr, i, x1, y1, x1, boardLength, boardWidth) && Icheck(arr, i, x2, y2, x2, boardLength, boardWidth))
                {
                    return true;
                }
            }
        }
    }

    ma = max(x1, x2);
    mi = min(x1, x2);
    if (y1 != y2) {
        for (int i = 0; i < boardWidth; i++) 
        {
            tempHead = findTheNode(arr, y1, i, boardLength, boardWidth);
            int y = y1;
            tempTail = findTheNode(arr, y2, i, boardLength, boardWidth);
            y = y2;
            if (Icheck(arr, y1, i, y2, i, boardLength, boardWidth))
            {
                if (Icheck(arr, y1, i, y1, x1, boardLength, boardWidth) && Icheck(arr, y2, i, y2, x2, boardLength, boardWidth))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool allCheck(CELL_2** arr, int y1, int x1, int y2, int x2, int boardLength, int boardWidth) 
{
    if (Icheck(arr, y1, x1, y2, x2, boardLength, boardWidth)) return true;
    else if (Lcheck(arr, y1, x1, y2, x2, boardLength, boardWidth)) return true;
    else if (UandZcheck(arr, y1, x1, y2, x2, boardLength, boardWidth)) return true;
    return false;
}

void deleteNode(CELL_2** arr, int y, int x, char bg[][86], int boardLength, int boardWidth)
{
    CELL_2* p = findTheNode(arr, y, x, boardLength, boardWidth);
    if (x == 0) 
    {
        if (arr[y]->next == NULL) 
        {
            arr[y]->deleteBox();
            if (arr[y]->j < 9) displayBackground(bg, arr[y]->j, y);
            arr[y] = NULL;
            return;
        }
        arr[y]->c = p->next->c;

        p = arr[y]->next;
        if (p->next == NULL) 
        {
            p->deleteBox();
            if (p->j < 9) displayBackground(bg, p->j, y);
            delete p;
            arr[y]->next = NULL;
        }
        else 
        {
            while (p->next->next != NULL)
            {
                p->c = p->next->c;
                p = p->next;
            }
            p->c = p->next->c;
            p->next->deleteBox();
            if (p->next->j < 9) displayBackground(bg, p->next->j, p->next->i);
            delete p->next;
            p->next = NULL;
        }
    }
    else if (p->next != NULL) 
    {
        while (p->next->next != NULL)
        {
            p->c = p->next->c;
            p = p->next;
        }
        p->c = p->next->c;
        p->next->deleteBox();
        if (p->next->j < 9) displayBackground(bg, p->next->j, p->next->i);
        delete p->next;
        p->next = NULL;
    }
    else 
    {
        p->deleteBox();
        if (p->j < 9) displayBackground(bg, p->j, p->i);
        delete p;
        p = findTheNode(arr, y, x - 1, boardLength, boardWidth);
        p->next = NULL;
    }
}

void deleteNode2(CELL_2** arr, int y, int x, char bg[][86], int boardLength, int boardWidth)
{
    CELL_2* p = findTheNode(arr, y, x, boardLength, boardWidth);
    if (x == 0)
    {
        if (arr[y]->next == NULL)
        {
            arr[y]->deleteBox2();
            if (arr[y]->j < 15) displayBackground2(bg, arr[y]->j, y);
            arr[y] = NULL;
            return;
        }
        arr[y]->c = p->next->c;

        p = arr[y]->next;
        if (p->next == NULL)
        {
            p->deleteBox2();
            if (p->j < 15) displayBackground2(bg, p->j, y);
            delete p;
            arr[y]->next = NULL;
        }
        else
        {
            while (p->next->next != NULL)
            {
                p->c = p->next->c;
                p = p->next;
            }
            p->c = p->next->c;
            p->next->deleteBox2();
            if (p->next->j < 15) displayBackground2(bg, p->next->j, p->next->i);
            delete p->next;
            p->next = NULL;
        }
    }
    else if (p->next != NULL)
    {
        while (p->next->next != NULL)
        {
            p->c = p->next->c;
            p = p->next;
        }
        p->c = p->next->c;
        p->next->deleteBox2();
        if (p->next->j < 15) displayBackground2(bg, p->next->j, p->next->i);
        delete p->next;
        p->next = NULL;
    }
    else
    {
        p->deleteBox2();
        if (p->j < 15) displayBackground2(bg, p->j, p->i);
        delete p;
        p = findTheNode(arr, y, x - 1, boardLength, boardWidth);
        p->next = NULL;
    }
}

void DifMode(CELL_2** arr, int y1, int x1, int y2, int x2, char bg[][86], int boardLength, int boardWidth)
{
    if (x1 > x2)
    {
        deleteNode(arr, y1, x1, bg, boardLength, boardWidth);
        deleteNode(arr, y2, x2, bg, boardLength, boardWidth);
    }
    else 
    {
        deleteNode(arr, y2, x2, bg, boardLength, boardWidth);
        deleteNode(arr, y1, x1, bg, boardLength, boardWidth);
    }
}

void DifMode2(CELL_2** arr, int y1, int x1, int y2, int x2, char bg[][86], int boardLength, int boardWidth)
{
    if (x1 > x2)
    {
        deleteNode2(arr, y1, x1, bg, boardLength, boardWidth);
        deleteNode2(arr, y2, x2, bg, boardLength, boardWidth);
    }
    else
    {
        deleteNode2(arr, y2, x2, bg, boardLength, boardWidth);
        deleteNode2(arr, y1, x1, bg, boardLength, boardWidth);
    }
}

bool checkValidPairs(CELL_2** arr, int boardLength, int boardWidth)
{
    CELL_2* Head, * temp;
    for (int i = 0; i < boardWidth; i++)//ban dau la 5
    {
        Head = arr[i];
        while (Head != NULL) 
        {
            int j = i;
            temp = Head->next;
            while (temp == NULL && j < boardWidth - 1) //ban dau la 4
            {
                j++;
                temp = arr[j];
            }
            while (temp != NULL) 
            {
                if (Head->c == temp->c)
                {
                    if (allCheck(arr, Head->i, Head->j, temp->i, temp->j, boardLength, boardWidth)) 
                    {
                        return true;
                    }
                }
                temp = temp->next;
                if ((temp == NULL) && (j < boardWidth - 1)) // ban dau la 4
                {
                    j++;
                    temp = findTheNode(arr, j, 0, boardLength, boardWidth);
                }
            }
            Head = Head->next;
        }
    }
    return false;
}