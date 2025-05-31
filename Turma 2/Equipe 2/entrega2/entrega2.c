#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

struct cliente {
    char nome[20];
    char cpf[12];
    char prioridade[10];
    struct cliente* proximo;
};


struct fila {
    struct cliente* inicio;
    struct cliente* fim;
    int tamanho;
};


void inicializarFila(struct fila* f);
void VerClientes(struct fila* f);
void ClientesDefinidos(struct fila* f);
void ClientesIndefinidos(struct fila* f);
void AdicionarClientes(struct fila* f);
void RemoverClientes(struct fila* f);
void OrdenarPorPrioridade(struct fila* f);
void BuscaLinear(struct fila* f);
void BuscaBinaria(struct fila* f);
void liberarFila(struct fila* f);
int obterPrioridadeNumerica(const char* prioridade);
void ordenarArray(struct cliente** array, int tamanho);
int compararNomes(const void* a, const void* b);

int main() {
    struct fila filaAtendimento;
    inicializarFila(&filaAtendimento);
    
    unsigned short int escolha;
    while(true) {
        puts("\n\033[1;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[m");
        puts("\033[1;34m     GERENCIADOR DE ATENDIMENTOS\033[m");
        puts("\033[1;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[m");
        puts("\033[1m\tSELECIONE UMA OPÇÃO\033[m");
        puts("-----------------------------------");
        puts("\033[32m[1] Ver Clientes");
        puts("[2] Adicionar Clientes");
        puts("[3] Remover Clientes");
        puts("[4] Ordenar por Prioridade");
        puts("[5] Busca Linear por Nome");
        puts("[6] Busca Binária por Nome\033[m");
        puts("\033[31m[0] Sair\033[m");
        puts("-----------------------------------");
        printf("\033[1m>\033[m ");
        scanf("%hu", &escolha);
        
        switch (escolha) {
            case 1:
                VerClientes(&filaAtendimento);
                break;
            case 2:
                AdicionarClientes(&filaAtendimento);
                break;
            case 3:
                RemoverClientes(&filaAtendimento);
                break;
            case 4:
                OrdenarPorPrioridade(&filaAtendimento);
                break;
            case 5:
                BuscaLinear(&filaAtendimento);
                break;
            case 6:
                BuscaBinaria(&filaAtendimento);
                break;
            case 0:
                puts("Programa encerrado.");
                liberarFila(&filaAtendimento);
                return 0;
            default:
                puts("Opção inválida, tente novamente:\n");
                break;
        }
    }
}

