//Bibliotecas do sistema
#include<stdio.h>
#include<stdlib.h>

//Bibliotecas do projeto
#include"mesa.h"

struct pontos
{
  int pontos_casa;
  int pontos_jogador;
};

int main(){

  // no início a lista está vazia, logo, o ponteiro inicio tem valor NULL
  // o ponteiro inicio conterá o endereço do primeiro elemento da lista
  // Mc representa a lista de cartas da CASA
  Mesa* mc = NULL;
  
  // Mj representa a lista de cartas do Jogador
  Mesa* mj = NULL;

  Baralho* ba = NULL;
  int op, jogar=0, estourou=0, i; 
  int parar_casa, mais_cartas; 

  while(op!=3){
    op = exibe_menu();
    switch(op){
      case 1:
        system("clear");
        ba = criar_baralho();
        mc = criar_mesa();
        mj = criar_mesa();      
        iniciar_jogo(mc, mj, ba);
        while(jogar!=3 && !estourou){
          printf("------------------------------------------------\n");
          printf("\tSuas cartas somam: %d\n", somar_cartas(mj));
          printf("------------------------------------------------\n");
          printf("\t 1 - Mais uma carta\n");
          printf("\t 2 - Suas cartas\n");
          printf("\t 3 - Parar\n");
          printf("Decisão: ");
          scanf("%d", &jogar);
          switch(jogar){
            case 1:
              mais_uma_carta(mj, ba, 1);
            break;
            case 2:
              exibe_cartas(mj);
              scanf("%d", &i);
            break;
            case 3:
            if(somar_cartas(mj)<17){
              printf("\nVocê não pode parar antes de atingir ao menos 17\n");
              jogar = 0;
            }
            break;
            default:
              printf("\nOpção inválida, tente novamente\n");
            break;
          }
          if(somar_cartas(mj)>=21)
            estourou = 1;
        }
        mais_cartas = 0;
        while(!mais_cartas){
          mais_uma_carta(mc, ba, 0);
          if(somar_cartas(mc)<21)
            mais_cartas = 0;
          else
            mais_cartas = 1;
        }
        
        finalizar_jogo(mc, mj);
        
        //Zerando as variavéis para o recomeço
        estourou = 0;
        jogar=0;
        liberar_mesa(mc);
        liberar_mesa(mj);
        scanf("%d", &i);
        system("clear");
        break;
      case 2:
        exibe_regras();
        scanf("%d", &i);
        system("clear");
        break;

      case 3:
        printf("\n---------Obrigado por jogar---------\n\n");
        return 0;
        break;
    }
  }
  return 0;
}