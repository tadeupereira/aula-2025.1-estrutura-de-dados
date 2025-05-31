#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    char codigo[9];
    char descricao[100];
    int quantidade;
    struct Produto* proximo;
} Produto;

typedef struct {
    Produto* inicio;
} ListaProdutos;

ListaProdutos* CriarLista() {
    ListaProdutos* lista = (ListaProdutos*) malloc(sizeof(ListaProdutos));
    if (!lista) {
        printf("Erro ao alocar memória para a lista!\n");
        exit(1);
    }
    lista->inicio = NULL;
    return lista;
}

void LiberarLista(ListaProdutos* lista) {
    Produto* atual = lista->inicio;
    while (atual != NULL) {
        Produto* produtoParaLiberar = atual;
        atual = atual->proximo;
        free(produtoParaLiberar);
    }
    free(lista);
}

void CadastrarProduto(ListaProdutos* lista, Produto item) {
    Produto* novo = (Produto*) malloc(sizeof(Produto));
    if (!novo) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    strcpy(novo->codigo, item.codigo);
    strcpy(novo->descricao, item.descricao);
    novo->quantidade = item.quantidade;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    printf("Produto cadastrado com sucesso!\n");
}

Produto RemoverProduto(ListaProdutos* lista, char codigo[]) {
    Produto removido;
    removido.codigo[0] = '\0';
    Produto* atual = lista->inicio;
    Produto* produtoAnterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        produtoAnterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto com código %s não encontrado!\n", codigo);
        return removido;
    }

    strcpy(removido.codigo, atual->codigo);
    strcpy(removido.descricao, atual->descricao);
    removido.quantidade = atual->quantidade;

    if (produtoAnterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        produtoAnterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Produto com código %s removido com sucesso!\n", removido.codigo);
    return removido;
}

void ExibirProdutos(ListaProdutos* lista) {
    if (lista->inicio == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    Produto* atual = lista->inicio;
    while (atual != NULL) {
        printf("\n"); 
        printf("Código: %s\n", atual->codigo);
        printf("Descrição: %s\n", atual->descricao);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("\n"); 
        atual = atual->proximo;
    }
}

void OrdenarProdutos(ListaProdutos* lista) {
    if (!lista->inicio || !lista->inicio->proximo) return;
    int trocou;
    Produto *atual, *limite = NULL;

    do {
        trocou = 0;
        atual = lista->inicio;
        while (atual->proximo != limite) {
            if (strcmp(atual->descricao, atual->proximo->descricao) > 0) {
                Produto temp = *atual;
                strcpy(atual->codigo, atual->proximo->codigo);
                strcpy(atual->descricao, atual->proximo->descricao);
                atual->quantidade = atual->proximo->quantidade;
                strcpy(atual->proximo->codigo, temp.codigo);
                strcpy(atual->proximo->descricao, temp.descricao);
                atual->proximo->quantidade = temp.quantidade;
                trocou = 1;
            }
            atual = atual->proximo;
        }
        limite = atual;
    } while (trocou);
    printf("Produtos ordenados por descrição com sucesso!\n");
}

Produto* BuscaLinear(ListaProdutos* lista, char descricao[]) {
    Produto* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->descricao, descricao) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int ListaParaVetor(ListaProdutos* lista, Produto** vetor) {
    int quantidadeProdutos = 0;
    Produto* atual = lista->inicio;
    while (atual != NULL) {
        quantidadeProdutos++;
        atual = atual->proximo;
    }
    *vetor = (Produto*) malloc(quantidadeProdutos * sizeof(Produto));
    atual = lista->inicio;
    for (int i = 0; i < quantidadeProdutos; i++) {
        (*vetor)[i] = *atual;
        atual = atual->proximo;
    }
    return quantidadeProdutos;
}

Produto BuscaBinaria(ListaProdutos* lista, char descricao[]) {
    Produto resultado;
    resultado.codigo[0] = '\0';  
    Produto* vetorProdutos;
    int tamanho = ListaParaVetor(lista, &vetorProdutos);

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (strcmp(vetorProdutos[i].descricao, vetorProdutos[j].descricao) > 0) {
                Produto temp = vetorProdutos[i];
                vetorProdutos[i] = vetorProdutos[j];
                vetorProdutos[j] = temp;
            }
        }
    }

    int esq = 0, dir = tamanho - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int comparacao = strcmp(vetorProdutos[meio].descricao, descricao);
        if (comparacao == 0) {
            resultado = vetorProdutos[meio];
            break;
        } else if (comparacao < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    free(vetorProdutos);
    return resultado;
}

int main() {
    ListaProdutos* listaProdutos = CriarLista();
    int opcao;
    do {
        printf("\nSistema de Gerenciamento de Estoque\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Exibir Produtos\n");
        printf("4. Ordenar Produtos por Descrição\n");
        printf("5. Busca Linear por Descrição\n");
        printf("6. Busca Binária por Descrição\n");
        printf("7. Sair\n");
        printf("Por gentileza, escolha a opção que você deseja realizar: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Produto novo;
                printf("\nIniciando o cadastro do produto\n");
                while (1) {
                    printf("Insira o código do produto (máximo 8 dígitos): ");
                    scanf("%s", novo.codigo);
                    if (strlen(novo.codigo) > 8) {
                        printf("O código do produto deve ter no máximo 8 dígitos!\n");
                        continue;
                    }
                    break;
                }
                printf("Insira a descrição do produto: ");
                scanf(" %[^\n]", novo.descricao);
                
                while (1) {
                    printf("Insira a quantidade do produto: ");
                    if (scanf("%d", &novo.quantidade) != 1) {
                        printf("Quantidade inválida! Por favor, digite apenas números inteiros positivos:\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (novo.quantidade < 0) {
                        printf("A quantidade não pode ser negativa! Digite apenas números inteiros positivos:\n");
                        continue;
                    }
                    break;
                }
                CadastrarProduto(listaProdutos, novo);
                break;
            }
            case 2: {
                char codigo[9];
                printf("Insira o código do produto que deseja remover: ");
                scanf("%s", codigo);
                RemoverProduto(listaProdutos, codigo);
                break;
            }
            case 3:
                ExibirProdutos(listaProdutos);
                break;
            case 4:
                OrdenarProdutos(listaProdutos);
                break;
            case 5: {
                char descricao[100];
                printf("Digite a descrição do produto: ");
                scanf(" %[^\n]", descricao);
                Produto* produto = BuscaLinear(listaProdutos, descricao);
                if (produto) {
                    printf("Produto encontrado: %s - %s - %d\n", produto->codigo, produto->descricao, produto->quantidade);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 6: {
                char descricao[100];
                printf("Digite a descrição do produto: ");
                scanf(" %[^\n]", descricao);
                Produto produto = BuscaBinaria(listaProdutos, descricao);
                if (produto.codigo[0] != '\0') {
                    printf("Produto encontrado: %s - %s - %d\n", produto.codigo, produto.descricao, produto.quantidade);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 7:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);
    LiberarLista(listaProdutos);
    return 0;
}