#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting_alg.h"

#define NUM_ELEMENTS 100000 // Número de elementos a serem gerados no arquivo randomfile.txt
#define MAX_VALUE 999999 // Valor máximo para os elementos gerados

// Definição de códigos de cor para o terminal
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Função para deletar os arquivos de saída
void deleteSortingFiles();

// Função para gerar um novo arquivo randomfile.txt
void generateRandomFile();

int main() {
    FILE *inputFile, *outputFile;
    int *numbers = NULL;
    int *originalNumbers = NULL;
    int count = 0;
    int num;
    int choice;
    char outputFileName[100];
    clock_t start, end;
    double cpu_time_used;

    while (1) {
        // Menu para selecionar o algoritmo de ordenação ou gerar arquivo
        printf("\nSelecione uma opção:\n");
        printf(RED "1. Bubble Sort\n" RESET);
        printf(GREEN "2. Heap Sort\n" RESET);
        printf(YELLOW "3. Quick Sort\n" RESET);
        printf(BLUE "4. Merge Sort\n" RESET);
        printf(MAGENTA "5. Bucket Sort\n" RESET);
        printf(CYAN "6. Shell Sort\n" RESET);
        printf(RED "7. Selection Sort\n" RESET);
        printf(GREEN "8. Radix Sort\n" RESET);
        printf(YELLOW "9. Insertion Sort\n" RESET);
        printf(BLUE "10. Sair\n" RESET);
        printf(MAGENTA "11. Gerar novo randomfile.txt\n" RESET);
        printf(CYAN "Escolha (1/2/3/4/5/6/7/8/9/10/11): " RESET);
        scanf("%d", &choice);

        if (choice == 10) {
            printf("Saindo do programa.\n");
            deleteSortingFiles();
            break;
        } else if (choice == 11) {
            generateRandomFile();
            continue;
        }

        // Abrir o arquivo randomfile.txt para leitura
        inputFile = fopen("rsrc/randomfile.txt", "r");
        if (inputFile == NULL) {
            perror("Erro ao abrir o arquivo rsrc/randomfile.txt");
            return EXIT_FAILURE;
        }

        // Contar o número de elementos no arquivo
        count = 0;
        while (fscanf(inputFile, "%d", &num) == 1) {
            count++;
        }
        rewind(inputFile);

        // Alocar memória para os vetores dinâmicos
        numbers = (int *)malloc(count * sizeof(int));
        originalNumbers = (int *)malloc(count * sizeof(int));
        if (numbers == NULL || originalNumbers == NULL) {
            perror("Erro ao alocar memória");
            return EXIT_FAILURE;
        }

        // Ler os números do arquivo e armazená-los no vetor
        count = 0;
        while (fscanf(inputFile, "%d", &num) == 1) {
            numbers[count] = num;
            originalNumbers[count] = num; // Fazer uma cópia dos números originais
            count++;
        }
        fclose(inputFile);

        // Restaurar os números originais antes de cada ordenação
        memcpy(numbers, originalNumbers, count * sizeof(int));

        // Medir o tempo de execução do algoritmo de ordenação
        start = clock();
        switch (choice) {
            case 1:
                bubbleSort(numbers, count);
                strcpy(outputFileName, "src/bubblesort.txt");
                break;
            case 2:
                heapSort(numbers, count);
                strcpy(outputFileName, "src/heapsort.txt");
                break;
            case 3:
                quickSort(numbers, 0, count - 1);
                strcpy(outputFileName, "src/quicksort.txt");
                break;
            case 4:
                mergeSort(numbers, 0, count - 1);
                strcpy(outputFileName, "src/mergesort.txt");
                break;
            case 5:
                bucketSort(numbers, count);
                strcpy(outputFileName, "src/bucketsort.txt");
                break;
            case 6:
                shellSort(numbers, count);
                strcpy(outputFileName, "src/shellsort.txt");
                break;
            case 7:
                selectionSort(numbers, count);
                strcpy(outputFileName, "src/selectionsort.txt");
                break;
            case 8:
                radixSort(numbers, count);
                strcpy(outputFileName, "src/radixsort.txt");
                break;
            case 9:
                insertionSort(numbers, count);
                strcpy(outputFileName, "src/insertionsort.txt");
                break;
            default:
                printf("Escolha inválida!\n");
                free(numbers);
                free(originalNumbers);
                continue;
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // Tempo em milissegundos

        // Abrir o arquivo de saída para escrita (apagando o existente)
        outputFile = fopen(outputFileName, "w");
        if (outputFile == NULL) {
            perror("Erro ao abrir o arquivo de saída");
            return EXIT_FAILURE;
        }

        // Escrever o algoritmo e o tempo de execução na primeira linha
        fprintf(outputFile, "Algorithm = %s | Time = %.2f ms\n", 
                (choice == 1) ? "Bubble Sort" :
                (choice == 2) ? "Heap Sort" :
                (choice == 3) ? "Quick Sort" :
                (choice == 4) ? "Merge Sort" :
                (choice == 5) ? "Bucket Sort" :
                (choice == 6) ? "Shell Sort" :
                (choice == 7) ? "Selection Sort" :
                (choice == 8) ? "Radix Sort" : "Insertion Sort", cpu_time_used);

        // Escrever o vetor ordenado no arquivo
        for (int i = 0; i < count; i++) {
            fprintf(outputFile, "%d\n", numbers[i]);
        }
        fclose(outputFile);

        printf("O vetor foi ordenado e salvo em %s\n", outputFileName);

        // Liberar a memória alocada
        free(numbers);
        free(originalNumbers);
    }

    return EXIT_SUCCESS;
}

// Função para deletar os arquivos de saída
void deleteSortingFiles() {
    const char *filenames[] = {
        "src/bubblesort.txt",
        "src/heapsort.txt",
        "src/quicksort.txt",
        "src/mergesort.txt",
        "src/bucketsort.txt",
        "src/shellsort.txt",
        "src/selectionsort.txt",
        "src/radixsort.txt",
        "src/insertionsort.txt"
    };

    for (int i = 0; i < 9; i++) {
        if (remove(filenames[i]) == 0) {
            printf("Arquivo %s deletado com sucesso.\n", filenames[i]);
        } else {
            perror("Erro ao deletar o arquivo");
        }
    }
}

// Função para gerar um novo arquivo randomfile.txt
void generateRandomFile() {
    FILE *file;
    file = fopen("rsrc/randomfile.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        int number = rand() % (MAX_VALUE + 1); // Gera um número aleatório entre 0 e 999999
        fprintf(file, "%d\n", number);
    }

    fclose(file);
    printf("Arquivo rsrc/randomfile.txt criado com sucesso.\n");
}
