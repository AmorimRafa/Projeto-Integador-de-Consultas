# Projeto Integrador: Sistema de Consultas (Fase I)

* [O que é este projeto?](#o-que-é-este-projeto)
* [Como executar?](#como-executar)
* [Protocolo Experimental](#protocolo-experimental)
* [Resultados e Relatório](#resultados-e-relatório)
* [Contribuição e Autoria](#contribuição-e-autoria)

---

Este repositório contém o código-fonte para o sistema de processamento de dados e análise de performance de busca sequencial, desenvolvido como parte da Fase I do Projeto Integrador.

## O que é este projeto?

O sistema realiza a leitura de grandes volumes de dados (Dataset de Produtos), organiza-os em memória dinâmica e executa testes de estresse para medir a eficiência de algoritmos de busca em linguagem C.

* **Página Oficial do Repositório:** [https://github.com/AmorimRafa/Projeto-Integrador-de-Consultas](https://github.com/AmorimRafa/Projeto-Integrador-de-Consultas)
* **Dataset:** Estrutura baseada em registros de `id`, `nome`, `categoria` e `valor`.

## Como executar?

Para compilar e rodar os testes de performance localmente, utilize um compilador C (como GCC ou Clang).

1.  **Compilação:**
    ```bash
    gcc -O3 main.c -o sistema_consultas
    ```
2.  **Execução:**
    ```bash
    ./sistema_consultas dataset3.csv
    ```

## Protocolo Experimental

Para garantir a validade científica das métricas, este projeto segue rigorosamente os seguintes critérios:
* **Carga Inicial:** O vetor dinâmico é totalmente carregado antes das medições.
* **Volume de Testes:** Realização de 30.000 buscas automatizadas por ciclo.
* **Cenários:** Testes cobrindo elementos no início, meio, fim e IDs inexistentes.
* **Média Final:** O tempo total é dividido pelo número de execuções após 10 repetições completas do protocolo.

## Resultados e Relatório

O programa gera métricas detalhadas que devem ser incluídas no relatório técnico:
* Contagem total de registros carregados.
* Tempo médio de busca em microssegundos.
* Análise de comportamento (Relação Tamanho do Vetor vs. Tempo).

## Contribuição e Autoria

Este é um projeto acadêmico. O histórico de contribuições e o desenvolvimento das funcionalidades podem ser verificados através dos commits dos integrantes:

* **Rafael Amorim**
* **Pedro Oliveira**
* **Caio Freitas**

A participação de todos os membros é comprovada pelo gráfico de contribuidores do GitHub.
