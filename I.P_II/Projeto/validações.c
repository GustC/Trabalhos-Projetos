#include <stdio.h>
#include "Validações.h"
#include "structs.h"

int busca(FILE *arq,char o){
	struct Usuario c;
	char opcao,nomeAux[50]="",telefoneAux[15]="",loginAux[15]="",senhaAux[15]="";
	int i=0,j,qtd=0,teste,codigoAux;
	switch (o){
	case 'P':
		digitarFone(telefoneAux);fflush(stdin);
		break;
	case 'N':
		digitarNome(nomeAux);fflush(stdin);
		for(j=0;j<(strlen(nomeAux));++j)
			nomeAux[j] = tolower(nomeAux[j]);
		break;
	case 'L':
		digitarLogin(loginAux);fflush(stdin);
		break;
	case 'C':
		digitarCodig(&codigoAux);
		break;
	case 'S':
		digitarSenha(senhaAux);
		break;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c,sizeof(struct Usuario),1,arq);
		if( teste == 0){
			if(feof(arq) != 0)
				break;
		}
		else
			++qtd;
	}
	if (qtd == 0){
		return -2;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c, sizeof(struct Usuario), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		i++;
		if(c.status == 1)
			continue;
		fflush(stdin);
		switch (o){
		case 'P': 
			if (strcmp(c.telefone, telefoneAux) == 0)
				return i;
			break;
		case 'N':
			for(j=0;j<(strlen(c.nome));++j)
				c.nome[j] = tolower(c.nome[j]);
			if(strstr(c.nome, nomeAux) !=NULL){
				printf("\nUsuario encontrado: %s\nEste era o desejado?(S- Sim / N- Nao)\nDigite a resposta: ",c.nome);
				scanf("%c",&opcao);fflush(stdin);
				opcao = toupper(opcao);
				if(opcao == 'S')
					return i;
			}
			break;
		case 'L':
			if(strcmp(c.login, loginAux) == 0){
				return i;
			}
			break;
		case 'C':
			if(c.codigo == codigoAux)
				return i;
			break;
		case 'S':
			if (strcmp(c.senha, senhaAux) == 0)
				return i;
		}

	}
	return -1;							//nao encontrado
}

int CateBusca(FILE *arq,char o){
	struct Categorias c;
	char opcao,nomeAux[50]="",loginAux[15]="",aux2[50]="",b;
	int i=0,j,qtd=0,teste,codigoAux;
	switch (o){
	case 'N':
		digitarNome(nomeAux);fflush(stdin);
		break;
	case 'C':
		digitarCodig(&codigoAux);
		break;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c,sizeof(struct Categorias),1,arq);
		if( teste == 0){
			if(feof(arq) != 0)
				break;
		}
		else
			++qtd;
	}
	if (qtd == 0){
		return -2;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c, sizeof(struct Categorias), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		if(c.status == 1)
			continue;
		i++;
		if(c.status == 1)
			continue;
		fflush(stdin);
		switch (o){
		case 'N':
			for(j=0;j<(strlen(c.nome));++j)
				c.nome[j] = tolower(c.nome[j]);
			if(strstr(c.nome, nomeAux) !=NULL){
				printf("\nUsuario encontrado: %s\nEste era o desejado?(S- Sim / N- Nao)\nDigite a resposta: ",c.nome);
				scanf("%c",&opcao);fflush(stdin);
				opcao = toupper(opcao);
				if(opcao == 'S')
					return i;
			}
			break;
		case 'C':
			if(c.codigo == codigoAux)
				return i;
			break;
		}

	}
	return -1;							//nao encontrado
}

