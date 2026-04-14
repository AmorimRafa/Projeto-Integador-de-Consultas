#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

//Abertura de arquivo
Produto* ler_arquivo_csv(const char* nome_arquivo, int* total_lido){
  FILE *arquivo = fopen(nome_arquivo, "r");

  if(arquivo == NULL){
    printf("ERRO: Nao foi possivel abrir o arquivo '%s'. Verifique se ele existe. \n", nome_arquivo);
    *total_lido = 0; // garante que leu  0 linhas
    return NULL; // nao havera vetor de produtos

  } else{
    printf("SUCESSO: Arquivo '%s' aberto corretamente! \n", nome_arquivo);
  }

  // leitura do arquivo
  int total_linhas = -1; //ignora cabecalho
  char linha_temp[1024]; //tamanho da linha

  // fgets(local de armazenamento, tamanho da linha, arquivo)
  while (fgets(linha_temp, sizeof(linha_temp), arquivo) != NULL) {
    total_linhas++;
  }

  if(total_linhas < 0){
    printf("AVISO: Seu arquivo esta vazio! \n");
    return NULL;
  }else if (total_linhas == 0){
    printf("AVISO: Seu arquivo so contem o cabecalho! \n");
    return NULL;
  }else{
    printf("verificacao: O arquivo tem %d linhas.\n", total_linhas);
  }
  *total_lido = total_linhas;
  

  Produto* vetor_dinamico = (Produto*) malloc(total_linhas * sizeof(Produto));
  if(vetor_dinamico == NULL){
    printf("ERRO FATAL: Sem memoria suficiente! \n");
    *total_lido = 0;
    fclose(arquivo);
    return NULL;
  }else{
    printf("SUCESSO: Vetor Alocado! \n");
  }
  rewind(arquivo); // volta o cursor para o inicio do arquivo

  // ====================================
  // Leitura dos dados
  // ====================================

  fgets(linha_temp, sizeof(linha_temp), arquivo); //roda 1 vez para pular o cabecalho

  int indice = 0;
  while(fgets(linha_temp, sizeof(linha_temp), arquivo) != NULL){
    linha_temp[strcspn(linha_temp, "\n")] = '\0';

    char* bloco = strtok(linha_temp, ",");
    if(bloco != NULL){
      vetor_dinamico[indice].id = atoi(bloco);
    }

    bloco = strtok(NULL, ",");
    if(bloco != NULL){
      strcpy(vetor_dinamico[indice].nome, bloco); 
    }

    bloco = strtok(NULL, ",");
    if(bloco != NULL){
      strcpy(vetor_dinamico[indice].categoria, bloco);
    }

    bloco = strtok(NULL, ",");
    if(bloco != NULL){
      vetor_dinamico[indice].valor =  atof(bloco);
    }

    indice++;
  }
  
  *total_lido = total_linhas;
  fclose(arquivo);

  return vetor_dinamico;

}

void liberar_memoria(Produto* vetor_dinamico){
  if(vetor_dinamico != NULL){
    free(vetor_dinamico);
    printf("Memoria Liberada com Sucesso! \n");
  }
}

  int buscar_por_id(Produto* vetor_dinamico, int total_produtos, int id_buscado){

    for(int i=0; i<total_produtos;i++){
      if(vetor_dinamico[i].id== id_buscado){
        return i; //sucesso na busca
      }
    }
    return -1; // nao existe esse indice (indicando falha na busca)
  };

  int buscar_categoria(Produto* vetor_dinamico, int total_produtos, const char* categoria){
    int categorizados = 0;

    for(int i=0; i < total_produtos; i++){
      if(strcmp(vetor_dinamico[i].categoria, categoria) == 0){
        printf("ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", vetor_dinamico[i].id, vetor_dinamico[i].nome, vetor_dinamico[i].categoria, vetor_dinamico[i].valor);
      }
      categorizados++;
    }
    //printf("categorizados %s \n", categorizados);  
    if(categorizados == 0){
    printf("ERRO: Produto nao encontrado! \n");  
    }
    return categorizados;
  }