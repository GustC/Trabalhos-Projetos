#include <stdio.h>
#include "Avaliações.h"
#include "Validações.h"

void menuAvaliacoes(FILE* avaliacoes, FILE* produtos, FILE*usuarios, int log){
	int o, i,posUsuario, status, statusa,verificar;
	char esc,opcao;
	struct Avaliacao a;
	struct Produtos p;
	struct Usuario u;
	system("cls");
	posUsuario = log;
	if (log == 0){
		printf("Por favor faca login antes de avaliar.\n");
		system("pause");
		return;
	}
	else{
		do{
			printf("Informe a sua escolha:\n1-Cadastrar uma nova avaliacao;\n2-Sair\nEscolha: ");
			scanf_s("%d", &o); fflush(stdin);
			while (o != 1 && o != 2){
				printf("Opcao invalida!");
				printf("Informe a sua escolha:\n1-Cadastrar uma nova avaliacao\n3-Sair\nEscolha: ");
				scanf_s("%d", &o); fflush(stdin);
			}
			system("cls");
			switch (o){
			case 1:
				printf("Como voce deseja achar o produto? (Parte do titulo-T ||Codigo do produto-C)");
				esc = toupper(getchar()); fflush(stdin);
				while (esc != 'T' && esc != 'C'){
					printf("Opcao invalida!");
					printf("Como voce deseja achar o produto? (Parte do titulo-T ||Codigo do produto-C)");
					esc = toupper(getchar()); fflush(stdin);
				}
				switch (esc){
				case 'T':
					i = Produtobusca(produtos, esc);
					break;
				case 'C':
					i = Produtobusca(produtos, esc);
					break;
				}			
				if (i == -1)
					printf("Nao encontrado!");
				else if (i == -2)
					printf("Armazenamento de produtos vazio!");
				else {
					fflush(stdin);
					fseek(produtos, sizeof(struct Produtos)*(i-1), 0);
					fseek(usuarios, sizeof(struct Usuario)*(posUsuario-1), 0);//// 
					status = fread(&p, sizeof(struct Produtos), 1, produtos);
					status = fread(&u, sizeof(struct Usuario), 1, usuarios);
					verificar = verificarAvaliacao(avaliacoes,p.codigo,u.codigo,1);// ---- ultimo paremetro '1' e o tipo de verificacao
					if (status != 1)
						printf("Erro de leitura");
					else if( verificar != -1 && verificar != -2){
							printf("Voce ja realizou uma avaliacao deste mesmo produto!"
								"\nA avaliacao sera cancela!\n");
							system("pause");
						}
					else{
						
						printf("\nQuantas estrelas voce daria para o produto?\n\t(de 5-muito bom e 1 para muito ruim)\nNota: ");
						scanf_s("%d", &a.nota);
						while (a.nota > 5 || a.nota < 1){
							printf("\nNota invalida!\nQuantas estrelas voce daria para o produto? (de 5-muito bom e 1 para muito ruim)\nNota: ");
							scanf_s("%d", &a.nota);
						} 
						fflush(stdin);
						printf("Voce ja comprou ou utilizou este produto?(S - Sim/ N - Nao)"
							"\nDigite a opcao: ");
						scanf("%c",&opcao);fflush(stdin);
						opcao = toupper(opcao);
						fflush(stdin);
						while(opcao != 'S' && opcao != 'N'){
							printf("\nOpcao invalida!\nDigite corretamente(S - Sim/ N - Nao): ");
							scanf("%c",&opcao);fflush(stdin);
							opcao = toupper(opcao);
						}
						if(opcao == 'S')
							a.comprou = 1;
						else
							a.comprou = 0;
						a.status = 0;
						a.codigoProduto = p.codigo;
						a.codigoUsuario = u.codigo;
						fseek(avaliacoes,0,2);
						statusa = fwrite(&a, sizeof(struct Avaliacao), 1, avaliacoes);
						if (statusa != 1)
							printf("Erro na escrita!");
						else{
							printf("Cadastramento da nova avaliacao feita com sucesso!\n");
							printf("Agradecemos a sua avaliacao!\n");
						}
					}
				}
				break;
			case 2:
				printf("\n\t\tObrigado !\nVoce sera deslogado e retornado para o menu principal!\n");
				system("pause");
				break;
			}
		} while (o != 2);
		return;
	}
}

void manutencao4(FILE* arq){
	FILE *aux;
	int status, erro = 0;
	struct Avaliacao avaliacao;
	aux = fopen("auxiliar", "wb");
	if (aux == NULL)
		printf("ERRO!\n");
	else{
		fseek(arq, 0, 0);

		while (1){
			status = fread(&avaliacao, sizeof(struct Avaliacao), 1, arq);
			if (status != 1){
				if (!feof(arq)){
					printf("Erro durante a limpeza, Erro de leitura!\n");
					erro = 1;
				}
				break;
			}
			else{
				if (avaliacao.status == 0){// 1 = deleta
					fseek(aux, 0, 2);
					status = fwrite(&avaliacao, sizeof(struct Avaliacao), 1, aux);
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
			remove("Avaliacoes.bin");
			rename("auxiliar", "Avaliacoes.bin");
		}
		else{
			fclose(aux);
			remove("auxiliar");
		}
	}
}
