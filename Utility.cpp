#include "Utility.h"
#include <iostream>
#include <conio.h>

void readLeaderBoard() 
{
    goToXY(60, 5);
    TextColor(3); //Mau chu
    cout << "LEADERBOARD";
    goToXY(30, 6);
    TextColor(2);
    cout << "NAME";
    goToXY(100, 6);
    cout << "POINT";
    TextColor(7);
    goToXY(30, 7);
    for (int i = 0; i < 75; i++) 
    {
        cout << "=";
    }

    ifstream f;
    f.open("leaderboard.txt");
    if (f) //Neu mo dc file
    {
        player p;

        int i = 0;
        while (getline(f, p.name, ' ')) 
        {
            f >> p.point;
            f.get();
            goToXY(30, 7 + i);
            for (int j = 0; j < 75; j++) 
            {
                cout << "=";
            }
            if (i <= 4) TextColor(4 - i / 2); // Mau nen va mau chu
            goToXY(30, 8 + i);
            cout << p.name;
            goToXY(100, 8 + i);
            cout << p.point;
            if (i <= 4) TextColor(7);// Mau chu
            i += 2;
        }
        f.close();
    }

    _getch();//dung man hinh
    system("cls");
}

void writeLeaderBoard(player p) 
{
    ifstream fin("leaderboard.txt");
    if (fin) 
    {
        player* list = new player[10];//Lay 10 nguoi diem cao nhat
        int no_player = 0; //so nguoi choi
        string s;

        while (getline(fin, s, ' ')) 
        {
            list[no_player].name = s;
            fin >> list[no_player].point;
            fin.get();
            no_player++;
        }

        int index = no_player - 1;
        for (index; index >= 0; index--) 
        {
            if (p.point <= list[index].point) 
            {
                break;
            }
        }

        if (no_player < 10) 
        {
            for (int i = no_player; i > index + 1; i--) 
            {
                list[i] = list[i - 1];
            }
            list[index + 1] = p;
            no_player++;
        }
        else 
        {
            if (index != no_player - 1) 
            {
                for (int i = no_player - 1; i > index + 1; i--) 
                {
                    list[i] = list[i - 1];
                }
                list[index + 1] = p;
            }
        }
        fin.close();


        ofstream fout("leaderboard.txt");

        for (int i = 0; i < no_player; i++) 
        {
            fout << list[i].name << " " << list[i].point << endl;
        }

        fout.close();

        delete[]list;
    }
    else 
    {
        ofstream fout("leaderboard.txt");
        fout << p.name << " " << p.point << endl;
        fout.close();
    }
}

void getPlayerInfo(player& p) 
{
    goToXY(50, 12);
    cout << "Enter player name: ";
    cin >> p.name;
    cin.ignore();
    p.life = 3; //So mang choi
    p.point = 0; //Diem so
}

void displayStatus(bool win) 
{
    if (win) {
        TextColor(3);
        goToXY(50, 10);
        cout << "__  ______  __  __  _      ______  _  __";
        goToXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / | | /| / / __ \\/ |/ /";
        goToXY(50, 12);
        cout << " \\  / /_/ / /_/ /  | |/ |/ / /_/ /    /";
        goToXY(50, 13);
        cout << " /_/\\____/\\____/   |__/|__/\\____/_/|_/";
        TextColor(7);
    }
    else 
    {
        TextColor(4);
        goToXY(50, 10);
        cout << "__  ______  __  __  __   ____  ________";
        goToXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / / /  / __ \\/ __/ __/";
        goToXY(50, 12);
        cout << " \\  / /_/ / /_/ / / /__/ /_/ /\\ \\/ _/";
        goToXY(50, 13);
        cout << " /_/\\____/\\____/ /____/\\____/___/___/";
        TextColor(7);
    }
}

void getBackground(char bg[][86])
{
    ifstream fin("pika.txt");
    if (fin) 
    {
        for (int i = 0; i < 23; i++) 
        {
            for (int j = 0; j < 86; j++) 
            {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else 
    {
        memset(bg, ' ', sizeof(bg));
    }
}

void displayBackground(char bg[][86], int x, int y) 
{
    TextColor(6);
    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 11; j++) 
        {
            goToXY((x + 1) * 10 + j, (y + 1) * 4 + i);// cong them 1 vao toa do la do chenh lech toa do giua bg[][] va gotoXY
            cout << bg[y * 4 + i][x * 10 + j];
        }
    }
    TextColor(7);
}

void displayBackground2(char bg[][86], int x, int y)
{
    TextColor(6);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            goToXY((x + 1) * 6 + j, (y + 1) * 2 + i);// cong them 1 vao toa do la do chenh lech toa do giua bg[][] va gotoXY
            cout << bg[y * 2 + i][x * 6 + j];
        }
    }
    TextColor(7);
}

