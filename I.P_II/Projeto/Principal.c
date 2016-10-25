#include <stdio.h>
#include <stdlib.h>
#include "Usuarios.h"
#include "Categorias.h"
#include "Produtos.h"
#include "Avaliações.h"
#include "Validações.h"


FILE * abrirArquivo(char nome[]){
	FILE * arq;
	arq = fopen(nome, "r + b");
	if (arq == NULL)
		arq = fopen(nome, "w + b");
	return arq;
}

int main(){
	int log=0;
	char opcao,opcaoCadastro;
	FILE *usuarios, *categorias,*produtos,*avaliacao;
	usuarios = abrirArquivo("Usuarios.bin");
	categorias = abrirArquivo("Categorias.bin");
	produtos = abrirArquivo("Produtos.bin");
	avaliacao = abrirArquivo("Avaliacoes.bin");
	if(usuarios == NULL || categorias == NULL || produtos == NULL || avaliacao==NULL){
		printf("Erro na criacao ou na abertura dos arquivos!\nO programa sera encerrado.\n");
	}
	do{
		system("cls");
		printf("\t%s\n","Bem vindo");
		printf("O que voce deseja?\n");
		printf("1 - %4s\n2 - %4s\n3 - %4s\ndigite sua opcao: ","Cadastro","Realizar login","Sair");//alinhar aqui
		scanf("%c",&opcao);fflush(stdin);
		switch (opcao)
		{
		case '1':{
			do{
				printf("\tO que deseja cadastrar?\n1 - %4s\n2 - %4s\n3 - %4s\n4 - %4s\nDigite sua opcao : ","Usuario","Categorias","Produtos","Sair");
				scanf("%c",&opcaoCadastro);fflush(stdin);
				switch (opcaoCadastro){
				case '1':
					menuUsuarios(usuarios,avaliacao,produtos);
					break;
				case '2':
					menuCategorias(categorias,produtos,avaliacao);
					break;
				case '3':
					menuProdutos(produtos,categorias,avaliacao);
					break;
				case '4':
					printf("Saindo do cadastramento!\n");
					break;
				default:
					break;
				}
			}while(opcaoCadastro!='4');
			break;
				 }
		case '2':
			log = Realizarlogin(usuarios,log);//---- se conseguiu retorna a posisao q é diferente de 0
			if(log != 0){
				menuAvaliacoes(avaliacao,produtos,usuarios,log);//------ log e igual a posicao do login do usuario q conseguiu loggar
			}
		case '3':
		default:
			break;
		}
	}while(opcao!='3');
	manutencao1(usuarios);
	manutencao2(categorias);
	manutencao3(produtos);
	manutencao4(avaliacao);
	fcloseall();
}