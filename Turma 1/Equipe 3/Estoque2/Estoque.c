#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DESC 100
#define MAX_COD 20

typedef struct Produto {
    char codigo[MAX_COD];
    char descricao[MAX_DESC];
    int quantidade;
    struct Produto* prox;
} Produto;

// Criar produto
Produto* criarProduto(char* codigo, char* descricao, int quantidade) {
    Produto* novo = (Produto*)malloc(sizeof(Produto));
    if (!novo) {
        printf("Erro de alocacao!\n");
        exit(1);
    }
    strcpy(novo->codigo, codigo);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    novo->prox = NULL;
    return novo;
}

// Adicionar produto - TAD por referência
void adicionarProduto(Produto** head, char* codigo, char* descricao, int quantidade) {
    Produto* novo = criarProduto(codigo, descricao, quantidade);
    novo->prox = *head;
    *head = novo;
    printf("Produto adicionado com sucesso!\n");
}

// Remover produto - retorna o item removido (ou NULL)
Produto* removerProduto(Produto** head, char* codigo) {
    Produto *atual = *head, *anterior = NULL;

    while (atual) {
        if (strcmp(atual->codigo, codigo) == 0) {
            if (anterior) anterior->prox = atual->prox;
            else *head = atual->prox;
            atual->prox = NULL;
            printf("Produto removido com sucesso!\n");
            return atual;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Produto nao encontrado.\n");
    return NULL;
}

// Listar produtos - TAD por valor
void listarProdutos(Produto* head) {
    Produto* atual = head;
    printf("\n--- Produtos em Estoque ---\n");
    if (!head) {
        printf("Nenhum produto em estoque.\n");
        return;
    }
    while (atual) {
        printf("Codigo: %s | Descricao: %s | Quantidade: %d\n",
               atual->codigo, atual->descricao, atual->quantidade);
        atual = atual->prox;
    }
}

// Trocar dados
void trocarProdutos(Produto* a, Produto* b) {
    char tempCod[MAX_COD], tempDesc[MAX_DESC];
    int tempQtd;

    strcpy(tempCod, a->codigo);
    strcpy(tempDesc, a->descricao);
    tempQtd = a->quantidade;

    strcpy(a->codigo, b->codigo);
    strcpy(a->descricao, b->descricao);
    a->quantidade = b->quantidade;

    strcpy(b->codigo, tempCod);
    strcpy(b->descricao, tempDesc);
    b->quantidade = tempQtd;
}

// Ordenar
void ordenarPorDescricao(Produto* head) {
    if (!head || !head->prox) {
        printf("Nao ha produtos suficientes para ordenar.\n");
        return;
    }
    bool trocou;
    Produto *ptr, *fim = NULL;

    do {
        trocou = false;
        ptr = head;
        while (ptr->prox != fim) {
            if (strcmp(ptr->descricao, ptr->prox->descricao) > 0) {
                trocarProdutos(ptr, ptr->prox);
                trocou = true;
            }
            ptr = ptr->prox;
        }
        fim = ptr;
    } while (trocou);

    printf("Produtos ordenados por descricao.\n");
}

// Busca linear
void buscaLinear(Produto* head, char* desc) {
    Produto* atual = head;
    while (atual) {
        if (strcmp(atual->descricao, desc) == 0) {
            printf("Produto encontrado: Codigo: %s | Descricao: %s | Quantidade: %d\n",
                   atual->codigo, atual->descricao, atual->quantidade);
            return;
        }
        atual = atual->prox;
    }
    printf("Produto nao encontrado.\n");
}

// Converter para vetor
Produto** converterParaVetor(Produto* head, int* tamanho) {
    int count = 0;
    Produto* atual = head;
    while (atual) {
        count++;
        atual = atual->prox;
    }

    if (count == 0) {
        *tamanho = 0;
        return NULL;
    }

    Produto** vetor = (Produto**)malloc(count * sizeof(Produto*));
    atual = head;
    for (int i = 0; i < count; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }
    *tamanho = count;
    return vetor;
}

void liberarVetor(Produto** vetor) {
    if (vetor) free(vetor);
}

// Busca binária
void buscaBinaria(Produto* head, char* desc) {
    ordenarPorDescricao(head);
    int tamanho = 0;
    Produto** vetor = converterParaVetor(head, &tamanho);

    int ini = 0, fim = tamanho - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(vetor[meio]->descricao, desc);
        if (cmp == 0) {
            printf("Produto encontrado (binaria): Codigo: %s | Descricao: %s | Quantidade: %d\n",
                   vetor[meio]->codigo, vetor[meio]->descricao, vetor[meio]->quantidade);
            liberarVetor(vetor);
            return;
        } else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    printf("Produto nao encontrado na busca binaria.\n");
    liberarVetor(vetor);
}

// Liberação
void liberarLista(Produto* head) {
    Produto* atual = head;
    while (atual) {
        Produto* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    printf("Memoria liberada.\n");
}

// Menu
void menu() {
    Produto* lista = NULL;
    int opcao;
    char buffer[20];
    char codigo[MAX_COD], descricao[MAX_DESC];
    int quantidade;

    do {
        printf("\n--- MENU ESTOQUE ---\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Listar produtos\n");
        printf("4. Ordenar por descricao\n");
        printf("5. Busca linear por descricao\n");
        printf("6. Busca binaria por descricao\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Codigo: "); fgets(codigo, MAX_COD, stdin);
                codigo[strcspn(codigo, "\n")] = 0;
                printf("Descricao: "); fgets(descricao, MAX_DESC, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                printf("Quantidade: ");
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &quantidade);
                adicionarProduto(&lista, codigo, descricao, quantidade);
                break;
            case 2: {
                printf("Codigo do produto a remover: "); fgets(codigo, MAX_COD, stdin);
                codigo[strcspn(codigo, "\n")] = 0;
                Produto* removido = removerProduto(&lista, codigo);
                if (removido) free(removido);
                break;
            }
            case 3:
                listarProdutos(lista);
                break;
            case 4:
                ordenarPorDescricao(lista);
                break;
            case 5:
                printf("Descricao a buscar: "); fgets(descricao, MAX_DESC, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                buscaLinear(lista, descricao);
                break;
            case 6:
                printf("Descricao a buscar (binaria): "); fgets(descricao, MAX_DESC, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                buscaBinaria(lista, descricao);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarLista(lista);
}

int main() {
    menu();
    return 0;
}