#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"

// Abertura e Leitura de Arquivo

Produto* ler_arquivo_csv(const char* nome_arquivo, int* total_lido){
    FILE *arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("| ERRO: Nao foi possivel abrir o arquivo '%s'. Verifique se ele existe. \n |", nome_arquivo);
        *total_lido = 0; 
        return NULL; 
    } else {
        printf("| SUCESSO: Arquivo '%s' aberto corretamente! |\n", nome_arquivo);
    }

    int total_linhas = -1; // ignora cabecalho
    char linha_temp[1024]; 

    while (fgets(linha_temp, sizeof(linha_temp), arquivo) != NULL) {
        if (strlen(linha_temp) < 2) continue; // Pula linhas vazias
        total_linhas++;
    }

    if(total_linhas <= 0){
        printf("| AVISO: Seu arquivo esta vazio ou so contem cabecalho! \n");
        fclose(arquivo);
        return NULL;
    }
    
    Produto* vetor_dinamico = (Produto*) malloc(total_linhas * sizeof(Produto));
    if(vetor_dinamico == NULL){
        printf("ERRO FATAL: Sem memoria suficiente! \n");
        *total_lido = 0;
        fclose(arquivo);
        return NULL;
    }

    rewind(arquivo); 
    fgets(linha_temp, sizeof(linha_temp), arquivo); // pula o cabecalho

    int indice = 0;
    while(fgets(linha_temp, sizeof(linha_temp), arquivo) != NULL){
        if (strlen(linha_temp) < 2) continue; // Protecao
        
        linha_temp[strcspn(linha_temp, "\n")] = '\0';

        char* bloco = strtok(linha_temp, ",");
        if(bloco != NULL) vetor_dinamico[indice].id = atoi(bloco);

        bloco = strtok(NULL, ",");
        if(bloco != NULL) strcpy(vetor_dinamico[indice].nome, bloco); 

        bloco = strtok(NULL, ",");
        if(bloco != NULL) strcpy(vetor_dinamico[indice].categoria, bloco);

        bloco = strtok(NULL, ",");
        if(bloco != NULL) vetor_dinamico[indice].valor =  atof(bloco);

        indice++;
    }
    
    *total_lido = indice; 
    fclose(arquivo);

    printf("| AUDITORIA: Exatos %d registros validados e carregados na memoria RAM. |\n", *total_lido);

    return vetor_dinamico;
}

void liberar_memoria(Produto* vetor_dinamico){
    if(vetor_dinamico != NULL){
        free(vetor_dinamico);
        printf("Memoria Liberada com Sucesso! \n");
    }
}


// Busca Sequencial

int buscar_por_id(Produto* vetor_dinamico, int total_produtos, int id_buscado){
    for(int i=0; i<total_produtos;i++){
        if(vetor_dinamico[i].id == id_buscado){
            return i; 
        }
    }
    return -1; 
}

int buscar_categoria(Produto* vetor_dinamico, int total_produtos, const char* categoria){
    int categorizados = 0; 
    for(int i=0; i < total_produtos; i++){
        if(strcmp(vetor_dinamico[i].categoria, categoria) == 0){
            printf("ID: %i | PRODUTO: %s | CATEGORIA: %s | VALOR: %.2f \n", 
                vetor_dinamico[i].id, vetor_dinamico[i].nome, vetor_dinamico[i].categoria, vetor_dinamico[i].valor);
            categorizados++; 
        }
    }
    if(categorizados == 0){
        printf("ERRO: Produto nao encontrado! \n");  
    }
    return categorizados;
}


// Registro de Logs

void gravar_logs(const char* nome_arquivo, const char* cenario, int repeticao, int buscas, double tempo_gasto){
    FILE *arquivo_log = fopen(nome_arquivo, "a");
    if(arquivo_log == NULL){
        printf("ERRO: Nao foi possivel abrir/criar o arquivo de logs em %s! \n", nome_arquivo);
        return;
    }
    fprintf(arquivo_log, "Ciclo %d,%s,%d buscas,%.6f seg\n", repeticao, cenario, buscas, tempo_gasto);
    fclose(arquivo_log);
}

// Teste de Busca sequnencial