void inicializarFila(struct fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

void VerClientes(struct fila* f) {
    if (f->tamanho == 0) {
        puts("\n\033[1;31mNenhum cliente na fila!\033[m");
        return;
    }
    
    struct cliente* atual = f->inicio;
    int id = 1;
    
    while (atual != NULL) {
        puts("----------------------------");
        printf("\033[1;35mID:\033[m %d\n", id);
        printf("\033[1;35mNome:\033[m %s\n", atual->nome);
        printf("\033[1;35mCPF:\033[m %s\n", atual->cpf);
        printf("\033[1;35mPrioridade:\033[m %s\n", atual->prioridade);
        puts("----------------------------");
        atual = atual->proximo;
        id++;
    }
}

void AdicionarClientes(struct fila* f) {
    unsigned short int escolha;
    while(true) {
        puts("-------------------------------------------");
        puts("\033[32m[1] Adicionar número definido de clientes");
        puts("[2] Adicionar número indefinido de clientes\033[m");
        puts("\033[33m[0] Menu\033[m");
        puts("-------------------------------------------");
        printf("\033[1m> \033[m");
        scanf("%hu", &escolha);
        
        switch (escolha) {
            case 1:
                ClientesDefinidos(f);
                break;
            case 2:
                ClientesIndefinidos(f);
                break;
            case 0:
                return;
            default:
                puts("\033[1;31mOpção inválida! tente novamente:\033[m");
                break;
        }
    }
}

void ClientesDefinidos(struct fila* f) {
    char nome[20];
    char cpf[12];
    unsigned numero;
    char prioridade[10];
    
    printf("\033[1;36mSelecione o número de clientes a serem adicionados: \033[m");
    scanf("%u", &numero);
    
    for(int i = 1; i <= numero; i++) {
        printf("Nome do cliente %d: ", i);
        scanf("%s", nome);
        
        while(true) {
            printf("CPF do cliente %d: ", i);
            scanf("%s", cpf);
            if(strlen(cpf) == 11) {
                break;
            } else {
                puts("CPF inválido, tente novamente");
            }
        }
        
        while(true) {
            printf("Prioridade do cliente %d (\033[31malta\033[m/\033[33mmedia\033[m/\033[32mbaixa\033[m): ", i);
            scanf("%s", prioridade);
            if(strcasecmp(prioridade, "alta") == 0 || 
               strcasecmp(prioridade, "media") == 0 || 
               strcasecmp(prioridade, "baixa") == 0) {
                break;
            } else {
                puts("Prioridade inválida! Use: alta, media ou baixa");
            }
        }
        
        
        struct cliente* novoCliente = (struct cliente*)malloc(sizeof(struct cliente));
        strcpy(novoCliente->nome, nome);
        strcpy(novoCliente->cpf, cpf);
        strcpy(novoCliente->prioridade, prioridade);
        novoCliente->proximo = NULL;
        
        if (f->fim == NULL) {
            f->inicio = f->fim = novoCliente;
        } else {
            f->fim->proximo = novoCliente;
            f->fim = novoCliente;
        }
        f->tamanho++;
    }
    puts("\n\033[36mTodos os clientes foram adicionados!\033[m\n");
}

void ClientesIndefinidos(struct fila* f) {
    char nome[20];
    char cpf[12];
    unsigned numero = 1;
    char prioridade[10];
    char sair[4];
    
    while(true) {
        printf("Nome do cliente %u: ", numero);
        scanf("%s", nome);
        
        while(true) {
            printf("CPF do cliente %u: ", numero);
            scanf("%s", cpf);
            if(strlen(cpf) == 11) {
                break;
            } else {
                puts("CPF inválido, tente novamente");
            }
        }
        
        while(true) {
            printf("Prioridade do cliente %u (\033[31malta\033[m/\033[33mmedia\033[m/\033[32mbaixa\033[m): ", numero);
            scanf("%s", prioridade);
            if(strcasecmp(prioridade, "alta") == 0 || 
               strcasecmp(prioridade, "media") == 0 || 
               strcasecmp(prioridade, "baixa") == 0) {
                break;
            } else {
                puts("Prioridade inválida! Use: alta, media ou baixa");
            }
        }
        
        struct cliente* novoCliente = (struct cliente*)malloc(sizeof(struct cliente));
        strcpy(novoCliente->nome, nome);
        strcpy(novoCliente->cpf, cpf);
        strcpy(novoCliente->prioridade, prioridade);
        novoCliente->proximo = NULL;
        
        if (f->fim == NULL) {
            f->inicio = f->fim = novoCliente;
        } else {
            f->fim->proximo = novoCliente;
            f->fim = novoCliente;
        }
        f->tamanho++;
        numero++;
        
        printf("Deseja sair? [sim/nao]: ");
        scanf("%s", sair);
        if(strcasecmp(sair, "sim") == 0) {
            return;
        }
    }
}

void RemoverClientes(struct fila* f) {
    if (f->tamanho == 0) {
        puts("\n\033[1;31mNenhum cliente na fila!\033[m");
        return;
    }
    
    VerClientes(f);
    
    int id;
    printf("\033[1;31mID do cliente a ser removido: \033[m");
    scanf("%d", &id);
    
    if (id < 1 || id > f->tamanho) {
        printf("\n\033[1;31mID inválido!\033[m");
        return;
    }
    
    struct cliente* atual = f->inicio;
    struct cliente* anterior = NULL;
    
    if (id == 1) {
        f->inicio = atual->proximo;
        if (f->inicio == NULL) {
            f->fim = NULL;
        }
        free(atual);
    } else {
        for (int i = 1; i < id; i++) {
            anterior = atual;
            atual = atual->proximo;
        }
        
        anterior->proximo = atual->proximo;
        if (atual == f->fim) {
            f->fim = anterior;
        }
        free(atual);
    }
    
    f->tamanho--;
    puts("\n\033[32mCliente removido com sucesso!\033[m");
}

int obterPrioridadeNumerica(const char* prioridade) {
    if (strcasecmp(prioridade, "alta") == 0) return 3;
    if (strcasecmp(prioridade, "media") == 0) return 2;
    if (strcasecmp(prioridade, "baixa") == 0) return 1;
    return 0;
}

void OrdenarPorPrioridade(struct fila* f) {
    if (f->tamanho <= 1) {
        puts("\n\033[1;33mNão há clientes suficientes para ordenar!\033[m");
        return;
    }
    
    struct cliente** array = (struct cliente**)malloc(f->tamanho * sizeof(struct cliente*));
    struct cliente* atual = f->inicio;
    
    for (int i = 0; i < f->tamanho; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }
    
    for (int i = 0; i < f->tamanho - 1; i++) {
        for (int j = 0; j < f->tamanho - 1 - i; j++) {
            if (obterPrioridadeNumerica(array[j]->prioridade) < 
                obterPrioridadeNumerica(array[j + 1]->prioridade)) {
                struct cliente* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    
    f->inicio = array[0];
    for (int i = 0; i < f->tamanho - 1; i++) {
        array[i]->proximo = array[i + 1];
    }
    array[f->tamanho - 1]->proximo = NULL;
    f->fim = array[f->tamanho - 1];
    
    free(array);
    puts("\n\033[32mClientes ordenados por prioridade!\033[m");
}

void BuscaLinear(struct fila* f) {
    if (f->tamanho == 0) {
        puts("\n\033[1;31mNenhum cliente na fila!\033[m");
        return;
    }
    
    char nomeBusca[20];
    printf("Digite o nome do cliente para buscar: ");
    scanf("%s", nomeBusca);
    
    struct cliente* atual = f->inicio;
    int posicao = 1;
    bool encontrado = false;
    
    while (atual != NULL) {
        if (strcasecmp(atual->nome, nomeBusca) == 0) {
            puts("----------------------------");
            printf("\033[1;32mCliente encontrado!\033[m\n");
            printf("\033[1;35mPosição:\033[m %d\n", posicao);
            printf("\033[1;35mNome:\033[m %s\n", atual->nome);
            printf("\033[1;35mCPF:\033[m %s\n", atual->cpf);
            printf("\033[1;35mPrioridade:\033[m %s\n", atual->prioridade);
            puts("----------------------------");
            encontrado = true;
            break;
        }
        atual = atual->proximo;
        posicao++;
    }
    
    if (!encontrado) {
        puts("\n\033[1;31mCliente não encontrado!\033[m");
    }
}

int compararNomes(const void* a, const void* b) {
    struct cliente* clienteA = *(struct cliente**)a;
    struct cliente* clienteB = *(struct cliente**)b;
    return strcasecmp(clienteA->nome, clienteB->nome);
}

void BuscaBinaria(struct fila* f) {
    if (f->tamanho == 0) {
        puts("\n\033[1;31mNenhum cliente na fila!\033[m");
        return;
    }
    
    char nomeBusca[20];
    printf("Digite o nome do cliente para buscar: ");
    scanf("%s", nomeBusca);
    
    struct cliente** array = (struct cliente**)malloc(f->tamanho * sizeof(struct cliente*));
    struct cliente* atual = f->inicio;
    
    for (int i = 0; i < f->tamanho; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }
    
    qsort(array, f->tamanho, sizeof(struct cliente*), compararNomes);
    
    int esquerda = 0, direita = f->tamanho - 1;
    bool encontrado = false;
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int comparacao = strcasecmp(array[meio]->nome, nomeBusca);
        
        if (comparacao == 0) {
            puts("----------------------------");
            printf("\033[1;32mCliente encontrado!\033[m\n");
            printf("\033[1;35mNome:\033[m %s\n", array[meio]->nome);
            printf("\033[1;35mCPF:\033[m %s\n", array[meio]->cpf);
            printf("\033[1;35mPrioridade:\033[m %s\n", array[meio]->prioridade);
            puts("----------------------------");
            encontrado = true;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        puts("\n\033[1;31mCliente não encontrado!\033[m");
    }
    
    free(array);
}

void liberarFila(struct fila* f) {
    struct cliente* atual = f->inicio;
    while (atual != NULL) {
        struct cliente* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
}
