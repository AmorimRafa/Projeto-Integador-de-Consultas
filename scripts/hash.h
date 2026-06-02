#ifndef HASH_H
#define HASH_H

#include "produto.h"

// ====================================
// Nó da Lista Encadeada
// ====================================

typedef struct No {
    int chave;              // ID do produto
    Produto* produto;       // Payload
    struct No* prox;        // Próximo nó
} No;

// ====================================
// Estrutura da Tabela Hash
// ====================================

typedef struct {
    No** buckets;
    int tamanho;
} HashTable;

// ====================================
// Protótipos
// ====================================

HashTable* criar_hash(int tamanho);
void inicializar_hash(HashTable* tabela);

#endif