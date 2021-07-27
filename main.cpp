#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

#define VERSION_GAME 0.4

int field[5][5], level = 0, fieldMirror[5][5];
string playerName = "";
string msgBeginner = "O Nivel Iniciante tem 3 minas espalhadas pelo campo.\n";
string msgEasy = "O Nivel facil tem 6 minas espalhadas pelo campo.\n";
string msgMiddle = "O Nivel Intermediario tem 9 minas espalhadas pelo campo.\n";
string msgHard = "O Nivel Dificil tem 12 minas espalhadas pelo campo.\n";

void pause();
void clear();
void drawInitialMenu();
void drawDifficultMenu();
void aboutGame();
void aboutMe();
void drawField();
void inicializerField();
bool verifyBomb(int row, int col);
void addBombs(int rowInitial, int colInitial);
void mountCel(int row, int col);
void mountField();
void showCell(int row, int col);
bool validatePosition(int row, int col);
void drawFullField();
void newGame();

int main()
{
    int option = 0;

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
            cout << "\n\nVoltar ao menu INICIAL? \n\t(0) - SIM, Quero Voltar.\n\t(1) - NAO, Quero sair do jogo. ";
            cin >> option;
            clear();
        }

    } while (option < 1 || option > 4);

    return 0;
}

/**
 * Pausa o terminal.
 */
void pause()
{
    cout << endl
         << "Pressione ENTER para continuar ... ";
    getchar(); // ENTER BEFORE
    getchar();
}

/**
 * Limpa o terminal.
 */
void clear()
{
#ifdef WIN32
    system("cls");
#endif

#ifndef WIN32
    system("clear");
#endif
}

/**
 * Desenha o Menu Inicial no terminal.
 */
void drawInitialMenu()
{
    cout << "-------- CAMPO MINADO v." << VERSION_GAME << " --------" << endl
         << endl
         << "Menu Principal" << endl
         << "(1) Novo Jogo" << endl
         << "(2) Sobre o Jogo" << endl
         << "(3) Sobre mim" << endl
         << "(4) Sair" << endl
         << endl
         << "Sua opcao: ";
}

/**
 * Desenha o Menu de Dificuldade no teminal.
 */
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

/**
 * Desenha as informacoes sobre o jogo no terminal.
 */
void aboutGame()
{
    cout << "SOBRE O JOGO\n";
    cout <<
        R"(
      Campo minado e um popular
      jogo de computador para um
      jogador. Foi inventado por
      Robert Donner em 1989 e 
      como objectivo revelar um 
      campo de minas sem que alguma
      seja detonada. Este jogo 
      tem sido reescrito para as
      mais diversas plataformas, 
      sendo a sua versao mais 
      popular a que vinha nativamente
      nas edicoes anteriores ao Windows 10.(WIKIPEDIA) )";
}

/**
 * Desenha as informacoes sobre o autor desse programa no terminal.
 */
void aboutMe()
{
    cout << "SOBRE MIM\nMarcos Daniel, tecnico em informatica e estudante do curso de sistemas de informacao.";
}

/**
 * Desenha o campo no terminal de acordo com seu estado(lugares ocultos, nao ocultos, etc)
 */
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

/**
 * Inicializa o Campo, tanto o espelho que o usuario ve quanto o campo necessario para o algoritmo.
 */
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
 * Verica se existe bomba em determinada localizacao.
 * @param row linha do campo.
 * @param col coluna do campo.
 * @return True se existe bomba na celula e false se nao existe. 
 */
bool verifyBomb(int row, int col)
{
    return (field[row][col] == -1 ? true : false);
}

/**
 * Adiciona as bombas no campo, de modo que a primeira jogada nunca sera uma bomba.
 * @param rowInitial a linha da primeira jogada.
 * @param colInitial a coluna da primeira jogada.
 */
void addBombs(int rowInitial, int colInitial)
{
    int seed = time(NULL);
    srand(seed);
    int bombs = (level / 8.0) * 25.0; // Quantidade de bombas de acordo com o nivel escolhido.
    int rowSelected, colSelected;
    for (int i = 0; i < bombs; i++)
    {
        while (true)
        {
            rowSelected = (rand() % 5);
            colSelected = (rand() % 5);
            if ((rowSelected != rowInitial || colSelected != colInitial) && field[rowSelected][colSelected] != -1)
            {
                field[rowSelected][colSelected] = -1;
                break;
            }
        }
    }
}

/**
 * Monta a celula do campo - Incrementa o numero da celula caso haja bomba ao redor
 * ESTRITAMENTE auxiliar a funcao mountField.
 * @param row linha da celula
 * @param col coluna da celula
 */
void mountCel(int row, int col)
{
    if (row == 4)
    {
        Sleep(100);
    }

    if (row < 0 || row > 4 || col < 0 || col > 4 || field[row][col] == -1)
    {
        return;
    }
    else
    {
        field[row][col] += 1;
    }
}

/**
 * Monta o campo - adiciona os numeros de acordo com as bombas ao redor.
 */
void mountField()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (field[i][j] == -1)
            {
                int iPos = (i + 1), iAnt = (i - 1);
                int jPos = (j + 1), jAnt = (j - 1);
                mountCel(iAnt, jAnt);
                mountCel(iAnt, j);
                mountCel(iAnt, jPos);
                mountCel(i, jPos);
                mountCel(iPos, jPos);
                mountCel(iPos, j);
                mountCel(iPos, jAnt);
                mountCel(i, jAnt);
            }
        }
    }
}

/**
 * Revela o valor da celula.
 */
void showCell(int row, int col)
{
    fieldMirror[row][col] = field[row][col];
}

/** 
 * Funcao que valida a posicao inserida pelo usuario.
 * @param row linha da celula
 * @param col coluna da celula
 */ 
bool validatePosition(int row, int col)
{
    if (row < 0 || row > 4 || col < 0 || col > 4)
    {
        cout << "\nPosicao invalida!\n";
        return false;
    }

    if (fieldMirror[row][col] != -2 && fieldMirror[row][col] != -1)
    {
        cout << "\nPosicao ja visualizada!\n";
        return false;
    }
    return true;
}

/**
 * Funcao que desenha o campo com todas os lugares ja visiveis. 
 * WARNING: A funcao vai redefinir a matriz espelho. (FieldMirror) 
 */
void drawFullField()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fieldMirror[i][j] = field[i][j];
        }
    }
    drawField();
}


/**
 * Funcao para a logica do jogo em si. Novo jogo e criado.
 */
void newGame()
{

    inicializerField();
    do
    {
        cout << "Digite seu nome: ";//Teste user souza-marcos
        cin >> playerName;
    } while (playerName == "");

    // Menu de dificuldade
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

        if (!validatePosition(row, col))
        {
            pause();
            continue;
        }

        if (turn == 1)
        {
            addBombs(row, col);
            mountField();
        }

        showCell(row, col);
        turn++;
        if (verifyBomb(row, col))
        {
            clear();
            cout << "\nBOOOMMM\nVoce perdeu!\n\n";
            Beep(500, 1000);
            drawFullField();
            pause();
            return;
        }

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

            drawFullField();
            pause();
            return;
        }
    }
}