#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "filesystem.h"

int fileSystem() {
	printf("Teste do Sistema de Arquivos\n\n");

	int arquivoTest01;

	//teste de abertura de arquivo
	arquivoTest01 = abrir("arquivoTest01.txt");
	if (arquivoTest01 != ERRO)
	{
		printf("ArquivoTest01 Aberto com sucesso!!!!");
	}
	else
	{
		printf("FALHA na abertura do arquivoTest01!!!!");
	}

	return EXIT_SUCCESS;
}

int main() {


	return fileSystem();
}