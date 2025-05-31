#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  


#define TAMANHO_INICIAL_FILA 5


typedef struct {
    int id;               
    char tipo[20];        
    char numero[20];       
    char dataHora[50];     
    char descricao[100];   
} Chamada;


typedef struct {
    Chamada* chamadas;     
    int frente;           
    int tras;              
    int capacidade;        
    int tamanhoAtual;      
} Fila;


void inicializarFila(Fila* fila) {
    fila->chamadas = (Chamada*)malloc(TAMANHO_INICIAL_FILA * sizeof(Chamada));
    if (fila->chamadas == NULL) {
        printf("Erro ao alocar memória para a fila. Encerrando o programa.\n");
        exit(EXIT_FAILURE); 
    }
    fila->frente = 0;
    fila->tras = 0;
    fila->capacidade = TAMANHO_INICIAL_FILA;
    fila->tamanhoAtual = 0;
    printf("Fila inicializada com capacidade %d.\n", TAMANHO_INICIAL_FILA);
}


void liberarFila(Fila* fila) {
    if (fila->chamadas != NULL) {
        free(fila->chamadas);
        fila->chamadas = NULL;
        printf("Memoria da fila liberada.\n");
    }
}


int estaVazia(Fila fila) {
    return fila.tamanhoAtual == 0;
}


int estaCheia(Fila fila) {
    return fila.tamanhoAtual == fila.capacidade;
}


void limparTerminal() {
#ifdef _WIN32
    system("cls"); 
#else
    system("clear"); 
#endif
}


Fila redimensionarFila(Fila fila) {
    int novaCapacidade = fila.capacidade * 2;
    Chamada* novoArray = (Chamada*)malloc(novaCapacidade * sizeof(Chamada));
    if (novoArray == NULL) {
        printf("Erro ao realocar memória para a fila. Encerrando o programa.\n");
        exit(EXIT_FAILURE);
    }

    
    for (int i = 0; i < fila.tamanhoAtual; i++) {
        novoArray[i] = fila.chamadas[(fila.frente + i) % fila.capacidade];
    }

    free(fila.chamadas);

    fila.chamadas = novoArray; 
    fila.frente = 0;           
    fila.tras = fila.tamanhoAtual; 
    fila.capacidade = novaCapacidade; 

    printf("Fila redimensionada para capacidade %d\n", fila.capacidade);
    return fila;
}


Fila adicionarChamada(Fila fila, int id, const char* tipo, const char* numero, const char* dataHora, const char* descricao) {
    if (estaCheia(fila)) {
        fila = redimensionarFila(fila); 
    }

    Chamada novaChamada;
    novaChamada.id = id;
    
    strncpy(novaChamada.tipo, tipo, sizeof(novaChamada.tipo) - 1);
    novaChamada.tipo[sizeof(novaChamada.tipo) - 1] = '\0'; 

    strncpy(novaChamada.numero, numero, sizeof(novaChamada.numero) - 1);
    novaChamada.numero[sizeof(novaChamada.numero) - 1] = '\0';

    strncpy(novaChamada.dataHora, dataHora, sizeof(novaChamada.dataHora) - 1);
    novaChamada.dataHora[sizeof(novaChamada.dataHora) - 1] = '\0';

    strncpy(novaChamada.descricao, descricao, sizeof(novaChamada.descricao) - 1);
    novaChamada.descricao[sizeof(novaChamada.descricao) - 1] = '\0';

    
    fila.chamadas[fila.tras] = novaChamada;
    fila.tras = (fila.tras + 1) % fila.capacidade; 
    fila.tamanhoAtual++; 

    printf("Chamada %d adicionada na fila: %s - %s - %s\n", id, tipo, numero, dataHora);
    return fila;
}


Fila removerChamada(Fila fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia, nao ha chamadas para remover\n");
        return fila;
    }

    int idRemover;
    printf("Digite o id da chamada que deseja remover: ");
    
    if (scanf("%d", &idRemover) != 1) {
        printf("Entrada invalida. Digite um numero para o ID.\n");
        while (getchar() != '\n'); 
        return fila;
    }
    getchar(); 

    int encontrado = 0;
    int indiceDaChamadaParaRemover = -1; 

    
    for (int i = 0; i < fila.tamanhoAtual; i++) {
        int idx = (fila.frente + i) % fila.capacidade;
        if (fila.chamadas[idx].id == idRemover) {
            indiceDaChamadaParaRemover = i; 
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        
        Chamada* tempArray = (Chamada*)malloc((fila.tamanhoAtual - 1) * sizeof(Chamada));
        if (tempArray == NULL) {
            printf("Erro ao alocar memória temporaria para remocao. Encerrando o programa.\n");
            exit(EXIT_FAILURE);
        }

        int count = 0;
        
        for (int i = 0; i < fila.tamanhoAtual; i++) {
            if (i != indiceDaChamadaParaRemover) {
                tempArray[count++] = fila.chamadas[(fila.frente + i) % fila.capacidade];
            }
        }
        
        free(fila.chamadas); 
        fila.chamadas = tempArray; 

        
        fila.frente = 0;
        fila.tras = count;
        fila.tamanhoAtual = count;
        
        fila.capacidade = fila.tamanhoAtual > 0 ? fila.tamanhoAtual : TAMANHO_INICIAL_FILA; 
        
        printf("Chamada com id %d removida da fila\n", idRemover);
    } else {
        printf("Chamada com id %d nao encontrada na fila\n", idRemover);
    }
    printf("\nPressione Enter para continuar...\n");
    getchar(); 
    return fila;
}