int mainMenu() 
{
    int choice[3] = { 0,0,0 }, temp, key, curChoice = 0;

    goToXY(35, 2);
    TextColor(6);
    cout << " _______   ______  __    __   ______    ______   __    __  __    __ ";
    goToXY(35, 3);
    cout << "/         /      |/  |  /  | /         /        /  |  /  |/  |  /  |";
    goToXY(35, 4);
    cout << "$$$$$$$  |$$$$$$/ $$ | /$$/ /$$$$$$  |/$$$$$$  |$$ |  $$ |$$ |  $$ |";
    goToXY(35, 5);
    cout << "$$ |__$$ |  $$ |  $$ |/$$/  $$ |__$$ |$$ |  $$/ $$ |__$$ |$$ |  $$ |";
    goToXY(35, 6);
    cout << "$$    $$/   $$ |  $$  $$<   $$    $$ |$$ |      $$    $$ |$$ |  $$ |";
    goToXY(35, 7);
    cout << "$$$$$$$/    $$ |  $$$$$     $$$$$$$$ |$$ |   __ $$$$$$$$ |$$ |  $$ |";
    goToXY(35, 8);
    cout << "$$ |       _$$ |_ $$ |$$    $$ |  $$ |$$  __/  |$$ |  $$ |$$  __$$ |";
    goToXY(35, 9);
    cout << "$$ |      / $$   |$$ | $$  |$$ |  $$ |$$    $$/ $$ |  $$ |$$    $$/ ";
    goToXY(35, 10);
    cout << "$$/       $$$$$$/ $$/   $$/ $$/   $$/  $$$$$$/  $$/   $$/  $$$$$$/  ";

    while (1) 
    {

        choice[curChoice] = 1;

        if (choice[0]) 
        {
            TextColor(112);//chu den nen trang
            for (int i = 0; i < 3; i++) 
            {
                goToXY(60, 14 + i);
                cout << "             ";//tao o dc chon mau trang
            }

            goToXY(64, 15);//dua con tro chuot vao giua o
            TextColor(112 + 3);//nen trang chu xanh
            cout << "PLAY"; //viet chu vao o dc chon
        }
        else 
        {
            TextColor(7); //chu mau trang nen den
            for (int i = 0; i < 3; i++) 
            {
                goToXY(60, 14 + i);
                cout << "             ";//o nen den
            }

            goToXY(64, 15);
            TextColor(3);
            cout << "PLAY";
        }

        if (choice[1]) 
        {
            TextColor(112);
            for (int i = 0; i < 3; i++) 
            {
                goToXY(60, 17 + i);
                cout << "             ";
            }

            goToXY(61, 18);
            TextColor(112 + 2);
            cout << "LEADERBOARD";
        }
        else 
        {
            TextColor(7);
            for (int i = 0; i < 3; i++) 
            {
                goToXY(60, 17 + i);
                cout << "             ";
            }

            goToXY(61, 18);
            TextColor(2);
            cout << "LEADERBOARD";
        }

        if (choice[2]) 
        {
            TextColor(112);
            for (int i = 0; i < 3; i++) 
            {
                goToXY(60, 20 + i);
                cout << "             ";
            }

            goToXY(64, 21);
            TextColor(112 + 4);
            cout << "EXIT";
        }
        else 
        {
            TextColor(7);
            for (int i = 0; i < 3; i++) 
            {
                goToXY(60, 20 + i);
                cout << "             ";
            }

            goToXY(64, 21);
            TextColor(4);//chu mau do
            cout << "EXIT";
        }

        TextColor(7);

        if (temp = _getch()) 
        {
            if (temp != 224 && temp)
            {
                if (temp == ENTER_KEY) //Neu nhan enter -> xoa man hinh va chuyen vao man choi
                {
                    system("cls");
                    return curChoice;
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