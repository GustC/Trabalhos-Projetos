#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "structs.h"


void menuAvaliacoes(FILE* avaliacoes, FILE* produtos, FILE*usuarios,int log);
void avaliacao(FILE* avaliacoes, FILE* produtos, FILE*usuarios,int log);
void manutencao4(FILE* avaliacoes);
int buscaAvaliacao(FILE* arq, int codigoAux);