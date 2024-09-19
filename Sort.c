#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para o Bubble Sort 
void bubbleSort(int vetor[], int n) {
    int aux, i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

// Função para o Selection Sort 
void selectionSort(int vetor[], int n) {
    int aux, i, j, menorIndice;
    for (i = 0; i < n - 1; i++) {
        menorIndice = i;
        for (j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[menorIndice]) {
                menorIndice = j;
            }
        }
        aux = vetor[menorIndice];
        vetor[menorIndice] = vetor[i];
        vetor[i] = aux;
    }
}

// Função para Inserction Sort
void insertionSort(int vetor[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

// Funções para ordenar com Merge Sort
void merge(int vetor[], int esquerda, int meio, int direita) { 
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;
    int vetEsquerda[n1], vetDireita[n2];
    
    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; i++)
        vetEsquerda[i] = vetor[esquerda + i];
    for (int j = 0; j < n2; j++)
        vetDireita[j] = vetor[meio + 1 + j];  
    
    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        if (vetEsquerda[i] <= vetDireita[j]) {
            vetor[k] = vetEsquerda[i];
            i++;
        } else {
            vetor[k] = vetDireita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de vetEsquerda
    while (i < n1) {
        vetor[k] = vetEsquerda[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de vetDireita
    while (j < n2) {
        vetor[k] = vetDireita[j];
        j++;
        k++;
    }
}

void mergeSort(int vetor[], int esquerda, int direita) {  
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        // Chama mergeSort nas duas metades
        mergeSort(vetor, esquerda, meio);      
        mergeSort(vetor, meio + 1, direita);

        // Junta as duas metades ordenadas
        merge(vetor, esquerda, meio, direita);
    }
}

// Gerar dados aleatórios
void vetorAleatorio(int vetor[], int tam) {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    for (int i = 0; i < tam; i++) {
        vetor[i] = rand() % 1000;  // Gera um número aleatório entre 0 e 999
    }
}

// Gerar dados ordenados
void vetorOrdenado(int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        vetor[i] = i;  // Atribui valores em ordem crescente
    }
}

// Gerar dados na ordem reversa
void vetorReverso(int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        vetor[i] = tam - i;  // Atribui valores em ordem decrescente
    }
}

// Função para medir o tempo de execução para algoritmos 
double tempoDeExecucao(void (*algoritmo)(int[], int), int vetor[], int tamanho) {
    clock_t inicio, fim;
    inicio = clock();  // Captura o tempo de início
    
    algoritmo(vetor, tamanho);  // Chama o algoritmo de ordenação
    
    fim = clock();  // Captura o tempo de fim
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;  // Calcula o tempo gasto em segundos
}

// Função específica para medir o tempo de execução do Merge Sort
double tempoDeExecucaoMergeSort(int vetor[], int tamanho) {
    clock_t inicio, fim;
    inicio = clock();  // Captura o tempo de início
    
    mergeSort(vetor, 0, tamanho - 1);  // Chama o Merge Sort com os parâmetros
    
    fim = clock();  // Recebe o tempo de fim
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;  // Irá calcular o tempo gasto em segundos
}

// Comparação dos algoritmos: ordenados, em aleatório e na ordem reversa
void compararAlgoritmos(int tamanhos[], int numTamanhos) {
    for (int i = 0; i < numTamanhos; i++) {
        int tamanho = tamanhos[i];
        int* vetor = (int*) malloc(tamanho * sizeof(int));  // Aloca o vetor dinamicamente
        
        printf("Tamanho do vetor: %d\n", tamanho);
        
        // 1. Comparar para dados aleatórios
        vetorAleatorio(vetor, tamanho);
        printf("Dados Aleatorios:\n");
        printf("Bubble Sort: %.6f s\n", tempoDeExecucao(bubbleSort, vetor, tamanho));
        printf("Selection Sort: %.6f s\n", tempoDeExecucao(selectionSort, vetor, tamanho));
        printf("Insertion Sort: %.6f s\n", tempoDeExecucao(insertionSort, vetor, tamanho));
        printf("Merge Sort: %.6f s\n\n", tempoDeExecucaoMergeSort(vetor, tamanho));

        // 2. Comparar para dados ordenados
        vetorOrdenado(vetor, tamanho);
        printf("Dados Ordenados:\n");
        printf("Bubble Sort: %.6f s\n", tempoDeExecucao(bubbleSort, vetor, tamanho));
        printf("Selection Sort: %.6f s\n", tempoDeExecucao(selectionSort, vetor, tamanho));
        printf("Insertion Sort: %.6f s\n", tempoDeExecucao(insertionSort, vetor, tamanho));
        printf("Merge Sort: %.6f s\n\n", tempoDeExecucaoMergeSort(vetor, tamanho));

        // 3. Comparar para dados em ordem reversa
        vetorReverso(vetor, tamanho);
        printf("Dados em Ordem Reversa:\n");
        printf("Bubble Sort: %.6f s\n", tempoDeExecucao(bubbleSort, vetor, tamanho));
        printf("Selection Sort: %.6f s\n", tempoDeExecucao(selectionSort, vetor, tamanho));
        printf("Insertion Sort: %.6f s\n", tempoDeExecucao(insertionSort, vetor, tamanho));
        printf("Merge Sort: %.6f s\n\n", tempoDeExecucaoMergeSort(vetor, tamanho));
        
        free(vetor);  // Libera o vetor após o uso
    }
}

int main() {
    int tamanhos[] = {100, 1000, 10000, 100000};  // Define os tamanhos dos vetores
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]); // O programa não precisará ficar calculando o tamanho do vetor
    
    compararAlgoritmos(tamanhos, numTamanhos);

    return 0;
}