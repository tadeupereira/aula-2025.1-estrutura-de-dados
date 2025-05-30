#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { BAIXA = 1, MEDIA, ALTA } Prioridade;

typedef struct Tarefa {
    char titulo[50];
    char descricao[100];
    Prioridade prioridade;
    struct Tarefa* prox;
} Tarefa;

Tarefa* inicio = NULL;

void adicionarTarefa(char* titulo, char* descricao, Prioridade prioridade) {
    Tarefa* nova = (Tarefa*)malloc(sizeof(Tarefa)); 
    strcpy(nova->titulo, titulo); 
    strcpy(nova->descricao, descricao); 
    nova->prioridade = prioridade; 
    nova->prox = inicio; 
    inicio = nova; 
}

void removerTarefa(char* titulo) {
    Tarefa* atual = inicio;
    Tarefa* anterior = NULL;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    if (anterior == NULL) {
        inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual); 
    printf("Tarefa removida com sucesso.\n");
}

void listarTarefas() {
    Tarefa* atual = inicio;
    if (atual == NULL) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }
    while (atual != NULL) {
        printf("Título: %s\nDescrição: %s\nPrioridade: %d\n---\n",
               atual->titulo, atual->descricao, atual->prioridade);
        atual = atual->prox;
    }
}

int prioridadeParaValor(Prioridade p) {
    return (p == ALTA) ? 3 : (p == MEDIA) ? 2 : 1;
}

int contarTarefas() {
    int count = 0;
    Tarefa* atual = inicio;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

void ordenarPorPrioridade() {
    int n = contarTarefas();
    if (n < 2) return;

    for (int i = 0; i < n - 1; i++) {
        Tarefa* atual = inicio;
        Tarefa* proximo = atual->prox;

        while (proximo != NULL) {
            if (prioridadeParaValor(atual->prioridade) < prioridadeParaValor(proximo->prioridade)) {
                char tmpTitulo[50], tmpDesc[100];
                Prioridade tmpPrioridade;

                strcpy(tmpTitulo, atual->titulo);
                strcpy(tmpDesc, atual->descricao);
                tmpPrioridade = atual->prioridade;

                strcpy(atual->titulo, proximo->titulo);
                strcpy(atual->descricao, proximo->descricao);
                atual->prioridade = proximo->prioridade;

                strcpy(proximo->titulo, tmpTitulo);
                strcpy(proximo->descricao, tmpDesc);
                proximo->prioridade = tmpPrioridade;
            }
            atual = proximo;
            proximo = proximo->prox;
        }
    }
}

Tarefa* buscaLinear(char* titulo) {
    Tarefa* atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

Tarefa** listaParaVetor(int* tamanho) {
    *tamanho = contarTarefas();
    Tarefa** vetor = malloc((*tamanho) * sizeof(Tarefa*));
    Tarefa* atual = inicio;
    for (int i = 0; i < *tamanho; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }
    return vetor;
}

Tarefa* buscaBinaria(char* titulo) {
    int tamanho;
    Tarefa** vetor = listaParaVetor(&tamanho);

    int ini = 0, fim = tamanho - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(vetor[meio]->titulo, titulo);
        if (cmp == 0) {
            Tarefa* resultado = vetor[meio];
            free(vetor);
            return resultado;
        } else if (cmp < 0) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    free(vetor);
    return NULL;
}

int main() {
    int opcao;
    char titulo[50], descricao[100];
    int prioridadeInt;

    do {
        printf("\n--- GERENCIADOR DE TAREFAS ---\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Remover tarefa\n");
        printf("3. Listar tarefas\n");
        printf("4. Ordenar por prioridade\n");
        printf("5. Buscar tarefa (linear)\n");
        printf("6. Buscar tarefa (binária)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Título: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Descrição: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Prioridade (1=Baixa, 2=Média, 3=Alta): ");
                scanf("%d", &prioridadeInt);
                getchar();

                adicionarTarefa(titulo, descricao, (Prioridade)prioridadeInt);
                printf("Tarefa adicionada!\n");
                break;

            case 2:
                printf("Título da tarefa a remover: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                removerTarefa(titulo);
                break;

            case 3:
                listarTarefas();
                break;

            case 4:
                ordenarPorPrioridade();
                printf("Tarefas ordenadas por prioridade!\n");
                break;

            case 5:
                printf("Título da tarefa a buscar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                {
                    Tarefa* resultado = buscaLinear(titulo);
                    if (resultado) {
                        printf("Encontrada!\nTítulo: %s\nDescrição: %s\nPrioridade: %d\n",
                            resultado->titulo, resultado->descricao, resultado->prioridade);
                    } else {
                        printf("Tarefa não encontrada.\n");
                    }
                }
                break;

            case 6:
                ordenarPorPrioridade();
                printf("Título da tarefa a buscar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                {
                    Tarefa* resultado = buscaBinaria(titulo);
                    if (resultado) {
                        printf("Encontrada!\nTítulo: %s\nDescrição: %s\nPrioridade: %d\n",
                            resultado->titulo, resultado->descricao, resultado->prioridade);
                    } else {
                        printf("Tarefa não encontrada.\n");
                    }
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
