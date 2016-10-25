#include <stdio.h>

#ifndef Estruturas
#define Estruturas

typedef struct Usuario{
	int codigo;
	char nome[50];
	char login[15];
	char senha[15];
	int idade;
	char sexo; // M – Masculino, F – Feminino
	char telefone[17];
	int status;
};

typedef struct Categorias{
	int codigo;
	char nome[50];
	int status;
};

typedef struct Produtos{
	int codigo;
	char titulo[100]; // ex: texto que fica destacado num e-commerce
	char descricao[256];
	int categoria; // código da categoria que está no arquivo categorias.bin
	float preco; // representa um valor numérico com 2 casas decimais
	int status;
};

typedef struct Avaliacao{
	int codigoUsuario; // usuário que está no arquivo usuarios.bin
	int codigoProduto; // produto que está no arquivo produtos.bin
	int nota;
	int comprou;
	int status;
};

typedef struct Busc{
	int codigoAux;
	char nomeAux[50],telefoneAux[17],loginAux[15];
};
#endif