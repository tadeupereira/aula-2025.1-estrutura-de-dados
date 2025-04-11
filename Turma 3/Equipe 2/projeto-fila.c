#include <stdio.h>
#include <string.h>

#define TAMANHO_FILA 100

typedef struct {
    char nome[100];
    char cpf[15];
    char prioridade[10];
} Cliente;

typedef struct {
    Cliente fila[TAMANHO_FILA];
    int frente;
    int tras;
} Fila;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
}

int filaCheia(Fila *f) {
    return f->tras == TAMANHO_FILA - 1;
}

int filaVazia(Fila *f) {
    return f->frente > f->tras;
}

void adicionarCliente(Fila *f, Cliente c) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível adicionar mais clientes.\n");
        return;
    }
    f->tras++;
    f->fila[f->tras] = c;
}

void removerCliente(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia. Nenhum cliente para remover.\n");
        return;
    }
    printf("Removendo cliente: %s\n", f->fila[f->frente].nome);
    f->frente++;
}

void listarClientes(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Clientes na fila:\n");
    for (int i = f->frente; i <= f->tras; i++) {
        printf("Nome: %s | CPF: %s | Prioridade: %s\n",
               f->fila[i].nome, f->fila[i].cpf, f->fila[i].prioridade);
    }
}

Cliente criarCliente(char *nome, char *cpf, char *prioridade) {
    Cliente c;
    strcpy(c.nome, nome);
    strcpy(c.cpf, cpf);
    strcpy(c.prioridade, prioridade);
    return c;
}