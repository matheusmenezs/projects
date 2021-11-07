#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declara��o da struct para armanezamento
* tempor�rio das informa��es do usu�rio
*/
struct user
{
    char name[50];
    int wins, jogos, simbol;
};
/*
* Declara��o das fun��es
*/
int verificaVitoria(char M[3][3]);
void zeraMatriz(char M[3][3]);
void zeraVariaveis(int turno, int win, int velha, int aux, int usuVi);

int main()
{
    // Declara��o das vari�veis
    int n = 3, aux = 1, op = 0, win = 0, velha = 0, usuVi = 0;
    int botJogX, botJogY, botVi = 0, turno = 0;
    int lin = 0, col = 0;
    char M[n][n];
    struct user u;
    u.jogos = 0;
    u.wins = 0;

    //Preenchendo a Matriz 3x3 com espa�os em branco
    zeraMatriz(M);
    // Utiliza��o da estrutura DOWHILE como menu de sele��o de op��es
    do
    {
        //Amostragem do Menu
        printf("----------------Menu----------------\n");
        //Esquema para printagem diferente
        //caso n�o seja o primeiro jogo
        if (!u.jogos)
        {
            printf("\t1. Jogar\n");
        }
        else
        {
            printf("\t1. Jogar Novamente\n");
        }
        printf("\t2. Sair\n");
        printf("------------------------------------\n");
        printf(" Op��o: ");
        //Leitura da vari�vel controladora do looping
        scanf("%d", &op);
        ////////Fim Menu//////////
        /*if (!u.jogos && op == 1)
        {
            op = 3;
        }*/
        switch (op)
        {
        case 1:
            //system("cls");       //Comando para limpar a tela no windows
            printf("\e[H\e[2J"); // Comando para limpar a tela no linux

            /*
            *Armazenando o nome do usuario;
            *Caso n�o seja o primeiro jogo
            */
            if (!u.jogos)
            {
                printf("Entre com o nome do usuario: ");
                scanf("%s", u.name);
            }
            //Leitura do s�mbolo do jogador
            printf("Escolha com qual simbolo deseja jogar:\n\t1 . X\n\t2 . O\n");
            printf("Op��o: ");
            scanf("%d", &u.simbol);

            if (u.simbol != 1 && u.simbol != 2)
            {
                printf("\nOpcao Invalida!, ir� jogar com X\n");
                u.simbol = 1;
            }
            printf("aux: %d\n", aux);
            while (aux != 0)
            {
                //system("cls"); //Comando para limpar a tela no windows
                //printf("\e[H\e[2J"); // Comando para limpar a tela no linux
                // Estrutura de repeti��o For para mostrar o tabuleiro
                if (!turno || botVi || usuVi)
                {
                    ////Printagem do tabuleiro////
                    for (int i = 0; i < (n + 2); i++)
                    {
                        printf("\t");
                        for (int j = 0; j < n; j++)
                        {
                            if (i != 1 && i != 3)
                            {
                                //Espa�os � serem preenchidos
                                if (i == 4)
                                {
                                    printf(" %c ", M[i - 2][j]);
                                }
                                else if (i == 2)
                                {
                                    printf(" %c ", M[i - 1][j]);
                                }
                                else
                                {
                                    printf(" %c ", M[i][j]);
                                }
                                if (j < 2)
                                {
                                    printf("|");
                                }
                            }
                            else
                            {
                                //Barra horizontal que cruza o tabuleiro
                                if (j < 2)
                                {
                                    printf("----");
                                }
                                else
                                {
                                    printf("---");
                                }
                            }
                        }
                        printf("\n");
                    }
                    ////Fim da printagem do tabuleiro////
                    if (win)
                    {
                        aux = 0;
                        break;
                    }
                }
                // Separa��o dos turnos entre o bot e o usu�rio
                // Usu�rio
                if (!turno && !win && !velha)
                {
                    ////Jogada do usuario
                    do{
                        /*
                        * Loop para verificar se o a posi��o
                        * escolhida pelo usu�rio j� esxiste
                        * dentro da matriz de caracteres
                        */
                        printf("\nJogador: %s", u.name);
                        printf("\nDigite a linha: ");
                        scanf("%d", &lin);
                        printf("Digite a coluna: ");
                        scanf("%d", &col);
                        // Verifica se a posi��o escolhida est� vazia
                        if(M[lin-1][col-1] == ' '){
                            if (u.simbol == 1)
                            {
                                M[lin - 1][col - 1] = 'X';
                            }
                            else
                            {
                                M[lin - 1][col - 1] = 'O';
                            }
                            turno = 1;
                        }else
                        {
                            printf("\nPosi��o inv�lida!,tente novamente\n");
                        }
                    }while(!turno);
                    //Verifica��o  de vit�ria do jogador ao fim de cada jogada
                    win = verificaVitoria(M);
                    if(win){
                        //variavel que corresponde � vitoria do jogador
                        usuVi = 1;
                    }
                }
                //Bot
                else if (!win && !velha)
                {
                    ////Jogada do bot
                    do
                    {
                        /*
                        * Loop para verificar se o n�mero
                        * aleat�rio tirado pelo bot j� existe
                        * dentro da matriz de caracteres
                        */
                        botJogX = (rand() % 3);
                        botJogY = (rand() % 3);
                        if (M[botJogX][botJogY] == ' ')
                        {
                            if (u.simbol == 1)
                            {
                                /*Verifica qual simbolo usar
                                a partir da escolha do usuario*/
                                M[botJogX][botJogY] = 'O';
                            }
                            else
                            {
                                M[botJogX][botJogY] = 'X';
                            }
                            turno = 0;
                        }
                        else
                        {
                            turno = 1;
                        }
                        //Verifica��o de V�toria do bot ao fim de cada jogada
                        win = verificaVitoria(M);
                        if(win){
                            botVi = 1;
                        }
                        //printf("\n\n\t%d  %d\n\n", botJogX, botJogY);
                    } while (turno != 0);
                    /* Utiliza o turno como auxiliar para o loop
                       caso a posicao aleatoria ja esteja preenchida
                       o programa continua no looping*/
                }
                if(!win && !velha)
                {
                    aux++;
                }
                if(aux==10){
                    velha=1;
                    aux = 0;
                    break;
                }
            }
            if (turno && !velha)
            {
                printf("\nParabens voc� ganhou!\n\n");
                zeraMatriz(M);
                u.wins++;
                u.jogos++;
            }
            else if (!turno && !velha)
            {
                printf("\nVitoria do bot!, tente novamente\n\n");
                zeraMatriz(M);
                u.jogos++;
            }
            else
            {
                printf("\nDeu Velha!!, tente novamente\n\n");
                zeraMatriz(M);
                u.jogos++;
            }
            break;
        case 2:

            break;
        default:
            printf("\nOpcao Inv�lida, tente novamente\n\n");
            break;
        }
    //  zeraVariaveis(turno, win, velha, aux, usuVi);
        turno = 0;
        win = 0;
        velha = 0;
        aux = 1;
        usuVi = 0;
    } while (op != 2);
    /*
    * Se a op��o selecionada no menu for 2, ou seja sair,
    * O programa sai da estrutura de repeti��o
    */
    return 0;
}

int verificaVitoria(char M[3][3])
{
    int res = 0;
    if ((M[0][0] == M[0][1] && M[0][1] == M[0][2] && M[0][2] != ' ') ||
        (M[1][0] == M[1][1] && M[1][1] == M[1][2] && M[1][2] != ' ') ||
        (M[2][0] == M[2][1] && M[2][1] == M[2][2] && M[2][2] != ' ') ||
        //Vitoria por linhas
        (M[0][0] == M[1][0] && M[1][0] == M[2][0] && M[2][0] != ' ') ||
        (M[0][1] == M[1][1] && M[1][1] == M[2][1] && M[2][1] != ' ') ||
        (M[0][2] == M[1][2] && M[1][2] == M[2][2] && M[2][2] != ' ') ||
        //Vitoria por colunas
        (M[0][0] == M[1][1] && M[1][1] == M[2][2] && M[2][2] != ' ') ||
        (M[2][0] == M[1][1] && M[1][1] == M[0][2] && M[0][2] != ' '))
    //Vitoria por Diagonais
    {
        res = 1;
    }
    return res;
}
void zeraMatriz(char M[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            M[i][j] = ' ';
        }
    }
}
