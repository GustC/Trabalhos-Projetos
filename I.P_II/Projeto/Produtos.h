#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structs.h"

void menuProdutos(FILE *arq,FILE *arqCate,FILE *arqAvaliacao);
void inserirProd(FILE *arq,FILE *arqCate);
void consultarProd(FILE *arq,FILE *arqAvaliacao,int posisao);
void alterarProd(FILE *arq,int posisao,FILE *arqCate);
void removerProd(FILE *arq,FILE *avaliacao);
void listarProd(FILE *arq);
void deletarAvaliacoesProd(FILE* avaliacoes, int cod);
void manutencao3(FILE *arq);
