#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_CPF 15

// Estrutura para representar a prioridade
typedef enum {
    BAIXA = 1,
    MEDIA = 2,
    ALTA = 3
} Prioridade;

// Estrutura para representar um cliente
typedef struct {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    Prioridade prioridade;
} Cliente;

// Estrutura do nó da fila
typedef struct No {
    Cliente cliente;
    struct No* proximo;
} No;

// Estrutura da fila
typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

// Função para criar um novo nó
No* criarNo(Cliente cliente) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return NULL;
    }
    novo->cliente = cliente;
    novo->proximo = NULL;
    return novo;
}

// Função para adicionar cliente na fila
void adicionarCliente(Fila* fila) {
    Cliente novoCliente;
    int prioridade;
    
    printf("\n=== ADICIONAR CLIENTE ===\n");
    printf("Nome: ");
    fgets(novoCliente.nome, MAX_NOME, stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0; // Remove \n
    
    printf("CPF: ");
    fgets(novoCliente.cpf, MAX_CPF, stdin);
    novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = 0; // Remove \n
    
    printf("Prioridade (1-Baixa, 2-Média, 3-Alta): ");
    scanf("%d", &prioridade);
    getchar(); // Limpa buffer
    
    if (prioridade < 1 || prioridade > 3) {
        printf("Prioridade inválida! Definindo como BAIXA.\n");
        prioridade = 1;
    }
    
    novoCliente.prioridade = (Prioridade)prioridade;
    
    No* novo = criarNo(novoCliente);
    if (novo == NULL) return;
    
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
    printf("Cliente adicionado com sucesso!\n");
}

// Função para remover cliente do início da fila
void removerCliente(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia! Nenhum cliente para remover.\n");
        return;
    }
    
    No* temp = fila->inicio;
    printf("\n=== CLIENTE ATENDIDO ===\n");
    printf("Nome: %s\n", temp->cliente.nome);
    printf("CPF: %s\n", temp->cliente.cpf);
    
    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(temp);
    fila->tamanho--;
    printf("Cliente removido da fila!\n");
}

// Função para listar todos os clientes
void listarClientes(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("\nFila vazia!\n");
        return;
    }
    
    printf("\n=== LISTA DE CLIENTES NA FILA ===\n");
    printf("Total de clientes: %d\n\n", fila->tamanho);
    
    No* atual = fila->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("Posição %d:\n", posicao);
        printf("  Nome: %s\n", atual->cliente.nome);
        printf("  CPF: %s\n", atual->cliente.cpf);
        printf("  Prioridade: ");
        switch (atual->cliente.prioridade) {
            case BAIXA: printf("Baixa\n"); break;
            case MEDIA: printf("Média\n"); break;
            case ALTA: printf("Alta\n"); break;
        }
        printf("\n");
        
        atual = atual->proximo;
        posicao++;
    }
}

// Função para remover cliente específico por nome
void removerClientePorNome(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    
    char nome[MAX_NOME];
    printf("\n=== REMOVER CLIENTE ESPECÍFICO ===\n");
    printf("Nome do cliente a remover: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    No* atual = fila->inicio;
    No* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->cliente.nome, nome) == 0) {
            if (anterior == NULL) {
                // Remover primeiro elemento
                fila->inicio = atual->proximo;
                if (fila->inicio == NULL) {
                    fila->fim = NULL;
                }
            } else {
                anterior->proximo = atual->proximo;
                if (atual == fila->fim) {
                    fila->fim = anterior;
                }
            }
            
            printf("Cliente %s removido com sucesso!\n", atual->cliente.nome);
            free(atual);
            fila->tamanho--;
            return;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Cliente não encontrado!\n");
}

