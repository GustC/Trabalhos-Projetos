#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structs.h"
#include "Produtos.h"

void menuCategorias(FILE *arq,FILE *arqProduto,FILE *avaliacao);
void inserirCate(FILE *arq);
void consultarCate(FILE *arq,int posisao);
void alterarCate(FILE *arq,int posisao);
void removerCate(FILE *arq,char login[]);
void listarCate(FILE *arq);
void deletarProdutos(FILE *arqProduto,FILE *avaliacao,int cod);
void manutencao2(FILE *arq);