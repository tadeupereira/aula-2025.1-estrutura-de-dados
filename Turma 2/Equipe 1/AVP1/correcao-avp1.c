#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define R     "\x1b[31m"
#define Y  "\x1b[33m"
#define G   "\x1b[32m"
    #define RESET   "\x1b[0m"
    #define MAX   15

typedef struct {
    char titulo[50];
    char descricao[200];
    int prioridade;
} Tarefa;

typedef struct {
    Tarefa tarefas[MAX];
    int qtd;
} Lista;

void limpar();
void pausar();

void adicionar (Lista *lista);
void remover (Lista *lista);

void visualizar(const Lista *lista);
void visualizacaoReduzida(const Lista *lista);

int main()
{
    setlocale(LC_ALL, "");

    Lista lista;
    lista.qtd = 0;

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
            pausar();
            continue;
        }
        getchar();


        switch(opcao) {
            case 1:
                adicionar(&lista);
                pausar();
                break;
            case 2:
                visualizar(&lista);
                pausar();
                break;
            case 3:
                remover(&lista);
                pausar();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                pausar();
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

void pausar() {
    printf("\nPressione Enter para continuar...");
    fgetc(stdin);
}

void adicionar (Lista *lista){

    limpar();
    printf("===============================\n");
    printf("     ADICIONAR UMA TAREFA      \n");
    printf("===============================\n");

    if (lista->qtd >= MAX) {
        printf("Sua lista de tarefas está cheia!\n");
        return;
    }
    Tarefa nova;

    printf("Digite o título da sua tarefa: ");
    fgets(nova.titulo, 50, stdin);

    printf("Digite a descricao da sua tarefa: ");
    fgets(nova.descricao, 200, stdin);

    int resultado;
    do{
        printf("Digite a prioridade (" R "1 - Alta" RESET "," Y " 2 - Média" RESET "," G " 3 - Baixa" RESET "): ");
        resultado = scanf("%d", &nova.prioridade);

        if (resultado != 1 || nova.prioridade < 1 || nova.prioridade > 3) {
            printf("Entrada inválida! Digite um número entre 1 e 3.\n");
            while (getchar() != '\n');
    }
    }while(nova.prioridade < 1 || nova.prioridade > 3);
    getchar();

    lista->tarefas[lista->qtd++] = nova;

    printf("Tarefa adicionada com sucesso.");
}

void remover (Lista *lista){
    limpar();
    printf("===============================\n");
    printf("      REMOVER UMA TAREFA       \n");
    printf("===============================\n");
    int posicao = 0;
    if (lista->qtd == 0) {
        printf("A lista está vazia. Nada para remover.\n");
        return;
    }
    visualizacaoReduzida(lista);
    printf("===============================\n");
    printf("Escolha qual tarefa deseja remover: ");
    int resultado = scanf("%d", &posicao);
    getchar();

    if (resultado != 1) {
        printf("Entrada inválida! Por favor, digite um número.\n");
        while (getchar() != '\n');
        return;
    }

    if (posicao < 1 || posicao > lista->qtd) {
        printf("Tarefa na posição %d não encontrada.\n", posicao);
        return;
    }

    for (int i = posicao - 1; i < lista->qtd - 1; i++) {
        lista->tarefas[i] = lista->tarefas[i + 1];
    }

    lista->qtd--;

    printf("Tarefa %d removida com sucesso.\n", posicao);
}

void visualizar(const Lista *lista){
    limpar();
    printf("===============================\n");
    printf("       LISTA DE TAREFAS        \n");
    printf("===============================\n");
    if(lista->qtd == 0) {
        printf("Sua lista está vazia.\n");
    }else {
        for (int i = 0; i < lista->qtd; i ++) {
            if (i != 0) {
                printf("-------------------------------\n");
            }
            printf("Título: %s", lista->tarefas[i].titulo);
            printf("Descrição: %s", lista->tarefas[i].descricao);
            printf("Prioridade: ");
            switch (lista->tarefas[i].prioridade) {
                case 1: printf(R "Alta" RESET"\n"); break;
                case 2: printf(Y "Média" RESET"\n"); break;
                case 3: printf(G "Baixa" RESET "\n"); break;
            }
        }
    }
}

void visualizacaoReduzida(const Lista *lista){
    if(lista->qtd == 0) {
        printf("Sua lista está vazia.\n");
    }else {
        for (int i = 0; i < lista->qtd; i ++) {
            printf("%d - %s", i+1, lista->tarefas[i].titulo);
        }
    }
}
