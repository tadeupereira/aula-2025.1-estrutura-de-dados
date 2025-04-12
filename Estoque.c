#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC 100
#define MAX_COD 20

typedef struct Produto {
    char codigo[MAX_COD];
    char descricao[MAX_DESC];
    int quantidade;
    struct Produto* prox;
} Produto;

Produto* lista = NULL;

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

int produto_ja_existente(char* codigo){
    Produto* atual = lista;
    while(atual){
        if(strcmp(atual->codigo, codigo) == 0){
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void adicionarProduto(char* codigo, char* descricao, int quantidade) {
    if(produto_ja_existente(codigo)){
        printf("Já existe um produto com esse código\n");
        return;
    }

    Produto* novo = criarProduto(codigo, descricao, quantidade);
    novo->prox = lista;
    lista = novo;
    printf("Produto adicionado com sucesso!\n");
}

void removerProduto(char* codigo) {
    Produto *atual = lista, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->codigo, codigo) == 0) {
            if (anterior) anterior->prox = atual->prox;
            else lista = atual->prox;
            free(atual);
            printf("Produto removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Produto nao encontrado.\n");
}

void listarProdutos() {
    Produto* atual = lista;
    printf("\n--- Produtos em Estoque ---\n");
    while (atual) {
        printf("Codigo: %s | Descricao: %s | Quantidade: %d\n",
               atual->codigo, atual->descricao, atual->quantidade);
        atual = atual->prox;
    }
}

void menu() {
    int opcao;
    char buffer[10];
    char codigo[MAX_COD], descricao[MAX_DESC];
    int quantidade;

    do {
        printf("\n--- MENU ESTOQUE ---\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Listar produtos\n");
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
                adicionarProduto(codigo, descricao, quantidade);
                break;
            case 2:
                printf("Codigo do produto a remover: "); fgets(codigo, MAX_COD, stdin);
                codigo[strcspn(codigo, "\n")] = 0;
                removerProduto(codigo);
                break;
            case 3:
                listarProdutos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}

int main() {
    printf("Entrou no main\n");
    menu();
    return 0;
}


