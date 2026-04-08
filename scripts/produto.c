#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

Produto* ler_arquivo_csv(const char* nome_arquivo, int* total_lido){
  FILE *arquivo = fopen(nome_arquivo, "r");

  if(arquivo == NULL){
    printf("ERRO: Nao foi possivel abrir o arquivo '%s'. Verifique se ele existe. \n", nome_arquivo);
    *total_lido = 0; // garante que leu  0 linhas
    return NULL; // nao havera vetor de produtos

  } else{
    printf("SUCESSO: Arquivo '%s' aberto corretamente! \n", nome_arquivo);
  }

  int contador_linhas =-1;
  char linha_temp[1024];

  while (fgets(linha_temp, sizeof(linha_temp), arquivo) != NULL) {
    contador_linhas++;
  }

  printf("verificacao: O arquivo tem %d linhas.\n", contador_linhas);

  rewind(arquivo);

  *total_lido = contador_linhas;

  fclose(arquivo);
  return NULL;

}
