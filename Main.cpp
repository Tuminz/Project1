#include "NormalMode.h"
#include "DifficultMode.h"
#include<iostream>

using namespace std;

//#include <Windows.h>
//#include <mmsystem.h>

void selectMenu(player p)
{
    int choice[3] = { 0, 0, 0 }, temp, key, curChoice = 0;
    int boardLength, boardWidth;
    while (1)
    {

        choice[curChoice] = 1;

        if (choice[0])
        {
            TextColor(112);//chu den nen trang
            for (int i = 0; i < 3; i++)
            {
                goToXY(60, 11 + i);
                cout << "             ";//tao o dc chon mau trang
            }

            goToXY(64, 12);//dua con tro chuot vao giua o
            TextColor(112 + 3);//nen trang chu xanh
            cout << "NORMAL"; //viet chu vao o dc chon
        }
        else
        {
            TextColor(7); //chu mau trang nen den
            for (int i = 0; i < 3; i++)
            {
                goToXY(60, 11 + i);
                cout << "             ";//o nen den
            }

            goToXY(64, 12);
            TextColor(3);
            cout << "NORMAL";
        }
        if (choice[1])
        {
            TextColor(112);
            for (int i = 0; i < 3; i++)
            {
                goToXY(60, 14 + i);
                cout << "             ";
            }

            goToXY(62, 15);
            TextColor(112 + 2);
            cout << "DIFFICULT";
        }
        else
        {
            TextColor(7);
            for (int i = 0; i < 3; i++)
            {
                goToXY(60, 14 + i);
                cout << "             ";
            }

            goToXY(62, 15);
            TextColor(2);
            cout << "DIFFICULT";
        }
        if (choice[2])
        {
            TextColor(112);
            for (int i = 0; i < 3; i++)
            {
                goToXY(60, 17 + i);
                cout << "             ";
            }

            goToXY(64, 18);
            TextColor(112 + 4);
            cout << "EXIT";
        }
        else
        {
            TextColor(7);
            for (int i = 0; i < 3; i++)
            {
                goToXY(60, 17 + i);
                cout << "             ";
            }

            goToXY(64, 18);
            TextColor(4);//chu mau do
            cout << "EXIT";
        }
        if (temp = _getch())
        {
            if (temp != 224 && temp)//neu k la dau mui ten
            {
                if (temp == ENTER_KEY) //Neu nhan enter -> xoa man hinh va chuyen vao man choi
                {
                    system("cls");
                    if (curChoice == 0)
                    {
                        TextColor(3);
                        goToXY(50, 10);
                        cout << "MOI NHAP KICH THUOC BANG" << endl;
                        TextColor(7);
                        goToXY(55, 12);
                        cout << "Chieu dai (<=18): ";
                        cin >> boardLength;
                        goToXY(55, 13);
                        cout << "Chieu rong (<=12): ";
                        cin >> boardWidth;
                        system("cls");
                        getPlayerInfo(p);
                        system("cls");
                        normalMode(p, boardLength, boardWidth);
                    }
                    else if (curChoice == 1)
                    {
                        TextColor(3);
                        goToXY(50, 10);
                        cout << "MOI NHAP KICH THUOC BANG" << endl;
                        TextColor(7);
                        goToXY(55, 12);
                        cout << "Chieu dai (<=18): ";
                        cin >> boardLength;
                        goToXY(55, 13);
                        cout << "Chieu rong (<=12): ";
                        cin >> boardWidth;
                        system("cls");
                        getPlayerInfo(p);
                        system("cls");
                        difficultMode(p, boardLength, boardWidth);
                    }
                    else
                    {
                        exit(0);
                        break;
                    }
                }
            }
            else //di chuyen len hoac xuong
            {
                key = _getch();
                switch (key)
                {
                case KEY_UP:
                    choice[curChoice] = 0;
                    if (curChoice > 0) curChoice--;
                    else curChoice = 2;
                    break;
                case KEY_DOWN:
                    choice[curChoice] = 0;
                    if (curChoice < 2) curChoice++;
                    else curChoice = 0;
                default:
                    break;
                }
            }
        }
    }
}

int main() 
{
    //PlaySound(TEXT("pikachu.wav"), NULL, SND_LOOP | SND_ASYNC);
    initWindow(1000, 500);

    int status;
    player p;

    while ((status = mainMenu()) != 2) 
    {
        if (status == 0)
        {
            selectMenu(p);
        }
        else if (status == 1)
        {
            readLeaderBoard();
        }
        else
        {
            exit;
            break;
        }
    }
    return 0;
}