int compararChamadasPorNumero(const void* a, const void* b) {
    Chamada* chamadaA = (Chamada*)a;
    Chamada* chamadaB = (Chamada*)b;
    return strcmp(chamadaA->numero, chamadaB->numero);
}


void ordenarChamadas(Fila* fila) {
    if (estaVazia(*fila)) {
        printf("Fila vazia, nao ha chamadas para ordenar.\n");
        return;
    }
    
    
    Chamada* tempArray = (Chamada*)malloc(fila->tamanhoAtual * sizeof(Chamada));
    if (tempArray == NULL) {
        printf("Erro ao alocar memória temporaria para ordenacao. Encerrando o programa.\n");
        exit(EXIT_FAILURE);
    }

   
    for (int i = 0; i < fila->tamanhoAtual; i++) {
        tempArray[i] = fila->chamadas[(fila->frente + i) % fila->capacidade];
    }

  
    qsort(tempArray, fila->tamanhoAtual, sizeof(Chamada), compararChamadasPorNumero);

    
    for (int i = 0; i < fila->tamanhoAtual; i++) {
        fila->chamadas[i] = tempArray[i];
    }
    fila->frente = 0; 
    fila->tras = fila->tamanhoAtual; 

    free(tempArray); 
    printf("Chamadas ordenadas por numero de telefone.\n");
}


void buscarChamadaLinear(Fila fila, const char* numeroBusca) {
    if (estaVazia(fila)) {
        printf("Fila vazia, nao ha chamadas para buscar.\n");
        return;
    }

    int encontrado = 0;
    printf("Resultados da busca linear por numero '%s':\n", numeroBusca);
    
    for (int i = 0; i < fila.tamanhoAtual; i++) {
        if (strcmp(fila.chamadas[i].numero, numeroBusca) == 0) {
            printf("ID: %d - Tipo: %s - Numero: %s - Data e Hora: %s\n",
                   fila.chamadas[i].id, fila.chamadas[i].tipo, fila.chamadas[i].numero, fila.chamadas[i].dataHora);
            printf("Descricao: %s\n", fila.chamadas[i].descricao);
            printf("------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhuma chamada encontrada com o numero '%s'.\n", numeroBusca);
    }
}


void buscarChamadaBinaria(Fila fila, const char* numeroBusca) {
    if (estaVazia(fila)) {
        printf("Fila vazia, nao ha chamadas para buscar.\n");
        return;
    }

    printf("Resultados da busca binaria por numero '%s':\n", numeroBusca);

    int baixo = 0;
    int alto = fila.tamanhoAtual - 1;
    int encontrado = 0;

   
    while (baixo <= alto) {
        int meio = baixo + (alto - baixo) / 2; 
        int comparacao = strcmp(fila.chamadas[meio].numero, numeroBusca);

        if (comparacao == 0) {
            
            for (int i = meio; i >= 0 && strcmp(fila.chamadas[i].numero, numeroBusca) == 0; i--) {
                printf("ID: %d - Tipo: %s - Numero: %s - Data e Hora: %s\n",
                       fila.chamadas[i].id, fila.chamadas[i].tipo, fila.chamadas[i].numero, fila.chamadas[i].dataHora);
                printf("Descricao: %s\n", fila.chamadas[i].descricao);
                printf("------------------------\n");
                encontrado = 1;
            }
            
            for (int i = meio + 1; i < fila.tamanhoAtual && strcmp(fila.chamadas[i].numero, numeroBusca) == 0; i++) {
                printf("ID: %d - Tipo: %s - Numero: %s - Data e Hora: %s\n",
                       fila.chamadas[i].id, fila.chamadas[i].tipo, fila.chamadas[i].numero, fila.chamadas[i].dataHora);
                printf("Descricao: %s\n", fila.chamadas[i].descricao);
                printf("------------------------\n");
                encontrado = 1;
            }
            break; 
        } else if (comparacao < 0) {
            baixo = meio + 1; 
        } else {
            alto = meio - 1; 
        }
    }

    if (!encontrado) {
        printf("Nenhuma chamada encontrada com o numero '%s'.\n", numeroBusca);
    }
}


void listarChamadas(Fila fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia, nao ha chamadas para listar\n");
        return;
    }

    printf("Chamadas na fila (%d de %d):\n", fila.tamanhoAtual, fila.capacidade);
    
    for (int i = 0; i < fila.tamanhoAtual; i++) {
        printf("ID: %d - Tipo: %s - Numero: %s - Data e Hora: %s\n",
               fila.chamadas[i].id, fila.chamadas[i].tipo, fila.chamadas[i].numero, fila.chamadas[i].dataHora);
        printf("Descricao: %s\n", fila.chamadas[i].descricao);
        printf("------------------------\n");
    }
}


