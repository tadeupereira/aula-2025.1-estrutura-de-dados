#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    char titulo[50];
    char descricao[100];
    char prioridade[10];
    struct Tarefa *proximo;
} Tarefa;
int prioridadeParaInt(char *prioridade) {
    if (strcmp(prioridade, "Alta") == 0) return 1;
    if (strcmp(prioridade, "Media") == 0) return 2;
    if (strcmp(prioridade, "Baixa") == 0) return 3;
    return 4;
}
Tarefa* inicializarLista() {
    return NULL;
}
Tarefa* adicionarTarefa(Tarefa *inicio, Tarefa nova) {
    Tarefa *novaTarefa = (Tarefa *)malloc(sizeof(Tarefa));
    if (!novaTarefa) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    *novaTarefa = nova;
    novaTarefa->proximo = inicio;
    printf("Tarefa adicionada com sucesso!\n");
    return novaTarefa;
}
Tarefa* removerTarefa(Tarefa *inicio, char *titulo) {
    Tarefa *atual = inicio;
    Tarefa *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior == NULL) {
                inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            printf("Tarefa '%s' removida com sucesso!\n", titulo);
            free(atual);
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Tarefa '%s' nao encontrada.\n", titulo);
    return inicio;
}

void listarTarefas(Tarefa *inicio) {
    if (inicio == NULL) {
        printf("Lista de tarefas vazia.\n");
        return;
    }

    printf("\nLista de Tarefas:\n");
    Tarefa *atual = inicio;
    while (atual != NULL) {
        printf("------------------------\n");
        printf("Titulo: %s\n", atual->titulo);
        printf("Descricao: %s\n", atual->descricao);
        printf("Prioridade: %s\n", atual->prioridade);
        atual = atual->proximo;
    }
}

Tarefa* ordenarPorPrioridade(Tarefa *inicio) {
    if (!inicio || !inicio->proximo) return inicio;

    Tarefa *ordenada = NULL;

    while (inicio != NULL) {
        Tarefa *atual = inicio;
        inicio = inicio->proximo;

        if (ordenada == NULL || prioridadeParaInt(atual->prioridade) < prioridadeParaInt(ordenada->prioridade)) {
            atual->proximo = ordenada;
            ordenada = atual;
        } else {
            Tarefa *aux = ordenada;
            while (aux->proximo != NULL && prioridadeParaInt(aux->proximo->prioridade) <= prioridadeParaInt(atual->prioridade)) {
                aux = aux->proximo;
            }
            atual->proximo = aux->proximo;
            aux->proximo = atual;
        }
    }

    return ordenada;
}
void buscarTarefaLinear(Tarefa *inicio, char *titulo) {
    Tarefa *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Tarefa encontrada!\n");
            printf("Titulo: %s\n", atual->titulo);
            printf("Descricao: %s\n", atual->descricao);
            printf("Prioridade: %s\n", atual->prioridade);
            return;
        }
        atual = atual->proximo;
    }
    printf("Tarefa '%s' nao encontrada.\n", titulo);
}
int copiarParaVetor(Tarefa *inicio, Tarefa **vetor) {
    int tamanho = 0;
    Tarefa *atual = inicio;

    while (atual != NULL) {
        vetor[tamanho] = atual;
        tamanho++;
        atual = atual->proximo;
    }

    return tamanho;
}
void buscarTarefaBinaria(Tarefa *inicio, char *titulo) {
    Tarefa *vetor[100];
    int tamanho = copiarParaVetor(inicio, vetor);
    for (int i = 1; i < tamanho; i++) {
        Tarefa *key = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j]->titulo, key->titulo) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }

    int esquerda = 0, direita = tamanho - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(vetor[meio]->titulo, titulo);
        if (cmp == 0) {
            printf("Tarefa encontrada!\n");
            printf("Titulo: %s\n", vetor[meio]->titulo);
            printf("Descricao: %s\n", vetor[meio]->descricao);
            printf("Prioridade: %s\n", vetor[meio]->prioridade);
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    printf("Tarefa '%s' nao encontrada na busca binaria.\n", titulo);
}

void liberarLista(Tarefa *inicio) {
    Tarefa *atual;
    while (inicio != NULL) {
        atual = inicio;
        inicio = inicio->proximo;
        free(atual);
    }
}

int main() {
    Tarefa *lista = inicializarLista();
    int opcao;
    Tarefa nova;
    char tituloBusca[50];

    do {
        printf("\nGerenciador de Tarefas:\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Remover Tarefa\n");
        printf("3. Listar Tarefas\n");
        printf("4. Ordenar por Prioridade\n");
        printf("5. Buscar Tarefa (Linear)\n");
        printf("6. Buscar Tarefa (Binaria)\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Titulo: ");
                scanf(" %[^\n]", nova.titulo);
                printf("Descricao: ");
                scanf(" %[^\n]", nova.descricao);
                printf("Prioridade (Alta, Media, Baixa): ");
                scanf(" %[^\n]", nova.prioridade);
                lista = adicionarTarefa(lista, nova);
                break;

            case 2:
                printf("Titulo da tarefa a remover: ");
                scanf(" %[^\n]", tituloBusca);
                lista = removerTarefa(lista, tituloBusca);
                break;

            case 3:
                listarTarefas(lista);
                break;

            case 4:
                lista = ordenarPorPrioridade(lista);
                printf("Tarefas ordenadas por prioridade!\n");
                break;

            case 5:
                printf("Titulo da tarefa a buscar (Linear): ");
                scanf(" %[^\n]", tituloBusca);
                buscarTarefaLinear(lista, tituloBusca);
                break;

            case 6:
                printf("Titulo da tarefa a buscar (Binaria): ");
                scanf(" %[^\n]", tituloBusca);
                buscarTarefaBinaria(lista, tituloBusca);
                break;

            case 7:
                liberarLista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 7);

    return 0;
}