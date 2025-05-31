#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMADAS 100

typedef struct {
    char numero[15];
    char dia[11];
    char horario[6];
} Chamada;

typedef struct {
    Chamada chamadas[MAX_CHAMADAS];
    int inicio;
    int fim;
} FilaChamadas;

FilaChamadas* inicializarFila() {
    FilaChamadas *fila = malloc(sizeof(FilaChamadas));
    if (fila != NULL) {
        fila->inicio = 0;
        fila->fim = 0;
    }
    return fila;
}

void liberarFila(FilaChamadas *fila) {
    free(fila);
}

int estaVazia(FilaChamadas *fila) {
    return fila->inicio == fila->fim;
}

int estaCheia(FilaChamadas *fila) {
    return fila->fim == MAX_CHAMADAS;
}

int dataValida(char *data) {
    return strlen(data) == 10 && data[2] == '/' && data[5] == '/';
}

int horarioValido(char *hora) {
    return strlen(hora) == 5 && hora[2] == ':';
}

void adicionarChamada(FilaChamadas *fila, Chamada chamada) {
    if (estaCheia(fila)) {
        printf("Fila cheia!\n");
        return;
    }
    fila->chamadas[fila->fim++] = chamada;
    printf("Chamada adicionada.\n");
}

Chamada removerChamada(FilaChamadas *fila) {
    Chamada vazia = {"", "", ""};

    if (estaVazia(fila)) {
        printf("Fila vazia!\n");
        return vazia;
    }

    Chamada removida = fila->chamadas[0];

    for (int i = 0; i < fila->fim - 1; i++) {
        fila->chamadas[i] = fila->chamadas[i + 1];
    }
    fila->fim--;

    printf("Chamada removida.\n");
    return removida;
}

void listarChamadas(FilaChamadas *fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    printf("\n--- Chamadas ---\n");
    for (int i = 0; i < fila->fim; i++) {
        printf("%d - Número: %s | Dia: %s | Horário: %s\n",
               i + 1,
               fila->chamadas[i].numero,
               fila->chamadas[i].dia,
               fila->chamadas[i].horario);
    }
}

void removerChamadaPorNumero(FilaChamadas *fila, char *numero) {
    int encontrou = 0;
    for (int i = 0; i < fila->fim; i++) {
        if (strcmp(fila->chamadas[i].numero, numero) == 0) {
            for (int j = i; j < fila->fim - 1; j++) {
                fila->chamadas[j] = fila->chamadas[j + 1];
            }
            fila->fim--;
            encontrou = 1;
            printf("Chamada %s removida do histórico.\n", numero);
            break;
        }
    }
    if (!encontrou)
        printf("Chamada não encontrada.\n");
}

void ordenarChamadasPorNumero(FilaChamadas *fila) {
    for (int i = 0; i < fila->fim - 1; i++) {
        for (int j = 0; j < fila->fim - 1 - i; j++) {
            if (strcmp(fila->chamadas[j].numero, fila->chamadas[j + 1].numero) > 0) {
                Chamada temp = fila->chamadas[j];
                fila->chamadas[j] = fila->chamadas[j + 1];
                fila->chamadas[j + 1] = temp;
            }
        }
    }
    printf("Chamadas ordenadas por número.\n");
}

int buscaLinear(FilaChamadas *fila, char *numero) {
    for (int i = 0; i < fila->fim; i++) {
        if (strcmp(fila->chamadas[i].numero, numero) == 0)
            return i;
    }
    return -1;
}

int buscaBinaria(FilaChamadas *fila, char *numero) {
    int esquerda = 0, direita = fila->fim - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(fila->chamadas[meio].numero, numero);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    return -1;
}

Chamada lerChamada() {
    Chamada c;
    printf("Número: ");
    fgets(c.numero, sizeof(c.numero), stdin);
    c.numero[strcspn(c.numero, "\n")] = '\0';

    do {
        printf("Dia (DD/MM/AAAA): ");
        fgets(c.dia, sizeof(c.dia), stdin);
        c.dia[strcspn(c.dia, "\n")] = '\0';
    } while (!dataValida(c.dia));
do {
        printf("Horário (HH:MM): ");
        fgets(c.horario, sizeof(c.horario), stdin);
        c.horario[strcspn(c.horario, "\n")] = '\0';
    } while (!horarioValido(c.horario));

    return c;
}

int main() {
    FilaChamadas *fila = inicializarFila();
    int opcao;
    char numero[15];

    do {
        printf("\nMenu:\n");
        printf("1 - Adicionar chamada\n");
        printf("2 - Remover primeira chamada\n");
        printf("3 - Remover chamada por número\n");
        printf("4 - Listar chamadas\n");
        printf("5 - Ordenar chamadas por número\n");
        printf("6 - Buscar (linear) chamada por número\n");
        printf("7 - Buscar (binária) chamada por número\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        system("cls");

        switch (opcao) {
            case 1:
                adicionarChamada(fila, lerChamada());
                break;
            case 2:
                removerChamada(fila);
                break;
            case 3:
                printf("Número da chamada a remover: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';
                removerChamadaPorNumero(fila, numero);
                break;
            case 4:
                listarChamadas(fila);
                break;
            case 5:
                ordenarChamadasPorNumero(fila);
                break;
            case 6:
                printf("Número a buscar (linear): ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';
                {
                    int pos = buscaLinear(fila, numero);
                    if (pos != -1)
                        printf("Encontrado na posição %d.\n", pos + 1);
                    else
                        printf("Não encontrado.\n");
                }
                break;
            case 7:
                ordenarChamadasPorNumero(fila);
                printf("Número a buscar (binária): ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';
                {
                    int pos = buscaBinaria(fila, numero);
                    if (pos != -1)
                        printf("Encontrado na posição %d.\n", pos + 1);
                    else
                        printf("Não encontrado.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarFila(fila);
    return 0;
}