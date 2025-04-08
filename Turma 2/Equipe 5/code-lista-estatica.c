#include <stdio.h>
#include <string.h>

const int MAX_TAREFAS = 10;
const int NULL_INDEX = -1;

typedef struct {
    int id;
    char titulo[50];
    char descricao[100];
    char prioridade[10];
    int proximo;
    int usado;
} Tarefa;

Tarefa tarefas[MAX_TAREFAS];
int inicio = NULL_INDEX;
int numeroTarefa = 1;

void inicializarLista() {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        tarefas[i].usado = 0;
        tarefas[i].proximo = NULL_INDEX;
    }
}

int alocarTarefa() {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (!tarefas[i].usado) {
            tarefas[i].usado = 1;
            return i;
        }
    }
    return NULL_INDEX;
}

void liberarTarefa(int index) {
    tarefas[index].usado = 0;
    tarefas[index].proximo = NULL_INDEX;
}

void insertLast(char* titulo, char* descricao, int prioridade) {
    int index = alocarTarefa();
    if (index == NULL_INDEX) {
        printf("Lista cheia!\n");
        return;
    }

    Tarefa* nova = &tarefas[index];
    nova->id = numeroTarefa++;
    strcpy(nova->titulo, titulo);
    strcpy(nova->descricao, descricao);

    switch (prioridade) {
        case 1: strcpy(nova->prioridade, "Alta"); break;
        case 2: strcpy(nova->prioridade, "Média"); break;
        case 3: strcpy(nova->prioridade, "Baixa"); break;
        default:
            printf("Prioridade inválida!\n");
            liberarTarefa(index);
            return;
    }

    nova->proximo = NULL_INDEX;

    if (inicio == NULL_INDEX) {
        inicio = index;
    } else {
        int atual = inicio;
        while (tarefas[atual].proximo != NULL_INDEX) {
            atual = tarefas[atual].proximo;
        }
        tarefas[atual].proximo = index;
    }
}

void listarTarefas() {
    if (inicio == NULL_INDEX) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    int atual = inicio;
    while (atual != NULL_INDEX) {
        Tarefa* t = &tarefas[atual];
        printf("ID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %s\n\n", t->id, t->titulo, t->descricao, t->prioridade);
        atual = t->proximo;
    }
}

void removerTarefa(int id) {
    int atual = inicio;
    int anterior = NULL_INDEX;

    while (atual != NULL_INDEX && tarefas[atual].id != id) {
        anterior = atual;
        atual = tarefas[atual].proximo;
    }

    if (atual == NULL_INDEX) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    if (anterior == NULL_INDEX) {
        inicio = tarefas[atual].proximo;
    } else {
        tarefas[anterior].proximo = tarefas[atual].proximo;
    }

    liberarTarefa(atual);
    printf("Tarefa removida com sucesso!\n");
}

void buscarTarefa(int id) {
    int atual = inicio;

    while (atual != NULL_INDEX) {
        if (tarefas[atual].id == id) {
            Tarefa* t = &tarefas[atual];
            printf("ID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %s\n", t->id, t->titulo, t->descricao, t->prioridade);
            return;
        }
        atual = tarefas[atual].proximo;
    }

    printf("Tarefa não encontrada.\n");
}

int main() {
    inicializarLista();
    int escolha, prioridade, id;
    char titulo[50], descricao[100];

    do {
        printf("\nGerenciador de Tarefas - Equipe 05\n\n");
        printf("\n1 - Adicionar\n2 - Remover\n3 - Listar\n4 - Buscar\n0 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &escolha) != 1) { 
            printf("Entrada inválida! Digite um número.\n");
            while (getchar() != '\n'); 
            escolha = -1; 
            continue; 
        }
        while (getchar() != '\n');

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

                insertLast(titulo, descricao, prioridade);
                break;

            case 2:
                printf("ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                removerTarefa(id);
                break;

            case 3:
                listarTarefas();
                break;

            case 4:
                printf("ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                buscarTarefa(id);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    return 0;
}
