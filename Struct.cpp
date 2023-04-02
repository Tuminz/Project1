#include"Struct.h"
#include "ConsoleSettings.h"
#include<iostream>
using namespace std;

char box[5][12] =
{
    {" --------- "},
    {"|         |"},
    {"|         |"},
    {"|         |"},
    {" --------- "}
};

char box2[3][8] =
{
    {" ----- "},
    {"|     |"},
    {" ----- "}
};

void CELL_1::drawBox(int color) // ve box lon
{
    if (!isValid) // neu k hop le
    {
        return;
    }
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++)
    {
        goToXY(x * 10, y * 4 + i);//di chuyen con tro den vi tri ve o tiep theo
        cout << box[i];
    }

    if (isSelected) //Truong hop con tro dang trong o nay
    {
        TextColor(color + (c % 6 + 1)); //white background
        for (int i = 1; i < 4; i++)
        {
            goToXY(x * 10 + 1, y * 4 + i);
            cout << "         ";
        }

        goToXY(x * 10 + 5, y * 4 + 2);//dua con tro chuot vao giua box
        cout << c;
        TextColor(7);
    }
    else
    {
        goToXY(x * 10 + 5, y * 4 + 2);
        TextColor(c % 6 + 1);
        cout << c;
        TextColor(7);
    }
}

void CELL_1::drawBox2(int color) //ve box nho
{
    if (!isValid) // neu k hop le
    {
        return;
    }
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 3; i++)
    {
        goToXY(x * 6, y * 2 + i);//di chuyen con tro den vi tri ve o tiep theo
        cout << box2[i];
    }

    if (isSelected) //Truong hop con tro dang trong o nay
    {
        TextColor(color + (c % 6 + 1)); //white background
        for (int i = 1; i < 2; i++)
        {
            goToXY(x * 6 + 1, y * 2 + i);
            cout << "     ";
        }

        goToXY(x * 6 + 3, y * 2 + 1); //dua con tro chuot vao giua box
        cout << c;
        TextColor(7);
    }
    else
    {
        goToXY(x * 6 + 3, y * 2 + 1);
        TextColor(c % 6 + 1);
        cout << c;
        TextColor(7);
    }
}

void CELL_1::deleteBox() // loi goi ham trong struct/ class, xoa box lon
{
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++)
    {
        goToXY(x * 10, y * 4 + i);
        cout << "           ";
    }
}
void CELL_1::deleteBox2() // xoa box nho
{
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 3; i++)
    {
        goToXY(x * 6, y * 2 + i);
        cout << "       ";
    }
}

void CELL_2::drawBox(int color) //Ve box lon
{
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++)
    {
        goToXY(x * 10, y * 4 + i);
        cout << box[i];
    }

    if (isSelected)
    {
        TextColor(color + (c % 6 + 1)); //white background
        for (int i = 1; i < 4; i++)
        {
            goToXY(x * 10 + 1, y * 4 + i);
            cout << "         ";
        }

        goToXY(x * 10 + 5, y * 4 + 2);
        cout << c;
        TextColor(7);
    }
    else
    {
        goToXY(x * 10 + 5, y * 4 + 2);
        TextColor(c % 6 + 1);
        cout << c;
        TextColor(7);
    }
}

void CELL_2::drawBox2(int color) //Ve box nho
{
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 3; i++)
    {
        goToXY(x * 6, y * 2 + i);
        cout << box2[i];
    }

    if (isSelected)
    {
        TextColor(color + (c % 6 + 1)); //white background
        for (int i = 1; i < 2; i++)
        {
            goToXY(x * 6 + 1, y * 2 + i);
            cout << "     ";
        }

        goToXY(x * 6 + 3, y * 2 + 1);
        cout << c;
        TextColor(7);
    }
    else
    {
        goToXY(x * 6 + 3, y * 2 + 1);
        TextColor(c % 6 + 1);
        cout << c;
        TextColor(7);
    }
}

void CELL_2::deleteBox() //Xoa box lon
{
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++)
    {
        goToXY(x * 10, y * 4 + i);
        cout << "           ";
    }
}

void CELL_2::deleteBox2() //Xoa box nho
{
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 3; i++)
    {
        goToXY(x * 6, y * 2 + i);
        cout << "       ";
    }
}