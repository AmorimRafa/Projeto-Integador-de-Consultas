# 🔍 Projeto Integrador: Sistema de Consultas e Benchmark de Algoritmos

Bem-vindo ao repositório oficial do Sistema de Consultas! Este projeto é um ambiente de testes de stress e análise de performance desenvolvido em **C** e executado num ambiente isolado via **Docker**. 

O objetivo principal é carregar grandes volumes de dados reais em memória RAM e executar um *benchmark* automatizado, comparando empiricamente o desempenho de algoritmos clássicos de pesquisa estruturada.

* **Página Oficial do Repositório:** [https://github.com/AmorimRafa/Projeto-Integrador-de-Consultas](https://github.com/AmorimRafa/Projeto-Integrador-de-Consultas)

## 📑 Índice
* [Evolução do Projeto](#-evolução-do-projeto)
* [Arquitetura e Explicação Técnica](#-arquitetura-e-explicação-técnica)
* [Estrutura do Repositório](#-estrutura-do-repositório)
* [Pré-requisitos e Execução (Docker)](#%EF%B8%8F-pré-requisitos-e-execução-docker)
* [Protocolo Experimental](#-protocolo-experimental)
* [Resultados e Logs](#-resultados-e-logs)
* [Autoria](#-contribuição-e-autoria)

---

## 🚀 Evolução do Projeto

O sistema foi desenvolvido em duas etapas incrementais para fins de validação científica:

* **Fase I (Baseline):** Implementação da carga de dados via leitura de ficheiros `.csv`, alocação em Vetor Dinâmico e testes de stress baseados em **Pesquisa Sequencial**.
* **Fase II (Otimização):** Implementação de uma **Tabela Hash** de raiz, com tratamento de colisões por Encadeamento (Listas Encadeadas). O sistema agora executa testes espelhados para medir o ganho real de performance sobre o baseline da Fase I.

---

## 🧠 Arquitetura e Explicação Técnica

Para garantir a máxima fiabilidade dos testes, o projeto evita *overheads* do sistema operativo durante os ciclos de pesquisa. As tecnologias e conceitos aplicados incluem:

1. **Gestão de Memória:** Uso extensivo de ponteiros, `malloc`, `calloc` e `free` para garantir que o dataset (composto por structs de `id`, `nome`, `categoria` e `valor`) não gere fugas de memória (*memory leaks*).
2. **Tratamento de Colisões:** A Tabela Hash utiliza o método de **Encadeamento Aberto**. Quando duas chaves resultam no mesmo índice, o novo registo é inserido no topo de uma lista encadeada (Política LIFO - *Last In, First Out*).
3. **Função Hash (Dobra Simples):** O algoritmo de dispersão matemático definido para este projeto divide a chave de pesquisa em blocos e calcula o módulo sobre o tamanho total da tabela.
   $$h(x) = \left( \lfloor x/1000 \rfloor + (x \pmod{1000}) \right) \pmod{m}$$
4. **Análise de Complexidade Teórica vs. Prática:** O projeto comprova empiricamente o comportamento da Pesquisa Sequencial ($O(n)$) e as degradações da Tabela Hash ($O(1)$ para $O(n)$) em cenários de alto índice de colisões.

---

## 📂 Estrutura do Repositório

O projeto utiliza a seguinte arquitetura de ficheiros e diretorias:

```text
Projeto-Integrador-de-Consultas/
├── logs/                 # Diretoria com os ficheiros CSV de resultados
│   ├── logs_hash.csv
│   └── logs_sequencial.csv
├── scripts/              # Código-fonte em C e executável
│   ├── app               # Binário gerado após a compilação
│   ├── app.c             # Arquivo principal (Main / Fluxo do Sistema)
│   ├── produto.c         # Implementação das lógicas de pesquisa e logs
│   └── produto.h         # Declaração das structs e assinaturas
├── .gitignore            # Arquivos ignorados pelo Git
├── dataset3.csv          # Base de dados oficial em texto plano
├── dataset_teste.csv     # Base de dados reduzida para testes rápidos
├── docker-compose.yml    # Orquestração do ambiente de compilação C
├── LICENSE               # Licença do projeto
└── README.md             # Documentação do projeto
⚙️ Pré-requisitos e Execução (Docker)
Para garantir que o código compila e corre exatamente da mesma forma em qualquer máquina, o projeto foi contentorizado.

Pré-requisitos:

Docker e Docker Compose instalados no seu sistema.

Passo a Passo:
Clone o repositório para a sua máquina local e aceda à pasta raiz do projeto.

Inicie o contentor interativo utilizando o serviço compiler configurado no Docker Compose:

Bash
docker-compose run --rm compiler bash
Dentro do terminal do contentor, navegue para a pasta de scripts e compile o código:

Bash
cd scripts
gcc app.c produto.c -o app
Execute o binário gerado para iniciar os testes:

Bash
./app
🔬 Protocolo Experimental
Para evitar oscilações de cache ou variações do processador, as métricas deste projeto seguem um protocolo científico rigoroso que funciona de forma 100% automatizada:

Isolamento de Variáveis: As tabelas (Vetor e Hash) são carregadas integralmente antes do disparo dos cronómetros (<time.h>).

Baterias de Repetição: O sistema executa 3 ciclos (iterações) completos do fluxo de testes para diluir anomalias de hardware.

Volume Constante: Em cada ciclo, o algoritmo realiza exatas 1.000 pesquisas consecutivas para cada chave.

Cenários Analisados: São procurados os IDs que se encontram na primeira posição (Início), no meio, na última posição (Fim) do dataset, além de uma chave inexistente.

📊 Resultados e Logs
Ao finalizar a execução, o programa fornece um relatório consolidado no terminal (Standard Output), contendo as métricas de estrutura de dados:

Contagem total de registos validados e alocados.

Contagem exata de colisões registadas na construção da Hash.

Tempos operacionais fracionados em microssegundos.

Além disso, os motores de teste exportam os dados em bruto (Raw Data) automaticamente para a pasta logs/, facilitando a construção de gráficos para análises académicas:

📄 logs_sequencial.csv

📄 logs_hash.csv

👥 Contribuição e Autoria
Este é um projeto com fins académicos. O histórico de desenvolvimento, as ramificações e a evolução da codebase podem ser verificados através da aba de commits do repositório.

Equipa de Desenvolvimento:

Rafael Amorim

Pedro Oliveira

Caio Freitas

A participação e a responsabilidade pelas Issues estão documentadas e registadas no gráfico de contribuidores e nos Pull Requests do GitHub.