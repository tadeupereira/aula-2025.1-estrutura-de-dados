#include "lista.h"

Lista* criarLista(){
    Lista* lista = (Lista *)malloc(sizeof(Lista));

    if (lista == NULL) {
        printf("Erro ao alocar memória para criar lista!\n");
        return NULL;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;

    return lista;
}

void limpar(Lista* lista){
    Tarefa *inicio = lista->inicio;

    while (inicio != NULL) {
        Tarefa *temp = inicio->prox;
        free(inicio);
        inicio = temp;
    }

    free(lista);
}

int vazia(const Lista* lista){
    if (lista == NULL) return 1;
    return lista->inicio == NULL;
}

int adicionarTarefa(Lista* lista, char titulo[50], char descricao[200], int prioridade){
    Tarefa* nova = (Tarefa*)malloc(sizeof(Tarefa));

    if (nova == NULL) {
        return 0;
    }

    strcpy(nova->titulo, titulo);
    strcpy(nova->descricao, descricao);
    nova->prioridade = prioridade;
    nova->prox = NULL;

    if(vazia(lista)){
        lista->inicio = nova;
    } else {
        lista->fim->prox = nova;
    }
    lista->qtd++;
    lista->fim = nova;
    return 1;
}

Tarefa removerTarefa(Lista* lista, int posicao){
    int i = 1;

    Tarefa *temp = lista->inicio;
    Tarefa *anterior = NULL;

    while (temp != NULL && i < posicao) {
        anterior = temp;
        temp = temp->prox;
        i++;
    }

    if (anterior == NULL) {
        lista->inicio = temp->prox;
    } else {
        anterior->prox = temp->prox;
    }

    if (temp == lista->fim){
        lista->fim = anterior;
    }

    lista->qtd--;

    Tarefa tarefa = *temp;
    free(temp);
    return tarefa;
}

void detalharTarefa(Tarefa *tarefa) {
    if(tarefa == NULL){
        printf("Tarefa não encontrada.");
        return;
    }
    printf("Título: %s\n", tarefa->titulo);
    printf("Descrição: %s\n", tarefa->descricao);
    printf("Prioridade: ");
    switch (tarefa->prioridade) {
        case 1: printf("Alta\n"); break;
        case 2: printf("Média\n"); break;
        case 3: printf("Baixa\n"); break;
    }
}

void visualizarLista(const Lista *lista){
    if(vazia(lista)) {
        printf("Sua lista está vazia.\n");
    }else {
        int i = 0;
        Tarefa* temp = lista->inicio;
        while(temp != NULL){
            if (i != 0) printf("------------------------------\n");
            i++;
            detalharTarefa(temp);
            temp = temp->prox;
        }
    }
}

void visualizacaoReduzida(const Lista *lista){
    if(vazia(lista)) {
        printf("Sua lista está vazia.\n");
    }else {
        int i = 0;
        Tarefa* temp = lista->inicio;
        while(temp != NULL){
            i++;
            printf("%d - %s\n", i, temp->titulo);
            temp = temp->prox;
        }
    }
}

void ordenarLista(Lista* lista, int (*comparar)(Tarefa*, Tarefa*)) {
    if (vazia(lista) || lista->inicio->prox == NULL) return;

    int trocou;
    do {
        trocou = 0;
        Tarefa *atual = lista->inicio;
        Tarefa *anterior = NULL;
        Tarefa *proximo = atual->prox;

        while (proximo != NULL) {
            if (comparar(atual, proximo) > 0) {
                if (anterior == NULL) {
                    lista->inicio = proximo;
                } else {
                    anterior->prox = proximo;
                }

                atual->prox = proximo->prox;
                proximo->prox = atual;

                anterior = proximo;
                proximo = atual->prox;

                trocou = 1;
            } else {
                anterior = atual;
                atual = proximo;
                proximo = proximo->prox;
            }
        }
    } while (trocou);

    Tarefa *temp = lista->inicio;
    while (temp->prox != NULL) {
        temp = temp->prox;
    }
    lista->fim = temp;
}

int compararPrioridade(Tarefa* a, Tarefa* b) {
    return a->prioridade - b->prioridade;
}

int compararTitulo(Tarefa* a, Tarefa* b) {
    return strcmp(a->titulo, b->titulo);
}

Tarefa* buscaLinear(Lista* lista, char titulo[50]) {
    if(vazia(lista)) return NULL;
    Tarefa* temp = lista->inicio;
    while(temp != NULL && temp->titulo != titulo){
        if (strcmp(temp->titulo, titulo) == 0) {
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
}

Tarefa** criarArray(Lista* lista) {
    if (vazia(lista)) return NULL;

    Tarefa** array = (Tarefa**)malloc(lista->qtd * sizeof(Tarefa*));
    if (array == NULL) {
        printf("Erro ao alocar memória para o array de tarefas!\n");
        return NULL;
    }

    Tarefa* atual = lista->inicio;
    int i = 0;
    while (atual != NULL && i < lista->qtd) {
        array[i] = atual;
        atual = atual->prox;
        i++;
    }

    return array;
}

Tarefa* buscaBinaria(Tarefa** array, int qtd, char titulo[50]) {
    if (array == NULL || qtd <= 0) return NULL;
    int esquerda = 0;
    int direita = qtd - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int comparacao = strcmp(array[meio]->titulo, titulo);

        if (comparacao == 0) {
            return array[meio];
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return NULL;
}
