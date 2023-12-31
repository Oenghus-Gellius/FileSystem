#define _CRT_SECURE_NO_WARNINGS

#include "filesystem.h"
#include <string.h>
#include <stdlib.h>


// Representa o sistema de arquivos.
Arquivo sistemaArquivos[NUMERO_MAXIMO_AQUIVOS];

// Usada para gerar o ID (descritor) de cada arquivo do sistema de arquivos.
unsigned geraID = 0;


/*  Abre o arquivo com o nome especificado.
    Retorna o ID (descritor) do arquivo em caso de sucesso ou ERRO se ocorrer um erro.
*/
int abrir(char* nomeArquivo) {
    unsigned int i;

    //verificando se atingiu o limite
    if (geraID >= NUMERO_MAXIMO_AQUIVOS)
    {
        return ERRO;
    }

    //verificando se exite arquivo com o mesmo nome
    for (i = 0; i < geraID; i++)
    {
        if (strcmp(sistemaArquivos[i].nome, nomeArquivo)==0)
        {   
            //Arquivo com esse nome j� esta aberto.
            return ERRO;
        }
    }
    //Abrindo arquivo modo leitura
    // Tenta abrir o arquivo em modo de leitura usando fopen_s.
    FILE* arquivo;
    arquivo = fopen(nomeArquivo, "a+");
    if (arquivo == NULL) {
        // N�o foi poss�vel abrir o arquivo.
        return ERRO;
    }

    //Preenche a estrutura de arquivo
    sistemaArquivos[geraID].ID = geraID;
    strcpy(sistemaArquivos[geraID].nome, nomeArquivo);

    sistemaArquivos[geraID].arquivo = arquivo;

    //incrementanado o contador de ID
    return geraID++;
}

/* L� o arquivo identificado por ID.
   Faz a leitura de n (tamanho) bytes do arquivo com a quantidade indicada.
   Retorna o conte�do lido do arquivo em caso de sucesso ou NULL se ocorrer um erro.
*/
void* ler(int ID, unsigned tamanho, unsigned quantidade) {

    void* conteudoLido;

    // Verifica se o ID do arquivo est� dentro do limite v�lido.
    if (ID < 0 || ID >= geraID) {
        return NULL; // ID inv�lido, retorna NULL para indicar erro.
    }

    // Obt�m o arquivo com o ID especificado.
    FILE* arquivo = sistemaArquivos[ID].arquivo;
    if (arquivo == NULL) {
        return NULL; // Arquivo n�o encontrado, retorna NULL para indicar erro.
    }

    // Aloca mem�ria para armazenar o conte�do lido.
    conteudoLido = malloc(tamanho * quantidade + 1);
    if (conteudoLido == NULL) {
        return NULL; // Falha na aloca��o de mem�ria, retorna NULL para indicar erro.
    }

    // L� os bytes do arquivo e armazena no conte�do lido.
    size_t bytesLidos = fread(conteudoLido, tamanho, quantidade, arquivo);

    // Verifica se a leitura foi bem-sucedida.
    if (bytesLidos != quantidade) {
        free(conteudoLido); // Libera a mem�ria alocada em caso de erro parcial.
        return NULL; // Erro na leitura, retorna NULL para indicar erro.
    }

    // Adiciona um caractere nulo de termina��o para formar uma string v�lida.
    ((char*)conteudoLido)[bytesLidos * tamanho] = '\0';

    return conteudoLido; // Retorna o conte�do lido em caso de sucesso.
}

/* Escreve o conte�do do buffer no arquivo identificado por ID.
   Faz a escrita de n (tamanho) bytes no arquivo com a quantidade indicada.
   Retorna o n�mero de bytes escritos no arquivo em caso de sucesso ou ERRO se ocorrer um erro.
*/
int escrever(int ID, const void* buffer, unsigned tamanho, unsigned quantidade) {

    // Verifica se o ID do arquivo est� dentro do limite v�lido.
    if (ID < 0 || ID >= geraID) {
        return ERRO; // ID inv�lido, retorna ERRO para indicar erro.
    }

    // Obt�m o arquivo com o ID especificado.
    FILE* arquivo = sistemaArquivos[ID].arquivo;

    if (arquivo == NULL) {
        return ERRO; // Arquivo n�o encontrado, retorna ERRO para indicar erro.
    }

    // Escreve os bytes do buffer no arquivo.
    size_t bytesEscritos = fwrite(buffer, tamanho, quantidade, arquivo);

    // Verifica se a escrita foi bem-sucedida.
    if (bytesEscritos != quantidade) {
        return ERRO; // Erro na escrita, retorna ERRO para indicar erro.
    }

    // A escrita foi bem-sucedida, retorna o n�mero de bytes escritos.
    return bytesEscritos;
}

/* Fecha o arquivo com o ID especificado.
   Retorna 1 em caso de sucesso ou ERRO se ocorrer um erro.
*/
int fechar(int ID) {

    // Verifica se o ID do arquivo est� dentro do limite v�lido.
    if (ID < 0 || ID >= geraID) {
        return ERRO; // ID inv�lido, retorna ERRO para indicar erro.
    }

    // Obt�m o arquivo com o ID especificado.
    FILE* arquivo = sistemaArquivos[ID].arquivo;
    if (arquivo == NULL) {
        return ERRO; // Arquivo n�o encontrado, retorna ERRO para indicar erro.
    }

    // Fecha o arquivo.
    if (fclose(arquivo) != 0) {
        return ERRO; // Erro ao fechar o arquivo, retorna ERRO para indicar erro.
    }

    // Marca o arquivo como fechado, definindo o ponteiro do arquivo como NULL.
    sistemaArquivos[ID].arquivo = NULL;

    return 1; // Retorna 1 para indicar sucesso no fechamento do arquivo.
}