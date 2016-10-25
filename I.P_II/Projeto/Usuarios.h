#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structs.h"

void menuUsuarios(FILE *arq,FILE *arqAvaliacao,FILE *arqProdutos);
void inserir(FILE *arq);
void consultar(FILE *arq,FILE *arqAvaliacao,FILE *arqProdutos,int posisao);
void alterar(FILE *arq,int posisao);
void remover(FILE *arq,char login[]);
void listar(FILE *arq);
void deletarAvaliacoesUsuarios(FILE* avaliacoes, int cod);
void manutencao1(FILE *arq);
