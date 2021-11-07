#include <stdio.h>
#include <stdlib.h>
#include "filaEncadeada.h"
#include <time.h>

int criar_dado(int *dado);

int main(void) {

  // No início as filas estão vazias, então o ponteiro inicio tem valor NULL

  Fila *SE = NULL;
  Fila *XP = NULL;
  Fila *XC = NULL;
  Fila *NP = NULL;
  Fila *NC = NULL;

  int opcao, ok, pos; 
  int dado; 
  int n; 

  // Criação das variáveis relacionadas a chamada de senhas
  int chamadas = 0; 
  int random; 
  int aux1, aux2; 
  int contadorX = -1; // Variável que impede chamadas de caixa caso não tenham mais disponíveis
  int contadorN = -1; // Variável que impede chamadas negociais caso não tenham mais disponíveis
  int vezes = 0; // Variável para contar se a chamada preferencial será chamada primeiro.

  // Variáveis que contam os atendimentos realizados
  int AtendXP = 0; 
  int AtendXC = 0;
  int AtendNP = 0;
  int AtendNC = 0;
  int fim; 

  // Variáveis que armazenam o tipo de atendimento e o perfil do cliente
  char tipo, perf; 

  printf("Insira o limite de atendimentos da sessão atual: ");
  scanf("%d", &n);

  SE = criar_fila();
  XP = criar_fila();
  XC = criar_fila();
  NP = criar_fila();
  NC = criar_fila();

  inicioCodigo(SE, dado, n);

  do {
    printf("\n\nMenu de opções\n");
    printf("\n1 - Retirada de senha");
    printf("\n2 - Chamada de senha");
    printf("\n3 - Encerrar");
    printf("\n\nOpção: ");
    scanf("%d", &opcao);

    switch(opcao){

      case 1:

        system("clear");

        ok = consultar_inicio_fila(SE, &dado);
    
        if (ok){

          printf("Atendimento Nº: %02d\n", dado);
          printf("\nDigite o tipo de atendimento (Coloque X para Caixa ou N para Negocial):");
          scanf(" %c", &tipo);
          printf("\nDigite o perfil do cliente (Coloque P para Preferencial ou C para Convencional):");
          scanf(" %c", &perf);

          if (((tipo != 'X') && (tipo != 'N')) || ((perf != 'P') && (perf != 'C'))) {

            system("clear");

            printf("Alguma coisa deu errado na retirada de senha. Repita o processo novamente.");
            printf("\nObservação: O sistema aceita somente letras maiúsculas.\n\n");

          } else {

            consultar_inicio_fila(SE, &dado);

            if ((tipo == 'X') && (perf == 'P')) {
              ok = enfileirar(XP,dado);
            } else if ((tipo == 'X') && (perf == 'C')) {
              ok = enfileirar(XC,dado);
            } else if ((tipo == 'N') && (perf == 'P')) {
              ok = enfileirar(NP,dado);
            } else {
              ok = enfileirar(NC,dado);
            }

            system("clear");

            pos = desenfileirar(SE);

            if(pos == 1){
          printf("Remoção na fila de senha realizada com sucesso!\n");
        }else{
          printf("Falha na remoção na lista de senha!\n"); }

            if (ok == 1) {

              printf("Ação realizada com sucesso.");
              printf("\n\nÚltima senha retirada: ");
              if (tipo == 'X') {
                printf("X");
              } else printf("N");
              if (perf == 'P') {
                printf("P");
              } else printf("C");
              
              printf(" %02d", dado);

              chamadas++; // Possibilita chamar por uma senha
              n--; // Contabiliza quantas senhas que ainda não foram retiradas

            } else {

              printf("Falha ao passar a senha para o atendimento correspondente.");

            }

          }

        } else printf("Operação cancelada. Todas as senhas já foram retiradas.");

        break;
 
      case 2:

        system("clear");

        if (chamadas == 0) {

          printf("Operação cancelada. Todos as chamadas disponíveis foram realizadas.");

        } else {

          // Gera um número aleatório
          srand(time(0)); 
          random = rand()%2; 

          if (contadorN == 0) random = 0;
          if (contadorX == 0) random = 1;

          if (random == 0) {

            aux1 = tamanho_fila(XP);
            aux2 = tamanho_fila(XC);
            contadorX = aux1 + aux2;

            if (contadorX == 0) {

              printf("Ocorreu um erro. Por favor tente novamente.\n\n");

            } else {

              if (((vezes < 2) || (aux2 == 0)) && (aux1 != 0)) {

                consultar_inicio_fila(XP, &dado);
                desenfileirar(XP);
                printf("Chamando a senha %02d para o Caixa Preferencial.\n\n", dado);
                AtendXP++;
                vezes++;

              } else {

                consultar_inicio_fila(XC, &dado);
                desenfileirar(XC);
                printf("Chamando a senha %02d para o Caixa Convencional.\n\n", dado);
                AtendXC++;
                vezes = 0;

              }

            contadorX--;

            }

          } else {

            aux1 = tamanho_fila(NP);
            aux2 = tamanho_fila(NC);
            contadorN = aux1 + aux2;

            if (contadorX == 0) {

              printf("Ocorreu um erro. Por favor tente novamente.\n\n");

            } else {

              if (((vezes < 2) || (aux2 == 0)) && (aux1 != 0)) {

                consultar_inicio_fila(NP, &dado);
                desenfileirar(NP);
                printf("Chamando a senha %02d para o Negocial Preferencial.\n\n", dado);
                AtendNP++;
                vezes++;

              } else {

                consultar_inicio_fila(NC, &dado);
                desenfileirar(NC);
                printf("Chamando a senha %02d para o Negocial Convencional.\n\n", dado);
                AtendNC++;
                vezes = 0;

              }

            contadorN--;

            }

          }

        chamadas--;

        }

        break;

      case 3:

        system("clear");
        printf("\n-------------- Atendimento Caixa -------------\n");
        printf("Atendimentos Preferenciais realizados: ");
        if (AtendXP == 0 ) {
          printf("NENHUM\n");
        } else {
          printf("%d\n", AtendXP);
        }
        printf("Atendimentos Convencionais realizados: ");
        if (AtendXC == 0 ) {
          printf("NENHUM\n");
        } else {
          printf("%d\n", AtendXC);
        }

        printf("\n------------- Atendimento Negocial -------------\n");
        printf("Atendimentos Preferenciais realizados: ");
        if (AtendNP == 0 ) {
          printf("NENHUM\n");
        } else {
          printf("%d\n", AtendNP);
        }
        printf("Atendimentos Convencionais realizados: ");
        if (AtendNC == 0 ) {
          printf("NENHUM\n");
        } else {
          printf("%d\n", AtendNC);
        }

         printf("\n------------ Verificação das filas -------------\n");
        printf("Quantidade de senhas disponíveis para retirar: %d\n", n);

        printf("Quantidade de senhas disponíveis para chamada: %d\n", chamadas);

        printf("Quantidade de chamadas realizadas: %d\n", AtendNC+AtendNP+AtendXC+AtendXP);

        if ((n != 0) || (chamadas != 0)) { // Verifica se não existe mais senhas para retirar ou atendimentos pendentes

          printf("\nAinda há senhas para serem atendidas. Encerramento do programa cancelado.\n\n");

        } else {
          
          printf("\n\nSessão completa. Encerrando...");

          liberar_fila(SE);
          liberar_fila(XP);
          liberar_fila(XC);
          liberar_fila(NP);
          liberar_fila(NC);

          fim = 1;

        }

        break;

      default:

        system("clear");
        printf("Opção inválida.\n\n");

        break;

    }

  } while (fim < 1);

  return 0;
}