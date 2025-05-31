#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define R     "\x1b[31m"
#define Y  "\x1b[33m"
#define G   "\x1b[32m"
#define RESET   "\x1b[0m"

struct tarefa {
    char titulo[50];
    char descricao[200];
    int prioridade;
    struct tarefa *prox;
};

void limpar();
void adicionar (struct tarefa **lista);
void remover (struct tarefa **lista);
void visualizar(struct tarefa *lista);
void visualizacaoReduzida(struct tarefa *lista);

int main()
{
    setlocale(LC_ALL, "");

    struct tarefa* lista = NULL;

    int opcao;
    do {
        limpar();
        printf("===============================\n");
        printf("    GERENCIADOR DE TAREFAS     \n");
        printf("===============================\n");
        printf("1. Adicionar nova tarefa\n2. Visualizar todas as tarefas\n3. Remover uma tarefa\n4. Sair\n");
        printf("===============================\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            while(getchar() != '\n');
            fgetc(stdin);
            continue;
        }
        getchar();


        switch(opcao) {
            case 1:
                adicionar(&lista);
                printf("\nPressione Enter para continuar...");
                fgetc(stdin);
                break;
            case 2:
                visualizar(lista);
                printf("\nPressione Enter para continuar...");
                fgetc(stdin);
                break;
            case 3:
                remover(&lista);
                printf("\nPressione Enter para continuar...");
                fgetc(stdin);
                break;
            case 4:
                printf("Saindo...\n");
                struct tarefa *temp;
                while (lista != NULL) {
                    temp = lista;
                    lista = lista->prox;
                    free(temp);
                }
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                fgetc(stdin);
        }
    } while(opcao != 4);
    return 0;
}

void limpar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void adicionar (struct tarefa **lista){

    limpar();
    printf("===============================\n");
    printf("     ADICIONAR UMA TAREFA      \n");
    printf("===============================\n");

    struct tarefa* nova = (struct tarefa*)malloc(sizeof(struct tarefa));

    if (nova == NULL) {
        printf("Erro ao alocar memória para nova tarefa!\n");
        return;
    }

    printf("Digite o título da sua tarefa: ");
    fgets(nova->titulo, 50, stdin);

    printf("Digite a descricao da sua tarefa: ");
    fgets(nova->descricao, 200, stdin);

    int resultado;
    do{
        printf("Digite a prioridade (" R "1 - Alta" RESET "," Y " 2 - Média" RESET "," G " 3 - Baixa" RESET "): ");
        resultado = scanf("%d", &nova->prioridade);
        getchar();

        if (resultado != 1 || nova->prioridade < 1 || nova->prioridade > 3) {
            printf("Entrada inválida! Digite um número entre 1 e 3.\n");
            while (getchar() != '\n');
    }
    }while(nova->prioridade < 1 || nova->prioridade > 3);
    getchar();

    nova->prox = NULL;

    if(*lista == NULL) {
        *lista = nova;
    }else {
        struct tarefa *temp = *lista;
        while(temp->prox != NULL){
            temp = temp->prox;
        }
        temp->prox = nova;
    }

    printf("Tarefa adicionada com sucesso.");
}
void remover (struct tarefa **lista){
    limpar();
    printf("===============================\n");
    printf("      REMOVER UMA TAREFA       \n");
    printf("===============================\n");
    int posicao = 0;
    if (*lista == NULL) {
        printf("A lista está vazia. Nada para remover.\n");
        return;
    }
    visualizacaoReduzida(*lista);
    printf("===============================\n");
    printf("Escolha qual tarefa deseja remover: ");
    int resultado = scanf("%d", &posicao);
    getchar();

    if (resultado != 1) {
        printf("Entrada inválida! Por favor, digite um número.\n");
        while (getchar() != '\n');
        return;
    }

    int i = 1;

    struct tarefa *temp = *lista;
    struct tarefa *anterior = NULL;

    while (temp != NULL && i < posicao) {
        anterior = temp;
        temp = temp->prox;
        i++;
    }
    if (temp == NULL) {
        printf("Tarefa na posição %d não encontrada.\n", posicao);
        return;
    }

    if (anterior == NULL) {
        *lista = temp->prox;
    } else {
        anterior->prox = temp->prox;
    }
    free(temp);

    printf("Tarefa %d removida com sucesso.\n", posicao);
}
void visualizar(struct tarefa *lista){
    limpar();
    printf("===============================\n");
    printf("       LISTA DE TAREFAS        \n");
    printf("===============================\n");
    if(lista == NULL) {
        printf("Sua lista está vazia.\n");
    }else {
        int i = 1;
        struct tarefa *temp = lista;
        while(temp != NULL){
            printf("Título: %s", temp->titulo);
            printf("Descrição: %s", temp->descricao);
            printf("Prioridade: ");
            switch (temp->prioridade) {
                case 1: printf(R "Alta" RESET"\n"); break;
                case 2: printf(Y "Média" RESET"\n"); break;
                case 3: printf(G "Baixa" RESET "\n"); break;
            }
            if (temp->prox != NULL) {
                printf("-------------------------------\n");
            }
            temp = temp->prox;
            i++;
        }
    }
}
void visualizacaoReduzida(struct tarefa *lista){
    if(lista == NULL) {
        printf("Sua lista está vazia.\n");
    }else {
        int i = 1;
        struct tarefa *temp = lista;
        while(temp != NULL){
            printf("%d - %s", i, temp->titulo);
            temp = temp->prox;
            i++;
        }
    }
}



