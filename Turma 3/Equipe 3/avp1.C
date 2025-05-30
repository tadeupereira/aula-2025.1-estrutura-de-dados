#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    char codigo[20];
    char descricao[50];
    int quantidade;
} Produto;


typedef struct {
    Produto produtos[MAX];
    int frente, tras;
} Fila;

void inicializarFila(Fila* fila) {
    fila->frente = -1;
    fila->tras = -1;
}

int filaVazia(Fila* fila) {
    return (fila->frente == -1);
}

int filaCheia(Fila* fila) {
    return (fila->tras == MAX - 1);
}

void adicionarProduto(Fila* fila) {
    if (filaCheia(fila)) {
        printf("A fila de estoque esta cheia.\n");
        return;
    }

    Produto p;
    printf("Digite o codigo do produto: ");
    scanf("%s", p.codigo);
    getchar();
    printf("Digite a descricao do produto: ");
    fgets(p.descricao, sizeof(p.descricao), stdin);
    p.descricao[strcspn(p.descricao, "\n")] = 0;
    printf("Digite a quantidade do produto: ");
    scanf("%d", &p.quantidade);

    if (filaVazia(fila)) {
        fila->frente = 0;
    }
    fila->tras++;
    fila->produtos[fila->tras] = p;
    printf("Produto adicionado com sucesso.\n");
}

void removerProduto(Fila* fila) {
    if (filaVazia(fila)) {
        printf("A fila de estoque esta vazia.\n");
        return;
    }

    printf("Produto removido: %s - %s\n", 
        fila->produtos[fila->frente].codigo, 
        fila->produtos[fila->frente].descricao);
    fila->frente++;

    if (fila->frente > fila->tras) {
        inicializarFila(fila);
    }
}

void listarProdutos(Fila* fila) {
    if (filaVazia(fila)) {
        printf("A fila de estoque esta vazia.\n");
        return;
    }

    printf("Lista de Produtos em Estoque:\n");
    for (int i = fila->frente; i <= fila->tras; i++) {
        printf("Codigo: %s\n", fila->produtos[i].codigo);
        printf("Descricao: %s\n", fila->produtos[i].descricao);
        printf("Quantidade: %d\n\n", fila->produtos[i].quantidade);
    }
    int main() {
        Fila estoque;
        inicializarFila(&estoque);
    
        int opcao;
        do {
            printf("\nGerenciador de Estoque\n");
            printf("1. Adicionar Produto\n");
            printf("2. Remover Produto\n");
            printf("3. Listar Produtos\n");
            printf("4. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
    
            switch (opcao) {
                case 1:
                    adicionarProduto(&estoque);
                    break;
                case 2:
                    removerProduto(&estoque);
                    break;
                case 3:
                    listarProdutos(&estoque);
                    break;
                case 4:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }
        } while (opcao != 4);
    
}