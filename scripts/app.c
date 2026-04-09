#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

int main(){
    int total_lido = 0;


  Produto* lista  = ler_arquivo_csv("../../dataset_teste.csv", &total_lido);

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
  
  return 0;
}