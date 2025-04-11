#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CLIENTES 50
#define MAX_TAMANHO_NOME 50

typedef struct {

    char clientes[MAX_CLIENTES][MAX_TAMANHO_NOME]; 
    int incio_da_fila, final_da_fila;

} Fila;

void criarFila(Fila *f) {

    f->final_da_fila = 0; 
    f->incio_da_fila = 0;

}

int filaEstaVazia(Fila *f) {

    return f->incio_da_fila == f->final_da_fila;

}

int filaEstaCheia(Fila *f) {

    return f->final_da_fila == MAX_CLIENTES; 
}

void adicionarNaFila(Fila *f, const char *cliente) {

    if (filaEstaCheia(f)) {
        printf("\033[1;37;41m(!) A Fila esta cheia\n");
        return;
    } 
    
    strncpy(f->clientes[f->final_da_fila], cliente, MAX_TAMANHO_NOME - 1);
    f->final_da_fila++;

    printf("\033[1;37;42m (!) Cliente %s acidionado a fila com sucesso\033[m\n", cliente);

}

char* removerDaFila(Fila *f) {
    if (filaEstaVazia(f)) {
        printf("\033[1;37;41m (!) Nao e possivel remover clientes porque a fila esta vazia\033[m\n");

        return NULL;

    } else {
        char *cliente = f->clientes[f->incio_da_fila];
        f->incio_da_fila++;
        
        return cliente;

    }
}

void exibirClientes (Fila *f) {
    if (filaEstaVazia(f)) {
        printf("\033[1;37;41m(!) Nao e possivel exibir clientes porque a fila esta vazia\033[m\n");
    }

    printf("==========================\n");
    printf("    CLIENTES NA LISTA     \n");
    printf("==========================\n");

    for (int i = f->incio_da_fila; i < f->final_da_fila; i++) {
        printf(" - %s\n", f->clientes[i]);
    }
    
}

int main () {

    Fila s_fila;

    int opcao;
    char nome_cliente[50], confirmar_remocao, confirmar_encerramento;

    criarFila(&s_fila);

    while (1) {
        printf("==========================\n");
        printf("           MENU           \n");
        printf("==========================\n");

        printf("[ 1 ] Adicionar cliente\n");
        printf("[ 2 ] Remover cliente\n");
        printf("[ 3 ] Listar Clientes\n");
        printf("[ 4 ] Encerrar Programa\n");

        printf("==========================\n");

        printf("Qual opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                printf("(!) Digite \"!\" para cancelar a acao\n");

                printf("Nome do cliente: ");
                fgets(nome_cliente, sizeof(nome_cliente), stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';

                if (nome_cliente[0] == '!') {
                    break;
                } 
    
                adicionarNaFila(&s_fila, nome_cliente);            

                break;            
            } case 2: {
                while (1) {
                    printf("Deseja mesmo remover um cliente? [S/N]: ");
                    scanf("%c", &confirmar_remocao);
                    getchar();

                    confirmar_remocao = tolower(confirmar_remocao);

                    if (confirmar_remocao == 's' || confirmar_remocao == 'n'){
                        if (confirmar_remocao == 's') {
                            char *confirma_remocao = removerDaFila(&s_fila);
                            if (confirma_remocao != NULL) {
                                printf("\033[1;30;42m    (!) Cliente %s removido com sucesso    \033[m\n", confirma_remocao);
                            }
                        } 

                        break;
                    } else {
                        printf("\033[1;30;41m    (!) Insira uma opcao valida    \033[m\n");
                    }
                }

                break;
            } case 3: {
                exibirClientes(&s_fila);            
                break;
            } case 4: {
                printf("Tem certeza que deseja encerrar?[S/N]: ");
                scanf("%c", &confirmar_encerramento);
                getchar();

                confirmar_encerramento = tolower(confirmar_encerramento);

                if (confirmar_encerramento == 's' || confirmar_encerramento == 'n') {
                    if (confirmar_encerramento == 's') {
                        printf("\033[1;30;41m   >>> (!) Programa encerrado <<<  \033[m\n");
                    } 
                }

                break;
            } default: {
                printf("\033[1;30;41m    (!) Insira uma opcao valida do menu    \033[m\n");
            }
        }

        if ((opcao == 4) && (confirmar_encerramento == 's')) {
            break;
        }
    }

    return 0;

}

