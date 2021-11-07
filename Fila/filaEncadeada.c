#include <stdio.h>
#include <stdlib.h>

#include "filaEncadeada.h"


//criando elemento
struct elemento{
    int dado;
    struct elemento *prox;
};

//typedef do elemento
typedef struct elemento Elemento;

//criando nó descritor
struct descritor{
    Elemento *inicio;
    Elemento *fim;
    int quant;
};


// função para alocar memória do tipo Fila
Fila* criar_fila()
{
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->inicio = NULL;
        fi->fim = NULL;
        fi->quant = 0;
    }
    return fi;
}



// função para liberar memória
int liberar_fila(Fila *fi)
{

  if(fi == NULL){    
    return 0;
  }

  Elemento *atual;

  while(fi->inicio != NULL){    
    atual = fi->inicio;
    fi->inicio = fi->inicio->prox;
    fi->quant--;
    free(atual);
  }

  free(fi);  

  return 1;
}


// função para alocar memória do tipo Elemento
Elemento* criar_elemento()
{
    return (Elemento*) malloc(sizeof(Elemento));
}


// Função para criar a lista com todos os atendimentos iniciais juntos
void inicioCodigo(Fila *fi, int dado, int n) {

  Elemento *no;
  no = criar_elemento();

  dado = 0;
  no->dado = dado;
  no->prox = NULL;

  int num = 0; // Variável usada para criar essa primeira lista

  int i;
  for (i=0;i<n;i++) {

    enfileirar(fi, num);
    num++;

  }

  fi->quant = n;
  dado = 0;

}


// função para inserir elemento no final da fila 
int enfileirar(Fila *fi, int dado)
{
  if(fi == NULL){
    return 0;
  }

  // cria um elemento novo
  Elemento *no;
  no = criar_elemento();

  if(no == NULL){
    return 0;
  } 

  // atribui valores ao elemento novo
  no->dado = dado;
  no->prox = NULL;

  // se a fila estiver vazia, insere no início da fila
  if(fi->inicio == NULL){    
    fi->inicio = no;  

  // senão insere elemento no final da fila  
  }else{
    (fi->fim)->prox = no;    
  }

  fi->fim = no;
  fi->quant++;

  return 1;
}

// função para remover elemento do início da fila
int desenfileirar(Fila *fi)
{
  if(fi == NULL){
    return 0;
  }

  // fila vazia, não remove nada
  if(fi->inicio == NULL){
    return 0;
  }

  // remove elemento do início da fila
  Elemento *no;
  no = fi->inicio;
  fi->inicio = fi->inicio->prox;
  fi->quant--;

  // libera Elemento no
  free(no);

  // se a fila ficou vazia
  if(fi->inicio == NULL){
    fi->fim = NULL;
  }

  return 1;
}


int consultar_inicio_fila(Fila *fi, int *dado)
{
  // verifica se a fila foi criada corretamente e se não está vazia
  if(fi == NULL || fi->inicio == NULL){
    return 0;
  }

  // copia o dado do início da fila
  *dado = fi->inicio->dado;

  return 1;
}

int tamanho_fila(Fila *fi)
{
    if(fi == NULL){
        return -1;
    }
    return fi->quant;
}
