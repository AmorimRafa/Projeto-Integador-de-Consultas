#ifndef PRODUTO_H
#define PRODUTO_H

// Definição da struct 
typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

Produto* ler_arquivo_csv(const char* nome_arquivo, int* total_lido);

#endif
