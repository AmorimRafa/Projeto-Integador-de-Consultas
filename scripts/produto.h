#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;


// tabela hash

typedef struct No {
    int chave;
    Produto* produto;
    struct No* prox;
} No;

typedef struct {
    No** buckets;
    int tamanho;
} HashTable;


// Funcoes Dataset


Produto* ler_arquivo_csv(const char* nome_arquivo, int* total_lido);
void liberar_memoria(Produto* vetor_dinamico);
int buscar_por_id(Produto* vetor_dinamico, int total_produtos, int id_buscado);
int buscar_categoria(Produto* vetor_dinamico, int total_produtos, const char* categoria);
void gravar_logs(const char* cenario, int repeticao, int buscas, double tempo_gasto);
void exec_teste(Produto* vetor_dinamico, int total_lido);


// funcoes hash

HashTable* criar_hash(int tamanho);
void inicializar_hash(HashTable* tabela);

// funcao sorteada
int funcao_hash(int id, int tamanho_tabela); 

// contador de colisoes
void inserir_hash(HashTable* tabela, Produto* produto, int* contador_colisoes);

#endif