#include <stdio.h>
#include "Produtos.h"
#include "Validações.h"


void menuProdutos(FILE *arq,FILE *arqCate,FILE *arqAvaliacao){
	char opcao,opcaoBusca=' ',nomeaux[50]="",login[15]="",teste;
	int resp,tamAux,cont=0; 
	do{
		system("cls");
		fflush(stdin);
		printf("\t%s","Menu do Produto");
		printf("\n1 - Inserir um novo Produto\n2 - Consultar Produto\n3 - Alterar Produto\n4 - Remover Produto\n"
			"5 - Listar \n6 - Sair\nDigite a sua opcao: ");
		scanf("%c",&opcao);fflush(stdin);
		switch (opcao)
		{
		case '1':
			fflush(stdin);
			inserirProd(arq,arqCate);
			break;
		case '2'://--------------------------- consultar
			fflush(stdin);
			printf("Como deseja procurar o produto que sera consultado?(T-Titulo / G-Categoria / D-Parte da descricao)");
			scanf("%c",&opcaoBusca);fflush(stdin);
			opcaoBusca = toupper(opcaoBusca);
			while (opcaoBusca != 'T' && opcaoBusca != 'G' && opcaoBusca != 'D'){
				printf("Resposta invalida! Como deseja procurar o Produto?\n"
					"(T-Titulo / C-Categoria / D-Parte da descricao)\nDigite sua opcao : ");
				scanf("%c",&opcaoBusca);fflush(stdin);
				opcaoBusca = toupper(opcaoBusca);
			}
			fflush(stdin);
			switch(opcaoBusca)
			{
			case 'T':
				fflush(stdin);
				resp = Produtobusca(arq,opcaoBusca);
				break;
			case 'G':
				fflush(stdin);
				resp = Produtobusca(arq,opcaoBusca);
				break;
			case 'D':
				fflush(stdin);
				resp = Produtobusca(arq,opcaoBusca);
				break;
			}
			if(resp == -1)
				printf("\nProduto nao encontrado!\n");
			else if(resp == -2)
				printf("\nNenhum produto cadastrado ainda!\n");
			else
				consultarProd(arq,arqAvaliacao,resp);
			system("pause");
			break;
		case '3'://--------------------------alterar
			fflush(stdin);
			printf("Como deseja procurar o produto que sera consultado?(C-Codigo  / T-Parte do Titulo)");
			scanf("%c",&opcaoBusca);fflush(stdin);
			opcaoBusca = toupper(opcaoBusca);
			while (opcaoBusca != 'C' && opcaoBusca != 'T' ){
				printf("Resposta invalida! Como deseja procurar o produto?\n(C-Codigo / T-Parte do Titulo)\nDigite sua opcao : ");
				scanf("%c",&opcaoBusca);fflush(stdin);
				opcaoBusca = toupper(opcaoBusca);
			}
			switch(opcaoBusca)
			{
			case 'T':
				resp = Produtobusca(arq,opcaoBusca);
				break;
			case 'C':
				resp = Produtobusca(arq,opcaoBusca);
				break;
			}
			if(resp == -1)
				printf("\nProduto nao encontrado!\n");
			else if(resp == -2)
				printf("\nNenhum produto cadastrado ainda!\n");
			else
				alterarProd(arq,resp,arqCate);   
			break;               
		case '4':                
			removerProd(arq,arqAvaliacao);
			break;
		case '5':
			listarProd(arq , arqCate, arqAvaliacao);
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

void inserirProd(FILE *arq,FILE *arqCate){
	int resp,teste,codAux;
	float auxValor;
	struct Produtos produto;
	fflush(stdin);
	printf("Cadastrando:\n\n");
	printf("Digite seu codigo desejado: ");// add verificador de codigo
	scanf("%i",&produto.codigo);
	fflush(stdin);
	printf("\nDigite o titulo do produto: ");
	fgets(produto.titulo,99,stdin);fflush(stdin);
	produto.titulo[(strlen(produto.titulo)-1)] = 0;
	printf("Digite a descricao do produto:( max 255 caracteres ): ");
	fgets(produto.descricao,255,stdin);fflush(stdin);
	produto.descricao[(strlen(produto.descricao)-1)] = 0 ;// funciona, coloca /0 no final da string
	do{
		printf("digite o codigo da categoria: ");
		scanf("%i",&codAux);
		resp = buscaCodCate(arqCate,codAux);
		if(resp == -1 )
			printf("\nCodigo nao exitente!\n");
	}while(resp == -1);
	produto.categoria = codAux;
	fflush(stdin);
	produto.preco = 0.0;
	digitarPreco(&auxValor);
	produto.preco = produto.preco+auxValor;//---------------------------TEM Q FICAR COM 2 CASAS DECIMAIS -------------
	fflush(stdin);
	produto.status=0;//------------------------------------------Flag do deletar -------------
	fseek(arq,0,2);
	resp = fwrite(&produto,sizeof(struct Produtos),1,arq);
	if(resp == 1)
		printf("\nCadastro realizado com sucesso!\n");
	else
		printf("\nErro na realizacao do cadastro!\n");
	system("pause");
}

void consultarProd(FILE *arq,FILE *arqAvaliacao,int posisao){
	int i=0,resp;
	float media;
	struct Produtos produto;
	fseek(arq,0,0);
	while(!feof(arq)){
		resp = fread(&produto, sizeof(struct Produtos), 1, arq);
		if(resp == 0){
			if(feof(arq)!=0)
				break;
		}
		i++; // i = qtd leitura efetuada com sucesso
		if(i == posisao)
		{
			if(produto.status==0){
				printf("\n\tDados do Produto Consultado\n");
				printf("Codigo : \t%s%i\n","",produto.codigo);
				printf("Titulo : \t%s\n",produto.titulo);
				printf("Preco : \t%s%.2f\n","",produto.preco);
				printf("Categoria : \t%i\n",produto.categoria);
				printf("Descricao :\t%s\n",produto.descricao);
				media = CalcularMedia(arqAvaliacao,produto.codigo);
				if(media == -1)
					printf("Este produto ainda nao foi avaliado !\n");
				else
					printf("Media das avaliacoes :\t%.1f\n",media);
				break;
			}
		}
	}
}

void alterarProd(FILE *arq,int posisao,FILE *arqCate){
	int i=0,resp,IntAux,resultBusc;
	float FloatAux;
	char opcao,respEscolha,escolhaAlterar,StrAux[256]="";
	struct Produtos produto;
	fseek(arq,sizeof(struct Produtos)*(posisao-1),0);
	resp = fread(&produto, sizeof(struct Produtos), 1, arq);
	if(resp != 1){
		printf("\nerro de leitura!\n");
		system("pause");
	}
	do{
		StrAux[0] = 0;
		printf("O que deseja alterar?\n1 - Codigo\n2 - Titulo\n3 - Descricao\n"
			"4 - Categoria\n5 - Preco\n6 - Cancelar alteracao\nDigite a opcao: ");
		scanf("%c",&opcao);fflush(stdin);
		switch(opcao){
		case '1':
			do{
				printf("digite o seu novo codigo: ");
				scanf("%i",&IntAux);
				printf("Realmente deseja %i como seu codigo novo?\n(S - Sim/N - Nao)\nDigite a escolha: ", IntAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);

			}while(respEscolha != 'S');
			break;
		case '2':
			do{
				digitarTitulo(StrAux);fflush(stdin);
				printf("Realmente deseja "" %s "" como seu novo titulo?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);fflush(stdin);
			}while(respEscolha != 'S');
			strcpy(produto.titulo, StrAux);
			break;
		case '3':
			do{
				digitarDescri(StrAux);fflush(stdin);
				printf("Realmente deseja ""%s"" como sua nova descricao?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);

			}while(respEscolha != 'S');
			strcpy(produto.descricao,StrAux);
			break;
		case '4':
			do{	printf("Digite a nova categoria: ");
			do{

				scanf("%i",&IntAux);
				resp = buscaCodCate(arqCate,IntAux);// procura nova categoria existente no arquivo categoria
				if(resp == -1 )
					printf("\nCodigo nao exitente!\n");
			}while(resp != 1);
			digitarSenha(StrAux);
			fflush(stdin);
			printf("\nRealmente deseja %i como sua nova categoria?\n(S - Sim/N - Nao)\nDigite a escolha: ",IntAux);
			scanf("%c",&respEscolha);fflush(stdin);
			respEscolha=toupper(respEscolha);
			}while(respEscolha != 'S');
			produto.categoria = IntAux;
			break;
		case '5':
			do{
				digitarPreco(&FloatAux);
				printf("\nRealmente deseja %f como seu novo preco?\n(S - Sim/N - Nao)\nDigite a escolha: ",FloatAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);
			}while(respEscolha != 'S');
			produto.preco = FloatAux;
			break;
		case '6':
			printf("Alteracao cancelada.\n");
			escolhaAlterar='N';
			break;
		default:
			printf("Opcao invalida ! Digite outra novamente!\n");
			break;
		}
		if(opcao != '6'){
			printf("Deseja modificar mais algum dado?( S - Sim | N - Nao)\nDigite sua respota: ");
			scanf("%c",&escolhaAlterar);fflush(stdin);
			escolhaAlterar = toupper(escolhaAlterar);
			fflush(stdin);
		}
	}while(escolhaAlterar != 'N' && opcao != '6');
	fseek(arq,-sizeof(struct Produtos),1);
	resp = fwrite(&produto,sizeof(struct Produtos),1,arq);
	fseek(arq,sizeof(struct Produtos)*(posisao-1),0);//-----------------so pra visualizar se realmente gravou , APAGAR Depois---------
	fread(&produto, sizeof(struct Produtos), 1, arq);//
	if(resp == 1)
		printf("Alteracao realizada com sucesso!\n");
	else
		printf("Erro na realizacao da alteracao!\n");
	system("pause");
}

void removerProd(FILE *arq,FILE *avaliacao){
	struct Produtos produto;
	int posisao,resp;
	char opcaoBusca=' ',escolha;
	printf("Como deseja procurar o produto que sera removido?(C-Codigo / T-Parte do Titulo)"
		"Digite sua opcao: ");
	scanf("%c",&opcaoBusca);fflush(stdin);
	opcaoBusca = toupper(opcaoBusca);
	while (opcaoBusca != 'C' && opcaoBusca != 'T'){
		printf("Resposta invalida! Como deseja procurar o produto?\n(C-Codigo / T-Parte do Titulo)"
			"\nDigite sua opcao : ");
		scanf("%c",&opcaoBusca);fflush(stdin);
		opcaoBusca = toupper(opcaoBusca);
	}
	posisao = Produtobusca(arq, opcaoBusca);
	fseek(arq,(posisao-1)*sizeof(struct Produtos),0);
	fread(&produto, sizeof(struct Produtos), 1, arq);
	printf("\nTem certeza que deseja remover o produto de:\n\ncodigo: \t%s%d","", produto.codigo);
	printf("\nTitulo: \t%s%s","", produto.titulo);
	printf("\nPreco:		%.2f",produto.preco);
	printf("\nDescricao: \t");
	puts(produto.descricao);
	printf("Categoria: \t%s%i","",produto.categoria);
	do{
		printf("\nDigite sua escolha( S - Sim | N - Nao): ");
		escolha = toupper(getchar());
		if(escolha != 'S' && escolha != 'N')
			printf("\nRespota invalida ! Digite corretamente !\n");
	}while(escolha != 'S' && escolha != 'N');
	fflush(stdin);
	if (escolha == 'S'){
		produto.status = 1;
		deletarAvaliacoesProd(avaliacao,produto.codigo);
		fseek(arq,-sizeof(struct Produtos),1);
		resp = fwrite(&produto,sizeof(struct Produtos),1,arq);
		/*fseek(arq,sizeof(struct Produtos)*(posisao-1),0);//-----------------so pra visualizar se realmente gravou , APAGAR Depois---------
		fread(&pessoa, sizeof(struct Produtos), 1, arq);*/
		if(resp != 1)
			printf("erro de gravação!\n");
		else
			printf("Produto removido!\n");
		system("pause");
	}
	else
		printf("Remocao do usuario cancelada!\n");
}

void listarProd(FILE *arq,FILE *arqCate,FILE *arqAvaliacao){
	int resp,qtd;
	char opcao;
	struct Produtos produto;
	fseek(arq,0,2);
	qtd = ftell(arq);
	qtd = qtd / (sizeof(struct Produtos));
	fseek(arq,0,0);
	fflush(stdin);
	printf("Como deseja ordenar ?\n(P - Preco / T - Titulo / A - Maior Nota de avaliacao)"
		"\nDigite sua opcao: ");
	scanf("%c",&opcao);fflush(stdin);
	opcao = toupper(opcao);
	fflush(stdin);
	while(opcao != 'P' && opcao != 'T' && opcao != 'A'){
		printf("Opcao invalida!\nDigite corretamente: ");
		scanf("%c",&opcao);fflush(stdin);
		opcao = toupper(opcao);fflush(stdin);
	}
	ordenar(arq,arqAvaliacao,qtd,opcao);
	/*
	printf("\nTitulo: ");
	puts(produto.titulo);
	printf("codigo: %i\n",produto.codigo);
	printf("codigo: %i\n",produto.categoria);
	printf("Preco: %.2d",produto.preco);
	printf("\nDescricao: ");
	puts(produto.descricao);
	printf("\n\n");*/
	system("pause");

}

void deletarAvaliacoesProd(FILE* avaliacoes, int cod){
	struct Avaliacao a;
	int st;
	fseek(avaliacoes, 0, 0);
	while (1){
		st = fread(&a, sizeof(struct Avaliacao), 1, avaliacoes);
		if(st == 0)
			if(feof(avaliacoes)!=0)
				break;
		if (st != 1){
			printf("Erro de leitura!");
			system("pause");
			return;
		}
		else{
			if (cod == a.codigoProduto){
				a.status = 1;
				fseek(avaliacoes, -sizeof(struct Avaliacao),1);
				st = fwrite(&a, sizeof(struct Avaliacao), 1, avaliacoes);
				fseek(avaliacoes,sizeof(struct Produtos),1);//-----------------so pra visualizar se realmente gravou , APAGAR Depois---------
				if (st != 1){
					printf("Erro de leitura!");
					system("pause");
					return;
				}
			}
		}
	}
}

void manutencao3(FILE *arq){
	FILE *aux;
	int status, erro = 0;
	struct Produtos produto;
	aux = fopen("auxiliar", "wb");
	if (aux == NULL)
		printf("ERRO!\n");
	else{
		fseek(arq, 0, 0);

		while (1){
			status = fread(&produto, sizeof(struct Produtos), 1, arq);
			if (status != 1){
				if (!feof(arq)){
					printf("Erro durante a limpeza, Erro de leitura!\n");
					erro = 1;
				}
				break;
			}
			else{
				if (produto.status == 0){// 1 = deleta
					fseek(aux,0,2);
					status = fwrite(&produto, sizeof(struct Produtos), 1, aux);
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
			remove("Produtos.bin");
			rename("auxiliar", "Produtos.bin");
		}
		else{
			fclose(aux);
			remove("auxiliar");
		}
	}
}
