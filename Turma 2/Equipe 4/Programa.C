#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMADAS 100

typedef struct {
    int id;
    char tipo[20];
    char numero[20];
    char dataHora[50];
    char descricao[100];
} Chamada;

typedef struct {
    Chamada chamadas[MAX_CHAMADAS];
    int frente;
    int tras;
} Fila;

void inicializarFila(Fila* fila) {
    fila->frente = 0;
    fila->tras = 0;
}

int estaVazia(Fila fila) {
    return fila.frente == fila.tras;
}

int estaCheia(Fila fila) {
    return fila.tras == MAX_CHAMADAS;
}

void limparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

Fila adicionarChamada(Fila fila, int id, const char* tipo, const char* numero, const char* dataHora, const char* descricao) {
    if (estaCheia(fila)) {
        printf("Fila cheia nao e possivel adicionar mais chamadas\n");
        return fila;
    }

    Chamada novaChamada;
    novaChamada.id = id;
    strncpy(novaChamada.tipo, tipo, sizeof(novaChamada.tipo) - 1);
    novaChamada.tipo[sizeof(novaChamada.tipo) - 1] = '\0';
    strncpy(novaChamada.numero, numero, sizeof(novaChamada.numero) - 1);
    novaChamada.numero[sizeof(novaChamada.numero) - 1] = '\0';
    strncpy(novaChamada.dataHora, dataHora, sizeof(novaChamada.dataHora) - 1);
    novaChamada.dataHora[sizeof(novaChamada.dataHora) - 1] = '\0';
    strncpy(novaChamada.descricao, descricao, sizeof(novaChamada.descricao) - 1);
    novaChamada.descricao[sizeof(novaChamada.descricao) - 1] = '\0';

    fila.chamadas[fila.tras] = novaChamada;
    fila.tras++;

    printf("Chamada %d adicionada na fila: %s - %s - %s\n", id, tipo, numero, dataHora);
    return fila;
}

Fila removerChamada(Fila fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia nao ha chamadas para remover\n");
        return fila;
    }

    int idRemover;
    printf("Digite o id da chamada que deseja remover: ");
    scanf("%d", &idRemover);

    int encontrado = 0;

    for (int i = fila.frente; i < fila.tras; i++) {
        if (fila.chamadas[i].id == idRemover) {
            for (int j = i; j < fila.tras - 1; j++) {
                fila.chamadas[j] = fila.chamadas[j + 1];
            }
            fila.tras--;
            printf("Chamada com id %d removida da fila\n", idRemover);
            encontrado = 1;
            getchar();
            break;
        }
    }

    if (!encontrado) {
        printf("Chamada com id %d nao encontrada na fila\n", idRemover);
        getchar();
    }

    return fila;
}

void listarChamadas(Fila fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia nao ha chamadas para listar\n");
        return;
    }

    printf("Chamadas na fila:\n");
    for (int i = fila.frente; i < fila.tras; i++) {
        printf("ID: %d - Tipo: %s - Numero: %s - Data e Hora: %s\n",
               fila.chamadas[i].id, fila.chamadas[i].tipo, fila.chamadas[i].numero, fila.chamadas[i].dataHora);
        printf("Descricao: %s\n", fila.chamadas[i].descricao);
        printf("------------------------\n");
    }
}

void exibirMenu() {
    printf("=================================\n");
    printf("     Sistema de Gerenciamento    \n");
    printf("        de Chamadas Telefonicas  \n");
    printf("=================================\n");
    printf("1. Adicionar uma chamada\n");
    printf("2. Remover uma chamada\n");
    printf("3. Listar todas as chamadas\n");
    printf("4. Sair\n");
    printf("=================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Fila fila;
    inicializarFila(&fila);

    int opcao;
    int id = 1;
    char tipo[20];
    char numero[20];
    char dataHora[50];
    char descricao[100];

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        limparTerminal();

        switch (opcao) {
            case 1:
                printf("Digite o tipo da chamada (feita ou recebida): ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = 0;

                printf("Digite o numero de telefone: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = 0;

                printf("Digite a data e hora da chamada (dd/mm/aaaa hh:mm): ");
                fgets(dataHora, sizeof(dataHora), stdin);
                dataHora[strcspn(dataHora, "\n")] = 0;

                printf("Digite uma descricao para a chamada (opcional): ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0;

                fila = adicionarChamada(fila, id++, tipo, numero, dataHora, descricao);
                break;

            case 2:
                fila = removerChamada(fila);
                break;

            case 3:
                listarChamadas(fila);
                break;

            case 4:
                printf("Saindo do sistema\n");
                break;

            default:
                printf("Opcao invalida Tente novamente\n");
                break;
        }

        if (opcao != 4) {
            printf("\nPressione Enter para voltar ao menu...\n");
            getchar();
            limparTerminal();
        }

    } while (opcao != 4);

    return 0;
}
