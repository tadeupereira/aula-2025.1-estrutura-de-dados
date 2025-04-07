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
            printf("Erro: Prioridade inválida! Digite somente 1,2 ou 3.\n");
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
    
    if (empty(temp)) {
        printf("\nTarefa não encontrada!\n");
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
        printf("\nOps...nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("Listando tarefas...\n\n");

    Tarefa* temp = head;

    while (temp != NULL) {
        printf("Tarefa ID %d\n", temp->id);
        printf("Título: %s\nDescrição: %s\nPrioridade: %s\n\n", temp->titulo, temp->descricao, temp->prioridade);
        temp = temp->proximo;
    }
}

void search(int id, Tarefa* head) {
    if (empty(head)) {
        printf("\nOps...nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("Listando tarefa %d...\n\n", id);

    Tarefa* temp = head;

    while (temp != NULL) {
        if(temp->id == id){
            printf("Tarefa ID %d\n", temp->id);
            printf("Título: %s\nDescrição: %s\nPrioridade: %s\n\n", temp->titulo, temp->descricao, temp->prioridade);
            return;
        }
        temp = temp->proximo;
    }

    printf("Tarefa com ID %d não encontrada.\n", id);
}

void cleanLista(Tarefa* head) {
    Tarefa* temp;
    while (head != NULL) {
        temp = head;
        head = head->proximo;
        free(temp);
    }
}

Tarefa* create() {
    return NULL;
}

int main() {
    Tarefa* listaTarefas = create();
    int escolha;

    char titulo[50], descricao[100];
    int prioridade;
    int id;
    
    do {
        printf("\nGerenciador de Tarefas - Equipe 05\n\n");
        printf("1 - Adicionar Tarefa\n");
        printf("2 - Remover Tarefa\n");
        printf("3 - Listar Tarefas\n");
        printf("4 - Buscar Tarefa por ID\n");
        printf("0 - Sair\n\n");
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

                printf("Escolha a prioridade\n(1) Alta\n(2) Média\n(3) Baixa\nDigite o número: ");
                scanf("%d", &prioridade);
                getchar(); 
                insertLast(&listaTarefas, titulo, descricao, prioridade);
                break;

            case 2:
                printf("Id da tarefa a remover: ");
                scanf("%d", &id);
                getchar(); 

                removerTarefa(&listaTarefas, id);
                break;

            case 3:
                listarTarefas(listaTarefas);
                break;

            case 4:
                printf("Digite o ID da tarefa: ");
                scanf("%d", &id);
                getchar(); 
                search(id, listaTarefas);
                break;            

            case 0:
                printf("Saindo...\n");
                cleanLista(listaTarefas);
                break;

            default:
                printf("Opção inválida!\n\n");
        }

    } while (escolha != 0);
    
    return 0;
}