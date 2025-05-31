#include "ui.h"

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    fgetc(stdin);
}

void titulo(const char *titulo){
    int larguraTotal = TITULO;
    int tamanhoTitulo = strlen(titulo);
    int espAnt, espDps;

    if (tamanhoTitulo >= larguraTotal) {
        tamanhoTitulo = larguraTotal - 2;
        espAnt = 1;
        espDps = 1;
    } else {
        espAnt = (larguraTotal - tamanhoTitulo) / 2;
        espDps = larguraTotal - tamanhoTitulo - espAnt;
    }

    for (int i = 0; i < larguraTotal; i++) {
        printf("=");
    }
    printf("\n");

    for (int i = 0; i < espAnt; i++) {
        printf(" ");
    }
    for (int i = 0; i < tamanhoTitulo; i++) {
        printf("%c", titulo[i]);
    }
    for (int i = 0; i < espDps; i++) {
        printf(" ");
    }
    printf("\n");

    for (int i = 0; i < larguraTotal; i++) {
        printf("=");
    }
    printf("\n");
}

int lerPrioridade(){
    int resultado, prioridade = 0;

    do{
        printf("Digite a prioridade (1 - Alta, 2 - Média, 3 - Baixa): ");
        resultado = scanf("%d", &prioridade);
        getchar();

        if (resultado != 1 || prioridade < 1 || prioridade > 3) {
            printf("Entrada inválida! Digite um número entre 1 e 3.\n");
            limparBuffer();
    }
    }while(prioridade < 1 || prioridade > 3);
    return prioridade;
}

int lerEscolha(int qtd){
    int resultado, escolha = 0;
    do{
        printf("Selecione o item desejado (Digite 0 para cancelar): ");
        resultado = scanf("%d", &escolha);
        getchar();

        if (resultado != 1 || escolha < 0 || escolha > qtd) {
            printf("Entrada inválida! Digite um número entre 0 e %d.\n", qtd);
            limparBuffer();
    }
    }while(escolha < 0 || escolha > qtd);
    return escolha;
}

void lerTarefa(Lista* lista){
    char titulo[50],  descricao[200];

    printf("Digite o título: ");
    fgets(titulo, 50, stdin);
    strtok(titulo, "\n");

    printf("Digite a descrição: ");
    fgets(descricao, 200, stdin);
    strtok(descricao, "\n");

    if(adicionarTarefa(lista, titulo, descricao, lerPrioridade())){
        printf("Tarefa adicionada com sucesso.");
    } else {
        printf("Erro ao alocar memória para criar nova tarefa!\n");
    }
}

void limparBuffer(){
    while (getchar() != '\n');
}

void telaHome(Lista* lista){
    int opcao;
    do {
        limparTela();
        titulo("GERENCIADOR DE TAREFAS");
        printf("1. Adicionar nova tarefa\n2. Visualizar todas as tarefas\n3. Remover uma tarefa\n4. Ordenar por Prioridade\n5. Ordenar por Título\n6. Busca Linear\n7. Busca Binária\n8. Sair\n");
        printf("==============================\n");

        opcao = lerEscolha(8);

        limparTela();

        switch(opcao) {
            case 1:
                telaAdicionar(lista);
                break;
            case 2:
                telaVisualizar(lista);
                break;
            case 3:
                telaRemover(lista);
                break;
            case 4:
                ordenarLista(lista, compararPrioridade);
                telaVisualizar(lista);
                break;
            case 5:
                ordenarLista(lista, compararTitulo);
                telaVisualizar(lista);
                break;
            case 6:
                telaBuscaLinear(lista);
                break;
            case 7:
                telaBuscaBinaria(lista);
                break;
            case 8:
                printf("Saindo...\n");
                limpar(lista);
                lista = NULL;
                break;
        }
        pausar();
    } while(opcao != 8);
}

void telaVisualizar(Lista* lista){
    titulo("LISTA DE TAREFAS");
    visualizarLista(lista);
}

void telaAdicionar(Lista* lista){
    titulo("ADICIONAR UMA TAREFA");
    lerTarefa(lista);
}

void telaRemover(Lista* lista){
    titulo("REMOVER UMA TAREFA");
    visualizacaoReduzida(lista);
    printf("==============================\n");
    if(!vazia(lista)) {
        int posicao = lerEscolha(lista->qtd);
        if(posicao != 0){
            Tarefa removida = removerTarefa(lista, posicao);
            printf("A tarefa %s foi removida com sucesso!\n", removida.titulo);
        } else {
            printf("A operação foi cancelada com sucesso!\n");
        }
    }
}

void telaBuscaLinear(Lista* lista){
    titulo("BUSCA LINEAR");
    char titulo[50];

    printf("Digite o título que deseja buscar: ");
    fgets(titulo, 50, stdin);
    strtok(titulo, "\n");
    printf("==============================\n");
    detalharTarefa(buscaLinear(lista, titulo));
}

void telaBuscaBinaria(Lista* lista){
    titulo("BUSCA BINÁRIA");
    char titulo[50];

    printf("Digite o título que deseja buscar: ");
    fgets(titulo, 50, stdin);
    strtok(titulo, "\n");

    printf("==============================\n");
    printf("ATENÇÃO: Para realizar a busca binária,\né necessário que as tarefas estejam\nordenadas em ordem alfabética pelo título.\n");
    printf("==============================\n");
    printf("Digite 1 para continuar ou 0 para cancelar.\n");
    int opcao = lerEscolha(1);
    printf("==============================\n");
    
    if(opcao){
        ordenarLista(lista, compararTitulo);
        detalharTarefa(buscaBinaria(criarArray(lista), lista->qtd, titulo));
    }   else {
        printf("A operação foi cancelada com sucesso!\n");
    }
}
