#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

int main(){
    int total_lido = 0;


  Produto* lista  = ler_arquivo_csv("../../dataset3.csv", &total_lido);
  
  return 0;
}