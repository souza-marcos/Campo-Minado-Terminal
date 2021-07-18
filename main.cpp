#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
//#include <conio.h>
using namespace std;

#define VERSION_GAME 0.4

int field[5][5], option = 0, level = 0, fieldMirror[5][5];
string playerName = "";
string msgBeginner = "O Nivel Iniciante tem 3 minas espalhadas pelo campo.\n";
string msgEasy = "O Nivel facil tem 6 minas espalhadas pelo campo.\n";
string msgMiddle = "O Nivel Intermediario tem 9 minas espalhadas pelo campo.\n";
string msgHard = "O Nivel Dificil tem 12 minas espalhadas pelo campo.\n";

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
    cout << "SOBRE O JOGO\nJogo de Campo Minado exigido como requisito parcial da materia de IAP - Introducao a Programacao.";
}

void aboutMe()
{
    cout << "SOBRE MIM\nMarcos Daniel, tecnico em informatica e estudante do curso de sistemas de informacao.";
}

void drawField()
{
    HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colors, 14); //Amarelo

    cout << "\t\tColunas" << endl
         << "\t   "; //3 spaces

    for (int i = 0; i < 5; i++)
    {
        cout << " " << i << "  ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        SetConsoleTextAttribute(colors, 14); //Amarelo
        cout << "Linha " << i << " -> ";
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
            if (fieldMirror[i][j] == -2)
            {
                cout << " ";
            }
            else if (fieldMirror[i][j] == -1)
            {
                SetConsoleTextAttribute(colors, 4); //Vermelho
                cout << "*";
            }
            else
            {
                SetConsoleTextAttribute(colors, 9); //Azul
                cout << fieldMirror[i][j];
            }
            SetConsoleTextAttribute(colors, 14); //Amarelo
            cout << " |";
        }
        cout << "\n\t   ";
        for (int i = 0; i < 5; i++)
        {
            cout << "---+";
        }
        cout << endl;
        SetConsoleTextAttribute(colors, 15);
    }
}

void inicializerField()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++) // -2 -> vazio
        {                           //
            field[i][j] = 0;        //
            fieldMirror[i][j] = -2;
        }
    }
}

/**
 * Retorna true se encontrar uma bomba
 * na posicao passada e false se nao encontrar
 */
bool verifyBomb(int *row, int *col)
{
    return (field[*row][*col] == -1 ? true : false);
}

void addBombs(int rowInitial, int colInitial)
{
    int seed = time(NULL);
    srand(seed);
    int bombs = (level / 8.0) * 25.0;
    int rowSelected, colSelected;
    for (int i = 0; i < bombs; i++)
    {
        while (true)
        {
            rowSelected = (rand() % 6);
            colSelected = (rand() % 6);
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
    // cout << "*CEL : " << *cel << endl
    //      << "&CEL: " << &cel << endl
    //      << "CEL: " << cel << endl;
    if (*cel != -1)
    {
        *cel += 1;
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

void showCell(int row, int col)
{
    fieldMirror[row][col] = field[row][col];
}

void newGame()
{

    inicializerField();
    do
    {
        cout << "Digite seu nome: ";
        cin >> playerName;
    } while (playerName == "");

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
            mountField();
        }
        showCell(row, col);
        turn++;
        if (verifyBomb(&row, &col))
        {
            clear();
            cout << "\nBOOOMMM\nVoce perdeu!\n\n";
            Beep(500, 1000);
            drawField();
            pause();
            return;
        };
        if (turn == (26 - (level * 3)))
        {
            clear();
            cout << "\nVoce Ganhou! Parabens!\n\n";
            
            //Music Victory Credits: https://github.com/ShaneMcC/beeps/blob/master/ff-victory.sh
            Beep(784, 100);
            Sleep(100);
            Beep(784, 600);
            Beep(622, 600);
            Beep(698, 600);
            Beep(784, 200);
            Sleep(200);
            Beep(698, 200);
            Beep(784, 800);
            //End Music Victory

            drawField();
            pause();
            return;
        }
    }
}

int main()
{
    do
    {
        clear();
        drawInitialMenu();
        cin >> option;
        clear();
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
        if (option >= 1 && option <= 4)
        {
            cout << "\n\nDeseja continuar? \n\t(0) - SIM\n\t(1) - NAO ";
            cin >> option;
            clear();
        }

    } while (option < 1 || option > 4);

    return 0;
}

/*
COORD c;
    c.X = 10;
    c.Y = 10;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

    
*/