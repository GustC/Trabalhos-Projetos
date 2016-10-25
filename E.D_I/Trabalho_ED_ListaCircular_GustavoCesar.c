#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct contato{
	char nome[100];
	char fone[15];
	struct contato *ant, *prox;
}TContato;

typedef struct indice{
	char letra;
	struct indice *ant,*prox;
	TContato *inicio;
}TIndice;

void cadastrar(TIndice **Li,char nome[]);
void exibir_fone(TIndice *L);
void alterar_fone(TIndice *L);
void exibir_agenda(TIndice *L);
void remover_contato(TIndice **L);
void limpar_lista(TIndice **L);
TIndice *verificar_indice(TIndice *L,char n[]);
TIndice *verificar_indice_posi(TIndice *L,char n[]);
TContato *verificar_contato_posi(TContato *L,char n[]);
TContato *busca_contato_nome_posi(TIndice *Li,char n[]);
TContato *verificar_contato(TContato *L,char n[]);



int main(){
	TContato *BuscaC;
	TIndice *Lista_indice=NULL,*aux;
	char op=' ',nome_aux[100],op2;
	do{
		if(op>=48 &&op<=57){			
			system("pause");
			system("cls");
		}
		printf(" M E N U\n");
		printf("1-Cadastrar\n2-Remover\n3-Exibir telefone do contato\n4-Alterar telefone\n5-Exibir Agenda\n"
			"6-Apagar agenda\n7-Sair\nDigite a opcao: ");
		scanf("%c",&op);fflush(stdin);
		switch(op){
		case '1':
			printf("\nDigite o nome ");
			do{
				gets(nome_aux);fflush(stdin);
				BuscaC = busca_contato_nome_posi(Lista_indice,nome_aux);
				if(BuscaC!=NULL)
					printf("Nome existente ! Digite outro nome: ");
			}while(BuscaC!=NULL);
			cadastrar(&Lista_indice,nome_aux);
			break;
		case '2': 
			remover_contato(&Lista_indice);
			break;
		case '3':
			exibir_fone(Lista_indice);
			break;
		case '4':
			alterar_fone(Lista_indice);
			break;
		case '5':
			exibir_agenda(Lista_indice);
			break;
		case '6':
			limpar_lista(&Lista_indice);
			break;
		case '7':
			break;
		default:
			printf("Opcao invalida !");
			break;
		}
	}while(op!='7');

	return 0;
}

void cadastrar(TIndice **Li,char nome[]){
	TContato *novo_c,*aux_c,*pos_c;
	TIndice *novo_i,*aux_i=*Li,*pos_i;
	if(*Li==NULL){// se a lista de Indices(Letras) esta vazia , adiciona
		novo_i = (TIndice *) malloc(sizeof(TIndice));
		*Li = novo_i;
		novo_i ->letra = toupper(nome[0]);
		novo_i->prox=novo_i;
		novo_i->ant=novo_i;
		novo_i->inicio=NULL;
	}
	else{
		aux_i=verificar_indice(*Li,nome);// vai retornar o endereço do indice, se existe algum indice com o nome dado
		if(aux_i==NULL){// se n existir , cria um indice
			pos_i=verificar_indice_posi(*Li,nome);//retorna a posisao do indice(letra) q seja maior q o novo indice
			novo_i=(TIndice *) malloc(sizeof(TIndice));
			novo_i->letra = nome[0];
			if(pos_i->letra < novo_i->letra){// adiciona no fim
				novo_i->prox=pos_i->prox;
				novo_i->ant=pos_i;
				pos_i->prox->ant=novo_i;
				pos_i->prox=novo_i;
				novo_i->inicio=NULL;
			}
			else{// adiciona no começo e no meio 
				novo_i->prox=pos_i;
				novo_i->ant=pos_i->ant;
				pos_i->ant->prox=novo_i;
				pos_i->ant=novo_i;
				novo_i->inicio=NULL;
			}
		}
	}
	aux_i=verificar_indice(*Li,nome);
	novo_c = (TContato *)malloc(sizeof(TContato));
	strcpy(novo_c->nome,nome);fflush(stdin);
	printf("Digite o tefone : ");
	gets(novo_c->fone);fflush(stdin);
	if(novo_c->nome[0]>=97 && novo_c->nome[0]<=122)
		novo_c->nome[0]=toupper(novo_c->nome[0]);
	if(aux_i->inicio==NULL){//se n existir contato com a letra desde indice
		novo_c->prox = novo_c;
		novo_c->ant=novo_c;
		aux_i->inicio=novo_c;
	}
	else{
		nome = novo_c->nome;
		pos_c=verificar_contato_posi(aux_i->inicio,nome);// retorna a posisao do contato com ordem alfabetica maior q a do nome q sera cadastrado
		if((pos_c->prox == aux_i->inicio) && strcmp(nome,pos_c->nome)>0){//add no fim
			novo_c->prox=pos_c->prox;
			novo_c->ant=pos_c;
			novo_c->prox->ant=novo_c;
			pos_c->prox=novo_c;

		}
		else if(pos_c->ant->prox == aux_i->inicio && strcmp(nome,pos_c->nome)<0){// add inicio
			novo_c->prox=pos_c;
			novo_c->ant=pos_c->ant;
			pos_c->ant->prox=novo_c;
			pos_c->ant=novo_c;
			aux_i->inicio = novo_c;
		}
		else{//add meio
			novo_c->prox=pos_c;
			novo_c->ant=pos_c->ant;
			pos_c->ant->prox=novo_c;
			pos_c->ant=novo_c;
		}
	}
}

