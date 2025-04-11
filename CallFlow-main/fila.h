#ifndef FILA_H
#define FILA_H

#define MAX_CHAMADAS 100

typedef struct {
    char numero[15];
    char nome[50];
    char dia[11];
    char horario[6];
} Chamada;

typedef struct {
    Chamada chamadas[MAX_CHAMADAS];
    int frente, tras;
} FilaChamadas;

void inicializarFila(FilaChamadas *fila);
int filaVazia(FilaChamadas *fila);
int filaCheia(FilaChamadas *fila);
void adicionarChamada(FilaChamadas *fila, Chamada chamada);
void removerChamada(FilaChamadas *fila);
void listarChamadas(FilaChamadas *fila);

#endif