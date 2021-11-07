// TAD para Lista Dinâmica Encadeada 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mesa.h"

typedef struct elementoMesa{
  int naipe;
  int carta;
  struct elementoMesa *prox;
}ElementoMesa;

typedef struct elementoBaralho{
  int naipe;
  int cartas[13];
  int qtd;
  struct elementoBaralho *prox;
}ElementoBaralho;


//**********Funções de Baralho**********//

// Função que cria uma lista encadeada baralho
Baralho* criar_baralho()
{
  Baralho *ba = (Baralho*) malloc(sizeof(Baralho));
  
  // se a lista baralho foi criada corretamente, indica que ela está vazia
  if(ba != NULL){
    *ba = NULL;
  } 

  // atribui valores ao elemento novo
  for(int i=1; i<=4; i++){
    ElementoBaralho *no =(ElementoBaralho*) malloc(sizeof(ElementoBaralho));
    no->naipe = i;
    for(int i=0;i<13; i++){
      no->cartas[i] = i+1;
    }
    no->qtd = 13;
    no->prox = (*ba);
    // insere elemento no início da lista
    *ba = no;
  }
  return ba;
}

// Função para liberar memória do baralho
int liberar_baralho(Baralho *ba)
{
  //Verifica se mesa está vazia
  if(ba == NULL){    
    return 0;
  }

  // libera todos os nós da lista mesa que foram alocados
  ElementoBaralho *no;
  while(*ba != NULL){
    no = *ba;
    *ba = (*ba)->prox;
    free(no);
  }

  // libera o ponteiro da mesa
  free(ba);

  return 1;  
}

// Remove uma determinada carta do baralho
int remover_carta(Baralho *ba, int naipe, int carta){
  
  if(ba == NULL){
    return 0;
  }

  // percorre a lista até achar o naipe
  ElementoBaralho *aux;
  aux = *ba;

  while(aux != NULL && aux->naipe != naipe){
    aux = aux->prox;
  }

  // Naipe não foi encontrado
  if(aux == NULL){
    return 0;
  }

  // Percorre o vetor de cartes até encontrar a carta no baralho
  int i=0;
  while(i < aux->qtd && aux->cartas[i] != carta){
    i++;
  }

  // Carta não existe no baralho
  if(i == aux->qtd){
    return 0;
  }
  
  // movimenta uma posição para trás, todos os elementos que estão depois da posição i, onde o elemento foi removido
  for(int k=i; k<aux->qtd-1; k++){
    aux->cartas[k] = aux->cartas[k+1];
  }
  aux->qtd--;
  return 1;
}



/*
******************************************************************
******************************************************************
******************************************************************
******************************************************************
******************************************************************
******************************************************************
*/


//**********Funções de Mesa**********//

// Função que cria uma lista encadeada mesa
Mesa* criar_mesa()
{
  Mesa *me = (Mesa*) malloc(sizeof(Mesa));  

  // se a lista mesa foi criada corretamente, indica que ela está vazia
  if(me != NULL){
    *me = NULL;
  } 

  return me;
}

// função para liberar memória da mesa
int liberar_mesa(Mesa *me)
{
  //Verifica se mesa está vazia
  if(me == NULL){    
    return 0;
  }

  // libera todos os nós da lista mesa que foram alocados
  ElementoMesa *no;
  while(*me != NULL){
    no = *me;
    *me = (*me)->prox;
    free(no);
  }

  // libera o ponteiro da mesa
  free(me);

  return 1;  
}

//Função para inserir cartas na lista de mesa
int inserir_mesa(Mesa *me, int naipe, int carta)
{
  if(me == NULL){
    return 0;
  }

  // cria um elemento novo
  ElementoMesa *no = (ElementoMesa*) malloc(sizeof(ElementoMesa));

  if(no == NULL){
    return 0;
  }

  // atribui valores ao elemento novo
  no->naipe = naipe;
  no->carta = carta;
  no->prox = (*me);

  // insere elemento no início da lista
  *me = no;

  return 1;
}