TIndice *verificar_indice(TIndice *L,char nome[]){
	TIndice *aux=L;
	char letra;
	if(L==NULL)
		printf("Lista Vazia!\n");
	else{
		letra=toupper(nome[0]);
		do{
			if(aux->letra==letra)
				return aux;
			aux=aux->prox;
		}while(aux!=L);	

	}
	return NULL;
}

TIndice *verificar_indice_posi(TIndice *L,char n[]){
	TIndice *aux=L;
	char letra;
	if(L==NULL){
		printf("Lista Vazia!\n");
		return NULL;
	}
	else{
		letra=toupper(n[0]);
		do{
			if(aux->letra > letra)
				return aux;
			aux=aux->prox;
		}while(aux!=L);	
		return aux->ant;
	}
}

TContato *verificar_contato_posi(TContato *L,char n[]){
	TContato *aux=L;
	if(L==NULL){
		printf("Lista Vazia!\n");
		return NULL;
	}
	else{

		do{
			if(strcmp(n,aux->nome)<0)
				return aux;
			aux=aux->prox;
		}while(aux!=L);	
		return aux->ant;
	}

}

TContato *busca_contato_nome_posi(TIndice *Li,char n[]){
	TIndice *posI;
	TContato *posC;
	int i;
	char nomeAux[100],nome2Aux[100],letra=n[0];
	posI=verificar_indice_posi(Li,n);
	if(posI!=NULL && posI->inicio!=NULL){
		posC=posI->inicio;
		for(i=0;n[i]!=0;i++){
			nomeAux[i]=tolower(n[i]);
		}
		nomeAux[i]=0;
		do{
			for(i=0;i!=strlen(posC->nome);i++){
				nome2Aux[i]=tolower(posC->nome[i]);
			}
			nome2Aux[i]=0;
			if(strcmp(nomeAux,nome2Aux)==0)
				return posC;
			posC=posC->prox;
		}while(posI->inicio!=posC);
	}
	return NULL;
}

TContato *verificar_contato(TContato *L,char n[]){


}

void exibir_fone(TIndice *L){
	TContato *BuscaC;
	char nome_aux[100],op;
	if(L==NULL){
		printf("Lista vazia!\n");
	}
	else{
		printf("\nDigite o nome :");
		do{
			gets(nome_aux);fflush(stdin);
			BuscaC = busca_contato_nome_posi(L,nome_aux);
			if(BuscaC==NULL){
				printf("Nome nao existente !\n ");
				do{
					printf("Deseja procurar outro nome? s - Sim\nn - Nao\n"
						"Digite sua escolha :");
					scanf("%c",&op);
				}while(op != 's' && op != 'n');
				if(op == 'n'){
					printf("Procura cancelada !\n");
					return;
				}
			}
		}while(BuscaC==NULL);
		printf("Contato %s \nTefone : %s",BuscaC->nome,BuscaC->fone);
	}
}

void alterar_fone(TIndice *L){
	TContato *BuscaC;
	char nome_aux[100],op;
	if(L==NULL){
		printf("Lista vazia !\n");
	}
	else{
		printf("\nDigite o nome :");
		do{
			gets(nome_aux);fflush(stdin);
			BuscaC = busca_contato_nome_posi(L,nome_aux);
			if(BuscaC==NULL){
				printf("Nome nao existente !\n ");
				do{
					printf("Deseja procurar outro nome? s - Sim\nn - Nao\n"
						"Digite sua escolha :");
					scanf("%c",&op);
				}while(op != 's' && op != 'n');
				if(op == 'n'){
					printf("Procura cancelada !\n");
					return;
				}
			}

		}while(BuscaC==NULL);
		printf("Digite o novo telefone: ");
		gets(BuscaC->fone);
		printf("Alteracao realizada com sucesso!\n");
	}
}

