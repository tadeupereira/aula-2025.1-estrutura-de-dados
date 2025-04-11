#include <ncurses.h>
#include <string.h>
#include "fila.h"

void inicializarFila(FilaChamadas *fila) {
    fila->frente = -1;
    fila->tras = -1;
}

int filaVazia(FilaChamadas *fila) {
    return fila->frente == -1;
}

int filaCheia(FilaChamadas *fila) {
    return (fila->tras + 1) % MAX_CHAMADAS == fila->frente;
}

void adicionarChamada(FilaChamadas *fila, Chamada chamada) {
    if (filaCheia(fila)) {
        mvprintw(LINES - 2, 0, "Fila cheia.");
        refresh(); getch(); return;
    }

    if (filaVazia(fila)) fila->frente = 0;

    fila->tras = (fila->tras + 1) % MAX_CHAMADAS;
    fila->chamadas[fila->tras] = chamada;

    mvprintw(LINES - 2, 0, "Chamada adicionada.");
    refresh(); getch();
}

int selecionarChamada(FilaChamadas *fila) {
    if (filaVazia(fila)) return -1;

    clear(); mvprintw(0, 0, "Selecione a chamada:");

    int i = fila->frente;
    int linha = 2;
    do {
        mvprintw(linha, 0, "%d. Nome: %s, Número: %s, Dia: %s, Horário: %s",
            linha - 2, fila->chamadas[i].nome, fila->chamadas[i].numero,
            fila->chamadas[i].dia, fila->chamadas[i].horario);
        i = (i + 1) % MAX_CHAMADAS;
        linha++;
    } while (i != (fila->tras + 1) % MAX_CHAMADAS);

    mvprintw(linha, 0, "Número da chamada: ");
    refresh();

    int selecao;
    echo();
    scanw("%d", &selecao);
    noecho();

    return (selecao >= 0 && selecao < linha - 2) ? selecao : -1;
}

void removerChamada(FilaChamadas *fila) {
    int selecao = selecionarChamada(fila);
    if (selecao == -1) {
        mvprintw(LINES - 2, 0, "Seleção inválida.");
        refresh(); getch(); return;
    }

    int indice = (fila->frente + selecao) % MAX_CHAMADAS;
    if (fila->frente == fila->tras) {
        inicializarFila(fila);
    } else if (indice == fila->frente) {
        fila->frente = (fila->frente + 1) % MAX_CHAMADAS;
    } else {
        int i = indice;
        while (i != fila->tras) {
            fila->chamadas[i] = fila->chamadas[(i + 1) % MAX_CHAMADAS];
            i = (i + 1) % MAX_CHAMADAS;
        }
        fila->tras = (fila->tras - 1 + MAX_CHAMADAS) % MAX_CHAMADAS;
    }

    mvprintw(LINES - 2, 0, "Chamada removida.");
    refresh(); getch();
}

void listarChamadas(FilaChamadas *fila) {
    if (filaVazia(fila)) {
        mvprintw(LINES - 2, 0, "Fila vazia.");
        refresh(); getch(); return;
    }

    clear(); mvprintw(0, 0, "Chamadas:");
    int i = fila->frente, linha = 2;
    do {
        mvprintw(linha++, 0, "Nome: %s, Número: %s, Dia: %s, Horário: %s",
            fila->chamadas[i].nome, fila->chamadas[i].numero,
            fila->chamadas[i].dia, fila->chamadas[i].horario);
        i = (i + 1) % MAX_CHAMADAS;
    } while (i != (fila->tras + 1) % MAX_CHAMADAS);
    refresh(); getch();
}