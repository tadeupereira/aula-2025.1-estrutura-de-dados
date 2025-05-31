#ifndef UI_INCLUDED
#define UI_INCLUDED

#include "lista.h"

#define TITULO  30

void limparTela();
void pausar();
void titulo(const char *titulo);

int lerPrioridade();
int lerEscolha(int qtd);
void lerTarefa(Lista* lista);

void limparBuffer();

void telaHome(Lista* lista);
void telaVisualizar(Lista* lista);
void telaAdicionar(Lista* lista);
void telaRemover(Lista* lista);
void telaBuscaLinear(Lista* lista);
void telaBuscaBinaria(Lista* lista);

#endif // UI_INCLUDED