void exibir_agenda(TIndice *L){
	TContato *aux_c;
	TIndice *aux_i=L;
	if(L == NULL)
		printf("Listas vazia!\n");
	else{
		printf("\nExibindo Lista completa : \n");
		do{
			printf("\n	Letra %c:\n",aux_i->letra);
			aux_c = aux_i->inicio;
			do{
				printf("		nome : %s telefone : %s\n",aux_c->nome,aux_c->fone);
				aux_c = aux_c ->prox;
			}while(aux_c!=aux_i->inicio);
			aux_i = aux_i ->prox;
		}while(aux_i!=L);
	}
}

void remover_contato(TIndice **L){
	TContato *BuscaC,*auxC;
	TIndice *pos_i,*auxI,*aux_LI=*L;
	char nome_aux[100],op;
	if(L==NULL){
		printf("Lista Vazia!");
	}
	else{
		printf("\nDigite o nome :");
		do{
			gets(nome_aux);fflush(stdin);
			BuscaC = busca_contato_nome_posi(aux_LI,nome_aux);
			if(BuscaC==NULL){
				printf("Nome nao existente !\n ");
				do{
					printf("Deseja procurar outro nome? s - Sim\nn - Nao\n"
						"Digite sua escolha :");
					scanf("%c",&op);fflush(stdin);
				}while(op != 's' && op != 'n');
				if(op == 'n'){
					printf("Procura cancelada !\nOperacao de remocao cancelada!\n");
					return;
				}
			}
		}while(BuscaC==NULL);
		pos_i=verificar_indice(*L,nome_aux);
		if((BuscaC->prox == pos_i->inicio ) && BuscaC->ant == pos_i->inicio){    // Quando houver somente 1 contato na lista do indice , remove os dois (indice e contato)
			if(pos_i->prox == pos_i->ant){//se so existir um unico indice
				pos_i->inicio == NULL;
				free(BuscaC);
				free(pos_i);
				*L = NULL;
			}
			else{// mais de um indices na lista
				pos_i->inicio == NULL;
				free(BuscaC);
				auxI = pos_i->ant;
				pos_i->prox->ant=auxI;
				auxI->prox=pos_i->prox;
				free(pos_i);
			}
		}
		else if(pos_i->inicio == BuscaC){
			auxC = BuscaC->ant;
			auxC->prox = BuscaC->prox;
			BuscaC->prox->ant = auxC;
			pos_i->inicio = BuscaC->prox;
			free(BuscaC);
		}
		else{
			auxC = BuscaC->ant;
			auxC->prox = BuscaC->prox;
			BuscaC->prox->ant = auxC;
			free(BuscaC);
		}
		printf("Remocao realizada com sucesso!\n");
	}

}

void limpar_lista(TIndice **L){
	TIndice *posUlt_i,*aux_I;
	TContato *posUlt_c,*aux_C;
	if(*L==NULL){
		printf("Lista vazia!");
	}
	else{
		posUlt_i = (*L)->ant;
		posUlt_c = posUlt_i->inicio->ant;
		if((posUlt_i->ant == *L && posUlt_i->prox == *L) && posUlt_i->inicio->prox == posUlt_i->inicio->ant){// caso com um so indice e um contato
			aux_C = posUlt_i->inicio;							
			posUlt_i->inicio=NULL;
			free(aux_C);
			*L = NULL;
			free(posUlt_i);
		}
		else{
			do{
				do{
					aux_C= posUlt_c->prox;
					posUlt_c->ant->prox = aux_C;
					aux_C->ant=posUlt_c->ant;
					free(posUlt_c);
					posUlt_c=aux_C->ant;
				}while(posUlt_c!=posUlt_i->inicio);

				if((posUlt_i->ant == *L && posUlt_i->prox == *L) && posUlt_c==aux_C)
					break;
				posUlt_i->inicio==NULL;
				free(posUlt_c);
				aux_I  = posUlt_i->prox;
				posUlt_i -> ant ->prox= aux_I;
				aux_I->ant=posUlt_i->ant;
				free(posUlt_i);
				posUlt_i = posUlt_i->ant;
			}while(posUlt_i!=*L);

			aux_C = posUlt_i->inicio;							
			posUlt_i->inicio=NULL;
			free(aux_C);
			*L = NULL;
			free(posUlt_i);

		}
	printf("Lista limpa com sucesso!\n");
	
	}
}

