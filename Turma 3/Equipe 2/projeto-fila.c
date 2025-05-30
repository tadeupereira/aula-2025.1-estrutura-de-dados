#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cliente {
    char nome[100];
    char cpf[15];
    char prioridade[10];
    struct Cliente *prox;
} Cliente;

typedef struct {
    Cliente *inicio;
} Fila;

int compararPrioridade(const char *p1, const char *p2) {
    if (strcmp(p1, p2) == 0) return 0;
    if (strcmp(p1, "alta") == 0) return -1;
    if (strcmp(p1, "media") == 0 && strcmp(p2, "baixa") == 0) return -1;
    return 1;
}

Cliente* criarCliente(char *nome, char *cpf, char *prioridade) {
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    if (c == NULL) {
        printf("Erro ao alocar memoria para cliente.\n");
        exit(1);
    }
    strcpy(c->nome, nome);
    strcpy(c->cpf, cpf);
    strcpy(c->prioridade, prioridade);
    c->prox = NULL;
    return c;
}

Fila* inicializarFila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    f->inicio = NULL;
    return f;
}

void adicionarCliente(Fila *f, Cliente *novo) {
    if (f->inicio == NULL || compararPrioridade(novo->prioridade, f->inicio->prioridade) < 0) {
        novo->prox = f->inicio;
        f->inicio = novo;
    } else {
        Cliente *atual = f->inicio;
        while (atual->prox != NULL &&
               compararPrioridade(novo->prioridade, atual->prox->prioridade) >= 0) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

Cliente* removerCliente(Fila *f) {
    if (f->inicio == NULL) {
        printf("Fila vazia. Nenhum cliente para remover.\n");
        return NULL;
    }
    Cliente *removido = f->inicio;
    f->inicio = f->inicio->prox;
    removido->prox = NULL;
    return removido;
}

Cliente* buscarClienteLinear(Fila *f, const char *nome) {
    Cliente *atual = f->inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int compararPorNome(const void *a, const void *b) {
    Cliente *c1 = *(Cliente **)a;
    Cliente *c2 = *(Cliente **)b;
    return strcmp(c1->nome, c2->nome);
}

Cliente* buscarClienteBinaria(Fila *f, const char *nome) {
    int n = 0;
    Cliente *atual = f->inicio;
    while (atual != NULL) {
        n++;
        atual = atual->prox;
    }

    if (n == 0) return NULL;

    Cliente **vetor = (Cliente **)malloc(n * sizeof(Cliente *));
    atual = f->inicio;
    for (int i = 0; i < n; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }

    qsort(vetor, n, sizeof(Cliente *), compararPorNome);

    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(nome, vetor[meio]->nome);
        if (cmp == 0) {
            Cliente *encontrado = vetor[meio];
            free(vetor);
            return encontrado;
        } else if (cmp < 0) {
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }

    free(vetor);
    return NULL;
}

void listarClientes(Fila *f) {
    Cliente *atual = f->inicio;
    if (atual == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Clientes na fila:\n");
    while (atual != NULL) {
        printf("Nome: %s | CPF: %s | Prioridade: %s\n",
               atual->nome, atual->cpf, atual->prioridade);
        atual = atual->prox;
    }
}

void liberarFila(Fila *f) {
    Cliente *atual = f->inicio;
    while (atual != NULL) {
        Cliente *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(f);
}