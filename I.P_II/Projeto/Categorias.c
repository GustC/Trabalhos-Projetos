#include <stdio.h>
#include "Categorias.h"
#include "Validações.h"


void menuCategorias(FILE *arq,FILE *arqProduto,FILE *avaliacao){
	char opcao,opcaoBusca=' ',nomeaux[50]="",login[15]="";
	int resp,tamAux,cont=0; 
	struct Busc q;
	do{
		system("cls");
		fflush(stdin);
		printf("\t%s","Menu Categoria");
		printf("\n1 - Inserir uma nova categoria\n2 - Consultar categoria\n3 - Alterar categoria\n4 - Remover categoria\n"
			"5 - Listar\n6 - Sair\nDigite a sua opcao: ");
		scanf("%c",&opcao);fflush(stdin);
		switch (opcao)
		{
		case '1':
			fflush(stdin);
			inserirCate(arq);
			break;
		case '2'://--------------------------- consultar
			fflush(stdin);
			opcaoBusca = 'N';
			fflush(stdin);
			resp = CateBusca(arq,opcaoBusca);
			if(resp == -1)
				printf("\nCategoria nao encontrado!\n");
			else if(resp == -2)
				printf("\nNenhum Categoria cadastrado ainda!\n");
			else
				consultarCate(arq,resp);
			system("pause");
			break;
		case '3'://--------------------------alterar
			fflush(stdin);
			printf("Como deseja procurar o Categoria que sera consultado?(C-Codigo / N-Parte do nome ou nome)");
			scanf("%c",&opcaoBusca);fflush(stdin);
			opcaoBusca = toupper(opcaoBusca);
			while (opcaoBusca != 'N' && opcaoBusca != 'C'){
				printf("Resposta invalida! Como deseja procurar o Categoria?\n(C-Codigo / N-Parte do nome ou nome)\nDigite sua opcao : ");
				scanf("%c",&opcaoBusca);fflush(stdin);
				opcaoBusca = toupper(opcaoBusca);
			}
			switch(opcaoBusca)
			{
			case 'N':
				resp = CateBusca(arq,opcaoBusca);
				break;
			case 'C':
				resp = CateBusca(arq,opcaoBusca);
				break;
			}
			if(resp == -1)
				printf("\nCategoria nao encontrado!\n");
			else if(resp == -2)
				printf("\nNenhum Categoria cadastrado ainda!\n");
			else
				alterarCate(arq,resp);   
			break;               
		case '4':                
			removerCate(arq,arqProduto,avaliacao);
			break;
		case '5':
			listarCate(arq);
			break;
		case '6':
			break;
		default:
			printf("Opcao invalida!\nDigite uma valida!\n");
			system("pause");
			break;
		}
	}while(opcao != '6');
}

void inserirCate(FILE *arq){
	int opcao,resp,teste;
	char nomeTeste[50];
	struct Categorias categoria;
	fflush(stdin);
	printf("Cadastrando:\n\n");
	do{
	printf("Digite seu codigo desejado: ");// add verificador de codigo
	scanf("%i",&categoria.codigo);
	resp = buscaCodCate(arq, categoria.codigo);
	if(resp != -1 && resp != -2)
		printf("\nCodigo de categoria ja existente!\nDigite outro por favor\n");
	}while(resp != -1 && resp != -2);
	fflush(stdin);
	printf("Digite o seu nome: ");
	fgets(categoria.nome,49,stdin);fflush(stdin);
	categoria.nome[(strlen(categoria.nome)-1)] = 0;
	categoria.status=0;//------------------------------------------Flag do deletar -------------
	fseek(arq,0,2);
	resp = fwrite(&categoria,sizeof(struct Categorias),1,arq);
	if(resp == 1)
		printf("Cadastro realizado com sucesso!\n");
	else
		printf("Erro na realizacao do cadastro!\n");
	system("pause");
}

void consultarCate(FILE *arq,int posisao){
	int i=0,resp;
	struct Categorias categoria;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp = fread(&categoria, sizeof(struct Categorias), 1, arq);
		if(resp == 0){
			if(feof(arq)!=0)
				break;
		}
		i++; // i = qtd leitura efetuada com sucesso
		if(i == posisao&&categoria.status != 1)
		{
			printf("\n\tCategoria consultada\n");
			printf("nome : %s\t%s\n","",categoria.nome);// -------------n ta alinhando
			printf("codigo : \t%s%i\n","",categoria.codigo);
			break;
		}
	}
}

