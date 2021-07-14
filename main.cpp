#include <iostream>
#include <ctime>
#include <windows.h>
//#include <conio.h>
using namespace std;

#define VERSION_GAME 0.1

int field[5][5], option = 0, level = 0;
string playerName = "";
string msgBeginner = "O Nivel facil tem 5 minas espalhadas pelo campo.\n";
string msgEasy = "O Nivel facil tem 5 minas espalhadas pelo campo.\n";
string msgMiddle = "O Nivel facil tem 5 minas espalhadas pelo campo.\n";
string msgHard = "O Nivel facil tem 5 minas espalhadas pelo campo.\n";

void pause()
{
    cout << endl
         << "Pressione alguma tecla para continuar ... ";
    getchar(); // ENTER BEFORE
    getchar();
}

void clear()
{
#ifdef WIN32
    system("cls");
#endif

#ifndef WIN32
    system("clear");
#endif
}

void drawInitialMenu()
{
    cout << "-------- CAMPO MINADO v." << VERSION_GAME << " --------" << endl
         << endl
         << "Menu Principal" << endl
         << endl
         << "(1) Novo Jogo" << endl
         << "(2) Sobre o Jogo" << endl
         << "(3) Sobre mim" << endl
         << "(4) Sair" << endl
         << endl
         << "Sua opcao: ";
}

void drawDifficultMenu()
{
    cout << "-------- CAMPO MINADO v." << VERSION_GAME << " --------" << endl
         << endl
         << playerName << ", escolha un nivel de dificuldade " << endl
         << endl
         << "(1) - Iniciante" << endl
         << "(2) - Facil" << endl
         << "(3) - Intermediario" << endl
         << "(4) - Dificil" << endl
         << endl
         << "Sua opcao: ";
}

void aboutGame()
{
    cout << "ABOUT GAME";
}

void aboutMe()
{
    cout << "ABOUT ME";
}

void newGame()
{
    cout << "NEW GAME";
    cout << "Digite seu nome: ";
    cin >> playerName;
    if (playerName == "")
    {
        return;
    }

    do
    {
        clear();
        drawDifficultMenu();
        cin >> level;
        switch (level)
        {
        case 1:
            cout << msgBeginner;
            break;
        case 2:
            cout << msgEasy;
            break;
        case 3:
            cout << msgMiddle;
            break;
        case 4:
            cout << msgHard;
            break;
        default:
            cout << "Opcao Invalida\n";
            break;
        }
        pause();
        clear();
    } while (level<1 | level> 4);



}

void drawField()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << field[i][j];
        }
    }
}

int main()
{
    /**
     * Inicializacao do campo.
     */
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            field[i][j] = 0;
        }
    }

    do
    {
        drawInitialMenu();
        cin >> option;

        switch (option)
        {
        case 1:
            newGame();
            break;
        case 2:
            aboutGame();
            break;
        case 3:
            aboutMe();
            break;
        case 4:
            cout << "VOLTE SEMPRE! FLW.";
            return 0;
        default:
            cout << "Opcao invalida!";
            break;
        }

    } while (option < 1 || option > 4);

    return 0;
}

/*
COORD c;
    c.X = 10;
    c.Y = 10;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

    for (int i = 0; i < 4; i++)
    {
        Beep(300, 150);
    }
*/