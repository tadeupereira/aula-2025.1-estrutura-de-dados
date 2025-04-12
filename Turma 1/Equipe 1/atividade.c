#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_maximo 100
#define tamanho_titulo 50
#define tamanho_descricao 100
#define tamanho_prioridade 10

typedef struct {
    char titulo[tamanho_titulo];
    char descricao[tamanho_descricao];
    char prioridade[tamanho_prioridade];
} tarefa;

tarefa minhas_tarefas[tamanho_maximo];
int quantidade_tarefas= 0;

void adicionar_tarefa(){
    if(quantidade_tarefas >= tamanho_maximo) {
        printf("Lista cheia.\n");
        return;
    }

    printf("Digite o título da sua tarefa: \n");
    fgets(minhas_tarefas[quantidade_tarefas].titulo, tamanho_titulo, stdin);
    minhas_tarefas[quantidade_tarefas].titulo[strcspn(minhas_tarefas[quantidade_tarefas].titulo, "\n")] = 0;

    printf("Digite a descrição da sua tarefa: \n");
    fgets(minhas_tarefas[quantidade_tarefas].descricao, tamanho_descricao, stdin);
    minhas_tarefas[quantidade_tarefas].descricao[strcspn(minhas_tarefas[quantidade_tarefas].descricao, "\n")] = 0;

    printf("Digite a prioridade: \n");
    fgets(minhas_tarefas[quantidade_tarefas].prioridade, tamanho_prioridade, stdin);
    minhas_tarefas[quantidade_tarefas].prioridade[strcspn(minhas_tarefas[quantidade_tarefas].prioridade, "\n")] = 0;

    quantidade_tarefas++;
    printf("Tarefa adicionada!\n");
}

void remover_tarefa(){
    int escolha;

    printf("Escolha a tarefa para ser removida (1 a %d): \n", quantidade_tarefas);
    scanf("%d", &escolha);
    getchar();
    escolha--; 

    if(escolha < 0 || escolha >= quantidade_tarefas){
        printf("Escolha inválida. Nenhuma tarefa removida\n");
        return;
    }

    for(int i = escolha; i < quantidade_tarefas - 1; i++){ 
        minhas_tarefas[i] = minhas_tarefas[i + 1];
    }

    quantidade_tarefas--;
    printf("Tarefa removida!\n");
}

void listar_tarefas(){
    if(quantidade_tarefas == 0){
        printf("Nenhuma tarefa cadastrada ainda.\n");
        return;
    }

    for(int i = 0; i < quantidade_tarefas; i++){
        printf("\n[%d] Título: %s\n", i + 1, minhas_tarefas[i].titulo);
        printf("Descrição: %s\n", minhas_tarefas[i].descricao);
        printf("Prioridade: %s\n", minhas_tarefas[i].prioridade);
    }
}

int main(){
    int opcao;

    while(1){
        printf("\n==========MENU==========\n");
        printf("1. Adicionar nova tarefa.\n");
        printf("2. Remover tarefa.\n");
        printf("3. Listar todas as tarefas.\n");
        printf("0. Encerrar programa.\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 1){
            adicionar_tarefa();
        } else if(opcao == 2){
            remover_tarefa();
        } else if(opcao == 3){
            listar_tarefas();
        } else if(opcao == 0){
            printf("Desligando programa...\n");
            break;
        } else {
            printf("Opção inválida. Escolha novamente\n");
        }
    }
}