int Produtobusca(FILE *arq,char o){//----------------------------
	struct Produtos c;
	char opcao,tituloAux[100]="",loginAux[15]="",DescriAux[256]="";
	int i=0,j,qtd=0,teste,codigoAux,categoAux;
	fflush(stdin);
	switch (o){
	case 'C':
		digitarCodig(&codigoAux);
		break;
	case 'D':
		digitarDescri(DescriAux);fflush(stdin);
		for(j=0;j<(strlen(DescriAux));++j)
			DescriAux[j] = tolower(DescriAux[j]);
		break;
	case 'G':
		digitarCodig(&categoAux);
		break;
	case 'T':
		digitarTitulo(tituloAux);fflush(stdin);
		for(j=0;j<(strlen(tituloAux));++j)
			tituloAux[j] = tolower(tituloAux[j]);
		break;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c,sizeof(struct Produtos),1,arq);
		if( teste == 0){
			if(feof(arq) != 0)
				break;
		}
		else
			++qtd;
	}
	if (qtd == 0){
		return -2;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c, sizeof(struct Produtos), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		i++;
		fflush(stdin);
		if(c.status == 1)
			continue;
		switch (o){
		case 'C': 
			if (c.codigo == codigoAux)
				return i;
			break;
		case 'T':
			for(j=0;j<(strlen(c.titulo));++j)
				c.titulo[j] = tolower(c.titulo[j]);
			if(strstr(c.titulo, tituloAux) !=NULL){
				printf("\nUsuario encontrado: %s\nEste era o desejado?(S- Sim / N- Nao)\nDigite a resposta: ",c.titulo);
				scanf("%c",&opcao);fflush(stdin);
				opcao = toupper(opcao);
				if(opcao == 'S')
					return i;
			}
			break;
		case 'D':
			for(j=0;j<(strlen(c.descricao));++j)
				c.descricao[j] = tolower(c.descricao[j]);
			if(strstr(c.descricao, DescriAux) !=NULL){
				printf("\nDescricao encontrada: %s\nEsta era a desejada?(S- Sim / N- Nao)\nDigite a resposta: ",c.descricao);
				scanf("%c",&opcao);fflush(stdin);
				opcao = toupper(opcao);
				if(opcao == 'S')
					return i;
			}

			break;
		case 'G':
			if(c.categoria == categoAux)
				return i;
			break;
		}
	}
	return -1;							//nao encontrado
}

