#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    int id;
    char titulo[50];
    char descricao[100];
    char prioridade[10];
    struct Tarefa* proximo;
} Tarefa;

int numeroTarefa = 1;

Tarefa* criarTarefa(char* titulo, char* descricao, int prioridade) {
    Tarefa* novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
    if (novaTarefa == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    strcpy(novaTarefa->titulo, titulo);
    strcpy(novaTarefa->descricao, descricao);

    switch (prioridade) {
        case 1:
            strcpy(novaTarefa->prioridade, "Alta");
            break;
        case 2:
            strcpy(novaTarefa->prioridade, "Média");
            break;
        case 3:
            strcpy(novaTarefa->prioridade, "Baixa");
            break;
        default:
            printf("Erro: Prioridade inválida!\n");
            free(novaTarefa);
            return NULL;
    }

    novaTarefa->id = numeroTarefa++;
    novaTarefa->proximo = NULL;
    return novaTarefa;
}

int empty(Tarefa* head) {
    return (head == NULL);
}

Tarefa* create() {
    return NULL;
}

void insertLast(Tarefa** head, char* titulo, char* descricao, int prioridade) {
    Tarefa* novaTarefa = criarTarefa(titulo, descricao, prioridade);
    if (empty(*head)) {
        *head = novaTarefa;
    } else {
        Tarefa* temp = *head;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novaTarefa;
    }
}

void removerTarefa(Tarefa** head, int id) {
    Tarefa* temp = *head;
    Tarefa* anterior = NULL;

    while (temp != NULL && temp->id != id) {
        anterior = temp;
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Tarefa não encontrada!\n");
        return;
    }

    if (anterior == NULL) {
        *head = temp->proximo;
    } else {
        anterior->proximo = temp->proximo;
    }

    free(temp);
    printf("Tarefa removida com sucesso!\n");
}

void listarTarefas(Tarefa* head) {
    if (empty(head)) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }

    Tarefa* temp = head;
    printf("\nListando tarefas...\n");
    while (temp != NULL) {
        printf("\nTarefa ID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %s\n",
               temp->id, temp->titulo, temp->descricao, temp->prioridade);
        temp = temp->proximo;
    }
    printf("\n");
}

void buscaLinearPorTitulo(Tarefa* head, char* tituloBusca) {
    Tarefa* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->titulo, tituloBusca) == 0) {
            printf("\nTarefa encontrada:\nID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %s\n",
                   temp->id, temp->titulo, temp->descricao, temp->prioridade);
            return;
        }
        temp = temp->proximo;
    }
    printf("\nTarefa com título '%s' não encontrada.\n", tituloBusca);
}

int tamanhoLista(Tarefa* head) {
    int tamanho = 0;
    while (head != NULL) {
        tamanho++;
        head = head->proximo;
    }
    return tamanho;
}

void listaParaArray(Tarefa* head, Tarefa** array) {
    int i = 0;
    while (head != NULL) {
        array[i++] = head;
        head = head->proximo;
    }
}

int prioridadeValor(char* prioridade) {
    if (strcmp(prioridade, "Alta") == 0) return 1;
    if (strcmp(prioridade, "Média") == 0) return 2;
    if (strcmp(prioridade, "Baixa") == 0) return 3;
    return 4;
}

void ordenarPorPrioridade(Tarefa** head) {
    int n = tamanhoLista(*head);
    if (n < 2) return;

    Tarefa* array[n];
    listaParaArray(*head, array);

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (prioridadeValor(array[j]->prioridade) > prioridadeValor(array[j+1]->prioridade)) {
                Tarefa* temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < n-1; i++) {
        array[i]->proximo = array[i+1];
    }
    array[n-1]->proximo = NULL;
    *head = array[0];

    printf("\nTarefas ordenadas por prioridade!\n");
}

void ordenarPorTitulo(Tarefa** head) {
    int n = tamanhoLista(*head);
    if (n < 2) return;

    Tarefa* array[n];
    listaParaArray(*head, array);

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (strcmp(array[j]->titulo, array[j+1]->titulo) > 0) {
                Tarefa* temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < n-1; i++) {
        array[i]->proximo = array[i+1];
    }
    array[n-1]->proximo = NULL;
    *head = array[0];

    printf("\nTarefas ordenadas por título!\n");
}

void buscaBinariaPorTitulo(Tarefa* head, char* tituloBusca) {
    int n = tamanhoLista(head);
    if (n == 0) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }

    Tarefa* array[n];
    listaParaArray(head, array);

    int inicio = 0, fim = n - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int comparacao = strcmp(tituloBusca, array[meio]->titulo);

        if (comparacao == 0) {
            printf("\nTarefa encontrada:\nID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %s\n",
                   array[meio]->id, array[meio]->titulo, array[meio]->descricao, array[meio]->prioridade);
            return;
        } else if (comparacao < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("\nTarefa com título '%s' não encontrada.\n", tituloBusca);
}

void cleanLista(Tarefa* head) {
    Tarefa* temp;
    while (head != NULL) {
        temp = head;
        head = head->proximo;
        free(temp);
    }
}

int main() {
    Tarefa* listaTarefas = create();
    int escolha;
    char titulo[50], descricao[100];
    int prioridade, id;

    do {
        printf("\nGerenciador de Tarefas\n");
        printf("1 - Adicionar Tarefa\n");
        printf("2 - Remover Tarefa\n");
        printf("3 - Listar Tarefas\n");
        printf("4 - Buscar Tarefa por Título (Linear)\n");
        printf("5 - Buscar Tarefa por Título (Binária)\n");
        printf("6 - Ordenar Tarefas por Prioridade\n");
        printf("7 - Ordenar Tarefas por Título\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                printf("Título: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Descrição: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0;

                printf("Prioridade (1-Alta, 2-Média, 3-Baixa): ");
                scanf("%d", &prioridade);
                getchar();

                insertLast(&listaTarefas, titulo, descricao, prioridade);
                break;

            case 2:
                printf("ID da tarefa para remover: ");
                scanf("%d", &id);
                getchar();
                removerTarefa(&listaTarefas, id);
                break;

            case 3:
                listarTarefas(listaTarefas);
                break;

            case 4:
                printf("Digite o título da tarefa: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                buscaLinearPorTitulo(listaTarefas, titulo);
                break;

            case 5:
                printf("Digite o título da tarefa (lista precisa estar ordenada): ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                buscaBinariaPorTitulo(listaTarefas, titulo);
                break;

            case 6:
                ordenarPorPrioridade(&listaTarefas);
                break;

            case 7:
                ordenarPorTitulo(&listaTarefas);
                break;

            case 0:
                printf("Saindo...\n");
                cleanLista(listaTarefas);
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (escolha != 0);

    return 0;
}
