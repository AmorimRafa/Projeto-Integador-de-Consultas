#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"
#include "hash.h"

int main(){
    int total_lido = 0;
    
    printf("\n|----------------------------------------------------------------------------------------------|\n");
    printf("|-----------------------------IMPLEMENTACAO DE TESTES DE BUSCA---------------------------------|\n");
    printf("|----------------------------------------------------------------------------------------------|\n");

    clock_t tempo_inicial = clock(); // Inicio do Clock Geral

    // ==============================================
    // FASE 1: LEITURA DO DATASET E CRIAÇÃO DO HASH
    // ==============================================
    printf("\n|---------------------------------------FASE DE CARREGAMENTO-----------------------------------|\n");

    clock_t inicio_leitura = clock();

    Produto* lista = ler_arquivo_csv("../dataset3.csv", &total_lido);

    // [ISSUE 3 FASE 1] TRAVA DE SEGURANÇA: Se falhar a leitura, aborta para não travar o SO
    if(lista == NULL){
        printf("| ERRO CRITICO: Falha ao carregar Produtos! Encerrando sistema...\n");
        printf("|----------------------------------------------------------------------------------------------|\n");
        return 1;
    }

    printf("| SUCESSO: O Dataset foi carregado na memoria RAM com exito!\n");

    // [ISSUE 23 FASE 2] Criacao da Tabela Hash
    HashTable* tabela = criar_hash(total_lido);

    if(tabela == NULL){
        printf("| ERRO CRITICO: Falha ao criar tabela hash.\n");
        liberar_memoria(lista);
        return 1;
    }

    printf("| SUCESSO: Tabela Hash criada com %d buckets.\n", total_lido);

    clock_t final_leitura = clock();

    printf("|----------------------------------------------------------------------------------------------|\n");

    // ==========================================
    // FASE 2: BUSCA MANUAL
    // ==========================================
    printf("\n|---------------------------------------FASE DE BUSCA ISOLADA----------------------------------|\n");
    int id_buscado = 0;
    printf("| Selecione o ID a ser buscado: ");
    scanf("%d", &id_buscado);

    clock_t inicio_busca = clock();
    int consulta = buscar_por_id(lista, total_lido, id_buscado);
    clock_t final_busca = clock();

    if(consulta != -1){
        printf("| SUCESSO: O produto foi encontrado! \n");
        printf("| ID: %i | PRODUTO: %-15s | CATEGORIA: %-15s | VALOR: %.2f \n", 
               lista[consulta].id, lista[consulta].nome, lista[consulta].categoria, lista[consulta].valor);      
    } else {
        printf("| ERRO: Produto nao encontrado no banco de dados! \n");
    }
    printf("|----------------------------------------------------------------------------------------------|\n");

    // ==========================================
    // FASE 3: PROTOCOLO EXPERIMENTAL (BENCHMARK)
    // ==========================================
    printf("\n|---------------------------------------FASE DE ESTRESSE---------------------------------------|\n");
    exec_teste(lista, total_lido);

    // ==========================================
    // FASE 4: ENCERRAMENTO E LIMPEZA
    // ==========================================
    printf("\n|---------------------------------------LIMPEZA DE MEMORIA-------------------------------------|\n");
    liberar_memoria(lista);

    clock_t tempo_final = clock(); // Fim do Clock Geral

    // ==========================================
    // FASE 5: RELATORIO DE DESEMPENHO [ISSUE 3] Formatação alinhada
    // ==========================================
    double duracao_geral = (double) (tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    double duracao_leitura = (double) (final_leitura - inicio_leitura) / CLOCKS_PER_SEC;
    double duracao_busca = (double) (final_busca - inicio_busca) / CLOCKS_PER_SEC;
    
    printf("\n|-------------------------------------------ANALISE FINAL--------------------------------------|\n");
    printf("| Tempo total de execucao do sistema:           %.3f seg\n", duracao_geral);
    printf("| Tempo de alocacao e leitura do CSV:           %.5f seg\n", duracao_leitura);
    printf("| Tempo da busca manual isolada (1 iteracao):   %.6f seg\n", duracao_busca); 
    printf("|----------------------------------------------------------------------------------------------|\n\n");
    
    return 0;
}