int PosiProduto(FILE *arq,int cod){
	int teste,qtd=0,i=0;
	struct Produtos produto;
	
	fseek(arq,0,1);
	while(1){
		teste = fread(&produto, sizeof(struct Produtos), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				return -2;
		i++;
		fflush(stdin);
		if(produto.codigo == cod)
			return i;
	}
	return -1;		
}

int PosiAvaliacao(FILE *arq,int cod){
	int teste,qtd=0,i=0;
	struct Avaliacao avalia;
	/*while(1){
	teste = fread(&avalia,sizeof(struct Avaliacao),1,arq);
	if( teste == 0){
	if(feof(arq) != 0)
	break;
	}
	else
	++qtd;
	}
	if (qtd == 0){
	return -2;
	}*/
	fseek(arq,0,1);
	while(1){
		teste = fread(&avalia, sizeof(struct Avaliacao), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				return -2;
		i++;
		fflush(stdin);
		if(avalia.codigoUsuario == cod)
			return i;
	}
	return -1;		
}

int VerificarUsuario(FILE *arq, char nome[]){
	int teste,qtd=0,i=0;
	struct Usuario c;
	fseek(arq,0,0);
	while(1){
		teste = fread(&c, sizeof(struct Usuario), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		i++;
		fflush(stdin);
		if(strcmp(nome,c.nome)==0)
			return i;
	}
	return -1;			
}

int VerificarCodUsuario(FILE *arq,int codaux){
	int teste,qtd=0,i=0;
	struct Usuario c;
	fseek(arq,0,0);
	while(1){
		teste = fread(&c, sizeof(struct Usuario), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		i++;
		fflush(stdin);
		if(codaux == c.codigo)
			return i;
	}
	return -1;			
}

int buscaCodCate(FILE *arq, int codaux){
	int teste,qtd=0,i=0;
	struct Categorias c;
	fseek(arq,0,0);
	while(1){
		teste = fread(&c,sizeof(struct Categorias),1,arq);
		if( teste == 0){
			if(feof(arq) != 0)
				break;
		}
		else
			++qtd;
	}
	if (qtd == 0){
		return -2;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&c, sizeof(struct Categorias), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		i++;
		fflush(stdin);
		if(codaux==c.codigo)
			return i;
	}
	return -1;			
}

void digitarNome(char nomeaux[]){
	int cont=0;
	char teste;
	fflush(stdin);
	printf("Digite o nome (no max 50 caracteres): ");
	do{
		if((teste = getche())== 13)
			break;
		fflush(stdin);
		nomeaux[cont] = teste;
		if(cont > 49)
			getche();
		else if(nomeaux[cont] == 8 && cont > 0){
			printf(" %c",8);
			cont--;
			continue;
		}
		else
			cont++;
	}while(cont >= 0);
}

void digitarLogin(char logAux[]){
	int cont=0,resp;
	char teste;
	fflush(stdin);
	printf("Digite o login (no max 50 caracteres): ");
	do{
		if((teste = getche())== 13)
			break;
		fflush(stdin);
		logAux[cont] = teste;
		if(cont > 14)
			getche();
		else if(logAux[cont] == 8 && cont > 0){
			printf(" %c",8);
			cont--;
			continue;
		}
		else
			cont++;
	}while(cont >= 0);
}

void digitarTitulo(char tituaux[]){
	int cont=0;
	char teste;
	printf("Digite o titulo (no max 99 caracteres): ");
	do{
		if((teste = getche())== 13)
			break;
		fflush(stdin);
		tituaux[cont] = teste;
		if(cont > 98)
			getche();
		else if(tituaux[cont] == 8 && cont > 0){
			printf(" %c",8);
			cont--;
			continue;
		}
		else
			cont++;
	}while(1);
	tituaux[cont]=0; 

}

void digitarDescri(char descriaux[]){
	int cont=0;
	char teste;
	printf("Digite a descricao (no max 15 caracteres): ");
	do{
		if((teste = getche())== 13)
			break;
		fflush(stdin);
		descriaux[cont] = teste;
		if(cont > 255)
			getche();
		else if(descriaux[cont] == 8 && cont > 0){
			printf(" %c",8);
			cont--;
			continue;
		}
		else
			cont++;
	}while(1);
	descriaux[cont]=0; 
}

void digitarCodig(int *codig){
	int x;
	char teste;
	printf("Digite o codigo: (somente numeros)\ndigite : ");
	scanf("%i",&x);
	*codig = x;
	
}

void digitarFone(char nomeaux[]){

	int cont=0;
	char teste;
	printf("Digite o telefone (no max 17 caracteres): ");
	do{
		if((teste = getche())== 13)
			break;
		fflush(stdin);
		nomeaux[cont] = teste;
		if(cont > 16)
			getche();
		else if(nomeaux[cont] == 8 && cont > 0){
			printf(" %c",8);
			cont--;
			continue;
		}
		else
			cont++;
	}while(1);
	nomeaux[cont]=0;
}

void digitarSenha(char x[]){

	int cont=0;
	char teste;
	x[cont]=0;
	printf("Digite a senha (no max 14 caracteres): ");
	do{
		if((teste = getch())== 13)
			break;
		fflush(stdin);

		x[cont] = teste;
		if(cont > 16)
			getche();
		else if(x[cont] == 8 && cont > 0){
			printf("%c %c",8,8);
			cont--;
			continue;
		}
		else
			printf("*");
		cont++;
	}while(1);
	x[cont]=0;
}

void digitarPreco(float *x){
	float precoaux;
	int cont=0, ponto=0;
	char teste,numeroaux[200],parteDeci[3];
	printf("Digite o preco (somente numeros e ponto para casas decimais): ");
	do{
		if(ponto == 3){
			numeroaux[cont]=0;
			parteDeci[ponto -1]=0;
			break;
		}
		if((teste = getche())== 13){
			numeroaux[cont]=0;
			break;
		}

		fflush(stdin);
		numeroaux[cont] = teste;
		if(teste == '.' || ponto > 0){
			if(ponto >= 1)
				parteDeci[ponto-1]=teste;
			cont ++;
			ponto++;

		}
		else if((teste < 48 || teste > 57 || numeroaux[cont] == 8) && cont > 0 ){
			printf(" %c",8);
			cont--;
			
		}
		else
			cont++;
	}while(1);
	precoaux = atoi(numeroaux);
	precoaux = precoaux + ((atoi(parteDeci))/100.0);
	*x = precoaux;
}

int verificarAvaliacao(FILE *arq,int codigProduto,int codigUsuario,int flag){
	int teste,qtd=0,i=0;
	struct Avaliacao avali;
	fseek(arq,0,0);
	while(1){
		teste = fread(&avali,sizeof(struct Avaliacao),1,arq);
		if( teste == 0){
			if(feof(arq) != 0)
				break;
		}
		else
			++qtd;
	}
	if (qtd == 0){
		return -2;
	}
	fseek(arq,0,0);
	while(1){
		teste = fread(&avali, sizeof(struct Avaliacao), 1, arq);
		if(teste == 0)	
			if(feof(arq)!=0)
				break;
		i++;
		fflush(stdin);
		if(flag == 1){
			if(codigProduto == avali.codigoProduto)
				if(codigUsuario == avali.codigoUsuario)
					return i;
		}
		if(flag == 2){
			if(codigUsuario = avali.codigoUsuario)
				return avali.codigoProduto;
		}
	}
	return -1;			
}

int Realizarlogin(FILE *usuarios, int aux){
	int sen, st = 0 ,log;
	char t,escolha;
	log = aux;
	if (log == 1){
		printf("Deslogue antes de logar de novo!\n");
		system("pause");
		return log;
	}
	else{
		log = busca(usuarios, 'L');
		printf("\n");
		sen = busca(usuarios, 'S');
		printf("\n");
		while (log == -1 || sen == -1)
		{
			printf("Senha ou login errados!\n");
			printf("Deseja tentar logar novamente?(S - Sim / N - Nao)"
				"Digite sua escolha: ");
			do{
				fflush(stdin);
				scanf("%c",&escolha);fflush(stdin);
				escolha=toupper(escolha);

				if(escolha != 'S' && escolha != 'N')
					printf("Opcao invalida!\n");
			}while(escolha != 'S' && escolha != 'N');
			if(escolha == 'N')
				return 0;// ---- log com 0 = nao logado
			t = 'L';
			log = busca(usuarios, t);
			printf("\n");
			t = 'S';
			sen = busca(usuarios, t);
		}
		printf("Login realizado com sucesso!\n");
		system("pause");
		return log;
	}
}

int Deslogar(int log){
	if (log == 1)
		log = 0;
	else{
		printf("Voce nao esta logado!\n");
		system("pause");
	}
	return log;
}

float CalcularMedia(FILE *avaliacoes,int codpruduto){
	float media;
	int soma=0,qtd=0,st,somaPessos=0;
	struct Avaliacao a;
	fseek(avaliacoes, 0, 0);
	while (1){
		st=fread(&a, sizeof(struct Avaliacao), 1, avaliacoes);
		if (st != 1){
			if(feof(avaliacoes) != 0)
				break;
			printf("Erro de leitura");
			system("pause");
			return;
		}
		if(a.status == 1)
			continue;
		else{
			
			if (a.codigoProduto == codpruduto){
				if (a.comprou == 1){
					soma = soma + (a.nota) * 2;
					somaPessos = somaPessos + 2;
				}
				else{
					soma = soma + (a.nota);
					somaPessos = somaPessos + 1;
				}
				qtd++;
			}
		}
	}
	if(somaPessos != 0)
		media = soma / somaPessos;
	else
		media = -1;
	return media;
}

void ordenar(FILE *arq , FILE *avaliacoes,int qtd,char opcao){
	int i=0,qtdAva=0,j,chave,resp,aux;
	float chavePreco,vetMedias[100]={0};
	char chaveTitulo[50];
	struct Produtos produto,ProduAux[1000],auxStruct;
	struct Avaliacao avali;
	fseek(arq,0,0);
	while(1){
		resp=fread(&produto,sizeof(struct Produtos),1,arq);
		if(resp == 0)
			if(feof(arq) != 0)
				break;
		if(produto.status==1)
			continue;
		ProduAux[i] = produto;
		vetMedias[i] = CalcularMedia(avaliacoes,produto.codigo);
		i++;
	}
	for (i = 1; i <= qtd - 1; i++) {
		auxStruct = ProduAux[i];
		chavePreco = vetMedias[i];
		j = i - 1;
		while (j >= 0 && ProduAux[j].categoria > auxStruct.categoria) {
			ProduAux[j+1] = ProduAux[j];
			vetMedias[j+1] = vetMedias[j];
			j = j - 1;
		}
		ProduAux[j+1] = auxStruct;
		vetMedias[j+1] = chavePreco;
	}	switch (opcao)
	{
	case 'T':
		for (i = 1; i <= qtd - 1; i++) {
			auxStruct = ProduAux[i];
			j = i - 1;
			while (j >= 0 && strcmp(ProduAux[j].titulo,auxStruct.titulo)>0) {
				ProduAux[j+1] = ProduAux[j];
				j = j - 1;
			}
			ProduAux[j+1] = auxStruct;
		}
		break;
	case 'P':
		for (i = 1; i <= qtd - 1; i++) {
			auxStruct = ProduAux[i];
			j = i - 1;
			while (j >= 0 && ProduAux[j].preco < auxStruct.preco) {
				ProduAux[j+1] = ProduAux[j];
				j = j - 1;
			}
			ProduAux[j+1] = auxStruct;
		}
		break;
	case 'A':
		for (i = 1; i <= qtd-1 ; i++) {
			auxStruct = ProduAux[i];
			chavePreco = vetMedias[i];
			j = i - 1;
			while (j >= 0 && vetMedias[j] < chavePreco) {
				ProduAux[j+1] = ProduAux[j];
				vetMedias[j+1] = vetMedias[j];
				j = j - 1;
			}
			ProduAux[j+1] = auxStruct;
			vetMedias[j+1] = chavePreco;

		}
		break;
			 
	}
	for(i=0;i<qtd;i++){
		printf("\nCategoria: %i\n",ProduAux[i].categoria);
		if(opcao == 'A'){
			if(vetMedias[i]==-1)
				printf("Produto Sem avaliacao! ");
			else
				printf("Media de avaliacoes: %.1f",vetMedias[i]);
		}
		printf("\nTitulo: ");
		puts(ProduAux[i].titulo);
		printf("codigo: %i\n",ProduAux[i].codigo);
		printf("Preco: %.2f",ProduAux[i].preco);
		printf("\nDescricao: ");
		puts(ProduAux[i].descricao);
		printf("\n\n");
	}
}