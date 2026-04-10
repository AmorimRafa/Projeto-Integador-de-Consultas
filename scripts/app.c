#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"

int main(){
    int total_lido = 0;

  clock_t tempo_inicial = clock(); //Inicio do Clock

  Produto* lista  = ler_arquivo_csv("../../dataset3.csv", &total_lido);

  if(lista != NULL){
    printf("Produtos carregados com sucesso!\n ");
  } else { 
    printf("Erro ao carregar Produtos! \n");
    liberar_memoria(lista);
   }

   for(int i = 0; i < total_lido; i++){
    printf("\n ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", 
      lista[i].id, lista[i].nome, lista[i].categoria, lista[i].valor);
   }
   printf("\n----------------------------------------------\n");


  liberar_memoria(lista);
  
  clock_t tempo_final = clock(); //Fim do Clock
  double duracao = (double) (tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
  printf("O tempo de execucao foi %.5f seg\n", duracao);

  return 0;
}