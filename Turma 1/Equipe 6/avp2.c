#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_NOME 100
#define TAM_CPF 15

typedef struct Cliente {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    int prioridade;
    struct Cliente *proximo;
} Cliente;

typedef struct {
    Cliente *inicio;
    Cliente *fim;
} FilaDeClientes;

int validarNome(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isdigit(nome[i])) {
            return 0;
        }
    }
    return 1;
}

int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    return 1;
}

FilaDeClientes *criarFilaDeClientes() {
    FilaDeClientes *fila = (FilaDeClientes *)malloc(sizeof(FilaDeClientes));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void liberarFilaDeClientes(FilaDeClientes *fila) {
    Cliente *atual = fila->inicio;
    while (atual != NULL) {
        Cliente *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(fila);
}

void inserirClienteNaFila(FilaDeClientes *fila, const char *nome, const char *cpf, int prioridade) {
    Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
    strcpy(novoCliente->nome, nome);
    strcpy(novoCliente->cpf, cpf);
    novoCliente->prioridade = prioridade;
    novoCliente->proximo = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novoCliente;
    } else {
        fila->fim->proximo = novoCliente;
    }
    fila->fim = novoCliente;
}

void removerClienteDaFila(FilaDeClientes *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    Cliente *removido = fila->inicio;
    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    printf("Cliente removido: %s\n", removido->nome);
    free(removido);
}

void exibirClientesDaFila(FilaDeClientes *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    Cliente *atual = fila->inicio;
    while (atual != NULL) {
        printf("Nome: %s | CPF: %s | Prioridade: ", atual->nome, atual->cpf);
        switch (atual->prioridade) {
            case 1: printf("Alta\n"); break;
            case 2: printf("Media\n"); break;
            case 3: printf("Baixa\n"); break;
            default: printf("Desconhecida\n");
        }
        atual = atual->proximo;
    }
}

void ordenarFilaPorPrioridade(FilaDeClientes *fila) {
    if (fila->inicio == NULL) return;

    Cliente *i, *j;
    for (i = fila->inicio; i != NULL; i = i->proximo) {
        for (j = i->proximo; j != NULL; j = j->proximo) {
            if (i->prioridade > j->prioridade) {

                char nomeTemp[TAM_NOME];
                char cpfTemp[TAM_CPF];
                int prioridadeTemp;

                strcpy(nomeTemp, i->nome);
                strcpy(cpfTemp, i->cpf);
                prioridadeTemp = i->prioridade;

                strcpy(i->nome, j->nome);
                strcpy(i->cpf, j->cpf);
                i->prioridade = j->prioridade;

                strcpy(j->nome, nomeTemp);
                strcpy(j->cpf, cpfTemp);
                j->prioridade = prioridadeTemp;
            }
        }
    }
}

Cliente *buscarClientePorNomeLinear(FilaDeClientes *fila, const char *nome) {
    Cliente *atual = fila->inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

Cliente *buscarClientePorNomeBinaria(FilaDeClientes *fila, const char *nome) {
    int tamanho = 0;
    Cliente *atual = fila->inicio;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }

    if (tamanho == 0) return NULL;

    Cliente **vetor = (Cliente **)malloc(tamanho * sizeof(Cliente *));
    atual = fila->inicio;
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = atual;
        atual = atual->proximo;
    }

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (strcmp(vetor[i]->nome, vetor[j]->nome) > 0) {
                Cliente *temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }

    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, vetor[meio]->nome);
        if (cmp == 0) {
            Cliente *resultado = vetor[meio];
            free(vetor);
            return resultado;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    free(vetor);
    return NULL;
}

void exibirMenu() {
    printf("\n========= GERENCIADOR DE ATENDIMENTO =========\n");
    printf("1 - Adicionar Cliente\n");
    printf("2 - Remover Cliente\n");
    printf("3 - Listar Clientes\n");
    printf("4 - Ordenar por Prioridade\n");
    printf("5 - Busca Linear por Nome\n");
    printf("6 - Busca Binaria por Nome\n");
    printf("0 - Sair\n");
    printf("===============================================\n");
    printf("Escolha: ");
}

int main() {
    FilaDeClientes *fila = criarFilaDeClientes();
    int opcao;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    int prioridade;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                do {
                    printf("Nome: ");
                    fgets(nome, TAM_NOME, stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    if (!validarNome(nome)) {
                        printf("Nome invalido! Nao deve conter numeros.\n");
                    }
                } while (!validarNome(nome));

                do {
                    printf("CPF (11 numeros): ");
                    fgets(cpf, TAM_CPF, stdin);
                    cpf[strcspn(cpf, "\n")] = 0;

                    if (!validarCPF(cpf)) {
                        printf("CPF invalido! Deve conter exatamente 11 numeros.\n");
                    }
                } while (!validarCPF(cpf));

                do {
                    printf("Prioridade (1-Alta, 2-Media, 3-Baixa): ");
                    scanf("%d", &prioridade);
                    getchar();

                    if (prioridade < 1 || prioridade > 3) {
                        printf("Prioridade invalida! Use 1, 2 ou 3.\n");
                    }
                } while (prioridade < 1 || prioridade > 3);

                inserirClienteNaFila(fila, nome, cpf, prioridade);
                printf("Cliente adicionado com sucesso.\n");
                break;

            case 2:
                removerClienteDaFila(fila);
                break;

            case 3:
                exibirClientesDaFila(fila);
                break;

            case 4:
                ordenarFilaPorPrioridade(fila);
                printf("Clientes ordenados por prioridade.\n");
                break;

            case 5:
                printf("Nome para buscar (Linear): ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;

                Cliente *clienteEncontradoLinear = buscarClientePorNomeLinear(fila, nome);
                if (clienteEncontradoLinear) {
                    printf("Encontrado: %s | CPF: %s | Prioridade: %d\n",
                           clienteEncontradoLinear->nome,
                           clienteEncontradoLinear->cpf,
                           clienteEncontradoLinear->prioridade);
                } else {
                    printf("Cliente nao encontrado.\n");
                }
                break;

            case 6:
                printf("Nome para buscar (Binaria): ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;

                Cliente *clienteEncontradoBinaria = buscarClientePorNomeBinaria(fila, nome);
                if (clienteEncontradoBinaria) {
                    printf("Encontrado: %s | CPF: %s | Prioridade: %d\n",
                           clienteEncontradoBinaria->nome,
                           clienteEncontradoBinaria->cpf,
                           clienteEncontradoBinaria->prioridade);
                } else {
                    printf("Cliente nao encontrado.\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberarFilaDeClientes(fila);
    return 0;
}