// Função auxiliar para trocar dois clientes
void trocarClientes(Cliente* a, Cliente* b) {
    Cliente temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar clientes por prioridade (Bubble Sort)
void ordenarPorPrioridade(Fila* fila) {
    if (fila->tamanho <= 1) {
        printf("Fila com poucos elementos para ordenar.\n");
        return;
    }
    
    No* atual;
    No* proximo;
    int trocou;
    
    do {
        trocou = 0;
        atual = fila->inicio;
        
        while (atual != NULL && atual->proximo != NULL) {
            proximo = atual->proximo;
            
            // Ordena por prioridade (ALTA primeiro)
            if (atual->cliente.prioridade < proximo->cliente.prioridade) {
                trocarClientes(&atual->cliente, &proximo->cliente);
                trocou = 1;
            }
            
            atual = atual->proximo;
        }
    } while (trocou);
    
    printf("Fila ordenada por prioridade (Alta -> Média -> Baixa)!\n");
}

// Função para busca linear por nome
void buscaLinear(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    
    char nome[MAX_NOME];
    printf("\n=== BUSCA LINEAR ===\n");
    printf("Nome do cliente: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    No* atual = fila->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        if (strcmp(atual->cliente.nome, nome) == 0) {
            printf("Cliente encontrado na posição %d:\n", posicao);
            printf("  Nome: %s\n", atual->cliente.nome);
            printf("  CPF: %s\n", atual->cliente.cpf);
            printf("  Prioridade: ");
            switch (atual->cliente.prioridade) {
                case BAIXA: printf("Baixa\n"); break;
                case MEDIA: printf("Média\n"); break;
                case ALTA: printf("Alta\n"); break;
            }
            return;
        }
        
        atual = atual->proximo;
        posicao++;
    }
    
    printf("Cliente não encontrado!\n");
}

// Função auxiliar para converter fila em array (para busca binária)
Cliente* filaParaArray(Fila* fila) {
    if (fila->tamanho == 0) return NULL;
    
    Cliente* array = (Cliente*)malloc(fila->tamanho * sizeof(Cliente));
    if (array == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return NULL;
    }
    
    No* atual = fila->inicio;
    int i = 0;
    
    while (atual != NULL) {
        array[i] = atual->cliente;
        atual = atual->proximo;
        i++;
    }
    
    // Ordenar array por nome para busca binária
    for (i = 0; i < fila->tamanho - 1; i++) {
        for (int j = 0; j < fila->tamanho - i - 1; j++) {
            if (strcmp(array[j].nome, array[j + 1].nome) > 0) {
                trocarClientes(&array[j], &array[j + 1]);
            }
        }
    }
    
    return array;
}

// Função para busca binária por nome
void buscaBinaria(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    
    char nome[MAX_NOME];
    printf("\n=== BUSCA BINÁRIA ===\n");
    printf("Nome do cliente: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    Cliente* array = filaParaArray(fila);
    if (array == NULL) return;
    
    int esquerda = 0;
    int direita = fila->tamanho - 1;
    int encontrado = 0;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int comparacao = strcmp(array[meio].nome, nome);
        
        if (comparacao == 0) {
            printf("Cliente encontrado:\n");
            printf("  Nome: %s\n", array[meio].nome);
            printf("  CPF: %s\n", array[meio].cpf);
            printf("  Prioridade: ");
            switch (array[meio].prioridade) {
                case BAIXA: printf("Baixa\n"); break;
                case MEDIA: printf("Média\n"); break;
                case ALTA: printf("Alta\n"); break;
            }
            encontrado = 1;
            break;
        }
        
        if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("Cliente não encontrado!\n");
    }
    
    free(array);
}

// Função para liberar memória da fila
void liberarFila(Fila* fila) {
    No* atual = fila->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

// Função para exibir o menu
void exibirMenu() {
    printf("\n=== SISTEMA DE GERENCIAMENTO DE ATENDIMENTO ===\n");
    printf("1. Adicionar cliente na fila\n");
    printf("2. Atender próximo cliente (remover)\n");
    printf("3. Listar todos os clientes\n");
    printf("4. Remover cliente específico\n");
    printf("5. Ordenar por prioridade\n");
    printf("6. Busca linear por nome\n");
    printf("7. Busca binária por nome\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    
    int opcao;
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpa buffer
        
        switch (opcao) {
            case 1:
                adicionarCliente(&fila);
                break;
            case 2:
                removerCliente(&fila);
                break;
            case 3:
                listarClientes(&fila);
                break;
            case 4:
                removerClientePorNome(&fila);
                break;
            case 5:
                ordenarPorPrioridade(&fila);
                break;
            case 6:
                buscaLinear(&fila);
                break;
            case 7:
                buscaBinaria(&fila);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while (opcao != 0);
    
    liberarFila(&fila);
    return 0;
}