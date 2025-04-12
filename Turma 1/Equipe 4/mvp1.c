#include <stdio.h>
#include <string.h>

#define TAM_FILA 10

typedef struct {
    int numero;
    char dia[11];
    char hora[6];
} Chamada;

typedef struct {
    Chamada fila[TAM_FILA];
    int primeiro;
    int ultimo;
    int qtdchamada;
} Fila;

void inifila(Fila* f) {
    f->primeiro = 0;
    f->ultimo = 0;
    f->qtdchamada = 0;
}

int chamada_existe(Fila* f, int numero, char dia[], char hora[]) {
    for (int i = 0; i < f->qtdchamada; i++) {
        int pos = (f->primeiro + i) % TAM_FILA;
        if (f->fila[pos].numero == numero &&
            strcmp(f->fila[pos].dia, dia) == 0 &&
            strcmp(f->fila[pos].hora, hora) == 0) {
            return 1;
        }
    }
    return 0;
}

void adicionar_chamada(Fila* f, int numero, char dia[], char hora[]) {
    if (f->qtdchamada == TAM_FILA) {
        printf("Fila cheia! Nao e possivel adicionar mais chamadas.\n");
    } else if (chamada_existe(f, numero, dia, hora)) {
        printf("Essa chamada ja existe! Por isso não foi adicionada.\n");
    } else {
        f->fila[f->ultimo].numero = numero;
        strcpy(f->fila[f->ultimo].dia, dia);
        strcpy(f->fila[f->ultimo].hora, hora);
        f->ultimo = (f->ultimo + 1) % TAM_FILA;
        f->qtdchamada++;
        printf("Chamada adicionada com sucesso!\n");
    }
}

void remover_chamada(Fila* f) {
    if (f->qtdchamada == 0) {
        printf("Fila vazia! Nao ha chamadas para remover.\n");
    } else {
        printf("Chamada %d removida com sucesso!\n", f->fila[f->primeiro].numero);
        f->primeiro = (f->primeiro + 1) % TAM_FILA;
        f->qtdchamada--;
    }
}

void imprimir_fila(Fila* f) {
    if (f->qtdchamada == 0) {
        printf("Fila vazia! Nenhuma chamada armazenada.\n");
        return;
    }

    printf("\nChamadas armazenadas:\n");
    for (int i = 0; i < f->qtdchamada; i++) {
        int pos = (f->primeiro + i) % TAM_FILA;
        printf("Numero: %d | Dia: %s | Hora: %s\n",
               f->fila[pos].numero,
               f->fila[pos].dia,
               f->fila[pos].hora);
    }
}

int main() {
    Fila minha_fila;
    inifila(&minha_fila);

    int opcao, numero;
    char dia[11];
    char hora[6];

    while (1) {
        printf("\nMENU\n");
        printf("1 - Adicionar chamada\n");
        printf("2 - Remover chamada\n");
        printf("3 - Listar chamadas\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf(" %d", &opcao) != 1) {
            printf("Entrada invalida! Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite o numero da chamada: ");
                if (scanf(" %d", &numero) != 1) {
                    printf("Entrada invalida! Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Digite o dia da chamada (formato dd/mm/aaaa): ");
                scanf(" %10s", dia);

                printf("Digite a hora da chamada (formato hh:mm): ");
                scanf(" %5s", hora);

                adicionar_chamada(&minha_fila, numero, dia, hora);
                break;

            case 2:
                remover_chamada(&minha_fila);
                break;

            case 3:
                imprimir_fila(&minha_fila);
                break;

            case 4:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}