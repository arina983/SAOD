#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSortOriginal(int arr[], int n, int *comparisons, int *movements) {
    int i, j, k;
    *comparisons = 0;
    *movements = 0;

    for (i = 0; i < n-1; i++) {
        k = i;
        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[k])
                k = j;
        }
        if (k != i) {
            int temp = arr[k];
            arr[k] = arr[i];
            arr[i] = temp;
            (*movements)++;
        }
    }
}

void selectionSortImproved(int arr[], int n, int *comparisons, int *movements) {
    int i, j, k;
    *comparisons = 0;
    *movements = 0;

    for (i = 0; i < n-1; i++) {
        k = i;
        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[k])
                k = j;
        }
        // Улучшение: выполняем обмен только если минимальный элемент не на своем месте
        if (k != i) {
            int temp = arr[k];
            arr[k] = arr[i];
            arr[i] = temp;
            (*movements)++;
        }
    }
}

void generateDecreasingArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;
}

void generateIncreasingArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}

int main() {
    srand(time(NULL));
    int n_values[] = {10, 100};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|  N  |  M+C (теоретич.)  | Исходный Mфакт+Cфакт             | Улучшенный Mфакт+Cфакт           |\n");
    printf("|     |                   |----------------------------------|----------------------------------|\n");
    printf("|     |                   |  Убыв.   |  Случ.   |  Возраст.  |  Убыв.   |  Случ.   |  Возраст.  |\n");
    printf("|-----|-------------------|----------|----------|------------|----------|----------|------------|\n");

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        int arr[n], arr_copy[n];
        int comparisons, movements;

        // Убывающий массив
        generateDecreasingArray(arr, n);
        for (int j = 0; j < n; j++) arr_copy[j] = arr[j]; // Копируем массив
        selectionSortOriginal(arr, n, &comparisons, &movements);
        int decreasing_total_original = comparisons + movements;

        generateDecreasingArray(arr_copy, n);
        selectionSortImproved(arr_copy, n, &comparisons, &movements);
        int decreasing_total_improved = comparisons + movements;

        // Случайный массив
        generateRandomArray(arr, n);
        for (int j = 0; j < n; j++) arr_copy[j] = arr[j];
        selectionSortOriginal(arr, n, &comparisons, &movements);
        int random_total_original = comparisons + movements;

        generateRandomArray(arr_copy, n);
        selectionSortImproved(arr_copy, n, &comparisons, &movements);
        int random_total_improved = comparisons + movements;

        // Возрастающий массив
        generateIncreasingArray(arr, n);
        for (int j = 0; j < n; j++) arr_copy[j] = arr[j];
        selectionSortOriginal(arr, n, &comparisons, &movements);
        int increasing_total_original = comparisons + movements;

        generateIncreasingArray(arr_copy, n);
        selectionSortImproved(arr_copy, n, &comparisons, &movements);
        int increasing_total_improved = comparisons + movements;

        printf("| %3d | %17d | %8d | %8d | %10d | %8d | %8d | %10d |\n", 
               n, ((n*n)-n)/2 + 3*(n - 1), 
               decreasing_total_original, random_total_original, increasing_total_original, 
               decreasing_total_improved, random_total_improved, increasing_total_improved);
    }

    printf("-------------------------------------------------------------------------------------------------\n");

    return 0;
}