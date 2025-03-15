#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

// Глобальные счетчики для сравнений и пересылок
int comparisons = 0;
int swaps = 0;

void FillInc(int n,int A[n]){
    for (int i = 0; i < n; i ++) {
        A[i] = i + 1;
    }
}
void FillDec(int n, int A[n]){
    for (int j = 0; j < n; j ++){
        A[j] = n - j;
    }
} 
void FillRand(int n, int A[n]){
    srand(time(NULL));
    for (int k = 0; k < n; k ++ ){
        A[k] = rand() % 100;
    }
}
void PrintMas(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
int selectSort(int arr[], int n){
    comparisons = 0;// Сброс счётчиков до начала сортировки 
	swaps = 0;
    for (int i = 0; i < n - 1; i ++){
        int k = i;
        for (int j = i + 1; j < n; j ++){
            comparisons ++;  // Увеличиваем счетчик сравнений
            if(arr[j] < arr[k]){
                k = j;
            }
        }
            swaps++; // Увеличиваем счетчик пересылок
        int temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;
    }
    return 0;
}

int main(){
    int n;
    printf("Введите размер массива А: ");
    scanf("%d", &n);
    int A[n];
    FillInc(n, A);
    //заполнение массива возрастающими числами
    printf("Массив заполненный возрастающими числами:\n");
    PrintMas(n, A);

    printf("Массив после сортировки: \n");
    selectSort(A, n);
    for (int i = 0; i < n; i ++){
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество пересылок: %d\n", swaps);
    //Заполнение массива убывающими числами
    FillDec(n, A);
    printf("Массив заполненный убывающими числами:\n");
    PrintMas(n, A);
    printf("Массив после сортировки: \n");
    selectSort(A, n);
    for (int i = 0; i < n; i ++){
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество пересылок: %d\n", swaps);
    // Заполнение массива случайными числами
    FillRand(n, A);
    printf("Массив, заполненный случайными числами:\n");
    PrintMas(n, A);
    printf("Массив после сортировки: \n");
    selectSort(A, n);
    for (int i = 0; i < n; i ++){
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество пересылок: %d\n", swaps);
    return 0;
}