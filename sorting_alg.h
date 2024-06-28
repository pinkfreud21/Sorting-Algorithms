#ifndef SORTING_ALG_H
#define SORTING_ALG_H

// Declaração das funções de ordenação
void bubbleSort(int arr[], int n);
void swap(int *a, int *b);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void bucketSort(int arr[], int n);
void shellSort(int arr[], int n);
void selectionSort(int arr[], int n);
void radixSort(int arr[], int n);
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
void insertionSort(int arr[], int n);

#endif // SORTING_ALG_H
