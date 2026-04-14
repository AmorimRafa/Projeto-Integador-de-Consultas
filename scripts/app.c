#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"

int main(){
    int total_lido = 0;

  clock_t tempo_inicial = clock(); //Inicio do Clock
  clock_t inicio_leitura = clock(); //Inicio do Clock

  Produto* lista  = ler_arquivo_csv("../../dataset3.csv", &total_lido);
  clock_t final_leitura = clock();

  if(lista != NULL){
    printf("Produtos carregados com sucesso!\n ");
  } else { 
    printf("Erro ao carregar Produtos! \n");
    liberar_memoria(lista);
   }

   /*for(int i = 0; i < total_lido; i++){
    printf("\n ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", 
      lista[i].id, lista[i].nome, lista[i].categoria, lista[i].valor);
   }
   printf("\n----------------------------------------------\n");*/

   int id_buscado = 0;
   printf("Selcione o id a ser buscado: \n");
   scanf("%d", &id_buscado);

   clock_t inicio_busca = clock();
   int consulta = buscar_por_id(lista, total_lido, id_buscado);
   clock_t final_busca = clock();

   if(consulta != -1){
    printf("SUCESSO: O produto foi encontrado! \n");
    printf("ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", 
      lista[consulta].id,lista[consulta].nome, lista[consulta].categoria, lista[consulta].valor);      
  }else{printf("ERRO: Produto nao encontrado! \n");}

  char categoria[31];
  printf("Selcione a categoria a ser buscada: \n");
  scanf("%s", categoria);
  int consulta_cat = buscar_categoria(lista, total_lido, categoria);


  liberar_memoria(lista);
  
  clock_t tempo_final = clock(); //Fim do Clock
  double duracao_geral = (double) (tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
  double duracao_leitura = (double) (final_leitura - inicio_leitura) / CLOCKS_PER_SEC;
  double duracao_busca = (double) (final_busca - inicio_busca) / CLOCKS_PER_SEC;
  printf("O tempo de execucao geral foi de: %.5f seg\n", duracao_geral);
  printf("O tempo de execucao de leitura foi de: %.5f seg\n", duracao_leitura);
  printf("O tempo de execucao de busca foi de: %.5f seg\n", duracao_busca);
  
  return 0;
}