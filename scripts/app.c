#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

int main(){
    int total_lido = 0;


  Produto* lista  = ler_arquivo_csv("../../dataset_teste.csv", &total_lido);
  liberar_memoria(lista);
  
  return 0;
}