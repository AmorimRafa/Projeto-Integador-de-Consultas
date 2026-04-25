#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"

int main(){
    int total_lido = 0;
  printf("\n|----------------------------------------------------------------------------------------------|\n");
    printf("|-----------------------------IMPLEMENTACAO DE TESTES DE BUSCA---------------------------------|\n");
    printf("|----------------------------------------------------------------------------------------------|\n");

  clock_t tempo_inicial = clock(); //Inicio do Clock
  clock_t inicio_leitura = clock(); //Inicio do Clock

  Produto* lista  = ler_arquivo_csv("../dataset3.csv", &total_lido);
  clock_t final_leitura = clock();

  printf("\n\n|---------------------------------------FASE DE LISTAGEM---------------------------------------|\n");
  if(lista != NULL){
    printf("| Produtos carregados com sucesso!\n ");
  } else { 
    printf("Erro ao carregar Produtos! \n");
    liberar_memoria(lista);
   }
  printf("|---------------------------------------------------------------------------------------------|\n");

  printf("\n\n|---------------------------------------FASE DE BUSCA------------------------------------------|\n");
   int id_buscado = 0;
   printf("| Selcione o id a ser buscado: \n");
   scanf("%d", &id_buscado);

   clock_t inicio_busca = clock();
   int consulta = buscar_por_id(lista, total_lido, id_buscado);
   clock_t final_busca = clock();

   if(consulta != -1){
    printf("| SUCESSO: O produto foi encontrado! \n");
    printf("| ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", 
      lista[consulta].id,lista[consulta].nome, lista[consulta].categoria, lista[consulta].valor);      
  }else{printf("| ERRO: Produto nao encontrado! \n");}
  printf("|----------------------------------------------------------------------------------------------|\n");

  printf("\n\n|---------------------------------------FASE DE TESTE------------------------------------------|\n");
  exec_teste(lista, total_lido);

  liberar_memoria(lista);
  printf("|---------------------------------------------------------------------------------------------------|\n");

  clock_t tempo_final = clock(); //Fim do Clock

  //Calculo de Tempo
  double duracao_geral = (double) (tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
  double duracao_leitura = (double) (final_leitura - inicio_leitura) / CLOCKS_PER_SEC;
  double duracao_busca = (double) (final_busca - inicio_busca) / CLOCKS_PER_SEC;
  printf("\n|-------------------------------------------ANALISE FINAL------------------------------------------|\n");
  printf("| O tempo de execucao do inicio ao fim do programa foi de: %.3f seg\n", duracao_geral);
  printf("| O tempo de execucao da leitura do arquivo foi de: %.5f seg\n", duracao_leitura);
  printf("| O tempo de execucao da busca isolada foi de: %.5f seg\n", duracao_busca);
  printf("\n|--------------------------------------------------------------------------------------------------|\n");
  return 0;
}