#include <stdio.h>
#include "usuarios.h"
#include "Validações.h"

void menuUsuarios(FILE *arq,FILE *arqAvaliacao,FILE *arqProdutos){
	char opcao,opcaoBusca=' ',nomeaux[50]="",login[15]="",teste;
	int resp,tamAux,cont=0; 
	do{
		system("cls");
		fflush(stdin);
		printf("\t%s","Menu do Usuario");
		printf("\n1 - Inserir um novo Usuario\n2 - Consultar Usario\n3 - Alterar Usuario\n4 - Remover Usuario\n"
			"5 - Listar\n6 - Sair\nDigite a sua opcao: ");
		scanf("%c",&opcao);fflush(stdin);
		switch (opcao)
		{
		case '1':
			fflush(stdin);
			inserir(arq);
			break;
		case '2'://--------------------------- consultar
			fflush(stdin);
			printf("Como deseja procurar o usuario que sera consultado?(L-Login / P-Telefone / N-Parte do nome ou nome)");
			scanf("%c",&opcaoBusca);fflush(stdin);
			opcaoBusca = toupper(opcaoBusca);
			while (opcaoBusca != 'N' && opcaoBusca != 'L' && opcaoBusca != 'P'){
				printf("Resposta invalida! Como deseja procurar o usuario?\n(L-Login / P-Telefone / N-Nome)\nDigite sua opcao : ");
				scanf("%c",&opcaoBusca);fflush(stdin);
				opcaoBusca = toupper(opcaoBusca);
			}
			fflush(stdin);
			switch(opcaoBusca)
			{
			case 'N':
				fflush(stdin);
				resp = busca(arq,opcaoBusca);
				break;
			case 'L':
				fflush(stdin);
				resp = busca(arq,opcaoBusca);
				break;
			case 'P':
				fflush(stdin);
				resp = busca(arq,opcaoBusca);
				break;
			}
			if(resp == -1)
				printf("\nUsuario nao encontrado!\n");
			else if(resp == -2)
				printf("\nNenhum usuario cadastrado ainda!\n");
			else
				consultar(arq,arqAvaliacao,arqProdutos,resp);
			system("pause");
			break;
		case '3'://--------------------------alterar
			fflush(stdin);
			printf("Como deseja procurar o usuario que sera consultado?(L-Login / P-Telefone / N-Parte do nome ou nome)");
			scanf("%c",&opcaoBusca);fflush(stdin);
			opcaoBusca = toupper(opcaoBusca);
			while (opcaoBusca != 'N' && opcaoBusca != 'L' && opcaoBusca != 'P'){
				printf("Resposta invalida! Como deseja procurar o usuario?\n(L-Login / P-Telefone / N-Nome)\nDigite sua opcao : ");
				scanf("%c",&opcaoBusca);fflush(stdin);
				opcaoBusca = toupper(opcaoBusca);
			}
			switch(opcaoBusca)
			{
			case 'N':
				resp = busca(arq,opcaoBusca);
				break;
			case 'L':
				resp = busca(arq,opcaoBusca);
				break;
			case 'C':
				resp = busca(arq,opcaoBusca);
				break;
			}
			if(resp == -1)
				printf("\nUsuario nao encontrado!\n");
			else if(resp == -2)
				printf("\nNenhum usuario cadastrado ainda!\n");
			else
				alterar(arq,resp);   
			break;               
		case '4':                
			remover(arq,nomeaux);
			break;
		case '5':
			listar(arq);
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

void inserir(FILE *arq){
	int opcao,resp,teste;
	char nomeTeste[50];
	struct Usuario pessoa;
	fflush(stdin);
	printf("Cadastrando:\n\n");
	do{
	printf("Digite seu codigo desejado: ");
	scanf("%i",&pessoa.codigo);
	resp = VerificarCodUsuario(arq,pessoa.codigo);
	if(resp != -1 && resp != -2)
		printf("Codigo de usuario existente!\nDigite outro por favor\n");
	}while(resp != -1 && resp != -2);
	fflush(stdin);
	printf("Digite o seu nome: ");
	fgets(pessoa.nome,49,stdin);fflush(stdin);
	pessoa.nome[(strlen(pessoa.nome)-1)] = 0;
	do{
		printf("Digite seu login( max 14 caracteres ): ");
		fgets(pessoa.login,14,stdin);fflush(stdin);
		pessoa.login[(strlen(pessoa.login)-1)] = 0 ;
		resp = VerificarUsuario(arq,pessoa.login);
		if(resp != -1 && resp != -2)
			printf("Login existente! Digite outro por favor\n");
	}while(resp != -1 && resp != -2);
	digitarSenha(pessoa.senha);
	do{
		printf("\nDigite seu sexo ( M - masculino / F - Feminino)\nDigite sua opcao:");
		scanf("%c",&pessoa.sexo);fflush(stdin);
		pessoa.sexo=toupper(pessoa.sexo);
		if(pessoa.sexo != 'M' && pessoa.sexo != 'F')
			printf("Opcao invalida!\nDigite Corretamente!\n");
	}while(pessoa.sexo != 'M' && pessoa.sexo != 'F');
	fflush(stdin);
	printf("Digite sua idade: ");
	scanf("%i",&pessoa.idade);
	fflush(stdin);
	printf("Digite seu telefone: ");
	fgets(pessoa.telefone,16,stdin);fflush(stdin);
	pessoa.telefone[(strlen(pessoa.telefone)-1)] = 0;
	pessoa.status=0;
	fseek(arq,0,2);
	resp = fwrite(&pessoa,sizeof(struct Usuario),1,arq);
	if(resp == 1)
		printf("Cadastro realizado com sucesso!\n");
	else
		printf("Erro na realizacao do cadastro!\n");
	system("pause");
}

void consultar(FILE *arq,FILE *arqAvaliacao,FILE *arqProdutos,int posisao){
	int i=0,resp,posisaoAva,posisaoProd,teste1,teste2;
	struct Usuario pessoa;
	struct Produtos produto;
	struct Avaliacao avalia;
	fseek(arq,0,0);
	while(1){
		resp = fread(&pessoa, sizeof(struct Usuario), 1, arq);
		if(resp == 0){
			if(feof(arq)!=0)
				break;
			// i = qtd leitura efetuada com sucesso
		}
		i++;
		if(i == posisao && pessoa.status != 1)
		{
			printf("\n\tDados do usuario Consultado\n");
			printf("nome :		%s\n",pessoa.nome);// -------------n ta alinhando
			printf("login : \t%s\n",pessoa.login);
			printf("codigo : \t%s%i\n","",pessoa.codigo);
			printf("idade : \t%i\n",pessoa.idade);
			printf("sexo :		"); //-------------- n ta alinhando tbm
			if(pessoa.sexo == 'M')
				printf("%s\n","Masculino");
			else
				printf("%s\n","Feminino");
			printf("telefone :\t%s\n",pessoa.telefone);
			fseek(arqAvaliacao,0,0);
			fseek(arqProdutos,0,0);
			printf("\n\n\t\tProdutos Avaliados\n\tTitulo\t\tNota\t\tAquisisao\n\n");
			while(1){

				posisaoAva=PosiAvaliacao(arqAvaliacao,pessoa.codigo);
				if(posisaoAva == -1 || posisaoAva == -2)
					break;
				fflush(stdin);//------------flag em 2 , para o segundo tipo 
				fseek(arqAvaliacao,-sizeof(struct Avaliacao) , 1 );
				teste1 = fread(&avalia, sizeof(struct Avaliacao), 1, arqAvaliacao);
				fflush(stdin);
				posisaoProd=PosiProduto(arqProdutos,avalia.codigoProduto);
				fflush(stdin);
				fseek(arqProdutos,-sizeof(struct Produtos) , 1 );
				fread(&produto, sizeof(struct Produtos), 1, arqProdutos);
				if(posisaoProd == -2 && posisaoAva == -2) // '-2' = fim de arquivo
					break;
				if(posisaoAva != -1 && posisaoProd != -1){
					printf("%10s\t\t%-5d\t\t",produto.titulo,avalia.nota);
					if(avalia.comprou == 1)
						printf("Adquirido\n");
					else
						printf("Nao Adquirido\n");
				}
			}
			break;
		}
	}

}

void alterar(FILE *arq,int posisao){
	int i=0,resp,IntAux,resultBusc;
	char opcao,respEscolha,escolhaAlterar,StrAux[50]="";
	struct Usuario pessoa;
	fseek(arq,sizeof(struct Usuario)*(posisao-1),0);
	resp = fread(&pessoa, sizeof(struct Usuario), 1, arq);
	if(resp != 1){
		printf("\nerro de leitura!\n");
		system("pause");
	}
	do{
		StrAux[0] = 0;
		printf("O que deseja alterar?\n1 - Codigo\n2 - Nome\n3 - Login\n"
			"4 - Senha\n5 - Idade\n6 - Telefone\n7 - Sexo\n8 - Cancelar alteracao\nDigite a opcao: ");
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
				digitarNome(StrAux);fflush(stdin);
				printf("Realmente deseja %s como seu novo nome?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);fflush(stdin);
			}while(respEscolha != 'S');
			break;
		case '3':
			do{
				do{
					digitarLogin(StrAux);fflush(stdin);
					resultBusc=VerificarUsuario(arq,StrAux);
					if(resultBusc == -1)
						printf("Login Existente! Utilize outro por favor!\n");
				}while(resultBusc != -1);
				printf("Realmente deseja %s como seu novo login?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);

			}while(respEscolha != 'S');
			break;
		case '4':
			do{	
				printf("Digite a nova senha: ");
				digitarSenha(StrAux);
				fflush(stdin);
				printf("\nRealmente deseja %s como sua nova senha?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);

			}while(respEscolha != 'S');
			strcpy(pessoa.senha,StrAux);
			break;
		case '5':
			do{
				printf("Digite sua nova idade: ");
				scanf("%i",&IntAux);
				printf("\nRealmente deseja %s como sua nova senha?\n(S - Sim/N - Nao)\nDigite a escolha: ",IntAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);

			}while(respEscolha != 'S');
			break;
		case '6':
			do{
				printf("Digite o novo telefone: ");
				digitarFone(StrAux);
				printf("\nRealmente deseja %s como seu novo telefone?\n(S - Sim/N - Nao)\nDigite a escolha: ",StrAux);
				scanf("%c",&respEscolha);fflush(stdin);
				respEscolha=toupper(respEscolha);
			}while(respEscolha != 'S');
			strcpy(pessoa.telefone,StrAux);
			break;
		case '8':
			printf("Alteracao cancelada.\n");
			escolhaAlterar='N';
			break;
		default:
			printf("Opcao invalida ! Digite outra novamente!\n");
			break;
		}
		if(opcao != '8'){
			printf("Deseja modificar mais algum dado?( S - Sim | N - Nao)\nDigite sua respota: ");
			scanf("%c",&escolhaAlterar);fflush(stdin);
			escolhaAlterar = toupper(escolhaAlterar);
			fflush(stdin);
		}
	}while(escolhaAlterar != 'N' || opcao != 8);
	fseek(arq,-sizeof(struct Usuario),1);
	resp = fwrite(&pessoa,sizeof(struct Usuario),1,arq);
	if(resp == 1)
		printf("Alteracao realizada com sucesso!\n");
	else
		printf("Erro na realizacao da alteracao!\n");
	system("pause");
}

void remover(FILE *arq){// ------ Nat fez -------
	struct Usuario pessoa;
	int posisao,resp;//----------------------------------PARAMOS AQUI !! ------------------------------------
	char opcaoBusca=' ',escolha;
	printf("Como deseja procurar o usuario que sera removido?(L-Login / P-Telefone / N-Parte do nome ou nome)");
	scanf("%c",&opcaoBusca);fflush(stdin);
	opcaoBusca = toupper(opcaoBusca);
	while (opcaoBusca != 'N' && opcaoBusca != 'L' && opcaoBusca != 'P'){
		printf("Resposta invalida! Como deseja procurar o usuario?\n(L-Login / P-Telefone / N-Nome)\nDigite sua opcao : ");
		scanf("%c",&opcaoBusca);fflush(stdin);
		opcaoBusca = toupper(opcaoBusca);
	}
	posisao = busca(arq, opcaoBusca);
	fseek(arq,(posisao-1)*sizeof(struct Usuario),0);
	fread(&pessoa, sizeof(struct Usuario), 1, arq);
	printf("Tem certeza que deseja remover o usuario de:\ncodigo: %d\n", pessoa.codigo);
	printf("\nIdade: %d", pessoa.idade);
	printf("\nLogin: ");
	puts(pessoa.login);
	printf("Nome:");
	puts(pessoa.nome);
	printf("\nTelefone: ");
	puts(pessoa.telefone);
	printf("\nSexo: %c", pessoa.sexo);
	do{
		printf("\nDigite sua escolha( S - Sim | N - Nao): ");
		escolha = toupper(getchar());
		if(escolha != 'S' && escolha != 'N')
			printf("\nRespota invalida ! Digite corretamente !\n");
	}while(escolha != 'S' && escolha != 'N');
	fflush(stdin);
	if (escolha == 'S'){
		pessoa.status = 1;
		fseek(arq,-sizeof(struct Usuario),1);
		resp = fwrite(&pessoa,sizeof(struct Usuario),1,arq);
		fseek(arq,sizeof(struct Usuario)*(posisao-1),0);//-----------------so pra visualizar se realmente gravou , APAGAR Depois---------
		fread(&pessoa, sizeof(struct Usuario), 1, arq);
		if(resp != 1)
			printf("erro de gravação!\n");
		else
			printf("Usuario removido!\n");
		system("pause");
	}
	else
		printf("Remocao do usuario cancelada!\n");
}

void listar(FILE *arq){
	int resp;
	struct Usuario pessoa;
	fseek(arq,0,0);
	while (!feof(arq)){
		resp = fread(&pessoa, sizeof(struct Usuario), 1, arq);
		if(resp != 1)
			if(feof(arq))
				break;
		if(pessoa.status == 0){
			printf("\nNome: ");
			puts(pessoa.nome);
			printf("Idade: %d\ncodigo: %d\n", pessoa.idade, pessoa.codigo);		
			printf("Sexo: %c\n",pessoa.sexo);
			printf("Login: ");
			puts(pessoa.login);
			printf("Telefone: ");
			puts(pessoa.telefone);
			printf("\n\n");
		}
	}
	system("pause");
}

void deletarAvaliacoesUsuarios(FILE* avaliacoes, int cod){
	struct Avaliacao a;
	int st;
	fseek(avaliacoes, 0, 0);
	while (1){
		st = fread(&a, sizeof(struct Avaliacao), 1, avaliacoes);
		if (st == 0)
			if(feof(avaliacoes)!=0)
				break;

		if (cod == a.codigoUsuario){
			a.status = 1;
			a.nota = 0;
			fseek(avaliacoes,-sizeof(struct Avaliacao),1);
			st = fwrite(&a, sizeof(struct Avaliacao), 1, avaliacoes);
			fseek(avaliacoes,sizeof(struct Avaliacao),1);
			if (st != 1){
				printf("Erro de leitura!");
				system("pause");
				return;
			}
		}
	}
}


void manutencao1(FILE *arq){
	FILE *aux;
	int status, erro = 0;
	struct Usuario pessoa;
	aux = fopen("auxiliar", "wb");
	if (aux == NULL)
		printf("ERRO!\n");
	else{
		fseek(arq, 0, 0);

		while (1){
			status = fread(&pessoa, sizeof(struct Usuario), 1, arq);
			if (status != 1){
				if (!feof(arq)){
					printf("Erro durante a limpeza, Erro de leitura!\n");
					erro = 1;
				}
				break;
			}
			else{
				if (pessoa.status == 0){// 1 = deleta
					fseek(aux,0,2);
					status = fwrite(&pessoa, sizeof(struct Usuario), 1, aux);
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
			remove("Usuarios.bin");
			rename("auxiliar", "Usuarios.bin");
		}
		else{
			fclose(aux);
			remove("auxiliar");
		}
	}
}