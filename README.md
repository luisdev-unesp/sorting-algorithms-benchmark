Sorting Benchmark - Classificação de Clientes

Este projeto foi desenvolvido para a disciplina de Algoritmos e Técnicas de Programação II na UNESP (IBILCE). O objetivo principal é realizar uma análise comparativa de desempenho entre diferentes algoritmos de ordenação aplicados ao contexto de classificação de clientes (bom/mau pagador).
📊 Algoritmos Analisados

O sistema implementa e compara a eficiência de cinco algoritmos clássicos, abrangendo diferentes complexidades computacionais:

    Algoritmos de Ordenação Eficiente (O(nlogn)):

        Quick Sort: Implementado com estratégia de particionamento para alta performance.

        Merge Sort: Utiliza a técnica de "dividir para conquistar" com estabilidade.

        Shell Sort: Uma extensão eficiente do Insertion Sort utilizando lacunas (gaps).

    Algoritmos de Ordenação Simples (O(n2)):

        Insertion Sort: Eficiente para pequenos conjuntos de dados ou vetores quase ordenados.

        Selection Sort: Implementação clássica baseada na seleção do menor elemento.

🛠️ Detalhes de Implementação

O projeto foca em medir como o tempo de execução escala conforme o volume de dados aumenta:

    Cálculo de Distância: Implementação de matriz de distância entre dados de referência e de avaliação para classificação.

    Benchmark de Tempo: Uso de funções de sistema para captura precisa do tempo de execução em segundos para cada algoritmo.

    Gerenciamento Dinâmico: Alocação de memória para manipulação de grandes vetores de dados, garantindo eficiência no uso de recursos do sistema.

    Relatório Técnico: Inclui análise gráfica comparativa, demonstrando visualmente o ponto de divergência entre algoritmos quadráticos e logarítmicos.

📂 Organização do Repositório

Seguindo os padrões de desenvolvimento de software, o projeto está organizado da seguinte forma:

    📁 src/: Arquivos de implementação (.c).

    📁 include/: Arquivos de cabeçalho e protótipos (.h).

    📁 docs/: Relatório técnico completo gerado via Overleaf (LaTeX).

    📄 Makefile: Script para automação da compilação.

🚀 Como Executar

    1. Clone o repositório.

    2. Compile o projeto utilizando o Makefile:
    '''bash
    make

    3. Execute o programa de benchmark:
    '''bash
    ./sorter

💻 Especificações do Sistema

Os testes foram realizados em ambiente Linux (Ubuntu), utilizando o compilador GCC com foco em medições de tempo reais para análise de complexidade de caso médio.
