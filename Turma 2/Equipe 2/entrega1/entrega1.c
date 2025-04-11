#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void VerClientes();

void ClientesDefinidos();
void ClientesIndefinidos();

void AdicionarClientes();
void RemoverClientes();

struct clientes {char nome[20]; char cpf[12]; char prioridade[10];};
struct clientes fila[100];

int fim = 0;

int main(){
	char input[10];
	unsigned short int escolha;
	while(true){
		puts("\n\033[1;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[m");
		puts("\033[1;34m     GERENCIADOR DE ATENDIMENTOS\033[m");
		puts("\033[1;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[m");
		puts("\033[1m\tSELECIONE UMA OPÇÃO\033[m");
		puts("-----------------------------------");
		puts("\033[32m[1] Ver Clientes");
		puts("[2] Adicionar Clientes");
		puts("[3] Remover Clientes\033[m");
		puts("\033[31m[0] Sair\033[m");
		puts("-----------------------------------");
		printf("\033[1m>\033[m ");
		scanf("%hu" , &escolha);
		switch (escolha){
			case 1:
				VerClientes();
				break;
			case 2:
				AdicionarClientes();
				break;
			case 3:
				RemoverClientes();
				break;
			case 0:
				puts("Programa encerrado.");
				return 0;
			default:
				puts("Opção inválida, tente novamente:\n");
				break;
		}
	}
}

void VerClientes(){
	if(fim == 0){
		puts("\n\033[1;31mNenhum cliente definido!\033[m");
	}
	else{
		for(int i = 0; i < fim; i++){
			puts("----------------------------");
			printf("\033[1;35mID:\033[m %d\n" , i + 1);
			printf("\033[1;35mNome:\033[m %s\n" , fila[i].nome);
			printf("\033[1;35mCPF:\033[m %s\n" , fila[i].cpf);
			printf("\033[1;35mPrioridade:\033[m %s\n" , fila[i].prioridade);
			puts("----------------------------");
		}
	}
}

void AdicionarClientes(){
	unsigned short int escolha;
	while(true){
		puts("-------------------------------------------");
		puts("\033[32m[1] Adicionar número definido de clientes");
		puts("[2] Adicionar número indefinido de clientes\033[m");
		puts("\033[33m[0] Menu\033[m");
		puts("-------------------------------------------");
		printf("\033[1m> \033[m");
		scanf("%hu" , &escolha);
		switch (escolha){
			case 1:
				ClientesDefinidos();
				break;
			case 2:
				ClientesIndefinidos();
				break;
			case 0:
				return;
			default:
				puts("\033[1;31mOpção inválida! tente novamente:\033[m");
				break;
		}
	}
}

void RemoverClientes(){
	int id;
	if(fim == 0){
		puts("\n\033[1;31mNenhum cliente definido!\033[m");
	}
	else{	
		for(int i = 0; i < fim; i++){
			puts("----------------------------");
			printf("\033[1;35mID: \033[m%d\n" , i + 1);
			printf("\033[1;35mNome:\033[m%s\n" , fila[i].nome);
			printf("\033[1;35mCPF: \033[m%s\n" , fila[i].cpf);
			printf("\033[1;35mPrioridade: \033[m %s\n" , fila[i].prioridade);
			puts("----------------------------");
		}

		printf("\033[1;31mID do usuário a ser removido: \033[m");
		scanf("%d" , &id);
		if(id < 1 || id > fim){
			printf("\n\033[1;31mID inválido!\033[m");
			return;
		}
		else{
			for(int i = id - 1; i < fim - 1; i++){
				fila[i] = fila[i + 1];
			}
		}
		fim--;
	}
}

void ClientesDefinidos(){
	char nome[20];
	char cpf[12];
	unsigned numero;
	char prioridade[10];
	printf("\033[1;36mSelecione o número de clientes a serem adicionados: \033[m");
	scanf("%u" , &numero);
	for(int i = 1; i <= numero; i++){
		printf("Nome do cliente %d: " , i);
		scanf("%s" , nome);
		while(true){
			printf("CPF no cliente %d: " , i);
			scanf("%s" , cpf);
			if(strlen(cpf) == 11){
				break;
			}
			else{
				puts("CPF inválido, tente novamente");
			}
		}
		printf("Prioridade do cliente %d (\033[31malta\033[m/\033[33mmedia\033[m/\033[32mbaixa\033[m): " , i);
		scanf("%s" , prioridade);
		strcpy(fila[fim].nome , nome);
		strcpy(fila[fim].cpf , cpf);
		strcpy(fila[fim].prioridade , prioridade);
		fim++;
	}
	puts("\n\033[36mTodos os clientes foram adicionados!\033[m\n");
}

void ClientesIndefinidos(){
	char nome[20];
	char cpf[12];
	unsigned numero = 1;
	char prioridade[10];
	char sair[4];
	while(true){
		printf("Nome do cliente %u: " , numero);
		scanf("%s" , nome);
		while(true){
			printf("CPF do cliente %u: " ,  numero);
			scanf("%s" , cpf);
			if(strlen(cpf) == 11){
				break;
			}
			else{
				puts("CPF inválido, tente novamente");
			}
		}
		printf("Prioridade do cliente %u (\033[31malta\033[m/\033[33mmedia\033[m/\033[32mbaixa\033[m): " , numero);
		scanf("%s" , prioridade);
		numero++;
		strcpy(fila[fim].nome , nome);
		strcpy(fila[fim].cpf , cpf);
		strcpy(fila[fim].prioridade , prioridade);
		fim++;
		printf("Deseja sair? [sim/nao]: ");
		scanf("%s" , sair);
		if(strcasecmp(sair , "sim") == 0){
			return;
		}
	}
}
