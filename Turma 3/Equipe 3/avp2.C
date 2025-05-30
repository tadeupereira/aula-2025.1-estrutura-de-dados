#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    char* codigo;
    char* descricao;
    int quantidade;
    struct Produto* proximo;
} Produto;

Produto* criarProduto(const char* codigo, const char* descricao, int quantidade) {
    Produto* novo = malloc(sizeof(Produto));
    if (!novo) return NULL;

    novo->codigo = strdup(codigo);
    novo->descricao = strdup(descricao);
    novo->quantidade = quantidade;
    novo->proximo = NULL;

    return novo;
}

Produto* adicionarProduto(Produto* inicio, const char* codigo, const char* descricao, int quantidade) {
    Produto* novo = criarProduto(codigo, descricao, quantidade);
    if (!novo) return inicio;

    novo->proximo = inicio;
    return novo;
}

Produto* removerProduto(Produto* inicio, const char* codigo) {
    Produto* atual = inicio;
    Produto* anterior = NULL;

    while (atual) {
        if (strcmp(atual->codigo, codigo) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else inicio = atual->proximo;

            printf("Produto removido: %s - %s\n", atual->codigo, atual->descricao);
            free(atual->codigo);
            free(atual->descricao);
            free(atual);
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Produto com código %s não encontrado.\n", codigo);
    return inicio;
}

void listarProdutos(Produto* inicio) {
    if (!inicio) {
        printf("A lista está vazia.\n");
        return;
    }

    Produto* atual = inicio;
    printf("\nLista de Produtos:\n");
    while (atual) {
        printf("Código: %s\n", atual->codigo);
        printf("Descrição: %s\n", atual->descricao);
        printf("Quantidade: %d\n\n", atual->quantidade);
        atual = atual->proximo;
    }
}

Produto** listaParaVetor(Produto* inicio, int* tamanho) {
    *tamanho = 0;
    Produto* atual = inicio;
    while (atual) {
        (*tamanho)++;
        atual = atual->proximo;
    }

    Produto** vetor = malloc(*tamanho * sizeof(Produto*));
    atual = inicio;
    for (int i = 0; i < *tamanho; i++) {
        vetor[i] = atual;
        atual = atual->proximo;
    }

    return vetor;
}

Produto* ordenarPorDescricao(Produto* inicio) {
    int tamanho;
    Produto** vetor = listaParaVetor(inicio, &tamanho);

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(vetor[j]->descricao, vetor[j + 1]->descricao) > 0) {
                Produto* temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < tamanho - 1; i++) {
        vetor[i]->proximo = vetor[i + 1];
    }
    vetor[tamanho - 1]->proximo = NULL;

    Produto* novoInicio = vetor[0];
    free(vetor);
    return novoInicio;
}

Produto* buscaLinear(Produto* inicio, const char* descricao) {
    Produto* atual = inicio;
    while (atual) {
        if (strcmp(atual->descricao, descricao) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

Produto* buscaBinaria(Produto* inicio, const char* descricao) {
    int tamanho;
    Produto** vetor = listaParaVetor(inicio, &tamanho);

    int inicioIdx = 0, fimIdx = tamanho - 1;
    while (inicioIdx <= fimIdx) {
        int meio = (inicioIdx + fimIdx) / 2;
        int cmp = strcmp(vetor[meio]->descricao, descricao);

        if (cmp == 0) {
            Produto* encontrado = vetor[meio];
            free(vetor);
            return encontrado;
        } else if (cmp < 0) {
            inicioIdx = meio + 1;
        } else {
            fimIdx = meio - 1;
        }
    }

    free(vetor);
    return NULL;
}

void liberarLista(Produto* inicio) {
    while (inicio) {
        Produto* temp = inicio;
        inicio = inicio->proximo;
        free(temp->codigo);
        free(temp->descricao);
        free(temp);
    }
}