void alterarCate(FILE *arq,int posisao){
	int i=0,resp,IntAux;
	char opcao,respEscolha,escolhaAlterar,StrAux[50]="";
	struct Categorias categoria;
	fseek(arq,sizeof(struct Categorias)*(posisao-1),0);
	resp = fread(&categoria, sizeof(struct Categorias), 1, arq);
	if(resp != 1){
		printf("\nerro de leitura!\n");
		system("pause");
	}
	do{
		StrAux[0] = 0;
		printf("O que deseja alterar?\n1 - Codigo\n2 - Nome\n3 - Cancelar alteracao\nDigite sua resposta : ");
		scanf("%c",&opcao);fflush(stdin);
		switch(opcao){
		case '1':
			do{
				printf("digite o seu novo codigo: ");
				scanf("%i",&IntAux);fflush(stdin);
				printf("Realmente deseja %i como seu codigo novo?\n(S - Sim/N - Nao)\nDigite a escolha: ", IntAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);
				fflush(stdin);
			}while(respEscolha != 'S');
			categoria.codigo = IntAux;
			break;
		case '2':
			do{
				digitarNome(StrAux);
				printf("Realmente deseja %s como seu novo nome?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);
				fflush(stdin);
			}while(respEscolha != 'S');
			strcpy(categoria.nome,StrAux);
			break;
		case '3':
			printf("Cancelando alteracao.\n");
			system("pause");
			break;
		default:
			printf("Opcao invalida ! Digite outra novamente!\n");
			break;
		}
		if(opcao != '3'){
			printf("Deseja modificar mais algum dado?( S - Sim | N - Nao)\nDigite sua respota: ");
			scanf("%c",&escolhaAlterar);fflush(stdin);
			escolhaAlterar = toupper(escolhaAlterar);
			fflush(stdin);
		}
	}while(escolhaAlterar != 'N' && opcao != '3');
	if(opcao != '3'){
		fseek(arq,-sizeof(struct Categorias),1);
		resp = fwrite(&categoria,sizeof(struct Categorias),1,arq);
		/*fseek(arq,sizeof(struct Usuario)*(posisao-1),0);-----------------so pra visualizar se realmente gravou , APAGAR Depois---------
		fread(&pessoa, sizeof(struct Usuario), 1, arq);*/
		if(resp == 1)
			printf("Alteracao realizada com sucesso!\n");
		else
			printf("Erro na realizacao da alteracao!\n");
		system("pause");
	}
}

void removerCate(FILE *arq,FILE *arqProduto,FILE *avaliacao){
	struct Categorias categoria;
	int posisao,resp;
	char opcaoBusca=' ',escolha;
	printf("Como deseja procurar a Categoria que sera removido?(C-Codigo / N-Parte do nome ou nome)");
	scanf("%c",&opcaoBusca);fflush(stdin);
	opcaoBusca = toupper(opcaoBusca);
	while (opcaoBusca != 'C' && opcaoBusca != 'N'){
		printf("Resposta invalida! Como deseja procurar a Categoria?\n(C-Codigo / N-Nome)\nDigite sua opcao : ");
		scanf("%c",&opcaoBusca);fflush(stdin);
		opcaoBusca = toupper(opcaoBusca);
	}
	posisao = CateBusca(arq, opcaoBusca);// --- retorna a posisao pos leitura efetuada ou seja e a posi + 1 ----
	fseek(arq,(posisao-1)*sizeof(struct Categorias),0);
	fread(&categoria, sizeof(struct Categorias), 1, arq);
	printf("Tem certeza que deseja remover a categoria de:\ncodigo: \t%d\n", categoria.codigo);
	printf("Nome:");
	puts(categoria.nome);
	do{
		printf("\nDigite sua escolha( S - Sim | N - Nao): ");
		escolha = toupper(getchar());
		if(escolha != 'S' && escolha != 'N')
			printf("\nRespota invalida ! Digite corretamente !\n");
	}while(escolha != 'S' && escolha != 'N');
	fflush(stdin);
	if (escolha == 'S'){
		categoria.status = 1;
		deletarProdutos(arqProduto,avaliacao,categoria.codigo);
		fseek(arq,-sizeof(struct Categorias),1);
		resp = fwrite(&categoria,sizeof(struct Categorias),1,arq);
		if(resp != 1)
			printf("erro de gravação!\n");
		else
			printf("Categoria removida!\n");
		system("pause");
	}
	else{
		printf("Remocao da Categoria cancelada!\n");
		system("pause");
	}
}

void listarCate(FILE *arq){
	int resp;
	struct Categorias categoria;
	fseek(arq,0,0);
	while (!feof(arq)){
		resp = fread(&categoria, sizeof(struct Categorias), 1, arq);
		if(resp != 1)
			if(feof(arq))
				break;
		if(categoria.status == 0){
			printf("\ncodigo: %d\n", categoria.codigo);
			printf("Nome: ");
			puts(categoria.nome);
			printf("\n\n");
		}
	}
	system("pause");
}

void deletarProdutos(FILE *arqProduto,FILE *avaliacao,int cod){
	struct Produtos a;
	int st;
	fseek(arqProduto, 0, 0);
	while (1){
		st = fread(&a, sizeof(struct Produtos), 1, arqProduto);
		if (st == 0){
			if(feof(arqProduto)!=0)
				break;
		}

		if (cod == a.categoria){
			a.status = 1;
			deletarAvaliacoesProd(avaliacao,a.codigo);//---- apos deletar o produto por conta da categoria deve-se remover tmb a avalia
			fseek(arqProduto,-sizeof(struct Produtos),1);
			st = fwrite(&a, sizeof(struct Produtos), 1, arqProduto);
			fseek(arqProduto,sizeof(struct Produtos),1);
			if (st != 1){
				printf("Erro de leitura!");
				system("pause");
				return;
			}
		}
	}
}


void manutencao2(FILE *arq){
	FILE *aux;
	int status, erro = 0;
	struct Categorias categoria;
	aux = fopen("auxiliar", "wb");
	if (aux == NULL)
		printf("ERRO!\n");
	else{
		fseek(arq, 0, 0);

		while (1){
			status = fread(&categoria, sizeof(struct Categorias), 1, arq);
			if (status != 1){
				if (!feof(arq)){
					printf("Erro durante a limpeza, Erro de leitura!\n");
					erro = 1;
				}
				break;
			}
			else{
				if (categoria.status == 0){// 1 = deleta
					fseek(aux,0,2);
					status = fwrite(&categoria, sizeof(struct Categorias), 1, aux);
					if (status != 1){
						printf("Erro durante a limpeza, Erro na gravacao!\n");
						erro = 1;
						break;
					}
				}
			}
		}
		if (erro == 0){
			fclose(arq);
			fclose(aux);
			remove("categorias.bin");
			rename("auxiliar", "categorias.bin");
		}
		else{
			fclose(aux);
			remove("auxiliar");
		}
	}
}