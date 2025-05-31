#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_SIZE 50

typedef struct {
    char name[MAX_NAME_SIZE];
    char cpf[14];
    int priority;
} client;

typedef struct node {
    client client;
    struct node *next;
} node;

typedef struct queue {
    node *first;
    node *last;
} queue;

queue *create_queue() {
    queue *f = malloc(sizeof(queue));
    if (f != NULL) {
        f->first = NULL;
        f->last = NULL;
    }
    return f;
}

int is_empty(queue *f) {
    return f->first == NULL;
}

void order(queue *f) {
    if (f->first == NULL || f->first->next == NULL)
        return;

    node *order = NULL;
    node *current = f->first;

    while (current != NULL) {
        node *next = current->next;

        if (order == NULL || current->client.priority < order->client.priority) {
            current->next = order;
            order = current;
        } else {
            node *temp = order;
            while (temp->next != NULL && temp->next->client.priority <= current->client.priority) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    f->first = order;

    node *last_node = order;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    f->last = last_node;
}

void clear_queue(queue *f) {
    node *current = f->first;
    while (current != NULL) {
        node *clear = current;
        current = current->next;
        free(clear);
    }
    free(f);
}

void add_queue(queue *f, char *name, char *cpf, int priority) {
    client c;
    strncpy(c.name, name, MAX_NAME_SIZE);
    strncpy(c.cpf, cpf, sizeof(c.cpf));
    c.priority = priority;

    node *new_node = malloc(sizeof(node));
    new_node->client = c;
    new_node->next = NULL;

    if (is_empty(f)) {
        f->first = new_node;
    } else {
        f->last->next = new_node;
    }
    f->last = new_node;

    order(f);
}

node *remove_queue(queue *f) {
    node *removed = f->first;
    f->first = f->first->next;

    if (f->first == NULL) {
        f->last = NULL;
    }
    removed->next = NULL;
    return removed;
}

void list_queue(queue *f) {
    node *current = f->first;

    while (current != NULL) {
        printf("Nome: %s\n", current->client.name);
        printf("CPF: %s\n", current->client.cpf);
        printf("Prioridade: %d\n", current->client.priority);
        printf("----------------------------------\n");

        current = current->next;
    }
}

node *search_linear(queue *f, char *name_client) {
    node *current = f->first;

    while (current != NULL) {
        if (strcmp(current->client.name, name_client) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int compare_by_name(const void *a, const void *b) {
    node *nodeA = *(node **)a;
    node *nodeB = *(node **)b;
    return strcmp(nodeA->client.name, nodeB->client.name);
}

node *binary_search_by_name(queue *f, char *name) {
    int count = 0;
    node *current = f->first;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (count == 0) return NULL;

    node **array = malloc(count * sizeof(node *));
    current = f->first;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    qsort(array, count, sizeof(node *), compare_by_name);

    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(array[mid]->client.name, name);
        if (cmp == 0) {
            node *result = array[mid];
            free(array);
            return result;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    free(array);
    return NULL;
}

int main() {
    queue *queue_fila = NULL;
    char name_client[50];
    char cpf[14];
    int priority;

    int option;

    while (1) {
        printf("\n==========================\n");
        printf("           MENU           \n");
        printf("==========================\n");

        printf("[ 1 ] Criar Fila\n");
        printf("[ 2 ] Adicionar cliente\n");
        printf("[ 3 ] Remover cliente\n");
        printf("[ 4 ] Listar Clientes\n");
        printf("[ 5 ] Busca Linear pelo nome\n");
        printf("[ 6 ] Busca Binaria pelo nome\n");
        printf("[ 7 ] Encerrar Fila\n");

        printf("==========================\n");

        printf("\nSelecione a opcao: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
        case 1:
            if (queue_fila != NULL) {
                printf("Fila já foi criada.\n");
            } else {
                queue_fila = create_queue();
                printf("Fila criada com sucesso\n");
            }
            break;
        case 2:
            if (queue_fila == NULL) {
                printf("Fila ainda não foi criada.\n");
                break;
            }

            printf("\nInforme o nome do cliente: ");
            fgets(name_client, sizeof(name_client), stdin);
            name_client[strcspn(name_client, "\n")] = '\0';

            printf("Informe o cpf do cliente: ");
            fgets(cpf, sizeof(cpf), stdin);
            cpf[strcspn(cpf, "\n")] = '\0';

            printf("Informe a prioridade no atendimento: ");
            scanf("%d", &priority);
            getchar();

            add_queue(queue_fila, name_client, cpf, priority);
            break;
        case 3:
            if (queue_fila == NULL || is_empty(queue_fila)) {
                printf("Não há clientes para remover!\n");
            } else {
                node *removed = remove_queue(queue_fila);
                printf("Cliente %s removido com sucesso.\n", removed->client.name);
                free(removed);
            }
            break;
        case 4:
            if (queue_fila == NULL || is_empty(queue_fila)) {
                printf("Nao ha clientes na fila\n");
            } else {
                printf("\n------ Lista de clientes ------\n");
                list_queue(queue_fila);
            }
            break;
        case 5:
            if (queue_fila == NULL) {
                printf("Fila ainda não foi criada.\n");
                break;
            }

            printf("\nInforme o nome do cliente que deseja buscar: ");
            fgets(name_client, sizeof(name_client), stdin);
            name_client[strcspn(name_client, "\n")] = '\0';

            {
                node *searched = search_linear(queue_fila, name_client);

                if (searched != NULL) {
                    printf("\nCliente encontrado\n");
                    printf("Nome: %s\n", searched->client.name);
                    printf("CPF: %s\n", searched->client.cpf);
                    printf("Prioridade: %d\n", searched->client.priority);
                } else {
                    printf("\nCliente não encontrado.\n");
                }
            }
            break;
        case 6:
            if (queue_fila == NULL) {
                printf("Fila ainda não foi criada.\n");
                break;
            }

            printf("\nInforme o nome do cliente que deseja buscar (binária): ");
            fgets(name_client, sizeof(name_client), stdin);
            name_client[strcspn(name_client, "\n")] = '\0';

            {
                node *searched_bin = binary_search_by_name(queue_fila, name_client);

                if (searched_bin != NULL) {
                    printf("\nCliente encontrado (busca binária)\n");
                    printf("Nome: %s\n", searched_bin->client.name);
                    printf("CPF: %s\n", searched_bin->client.cpf);
                    printf("Prioridade: %d\n", searched_bin->client.priority);
                } else {
                    printf("\nCliente não encontrado (busca binária).\n");
                }
            }
            break;
        case 7:
            printf("\nEncerrando programa... limpando fila.\n");
            if (queue_fila != NULL) {
                clear_queue(queue_fila);
                queue_fila = NULL;
            }
            exit(0);
        default:
            printf("Opção inválida.\n");
        }
    }

    return 0;
}
