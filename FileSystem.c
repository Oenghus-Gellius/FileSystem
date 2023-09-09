#include "fileSystem.h"

// Representa o sistema de arquivos.
Arquivo sistemaArquivos[NUMERO_MAXIMO_AQUIVOS];

// Usada para gerar o ID (descritor) de cada arquivo do sistema de arquivos.
unsigned geraID = 0;

/*  Abre o arquivo com o nome especificado.
    Retorna o ID (descritor) do arquivo em caso de sucesso ou ERRO se ocorrer um erro.
*/
int abrir(char* nomeArquivo) {
    return ERRO;
}

/* Lê o arquivo identificado por ID.
   Faz a leitura de n (tamanho) bytes do arquivo com a quantidade indicada.
   Retorna o conteúdo lido do arquivo em caso de sucesso ou NULL se ocorrer um erro.
*/
void* ler(int ID, unsigned tamanho, unsigned quantidade) {
    return NULL;
}

/* Escreve o conteúdo do buffer no arquivo identificado por ID.
   Faz a escrita de n (tamanho) bytes no arquivo com a quantidade indicada.
   Retorna o número de bytes escritos no arquivo em caso de sucesso ou ERRO se ocorrer um erro.
*/
int escrever(int ID, const void* buffer, unsigned tamanho, unsigned quantidade) {
    return ERRO;
}

/* Fecha o arquivo com o ID especificado.
   Retorna 1 em caso de sucesso ou ERRO se ocorrer um erro.
*/
int fechar(int ID) {
    return ERRO;
}