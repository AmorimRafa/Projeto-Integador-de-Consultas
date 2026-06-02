#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

// ====================================
// Inicialização dos índices
// ====================================

void inicializar_hash(HashTable* tabela){

    for(int i = 0; i < tabela->tamanho; i++){
        tabela->buckets[i] = NULL;
    }
}

// ====================================
// Criação da tabela hash
// ====================================

HashTable* criar_hash(int tamanho){

    HashTable* tabela = (HashTable*) malloc(sizeof(HashTable));

    if(tabela == NULL){
        printf("ERRO: Falha ao criar estrutura Hash.\n");
        return NULL;
    }

    tabela->tamanho = tamanho;

    tabela->buckets = (No**) malloc(tamanho * sizeof(No*));

    if(tabela->buckets == NULL){
        printf("ERRO: Falha ao alocar buckets.\n");
        free(tabela);
        return NULL;
    }

    inicializar_hash(tabela);

    printf("SUCESSO: Hash criada com %d buckets.\n", tamanho);

    return tabela;
}