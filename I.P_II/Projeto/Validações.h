#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include "structs.h"

int verificarCodigo();
int verificarNome(char *x[]);
int busca(FILE *arq,char t);//-- para usuario
int CateBusca(FILE *arq,char t);
int Produtobusca(FILE *arq,char t);
int VerificarUsuario(FILE *arq,char []);
int VerificarCodUsuario(FILE *arq,int codaux);
int buscaCodCate(FILE *arq,int codaux);
int PosiProduto(FILE *arq,int cod);//---retorna posisao do produto com base no codigo
int PosiAvaliacao(FILE *arq,int cod);
int verificarAvaliacao(FILE *arq,int codigProduto,int codigUsuario,int flag);//--- 1 = codigo produto  , ver o usuario e 2 = o inverso
void MenuBuscaA(char x);
void digitarLogin(char x[]);
void digitarCodig(int x);
void digitarNome(char x[]);
void digitarFone(char x[]);
void digitarSenha(char x[]);
void digitarPreco(float x[]);
void digitarDescri(char x[]);
void digitarTitulo(char x[]);			
int Realizarlogin(FILE*usuarios,int aux);
int Deslogar(int log);
float CalcularMedia(FILE*avaliacoes,int codpruduto);
void ordenar(FILE *arq , FILE *avaliacoes,int qtd,char opcao);