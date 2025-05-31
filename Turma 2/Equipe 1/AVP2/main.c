#include <locale.h>

#include "lista.h"
#include "ui.h"

int main() {
    setlocale(LC_ALL, "");

    Lista* lista = criarLista();

    telaHome(lista);
    lista = NULL;
    return 0;
}
