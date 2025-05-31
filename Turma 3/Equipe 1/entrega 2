#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    char titulo[50];
    char descricao[200];
    char prioridade[10];
    struct Tarefa* prox;
} Tarefa;

Tarefa* inicializar() {
    return NULL;
}

void liberar(Tarefa** inicio) {
    Tarefa* atual = *inicio;
    while (atual) {
        Tarefa* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *inicio = NULL;
}

int prioridadeParaInt(const char* prioridade) {
    if (strcmp(prioridade, "alta") == 0) return 1;
    if (strcmp(prioridade, "média") == 0) return 2;
    return 3;
}

void adicionarTarefa(Tarefa** inicio) {
    Tarefa* nova = malloc(sizeof(Tarefa));
    if (!nova) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    printf("\nTítulo: ");
    fgets(nova->titulo, sizeof(nova->titulo), stdin);
    strtok(nova->titulo, "\n");

    printf("Descrição: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    strtok(nova->descricao, "\n");

    printf("Prioridade (baixa, média, alta): ");
    fgets(nova->prioridade, sizeof(nova->prioridade), stdin);
    strtok(nova->prioridade, "\n");

    nova->prox = *inicio;
    *inicio = nova;

    printf("Tarefa adicionada com sucesso!\n");
}

void listarTarefas(Tarefa* inicio) {
    if (inicio == NULL) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\nLista de Tarefas:\n");
    Tarefa* atual = inicio;
    while (atual) {
        printf("Título: %s\n", atual->titulo);
        printf("Descrição: %s\n", atual->descricao);
        printf("Prioridade: %s\n\n", atual->prioridade);
        atual = atual->prox;
    }
}

void removerPorTitulo(Tarefa** inicio) {
    if (*inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    char titulo[50];
    printf("Digite o título da tarefa a remover: ");
    fgets(titulo, sizeof(titulo), stdin);
    strtok(titulo, "\n");

    Tarefa *atual = *inicio, *anterior = NULL;

    while (atual) {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior == NULL) {
                *inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Tarefa removida com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Tarefa não encontrada.\n");
}

void ordenarPorPrioridade(Tarefa* inicio) {
    if (!inicio) return;

    int trocado;
    Tarefa *atual;
    Tarefa *fim = NULL;

    do {
        trocado = 0;
        atual = inicio;

        while (atual->prox != fim) {
            int prioAtual = prioridadeParaInt(atual->prioridade);
            int prioProx = prioridadeParaInt(atual->prox->prioridade);

            if (prioAtual > prioProx) {
                char tempTitulo[50], tempDescricao[200], tempPrioridade[10];
                strcpy(tempTitulo, atual->titulo);
                strcpy(tempDescricao, atual->descricao);
                strcpy(tempPrioridade, atual->prioridade);

                strcpy(atual->titulo, atual->prox->titulo);
                strcpy(atual->descricao, atual->prox->descricao);
                strcpy(atual->prioridade, atual->prox->prioridade);

                strcpy(atual->prox->titulo, tempTitulo);
                strcpy(atual->prox->descricao, tempDescricao);
                strcpy(atual->prox->prioridade, tempPrioridade);

                trocado = 1;
            }
            atual = atual->prox;
        }
        fim = atual;
    } while (trocado);

    printf("Tarefas ordenadas por prioridade.\n");
}

void buscarPorTitulo(Tarefa* inicio) {
    if (inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    char titulo[50];
    printf("Digite o título da tarefa a buscar: ");
    fgets(titulo, sizeof(titulo), stdin);
    strtok(titulo, "\n");

    Tarefa* atual = inicio;
    while (atual) {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("\nTarefa encontrada:\n");
            printf("Título: %s\n", atual->titulo);
            printf("Descrição: %s\n", atual->descricao);
            printf("Prioridade: %s\n", atual->prioridade);
            return;
        }
        atual = atual->prox;
    }

    printf("Tarefa não encontrada.\n");
}

int contarTarefas(Tarefa* inicio) {
    int count = 0;
    Tarefa* atual = inicio;
    while (atual) {
        count++;
        atual = atual->prox;
    }
    return count;
}

void listaParaVetor(Tarefa* inicio, Tarefa** vetor, int tamanho) {
    Tarefa* atual = inicio;
    for (int i = 0; i < tamanho && atual != NULL; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }
}

void ordenarVetorPorTitulo(Tarefa** vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(vetor[j]->titulo, vetor[j + 1]->titulo) > 0) {
                Tarefa* temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void buscaBinariaPorTitulo(Tarefa* inicio) {
    int tamanho = contarTarefas(inicio);
    if (tamanho == 0) {
        printf("A lista está vazia.\n");
        return;
    }

    Tarefa** vetor = malloc(tamanho * sizeof(Tarefa*));
    if (!vetor) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    listaParaVetor(inicio, vetor, tamanho);
    ordenarVetorPorTitulo(vetor, tamanho);

    char titulo[50];
    printf("Digite o título da tarefa para busca binária: ");
    fgets(titulo, sizeof(titulo), stdin);
    strtok(titulo, "\n");

    int inicioIdx = 0, fimIdx = tamanho - 1;
    while (inicioIdx <= fimIdx) {
        int meio = (inicioIdx + fimIdx) / 2;
        int cmp = strcmp(titulo, vetor[meio]->titulo);
        if (cmp == 0) {
            printf("\nTarefa encontrada:\n");
            printf("Título: %s\n", vetor[meio]->titulo);
            printf("Descrição: %s\n", vetor[meio]->descricao);
            printf("Prioridade: %s\n", vetor[meio]->prioridade);
            free(vetor);
            return;
        } else if (cmp < 0) {
            fimIdx = meio - 1;
        } else {
            inicioIdx = meio + 1;
        }
    }

    printf("Tarefa não encontrada.\n");
    free(vetor);
}

int main() {
    Tarefa* lista = inicializar();
    int opcao;

    do {
        printf("\nMenu\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Remover tarefa por título\n");
        printf("4. Ordenar tarefas por prioridade\n");
        printf("5. Buscar tarefa por título (linear)\n");
        printf("6. Buscar tarefa por título (binária)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: adicionarTarefa(&lista); break;
            case 2: listarTarefas(lista); break;
            case 3: removerPorTitulo(&lista); break;
            case 4: ordenarPorPrioridade(lista); break;
            case 5: buscarPorTitulo(lista); break;
            case 6: buscaBinariaPorTitulo(lista); break;
            case 0: liberar(&lista); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
