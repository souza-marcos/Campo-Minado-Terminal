#include <iostream>
#include <ctime>

#include <windows.h>
#include <string>
//#include <conio.h>
using namespace std;

#define VERSION_GAME 0.1

int field[5][5], option = 0, level = 0, fieldMirror[5][5];
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

void drawField()
{
    cout << "\t\tColunas" << endl
         << "\t   "; //3 spaces

    for (int i = 0; i < 5; i++)
    {
        cout << " " << i << "  ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Linha " << i << " -> "; //1space
        for (int j = 0; j < 5; j++)
        {
            /**
             * TODO Change "field" per "fieldMirror"
             */
            //cout << " " << (field[i][j] == -2 ? " " : (field[i][j] == -1 ? "*" : to_string(field[i][j]))) << " |";
            cout << " " << field[i][j] << " |";
        }
        cout << "\n\t   ";
        for (int i = 0; i < 5; i++)
        {
            cout << "---+";
        }
        cout << endl;
    }
}

/**
 * Retorna true se 
 */
bool verifyBomb()
{
    return true;
}

void addBombs(int rowInitial, int colInitial)
{
    int seed = time(NULL);
    srand(seed);
    int bombs = (level / 8) * 25;
    int rowSelected, colSelected;
    for (int i = 0; i < bombs; i++)
    {
        while (true)
        {
            rowSelected = (rand() % 6) - 1;
            colSelected = (rand() % 6) - 1;
            if ((rowSelected != rowInitial || colSelected != colInitial) && field[rowSelected][colSelected] != -1)
            {
                field[rowSelected][colSelected] = -1;
                break;
            }
        }
    }
}

void mountCel(int *cel)
{
    if (*cel != -1)
    {
        *cel++;
    }
}

void mountField()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (field[i][j] == -1)
            {
                if (i == 0)
                {
                    if (j == 0)
                    {
                        mountCel(&field[i][j + 1]);
                        mountCel(&field[i + 1][j + 1]);
                    }
                    else if (j == 4)
                    {
                        mountCel(&field[i][j - 1]);
                        mountCel(&field[i + 1][j - 1]);
                    }
                    else
                    {
                        mountCel(&field[i][j + 1]);
                        mountCel(&field[i][j - 1]);
                        mountCel(&field[i + 1][j - 1]);
                        mountCel(&field[i + 1][j + 1]);
                    }
                    mountCel(&field[i + 1][j]);
                }
                else if (i == 4)
                {
                    if (j == 0)
                    {
                        mountCel(&field[i][j + 1]);
                        mountCel(&field[i - 1][j + 1]);
                    }
                    else if (j == 4)
                    {
                        mountCel(&field[i][j - 1]);
                        mountCel(&field[i - 1][j - 1]);
                    }
                    else
                    {
                        mountCel(&field[i][j + 1]);
                        mountCel(&field[i][j - 1]);
                        mountCel(&field[i - 1][j - 1]);
                        mountCel(&field[i - 1][j + 1]);
                    }
                    mountCel(&field[i - 1][j]);
                }
                else
                {
                    if (j == 0)
                    {
                        mountCel(&field[i][j + 1]);
                        mountCel(&field[i + 1][j + 1]);
                        mountCel(&field[i - 1][j + 1]);
                    }
                    else if (j == 4)
                    {
                        mountCel(&field[i][j - 1]);
                        mountCel(&field[i + 1][j - 1]);
                        mountCel(&field[i - 1][j - 1]);
                    }
                    else
                    {
                        mountCel(&field[i - 1][j - 1]);
                        mountCel(&field[i - 1][j + 1]);
                        mountCel(&field[i][j + 1]);
                        mountCel(&field[i + 1][j + 1]);
                        mountCel(&field[i + 1][j - 1]);
                        mountCel(&field[i][j - 1]);
                    }
                    mountCel(&field[i - 1][j]);
                    mountCel(&field[i + 1][j]);
                }
            }
        }
    }
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
    } while (level < 1 || level > 4);
    int turn = 1;
    while (true)
    {
        clear();
        drawField();
        int row, col;
        cout << "Digite a linha desejada: ";
        cin >> row;
        cout << "Digite a coluna desejada: ";
        cin >> col;

        if (turn == 1)
        {
            addBombs(row, col);
        }
        turn++;
    }
}

int main()
{
    /**
     * Inicializacao do campo.
     */
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++) // -2 -> vazio
        {                           //
            field[i][j] = 0;        //
            fieldMirror[i][j] = -2;
        }
    }

    //Test

    level = 4;
    addBombs(1, 1);
    mountField();
    drawField();

    return 0;

    //End Test

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