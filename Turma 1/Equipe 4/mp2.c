#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct Chamada {
    int numero;
    char dia[11];
    char hora[6];
} Chamada;

typedef struct Node {
    Chamada chamada;
    struct Node* prox;
} Node;

typedef struct {
    Node* inicio;
    Node* fim;
} Fila;

Fila* criar_fila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

int fila_vazia(Fila* f) {
    return f->inicio == NULL;
}

void adicionar_chamada(Fila* f, int numero, char dia[], char hora[]) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->chamada.numero = numero;
    strncpy(novo->chamada.dia, dia, 10);
    strncpy(novo->chamada.hora, hora, 5);
    novo->prox = NULL;

    if (fila_vazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void remover_chamada(Fila* f) {
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    Node* temp = f->inicio;
    f->inicio = f->inicio->prox;
    free(temp);
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    printf("Chamada removida com sucesso.\n");
}

void imprimir_fila(Fila* f) {
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    Node* atual = f->inicio;
    while (atual != NULL) {
        printf("Número: %d | Dia: %s | Hora: %s\n", atual->chamada.numero, atual->chamada.dia, atual->chamada.hora);
        atual = atual->prox;
    }
}

void ordenar_fila(Fila* f) {
    if (fila_vazia(f)) return;
    int trocou;
    Node* ptr;
    Node* lptr = NULL;

    do {
        trocou = 0;
        ptr = f->inicio;
        while (ptr->prox != lptr) {
            if (ptr->chamada.numero > ptr->prox->chamada.numero) {
                Chamada temp = ptr->chamada;
                ptr->chamada = ptr->prox->chamada;
                ptr->prox->chamada = temp;
                trocou = 1;
            }
            ptr = ptr->prox;
        }
        lptr = ptr;
    } while (trocou);
}

void busca_linear(Fila* f, int numero) {
    Node* atual = f->inicio;
    while (atual != NULL) {
        if (atual->chamada.numero == numero) {
            printf("Chamada encontrada: Número: %d | Dia: %s | Hora: %s\n", atual->chamada.numero, atual->chamada.dia, atual->chamada.hora);
            return;
        }
        atual = atual->prox;
    }
    printf("Chamada com número %d não encontrada.\n", numero);
}

void busca_binaria(Fila* f, int numero) {
    int tamanho = 0;
    Node* atual = f->inicio;
    while (atual != NULL) {
        tamanho++;
        atual = atual->prox;
    }

    if (tamanho == 0) {
        printf("Fila vazia.\n");
        return;
    }

    Chamada* array = (Chamada*)malloc(sizeof(Chamada) * tamanho);
    atual = f->inicio;
    for (int i = 0; i < tamanho; i++) {
        array[i] = atual->chamada;
        atual = atual->prox;
    }

    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (array[meio].numero == numero) {
            printf("Chamada encontrada: Número: %d | Dia: %s | Hora: %s\n", array[meio].numero, array[meio].dia, array[meio].hora);
            free(array);
            return;
        } else if (numero < array[meio].numero) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("Chamada com número %d não encontrada.\n", numero);
    free(array);
}

void liberar_fila(Fila* f) {
    while (!fila_vazia(f)) {
        remover_chamada(f);
    }
    free(f);
}

int main() {
    Fila* f = criar_fila();
    int opcao, numero;
    char dia[11], hora[6];

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar chamada\n");
        printf("2. Remover chamada\n");
        printf("3. Listar chamadas\n");
        printf("4. Ordenar chamadas\n");
        printf("5. Buscar chamada (linear)\n");
        printf("6. Buscar chamada (binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número: ");
                scanf("%d", &numero);
                printf("Digite o dia (dd/mm/aaaa): ");
                scanf("%s", dia);
                printf("Digite a hora (hh:mm): ");
                scanf("%s", hora);
                adicionar_chamada(f, numero, dia, hora);
                break;
            case 2:
                remover_chamada(f);
                break;
            case 3:
                imprimir_fila(f);
                break;
            case 4:
                ordenar_fila(f);
                printf("Chamadas ordenadas.\n");
                break;
            case 5:
                printf("Digite o número a buscar: ");
                scanf("%d", &numero);
                busca_linear(f, numero);
                break;
            case 6:
                ordenar_fila(f);
                printf("Digite o número a buscar: ");
                scanf("%d", &numero);
                busca_binaria(f, numero);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberar_fila(f);
    return 0;
}