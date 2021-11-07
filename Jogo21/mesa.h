// TAD para Lista Dinâmica Encadeada 

#ifndef _MESA
#define _MESA

//typedef das structs elementoMesa* Mesa e elementoBaralho* Baralho;
typedef struct elementoMesa* Mesa;
typedef struct elementoBaralho* Baralho;


//*****Funções de Baralho*****//
Baralho* criar_baralho();
int liberar_baralho(Baralho *ba);
int remover_carta(Baralho *ba, int naipe, int carta);
void exibe_baralho(Baralho *ba);


//*****Funções de Mesa*****//
//Funções para alocar e desalocar memória de mesa
Mesa* criar_mesa();
int liberar_mesa(Mesa *me);
int inserir_mesa(Mesa *me, int naipe, int carta);
void iniciar_jogo(Mesa *mc, Mesa *mj, Baralho * ba);

//*****Funções de Jogo*****//
void mais_uma_carta(Mesa *me, Baralho *ba, int jogador);
int somar_cartas(Mesa *me);
void finalizar_jogo(Mesa *m1, Mesa *m2);

//*****Funções de Exibição*****//
int exibe_menu();
void exibe_regras();
void exibe_cartas(Mesa *me);

#endif