//**********Funções de jogo**********//
void iniciar_jogo(Mesa *mc, Mesa *mj, Baralho *ba)
{
  // Sorteam 4 cartas, 2 para casa e 2 para o jogador
  int carta, naipe, naipes[4], naipeValor[4], cartasValor[4], ok; 
  char cartas[4];
  char simbolos[4][4] = {"♠", "♣", "♥", "♦"};
  
  //Realiza o sorteio das duas primeiras cartas e substitui os valores de exibição
  for(int i=0; i<4; i++){
    srand(time(0) + i);
    naipe = rand() % 3;
    carta = (rand() % 12)+1;

    naipeValor[i] = naipe+1;
    naipes[i] = naipe;
    cartasValor[i] = carta;
    switch(carta){
      case 1:
      cartas[i] = 'A';
      break;
      case 10:
      cartas[i] = '1';
      break;
      case 11:
      cartas[i] = 'Q';
      break;
      case 12:
      cartas[i] = 'J';
      break;
      case 13:
      cartas[i] = 'K';
      break;
      default:
      cartas[i] = carta + '0';
      break;
    }
  }

  // Insere na lista as duas cartas inicias sorteadas para a casa
  if(!inserir_mesa(mc, naipeValor[0], cartasValor[0]))
    printf("\n\nErro ao inserir na mesa\n");
    
  // Remove a carta do baralho
  if(!remover_carta(ba, naipeValor[0], cartasValor[0]))
      printf("\n\nErro ao remover carta do baralho\n");

  if(!inserir_mesa(mc, naipeValor[1], cartasValor[1]))
    printf("\n\nErro ao inserir na mesa\n");
  if(!remover_carta(ba, naipeValor[1], cartasValor[1]))
      printf("\n\nErro ao remover carta do baralho\n");
  

  // Insere na lista as duas cartas inicias sorteadas para o usuário
  if(!inserir_mesa(mj, naipeValor[2], cartasValor[2]))
    printf("\n\nErro ao inserir na mesa\n");
  if(!remover_carta(ba, naipeValor[2], cartasValor[2]))
    printf("\n\nErro ao remover carta do baralho\n");
  
  if(!inserir_mesa(mj, naipeValor[3], cartasValor[3]))
    printf("\n\nErro ao inserir na mesa\n");
  if(!remover_carta(ba, naipeValor[3], cartasValor[3]))
    printf("\n\nErro ao remover carta do baralho\n");

  printf ("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
  printf ("█ █▀▀▀▀▀▀▀▀▀▀█  █▀▀▀▀▀▀▀▀▀▀█                                                  █\n");
  if(cartas[1]=='1')
    printf ("█ █    ▄▄    █  █ 10       █                                                  █\n");
  else
    printf ("█ █    ▄▄    █  █ %c        █                                                  █\n", cartas[1]);
  printf ("█ █    ▄▄    █  █ %s        █                                                  █\n",simbolos[naipes[1]]);
  printf ("█ █    ▄▄    █  █          █               ===CASA===                         █\n");
  printf ("█ █    ▄▄    █  █       %s  █                                                  █\n",simbolos[naipes[1]]);
  if(cartas[1]=='1')
    printf ("█ █          █  █       10 █                                                  █\n");
  else
    printf ("█ █          █  █       %c  █                                                  █\n",cartas[1]);
  printf ("█ █▄▄▄▄▄▄▄▄▄▄█  █▄▄▄▄▄▄▄▄▄▄█                                                  █\n");
  printf ("█                                                                             █\n");
  printf ("█                                                                             █\n");
  printf ("█                                                                             █\n");
  printf ("█                     Cartas da primeira rodada sorteadas                     █\n");
  printf ("█                                                                             █\n");
  printf ("█                                                  █▀▀▀▀▀▀▀▀▀▀█  █▀▀▀▀▀▀▀▀▀▀█ █\n");
  if(cartas[2]=='1' && cartas[3]=='1')
    printf ("█                                                  █ 10       █  █ 10       █ █\n");
  else if(cartas[2]=='1')
    printf ("█                                                  █ 10       █  █ %c        █ █\n",cartas[3]);
  else if(cartas[3]=='1')
    printf ("█                                                  █ %c       █  █ 10       █ █\n",cartas[2]);
  else
    printf ("█                                                  █ %c        █  █ %c        █ █\n",cartas[2],cartas[3]);
  printf ("█                                                  █ %s        █  █ %s        █ █\n",simbolos[naipes[2]],simbolos[naipes[3]]);
  printf ("█              ===VOCÊ===                          █          █  █          █ █\n"); 
  printf ("█                                                  █       %s  █  █       %s  █ █\n",simbolos[naipes[2]],simbolos[naipes[3]]);
  if(cartas[2]=='1' && cartas[3]=='1')
    printf ("█                                                  █       10 █  █       10 █ █\n");
  else if(cartas[2]=='1')
    printf ("█                                                  █       10 █  █       %c  █ █\n",cartas[3]);
  else if(cartas[3]=='1')
    printf ("█                                                  █       %c  █  █       10 █ █\n",cartas[2]);
  else
    printf ("█                                                  █       %c  █  █       %c  █ █\n",cartas[2],cartas[3]);
  printf ("█                                                  █▄▄▄▄▄▄▄▄▄▄█  █▄▄▄▄▄▄▄▄▄▄█ █\n");
  printf ("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");
  
}

void mais_uma_carta(Mesa *me, Baralho *ba, int jogador)
{
  int naipe, carta, numero_existe, naipe_simbolo;
  char carta_simbolo;
  char simbolos[4][4] = {"♠", "♣", "♥", "♦"};
  srand(time(NULL));
  do{
    naipe = (rand() % 3) + 1;
    carta = (rand() % 12) + 1;
    numero_existe = remover_carta(ba, naipe, carta);
    if(numero_existe)
      inserir_mesa(me, naipe, carta);
  }while(!numero_existe);
  
  // Quando jogador for 0 a função executará o trecho de código de exibição para o usuário
  if(jogador){
    //-1 para pode encontrar o simbolo no vetor simbolos
    naipe_simbolo = naipe - 1;
    switch(carta){
      case 1:
      carta_simbolo = 'A';
      break;
      case 10:
      carta_simbolo = '1';
      break;
      case 11:
      carta_simbolo = 'Q';
      break;
      case 12:
      carta_simbolo = 'J';
      break;
      case 13:
      carta_simbolo = 'K';
      break;
      default:
      carta_simbolo = carta + '0';
      break;
    }
    printf("\n-------Carta Sorteada-------\n\n");
    printf ("        █▀▀▀▀▀▀▀▀▀▀█\n");
    if(carta_simbolo=='1')
      printf ("        █ 10       █\n");
    else
      printf ("        █ %c        █\n", carta_simbolo);
    printf ("        █ %s        █\n", simbolos[naipe_simbolo]);
    printf ("        █          █\n");
    printf ("        █       %s  █\n",simbolos[naipe_simbolo]);
    if(carta_simbolo=='1')
      printf ("        █       10 █\n");
    else
      printf ("        █       %c  █\n",carta_simbolo);
    printf ("        █▄▄▄▄▄▄▄▄▄▄█\n");
  }
}
void finalizar_jogo(Mesa *mc, Mesa *mj)
{
  int soma_casa, soma_jogador;
  soma_casa = somar_cartas(mc);
  soma_jogador = somar_cartas(mj);
  printf("\n\n============Fim de jogo============\n\n");
  if(soma_jogador>21)
    printf("Você estourou!, suas cartas somaram: %d\n", soma_jogador);
  if(soma_casa>21)
    printf("A casa estourou!, as cartas dela somaram: %d\n", soma_casa);
  
  if(soma_jogador==21)
    printf("Você atingiu 21\n");
  if(soma_jogador<21)
    printf("Suas cartas somaram: %d\n", soma_jogador);
  if(soma_casa==21)
    printf("A casa atingiu 21\n");

  if(soma_jogador<=21 || soma_casa<=21){
    if(soma_jogador>soma_casa && soma_jogador<=21){
      printf("\n\t Você venceu, Parabéns!!\n");
    }else if(soma_jogador<soma_casa && soma_casa<=21){
      printf("\n\t Você perdeu, tente novamente!\n");
    }else if(soma_jogador>21){
      printf("\n\t Você perdeu, tente novamente!\n");
    }else if(soma_casa>21){
      printf("\n\t Você venceu, Parabéns!!\n");
    }else{
      printf("\n\t Vocês empataram\n");
    }
  }else{
    printf("\n\t Ninguem venceu, tente novamente!\n");
  }
  printf("\n===================================\n");
  printf("Insira qualquer coisa para continuar: ");
}
int somar_cartas(Mesa *me)
{
  // Verifica se houve erro na alocação
  if(me == NULL)
    return 0;
  
  int soma=0;
  int a = 0;

  // Cria lista auxiliar
  ElementoMesa *aux = *me;

  // Busca valor das cartas na lista e calcula valor total
  while(aux->prox!= NULL){
    // Caso seja uma carta especial
    if(aux->carta>10){
      soma+= 10;
    } else if(aux->carta==1){                 // Caso seja um Ás
      soma+= 1;
      a++;
    } else{                                   // Caso seja uma carta normal
      soma+= aux->carta;
    }
    aux = aux->prox;
  }
  // Repetir condições para o último elemento da lista (aux->prox == NULL)
  if(aux->carta>10){
    soma+= 10;
  } else if(aux->carta==1){
    soma+= 1;
    a++;
  } else{
    soma+= aux->carta;
  }
  // Caso Ás = 10 não estoure 21, somar Ás valendo 10. Senão, Ás = 1
  for(; a>0; a--){
    if(soma + 9 <= 21){
      soma+=9;
    } else{
      a = 0;
    }
  }
  return soma;
}

//**********Funções de exibição**********//

// Função responsável por exibir o menu e validar a escolha do jogador
int exibe_menu()
{
    int op = 0;
    while(op>3 || op<1){
        printf ("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                   █▀▀█ █   █▀▀█ █▀▀ █ █    █ █▀▀█ █▀▀ █ █                   █\n");
        printf ("█                   █▀▀▄ █   █▄▄█ █   █▀▄ ▄  █ █▄▄█ █   █▀▄                   █\n");
        printf ("█                   █▄▄█ ▀▀▀ ▀  ▀ ▀▀▀ ▀ ▀ █▄▄█ ▀  ▀ ▀▀▀ ▀ ▀                   █\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                                1 - Jogar                                    █\n");
        printf ("█                                2 - Regras                                   █\n");
        printf ("█                                3 - Sair                                     █\n"); 
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█                                                                             █\n");
        printf ("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");
      printf("Opção: ");
      scanf("%d", &op);
      if(op>3 || op<1){
        system("clear");
        printf("\n-------Valor Inválido-------\n\n");
      }
    }
    return op;
}
// Função responsável por exibir as regras do jogo
void exibe_regras()
{
  int i;
  system ("clear"); // IMPRIME AS REGRAS
  printf ("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
  printf ("█                                                                             █\n");
  printf ("█                               -=-[ Regras ]-=-                              █\n");
  printf ("█                                                                             █\n");
  printf ("█                                                                             █\n");
  printf ("█  Pontuação das cartas:                                                      █\n");
  printf ("█                                                                             █\n");
  printf ("█  A - vale 1 ou 10 pontos.                                                   █\n");
  printf ("█  2 a 10 - vale o mesmo valor da carta.                                      █\n");
  printf ("█  J, Q e K - vale 10 pontos cada uma.                                        █\n");
  printf ("█                                                                             █\n");
  printf ("█                                                                             █\n");
  printf ("█  O Jogo:                                                                    █\n");
  printf ("█                                                                             █\n");
  printf ("█ O jogador e o computador recebem inicialmente duas cartas cada. O jogador   █\n");
  printf ("█ inicia a partida, decidindo entre permanecer com a mão que está (opção      █\n");
  printf ("█ stand), ou comprar mais cartas, na tentativa de atingir o máximo de pontos, █\n");
  printf ("█ desde que seja menor ou igual a 21 (opção hit). Quando o jogador passa      █\n");
  printf ("█ a vez, o computador joga da mesma maneira, tentando atingir a melhor        █\n");
  printf ("█ pontuação. Cada jogador pode no máximo acumular 5 cartas na mão e sempre    █\n");
  printf ("█ que alguém estoura o limite de 21 pontos, o adversário vence.               █\n");
  printf ("█                                                                             █\n");
  printf ("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");
  printf ("Insira qualquer coisa para retornar ao menu\n");
 
}

//Função que exibe todas as cartas do usuário
void exibe_cartas(Mesa *me){
  int naipe_simbolo;
  char carta_simbolo;
  char simbolos[4][4] = {"♠", "♣", "♥", "♦"};
  ElementoMesa *aux = (*me);

  printf("-------------Suas cartas-------------\n");
  while(aux->prox != NULL){
    naipe_simbolo = aux->naipe - 1;
    switch(aux->carta){
      case 1:
      carta_simbolo = 'A';
      break;
      case 10:
      carta_simbolo = '1';
      break;
      case 11:
      carta_simbolo = 'Q';
      break;
      case 12:
      carta_simbolo = 'J';
      break;
      case 13:
      carta_simbolo = 'K';
      break;
      default:
      carta_simbolo = aux->carta + '0';
      break;
    }
    printf ("\n        █▀▀▀▀▀▀▀▀▀▀█\n");
    if(carta_simbolo=='1')
      printf ("        █ 10       █\n");
    else
      printf ("        █ %c        █\n", carta_simbolo);
    printf ("        █ %s        █\n", simbolos[naipe_simbolo]);
    printf ("        █          █\n");
    printf ("        █       %s  █\n",simbolos[naipe_simbolo]);
    if(carta_simbolo=='1')
      printf ("        █       10 █\n");
    else
      printf ("        █       %c  █\n",carta_simbolo);
    printf ("        █▄▄▄▄▄▄▄▄▄▄█\n");
    aux = aux->prox;
  }
  switch(aux->carta){
    case 1:
    carta_simbolo = 'A';
    break;
    case 10:
    carta_simbolo = '1';
    break;
    case 11:
    carta_simbolo = 'Q';
    break;
    case 12:
    carta_simbolo = 'J';
    break;
    case 13:
    carta_simbolo = 'K';
    break;
    default:
    carta_simbolo = aux->carta + '0';
    break;
  }
  printf ("\n        █▀▀▀▀▀▀▀▀▀▀█\n");
  if(carta_simbolo=='1')
    printf ("        █ 10       █\n");
  else
    printf ("        █ %c        █\n", carta_simbolo);
  printf ("        █ %s        █\n", simbolos[naipe_simbolo]);
  printf ("        █          █\n");
  printf ("        █       %s  █\n",simbolos[naipe_simbolo]);
  if(carta_simbolo=='1')
    printf ("        █       10 █\n");
  else
    printf ("        █       %c  █\n",carta_simbolo);
  printf ("        █▄▄▄▄▄▄▄▄▄▄█\n");
  printf("Insira qualquer coisa para voltar ao menu: ");
}


// Função de teste para exibição do baralho
void exibe_baralho(Baralho* ba)
{
    ElementoBaralho *aux = (*ba);
    int j = 0 ;
    while(aux->prox!=NULL){
      printf("Naipe: ");
      printf(" %d\n", aux->naipe);
      printf("Cartas: ");
      for(int i=0; i<aux->qtd;i++){
        printf(" %d ", aux->cartas[i]);
      }
      aux = aux->prox;
      printf("\n");
    }
    printf("Naipe: ");
    printf(" %d\n", aux->naipe);
    printf("Cartas: ");
    for(int i=0; i<aux->qtd;i++){
      printf(" %d ", aux->cartas[i]);
    }
    printf("\n");
}

