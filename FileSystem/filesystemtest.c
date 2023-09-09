#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "filesystem.h"

int fileSystem() {
	printf("Teste do Sistema de Arquivos\n\n");

	int arquivoTest01;
	void* conteudoLido;

	char dados[] = "Teste se estou escrevendo no arquivo!!!";
	int bytesEscritos;

	//teste de abertura de arquivo
	arquivoTest01 = abrir("arquivoTest01.txt");
	if (arquivoTest01 != ERRO)
	{
		printf("\nArquivoTest01 Aberto com sucesso!!!!");
	}
	else
	{
		printf("\nFALHA na abertura do arquivoTest01!!!!");
	}

	//teste na leitura do arquivo
	conteudoLido = ler(arquivoTest01, sizeof(char), 100);

	if (conteudoLido != NULL) {
		printf("\nConteudo lido do arquivo: %s\n", (char*)conteudoLido);
		free(conteudoLido);
	}
	else {
		printf("\nErro ao ler o arquivo.\n");
	}

	//testando escrever no arquivo

	bytesEscritos = escrever(arquivoTest01, dados, sizeof(char), strlen(dados));
	if (bytesEscritos != ERRO) {
		printf("\n%s",dados);
		printf("\nBytes escritos no arquivo: %d\n", bytesEscritos);
	}
	else {
		printf("\nErro ao escrever no arquivo.\n");
	}

	//fechar arquivo
	if (fechar(arquivoTest01) != ERRO) {
		printf("nArquivoTest01 fechado com sucesso!!!!\n");
	}
	else {
		printf("\nErro ao fechar o arquivo.\n");
	}

	return EXIT_SUCCESS;
}

int main() {


	return fileSystem();
}