#ifndef PILHA_INCLUDED
#define PILHA_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarefa{
    char titulo[50];
    char descricao[200];
    int prioridade;
    struct tarefa* prox;
} Tarefa;

typedef struct {
    int qtd;
    Tarefa *inicio;
    Tarefa *fim;
} Lista;

Lista* criarLista();
void limpar(Lista* lista);
int vazia(const Lista* lista);
int adicionarTarefa(Lista* lista, char titulo[50], char descricao[200], int prioridade);
Tarefa removerTarefa(Lista* lista, int posicao);

void detalharTarefa(Tarefa *tarefa);
void visualizarLista(const Lista *lista);
void visualizacaoReduzida(const Lista *lista);

void ordenarLista(Lista* lista, int (*comparar)(Tarefa*, Tarefa*));
int compararPrioridade(Tarefa* a, Tarefa* b);
int compararTitulo(Tarefa* a, Tarefa* b);
Tarefa* buscaLinear(Lista* lista, char titulo[50]);
Tarefa** criarArray(Lista* lista);
Tarefa* buscaBinaria(Tarefa** array, int tamanho, char titulo[50]);

#endif // PILHA_INCLUDED
