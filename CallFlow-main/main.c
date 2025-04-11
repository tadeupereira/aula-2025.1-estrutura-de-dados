#include <ncurses.h>
#include <string.h>
#include "fila.h"
#include "validacoes.h"

void inputSeguro(char *destino, int tamanho) {
    echo();
    wgetnstr(stdscr, destino, tamanho - 1);
    noecho();
}

int main() {
    FilaChamadas fila;
    inicializarFila(&fila);

    initscr();
    start_color();
    use_default_colors();

    init_pair(1, COLOR_MAGENTA, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_CYAN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_BLUE, -1);

    bkgd(COLOR_PAIR(1));
    char titulo[] = "CallFlow";
    int linha = LINES / 2 - 1;
    int coluna = COLS / 2 - strlen(titulo) / 2;

    for (int i = 0; i < strlen(titulo); i++) {
        attron(COLOR_PAIR((i % 5) + 1));
        mvprintw(linha, coluna + i, "%c", titulo[i]);
        attroff(COLOR_PAIR((i % 5) + 1));
        refresh();
        usleep(200000);
    }

    getch();

    int opcao;
    Chamada novaChamada;

    do {
        clear();
        mvprintw(0, 0, "Sistema de Gerenciamento de Chamadas");
        mvprintw(2, 0, "1. Adicionar chamada");
        mvprintw(3, 0, "2. Remover chamada");
        mvprintw(4, 0, "3. Listar chamadas");
        mvprintw(5, 0, "0. Sair");
        mvprintw(7, 0, "Escolha uma opção: ");
        refresh();

        opcao = getch() - '0';

        switch (opcao) {
            case 1:
                clear();
                mvprintw(0, 0, "Digite o número: ");
                inputSeguro(novaChamada.numero, sizeof(novaChamada.numero));

                mvprintw(1, 0, "Digite o nome: ");
                inputSeguro(novaChamada.nome, sizeof(novaChamada.nome));

                while (1) {
                    mvprintw(2, 0, "Digite o dia (DD/MM/AAAA): ");
                    inputSeguro(novaChamada.dia, sizeof(novaChamada.dia));
                    if (validarData(novaChamada.dia)) break;
                    mvprintw(LINES - 2, 0, "Data inválida. Tente novamente.");
                    getch(); clear();
                }

                while (1) {
                    mvprintw(3, 0, "Digite o horário (HH:MM): ");
                    inputSeguro(novaChamada.horario, sizeof(novaChamada.horario));
                    if (validarHorario(novaChamada.horario)) break;
                    mvprintw(LINES - 2, 0, "Horário inválido. Tente novamente.");
                    getch(); clear();
                }

                adicionarChamada(&fila, novaChamada);
                break;

            case 2: removerChamada(&fila); break;
            case 3: listarChamadas(&fila); break;
            case 0: mvprintw(LINES - 2, 0, "Saindo..."); refresh(); break;
            default:
                mvprintw(LINES - 2, 0, "Opção inválida.");
                refresh();
                getch();
        }
    } while (opcao != 0);

    endwin();
    return 0;
}