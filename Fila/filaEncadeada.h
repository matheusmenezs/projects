#ifndef _FILA
#define _FILA

typedef struct descritor Fila;      

// funções para alocar e desalocar memória
Fila* criar_fila();

// função para obter informação da fila
int tamanho_fila(Fila *fi);
int liberar_fila(Fila *fi);

void inicioCodigo(Fila *fi, int dado, int n);

void retiraSenha(Fila *fi, int dado, int perfil, char tipo, char perf);

// funções para enfileirar e desenfileirar elementos da fila
int enfileirar(Fila *fi, int dado);        
int desenfileirar(Fila *fi);   

int consultar_inicio_fila(Fila *fi, int *dado); 

#endif 