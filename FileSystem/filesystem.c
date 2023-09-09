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
            //Arquivo com esse nome já esta aberto.
            return ERRO;
        }
    }
    //Abrindo arquivo modo leitura
    // Tenta abrir o arquivo em modo de leitura usando fopen_s.
    FILE* arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        // Não foi possível abrir o arquivo.
        return ERRO;
    }

    //Preenche a estrutura de arquivo
    sistemaArquivos[geraID].ID = geraID;
    strcpy(sistemaArquivos[geraID].nome, nomeArquivo);

    sistemaArquivos[geraID].arquivo = arquivo;

    //incrementanado o contador de ID
    return geraID++;
}

/* Lê o arquivo identificado por ID.
   Faz a leitura de n (tamanho) bytes do arquivo com a quantidade indicada.
   Retorna o conteúdo lido do arquivo em caso de sucesso ou NULL se ocorrer um erro.
*/
void* ler(int ID, unsigned tamanho, unsigned quantidade) {

    void* conteudoLido;

    // Verifica se o ID do arquivo está dentro do limite válido.
    if (ID < 0 || ID >= geraID) {
        return NULL; // ID inválido, retorna NULL para indicar erro.
    }

    // Obtém o arquivo com o ID especificado.
    FILE* arquivo = sistemaArquivos[ID].arquivo;
    if (arquivo == NULL) {
        return NULL; // Arquivo não encontrado, retorna NULL para indicar erro.
    }

    // Aloca memória para armazenar o conteúdo lido.
    conteudoLido = malloc(tamanho * quantidade);
    if (conteudoLido == NULL) {
        return NULL; // Falha na alocação de memória, retorna NULL para indicar erro.
    }

    // Lê os bytes do arquivo e armazena no conteúdo lido.
    size_t bytesLidos = fread(conteudoLido, tamanho, quantidade, arquivo);

    // Verifica se a leitura foi bem-sucedida.
    if (bytesLidos != quantidade) {
        free(conteudoLido); // Libera a memória alocada em caso de erro parcial.
        return NULL; // Erro na leitura, retorna NULL para indicar erro.
    }

    return conteudoLido; // Retorna o conteúdo lido em caso de sucesso.
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