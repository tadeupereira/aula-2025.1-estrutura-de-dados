#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define TAM_NOME 50
#define TAM_CPF 12

typedef enum {
    BAIXA = 0,
    MEDIA = 1,
    ALTA = 2
} Prioridade;

typedef struct {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    Prioridade prioridade;
} Cliente;

typedef struct {
    Cliente clientes[MAX_CLIENTES];
    int inicio;
    int fim;
    int tamanho;
} FilaEstatica;

FilaEstatica* criarFilaEstatica() {
    FilaEstatica* fila = (FilaEstatica*)malloc(sizeof(FilaEstatica));
    if (fila == NULL) {
        printf("Erro ao alocar memória para a fila estática.\n");
        exit(1);
    }
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    return fila;
}

int filaEstaticaCheia(FilaEstatica* fila) {
    return fila->tamanho == MAX_CLIENTES;
}

int filaEstaticaVazia(FilaEstatica* fila) {
    return fila->tamanho == 0;
}

void adicionarClienteFilaEstatica(FilaEstatica* fila, Cliente cliente) {
    if (filaEstaticaCheia(fila)) {
        printf("A fila está cheia. Não é possível adicionar mais clientes.\n");
        return;
    }
    
    fila->fim = (fila->fim + 1) % MAX_CLIENTES;
    fila->clientes[fila->fim] = cliente;
    fila->tamanho++;
    printf("Cliente %s adicionado com sucesso!\n", cliente.nome);
}

Cliente removerClienteFilaEstatica(FilaEstatica* fila) {
    Cliente clienteRemovido;
    strcpy(clienteRemovido.nome, "");
    
    if (filaEstaticaVazia(fila)) {
        printf("A fila está vazia. Não há clientes para remover.\n");
        return clienteRemovido;
    }
    
    clienteRemovido = fila->clientes[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_CLIENTES;
    fila->tamanho--;
    printf("Cliente %s removido com sucesso!\n", clienteRemovido.nome);
    
    return clienteRemovido;
}

void listarClientesFilaEstatica(FilaEstatica* fila) {
    if (filaEstaticaVazia(fila)) {
        printf("A fila está vazia. Não há clientes para listar.\n");
        return;
    }
    
    printf("\n=== Lista de Clientes ===\n");
    int i, pos;
    for (i = 0; i < fila->tamanho; i++) {
        pos = (fila->inicio + i) % MAX_CLIENTES;
        printf("Cliente %d:\n", i + 1);
        printf("  Nome: %s\n", fila->clientes[pos].nome);
        printf("  CPF: %s\n", fila->clientes[pos].cpf);
        printf("  Prioridade: ");
        switch (fila->clientes[pos].prioridade) {
            case BAIXA: printf("Baixa\n"); break;
            case MEDIA: printf("Média\n"); break;
            case ALTA: printf("Alta\n"); break;
        }
        printf("\n");
    }
}

void liberarFilaEstatica(FilaEstatica* fila) {
    free(fila);
}

Prioridade converterPrioridade(const char* prioridadeStr) {
    if (strcmp(prioridadeStr, "alta") == 0 || strcmp(prioridadeStr, "ALTA") == 0) {
        return ALTA;
    } else if (strcmp(prioridadeStr, "media") == 0 || strcmp(prioridadeStr, "MEDIA") == 0 ||
               strcmp(prioridadeStr, "média") == 0 || strcmp(prioridadeStr, "MÉDIA") == 0) {
        return MEDIA;
    } else {
        return BAIXA;
    }
}

void exibirMenu() {
    printf("\n==== Sistema de Gerenciamento de Atendimento ====\n");
    printf("1. Adicionar cliente\n");
    printf("2. Remover cliente\n");
    printf("3. Listar clientes\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    FilaEstatica* fila = criarFilaEstatica();
    
    int opcao;
    Cliente cliente;
    char prioridadeStr[10];
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Nome do cliente: ");
                fgets(cliente.nome, TAM_NOME, stdin);
                cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
                
                printf("CPF do cliente: ");
                fgets(cliente.cpf, TAM_CPF, stdin);
                cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0';
                
                printf("Prioridade (baixa, media, alta): ");
                fgets(prioridadeStr, 10, stdin);
                prioridadeStr[strcspn(prioridadeStr, "\n")] = '\0';
                cliente.prioridade = converterPrioridade(prioridadeStr);
                
                adicionarClienteFilaEstatica(fila, cliente);
                break;
                
            case 2:  
                removerClienteFilaEstatica(fila);
                break;
                
            case 3: 
                listarClientesFilaEstatica(fila);
                break;
                
            case 0:  
                printf("Encerrando o programa...\n");
                break;
                
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
    
    liberarFilaEstatica(fila);
    
    return 0;
}