void exibirMenu() {
    printf("=================================\n");
    printf("     Sistema de Gerenciamento    \n");
    printf("        de Chamadas Telefonicas  \n");
    printf("=================================\n");
    printf("1. Adicionar uma chamada\n");
    printf("2. Remover uma chamada (por ID)\n");
    printf("3. Listar todas as chamadas\n");
    printf("4. Ordenar chamadas por numero\n");
    printf("5. Buscar chamada por numero (Linear)\n");
    printf("6. Buscar chamada por numero (Binaria)\n");
    printf("7. Sair\n");
    printf("=================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Fila fila;                 
    inicializarFila(&fila);    

    int opcao;                 
    int id = 1;                
    char tipo[20];             
    char numero[20];           
    char dataHora[50];         
    char descricao[100];       
    char numeroBusca[20];      

    
    do {
        exibirMenu();      
        scanf("%d", &opcao); 
        getchar();         

        limparTerminal();  

        switch (opcao) {
            case 1: 
                
                do {
                    printf("Digite o tipo da chamada (feita ou recebida): ");
                    fgets(tipo, sizeof(tipo), stdin);
                    tipo[strcspn(tipo, "\n")] = 0; 
                    if (strlen(tipo) == 0) {
                        printf("O tipo da chamada nao pode ser vazio. Por favor, digite novamente.\n");
                    }
                } while (strlen(tipo) == 0);

               
                do {
                    printf("Digite o numero de telefone: ");
                    fgets(numero, sizeof(numero), stdin);
                    numero[strcspn(numero, "\n")] = 0;
                    if (strlen(numero) == 0) {
                        printf("O numero de telefone nao pode ser vazio. Por favor, digite novamente.\n");
                    }
                } while (strlen(numero) == 0);

                
                int dia, mes, ano, hora, minuto;
                int valid_datetime = 0;
                do {
                    printf("Digite a data e hora da chamada (dd/mm/aaaa hh:mm): ");
                    fgets(dataHora, sizeof(dataHora), stdin);
                    dataHora[strcspn(dataHora, "\n")] = 0; 

                    
                    if (sscanf(dataHora, "%d/%d/%d %d:%d", &dia, &mes, &ano, &hora, &minuto) == 5) {
                        
                        valid_datetime = 1;
                    } else {
                        printf("Formato de data e hora invalido. Use dd/mm/aaaa hh:mm. Por favor, digite novamente.\n");
                    }
                } while (!valid_datetime);

           
                printf("Digite uma descricao para a chamada (opcional): ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0;

                fila = adicionarChamada(fila, id++, tipo, numero, dataHora, descricao);
                break;

            case 2: 
                fila = removerChamada(fila);
                break;

            case 3:
                listarChamadas(fila);
                break;

            case 4: 
                ordenarChamadas(&fila); 
                break;

            case 5: 
                do {
                    printf("Digite o numero de telefone para busca linear: ");
                    fgets(numeroBusca, sizeof(numeroBusca), stdin);
                    numeroBusca[strcspn(numeroBusca, "\n")] = 0;
                    if (strlen(numeroBusca) == 0) {
                        printf("O numero para busca nao pode ser vazio. Por favor, digite novamente.\n");
                    }
                } while (strlen(numeroBusca) == 0);
                buscarChamadaLinear(fila, numeroBusca);
                break;

            case 6: 
                printf("Para a busca binaria funcionar corretamente, as chamadas devem estar ordenadas por numero.\n");
                printf("Se ainda nao ordenou, por favor, use a opcao 4 primeiro.\n");
                
                do {
                    printf("Digite o numero de telefone para busca binaria: ");
                    fgets(numeroBusca, sizeof(numeroBusca), stdin);
                    numeroBusca[strcspn(numeroBusca, "\n")] = 0;
                    if (strlen(numeroBusca) == 0) {
                        printf("O numero para busca nao pode ser vazio. Por favor, digite novamente.\n");
                    }
                } while (strlen(numeroBusca) == 0);
                buscarChamadaBinaria(fila, numeroBusca);
                break;

            case 7: 
                printf("Saindo do sistema...\n");
                break;

            default: 
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        
        if (opcao != 7) {
            printf("\nPressione Enter para voltar ao menu...\n");
            getchar(); 
            limparTerminal();
        }

    } while (opcao != 7);

    liberarFila(&fila);
    return 0; 
}