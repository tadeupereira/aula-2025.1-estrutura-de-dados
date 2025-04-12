#include <stdio.h>
#include <stdlib.h>

#define TAM 100

typedef struct {
    char nome[100];
    char cpf[15];
    char prioridade[10];
} Cliente;

typedef struct {
    Cliente clientes[TAM];
    int inicio;
    int fim;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == f->fim;
}

int filaCheia(Fila *f) {
    return f->fim == TAM;
}

int validarCPF(char *cpf) {
    int count = 0;

    for (int i = 0; cpf[i] != '\0'; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            count++;
        } else if (cpf[i] != '.' && cpf[i] != '-') {
            return 0;
        }
    }

    return count == 11;
}

void adicionarCliente(Fila *f) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel adicionar mais clientes.\n");
        return;
    }

    Cliente c;

    printf("Nome: ");
    scanf(" %[^\n]", c.nome);

    do {
        printf("CPF (somente numeros ou com . e -): ");
        scanf(" %s", c.cpf);

        if (!validarCPF(c.cpf)) {
            printf("CPF invalido! Digite novamente.\n");
        }
    } while (!validarCPF(c.cpf));

    printf("Prioridade (alta, media, baixa): ");
    scanf(" %s", c.prioridade);

    f->clientes[f->fim] = c;
    f->fim++;

    printf("Cliente adicionado com sucesso!\n");
}

void removerCliente(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhum cliente para remover.\n");
        return;
    }

    printf("Removendo cliente: %s\n", f->clientes[f->inicio].nome);
    f->inicio++;
}

void listarClientes(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("\n--- Clientes na Fila ---\n");
    for (int i = f->inicio; i < f->fim; i++) {
        printf("Nome: %s\n", f->clientes[i].nome);
        printf("CPF: %s\n", f->clientes[i].cpf);
        printf("Prioridade: %s\n\n", f->clientes[i].prioridade);
    }
}

int main() {
    Fila fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar cliente\n");
        printf("2. Remover cliente\n");
        printf("3. Listar clientes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarCliente(&fila);
                break;
            case 2:
                removerCliente(&fila);
                break;
            case 3:
                listarClientes(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}