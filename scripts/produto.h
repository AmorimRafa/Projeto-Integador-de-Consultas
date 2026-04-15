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
void liberar_memoria(Produto* vetor_dinamico);
int buscar_por_id(Produto* vetor_dinamico, int total_produtos, int id_buscado);
int buscar_categoria(Produto* vetor_dinamico, int total_produtos, const char* categoria);
void gravar_logs(const char* posicao, int repeticao, int total_buscas);
void exec_teste(Produto* vetor_dinamico, int total_lido);

#endif
