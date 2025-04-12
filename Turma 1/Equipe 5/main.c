#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct {
    char titulo[50];
    char descricao[100];
    char prioridade[10]; 
    int proximo;        
} Tarefa;

typedef struct {
    Tarefa tarefas[MAX];
    int inicio;  
    int livre;   
} ListaEstatica;


void inicializarLista(ListaEstatica *lista) {
    lista->inicio = -1; 
    lista->livre = 0;   
    for (int i = 0; i < MAX; i++) {
        lista->tarefas[i].proximo = -1; 
    }
}


void adicionarTarefa(ListaEstatica *lista, char *titulo, char *descricao, char *prioridade) {
    if (lista->livre >= MAX) {
        printf("ERRO: Lista esta cheia!\n");
        return;
    }

    int indice = lista->livre;
    strcpy(lista->tarefas[indice].titulo, titulo);
    strcpy(lista->tarefas[indice].descricao, descricao);
    strcpy(lista->tarefas[indice].prioridade, prioridade);

    lista->tarefas[indice].proximo = lista->inicio; 
    lista->inicio = indice; 
    lista->livre++;

    printf("Tarefa adicionada com sucesso!\n");
}

void removerTarefa(ListaEstatica *lista, char *titulo) {
    int atual = lista->inicio;
    int anterior = -1;

    while (atual != -1) {
        if (strcmp(lista->tarefas[atual].titulo, titulo) == 0) {
            
            if (anterior == -1) {
                
                lista->inicio = lista->tarefas[atual].proximo;
            } else {
                
                lista->tarefas[anterior].proximo = lista->tarefas[atual].proximo;
            }

            printf("Tarefa '%s' removida com sucesso!\n", titulo);
            return;
        }

        anterior = atual;
        atual = lista->tarefas[atual].proximo;
    }

    printf("Tarefa '%s' nao encontrada.\n", titulo);
}


void listarTarefas(ListaEstatica *lista) {
    int atual = lista->inicio;
    if (atual == -1) {
        printf("A lista de tarefas esta vazia.\n");
        return;
    }

    printf("\nLista de Tarefas:\n");
    while (atual != -1) {
        printf("-------------------------\n");
        printf("Titulo: %s\n", lista->tarefas[atual].titulo);
        printf("Descricao: %s\n", lista->tarefas[atual].descricao);
        printf("Prioridade: %s\n", lista->tarefas[atual].prioridade);
        atual = lista->tarefas[atual].proximo; 
    }
}

int main() {
    ListaEstatica lista;
    inicializarLista(&lista);

    int opcao;
    char titulo[50], descricao[100], prioridade[10];

    do {
        printf("\nGerenciador de Tarefas\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Remover Tarefa\n");
        printf("3. Listar Tarefas\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o titulo: ");
                scanf(" %[^\n]", titulo);
                printf("Digite a descricao: ");
                scanf(" %[^\n]", descricao);
                printf("Digite a prioridade (Alta, Media, Baixa): ");
                scanf(" %[^\n]", prioridade);
                adicionarTarefa(&lista, titulo, descricao, prioridade);
                break;

            case 2:
                printf("Digite o titulo da tarefa a remover: ");
                scanf(" %[^\n]", titulo);
                removerTarefa(&lista, titulo);
                break;

            case 3:
                listarTarefas(&lista);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}