void exec_teste(Produto* vetor_dinamico, int total_lido){
    int id_inicio = vetor_dinamico[0].id; 
    int id_meio = vetor_dinamico[total_lido / 2].id;
    int id_fim = vetor_dinamico[total_lido - 1].id;
    int id_inexistente = -99999;

    printf("\n|--- INICIANDO PROTOCOLO EXPERIMENTAL SEQUENCIAL ---|\n");

    for(int repeticao = 1; repeticao <= 3; repeticao++){
        printf("\n| Executando Ciclo numero %d/3... \n", repeticao);

        // --- TESTE INICIO ---
        clock_t inicio_t = clock(); 
        for(int i = 0; i < 1000; i++){
            buscar_por_id(vetor_dinamico, total_lido, id_inicio);
        }
        clock_t fim_t = clock(); 
        double teste_inicio = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_sequencial.csv", "Busca Inicio", repeticao, 1000, teste_inicio);

        // --- TESTE MEIO ---
        inicio_t = clock();
        for(int i = 0; i < 1000; i++){
            buscar_por_id(vetor_dinamico, total_lido, id_meio);
        }
        fim_t = clock();
        double teste_meio = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_sequencial.csv", "Busca Meio", repeticao, 1000, teste_meio);

        // --- TESTE FIM ---
        inicio_t = clock();
        for(int i = 0; i < 1000; i++){
            buscar_por_id(vetor_dinamico, total_lido, id_fim);
        }
        fim_t = clock();
        double teste_fim = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_sequencial.csv", "Busca Fim", repeticao, 1000, teste_fim);

        // --- TESTE INEXISTENTE ---
        inicio_t = clock();
        for(int i = 0; i < 1000; i++){
            buscar_por_id(vetor_dinamico, total_lido, id_inexistente);
        }
        fim_t = clock();
        double teste_inexistente = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_sequencial.csv", "Busca Inexistente", repeticao, 1000, teste_inexistente);

        // --- EXIBICAO DE RESULTADOS ---
        double media_ciclo = (teste_inicio + teste_meio + teste_fim + teste_inexistente) / 4;
        
        printf("|-----------------------------------------------------------------------------------------|\n");
        printf("|----Busca Inicio-----| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_inicio);
        printf("|-----Busca Meio------| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_meio);
        printf("|-----Busca Fim-------| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_fim);
        printf("|--Busca Inexistente--| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_inexistente);
        printf("|-----------------------------------------------------------------------------------------|\n");
        printf("|---Media do Ciclo----|       O tempo medio do ciclo %d foi de %.6f seg         |\n", repeticao, media_ciclo);
        printf("|-----------------------------------------------------------------------------------------|\n");
    }
}


// Inicialização da Tabela Hash


void inicializar_hash(HashTable* tabela){

    for(int i = 0; i < tabela->tamanho; i++){
        tabela->buckets[i] = NULL;
    }
}


// Criação da Tabela Hash


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

    printf("| SUCESSO: Hash criada com %d buckets. |\n", tamanho);

    return tabela;
}

// Função Hash 
int funcao_hash(int id, int tamanho_tabela){

    int bloco_esquerda = id / 1000;
    int bloco_direita = id % 1000;

    return (bloco_esquerda + bloco_direita) % tamanho_tabela;
}


// contagem de colisoes

void inserir_hash(HashTable* tabela, Produto* produto, int* contador_colisoes){
    int indice = funcao_hash(produto->id, tabela->tamanho);

    No* no = (No*) malloc(sizeof(No));
    no->chave = produto->id;
    no->produto = produto; 
    no->prox = NULL;

    if(tabela->buckets[indice] == NULL){
        
        tabela->buckets[indice] = no;
    } else {
        
        (*contador_colisoes)++;
        
        
        no->prox = tabela->buckets[indice]; //insere no inicio
        tabela->buckets[indice] = no;
    }
}


void liberar_hash(HashTable* tabela){
    if(tabela == NULL) return;

    for(int i = 0; i < tabela->tamanho; i++){
        No* atual = tabela->buckets[i];
        while(atual != NULL){
            No* temp = atual;
            atual = atual->prox;
            free(temp); 
        }
    }
    free(tabela->buckets); 
    free(tabela);          
    
    printf("| SUCESSO: Memoria da Tabela Hash liberada com exito!\n");
}

// busca na tabela

Produto* buscar_hash_id(HashTable* tabela, int id_buscado){
    int indice = funcao_hash(id_buscado, tabela->tamanho);
    
    No* atual = tabela->buckets[indice];
    
    // percorre a lista encadeada
    while(atual != NULL){
        if(atual->chave == id_buscado){
            return atual->produto; 
        }
        atual = atual->prox;
    }
    
    return NULL; 
}
    
// testes massivos Hash

void exec_teste_hash(HashTable* tabela, Produto* vetor_dinamico, int total_lido){
    int id_inicio = vetor_dinamico[0].id; 
    int id_meio = vetor_dinamico[total_lido / 2].id;
    int id_fim = vetor_dinamico[total_lido - 1].id;
    int id_inexistente = -99999;

    printf("\n|--- INICIANDO PROTOCOLO EXPERIMENTAL HASH ---|\n");

    for(int repeticao = 1; repeticao <= 3; repeticao++){
        printf("\n| Executando Ciclo numero %d/3 na Tabela Hash... \n", repeticao);

        // --- TESTE INICIO ---
        clock_t inicio_t = clock(); 
        for(int i = 0; i < 1000; i++){
            buscar_hash_id(tabela, id_inicio);
        }
        clock_t fim_t = clock(); 
        double teste_inicio = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_hash.csv", "Hash Inicio", repeticao, 1000, teste_inicio);

        // --- TESTE MEIO ---
        inicio_t = clock();
        for(int i = 0; i < 1000; i++){
            buscar_hash_id(tabela, id_meio);
        }
        fim_t = clock();
        double teste_meio = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_hash.csv", "Hash Meio", repeticao, 1000, teste_meio);

        // --- TESTE FIM ---
        inicio_t = clock();
        for(int i = 0; i < 1000; i++){
            buscar_hash_id(tabela, id_fim);
        }
        fim_t = clock();
        double teste_fim = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_hash.csv", "Hash Fim", repeticao, 1000, teste_fim);

        // --- TESTE INEXISTENTE ---
        inicio_t = clock();
        for(int i = 0; i < 1000; i++){
            buscar_hash_id(tabela, id_inexistente);
        }
        fim_t = clock();
        double teste_inexistente = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
        gravar_logs("../logs/logs_hash.csv", "Hash Inexistente", repeticao, 1000, teste_inexistente);

        double media_ciclo = (teste_inicio + teste_meio + teste_fim + teste_inexistente) / 4;
        
        printf("|-----------------------------------------------------------------------------------------|\n");
        printf("|----Hash Inicio------| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_inicio);
        printf("|-----Hash Meio-------| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_meio);
        printf("|-----Hash Fim--------| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_fim);
        printf("|--Hash Inexistente---| O programa levou %.6f seg para realizar 1000 buscas |\n", teste_inexistente);
        printf("|-----------------------------------------------------------------------------------------|\n");
        printf("|---Media do Ciclo----|       O tempo medio do ciclo %d foi de %.6f seg         |\n", repeticao, media_ciclo);
        printf("|-----------------------------------------------------------------------------------------|\n");
    }
}