#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    int categorizados = 0; //numero de registros encontrados

    for(int i=0; i < total_produtos; i++){
      if(strcmp(vetor_dinamico[i].categoria, categoria) == 0){
        printf("ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", 
          vetor_dinamico[i].id, vetor_dinamico[i].nome, vetor_dinamico[i].categoria, vetor_dinamico[i].valor);
          categorizados++; // adiciona registros encontrados
      }
      
    }
    //printf("categorizados %s \n", categorizados);  
    if(categorizados == 0){
    printf("ERRO: Produto nao encontrado! \n");  
    }
    return categorizados;
  }

  void gravar_logs(const char* posicao, int repeticao, int total_lido){
    FILE *arquivo_log = fopen("../logs/logs.csv", "a");
    if(arquivo_log == NULL){
      printf("ERRO: Nao foi possivel abrir o arquivo! \n");
      return;
    }

    fprintf(arquivo_log, "%s,%d,%d\n", posicao, repeticao, total_lido);
    fclose(arquivo_log);
  }

  void exec_teste(Produto* vetor_dinamico, int total_lido){
    int id_inicio = vetor_dinamico[total_lido].id;
    int id_meio = vetor_dinamico[total_lido / 2].id;
    int id_fim = vetor_dinamico[total_lido - 1].id;
    int id_inexistente = -99999;

    clock_t inicio_teste_geral = clock();

    for(int repeticao = 1; repeticao <= 3; repeticao++){
      printf("Executando repeticao %d de 3 \n", repeticao);

      clock_t inicio_teste_inicio = clock();
      for(int i = 0; i < 1000; i++){
      buscar_por_id(vetor_dinamico, total_lido, id_inicio);
      gravar_logs("Busca no Inicio", repeticao, 1000);
      }
      clock_t final_teste_inicio = clock();

      double teste_inicio = (double) (final_teste_inicio - inicio_teste_inicio) / CLOCKS_PER_SEC;
      printf("O tempo de execucao de busca no inicio na execucao %d foi de: %.5f seg\n", repeticao, teste_inicio);

      clock_t inicio_teste_meio = clock();
      for(int i = 0; i < 1000; i++){
      buscar_por_id(vetor_dinamico, total_lido, id_meio);
      gravar_logs("Busca no Meio", repeticao, 1000);
      }
      clock_t final_teste_meio = clock(); 

      double teste_meio = (double) (final_teste_meio - inicio_teste_meio) / CLOCKS_PER_SEC;
      printf("O tempo de execucao de busca no meio na execucao %d foi de: %.5f seg\n", repeticao, teste_meio);

      clock_t inicio_teste_fim = clock();
      for(int i = 0; i < 1000; i++){
      buscar_por_id(vetor_dinamico, total_lido, id_fim);
      gravar_logs("Busca no Fim", repeticao, 1000);
      }
      clock_t final_teste_fim = clock();

      double teste_fim = (double) (final_teste_fim - inicio_teste_fim) / CLOCKS_PER_SEC;
      printf("O tempo de execucao de busca no fim na execucao %d foi de: %.5f seg\n", repeticao, teste_fim);

      clock_t inicio_teste_inexistente = clock();
      for(int i = 0; i < 1000; i++){
      buscar_por_id(vetor_dinamico, total_lido, id_inexistente);
      gravar_logs("Busca Inexistente", repeticao, 1000);
      }
      clock_t final_teste_inexistente = clock();
      
      double teste_inexistente = (double) (final_teste_inexistente - inicio_teste_inexistente) / CLOCKS_PER_SEC;
      printf("O tempo de execucao de buscas inexistentes na execucao %d foi de: %.5f seg\n", repeticao, teste_inexistente);

      double media_by_repeticao = (double) (teste_inicio + teste_meio + teste_fim + teste_inexistente) / 4;
      printf("O tempo medio de consultas na repeticao %d foi de %.5f \n", repeticao, media_by_repeticao);
    }
    clock_t final_teste_geral = clock();

    double teste_geral = (double) (final_teste_geral - inicio_teste_geral) / CLOCKS_PER_SEC;

    printf("O tempo de execucao da rotina de buscas foi de: %.5f seg\n", teste_geral);
    
  }