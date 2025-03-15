#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Счетчики сравнений и перестановок
int C = 0;
int M = 0;

//массив возрастающих чисел
void FillInc(int n,int A[n]){
    for (int i = 0; i < n; i ++) {
        A[i] = i + 1;
    }
}
//массив убывающих чисел
void FillDec(int n, int A[n]){
    for (int j = 0; j < n; j ++){
        A[j] = n - j;
    }
} 
//массив случайных чисел
void FillRand(int n, int A[n]){
    srand(time(NULL));
    for (int k = 0; k < n; k ++ ){
        A[k] = rand() % 100;
    }
}
//вывод заполненного массива
void PrintMas(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void BubbleSort(int n, int A[n]){
    for(int i = 0; i < n - 1; i ++){
        for (int j = 0; j < n - i - 1; j ++){
            C ++;
            if(A[j] > A[j + 1]){
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                M ++;
            }
        }
    }
}

// Сброс счетчиков
void ResetCounters() {
    C = 0;
    M = 0;
}

int main(){
    int n;
    printf("Введите количество элементов массива: \n");
    scanf("%d", &n);
    int A[n];

    FillInc(n, A);
    printf("Массив заполненный возрастающими числами: \n");
    PrintMas(n, A);
    BubbleSort(n, A);
    printf("Отсортированный массив:\n");
    PrintMas(n, A);
    printf("Сумма M + C для возрастающего массива: %d\n", M + C);
    ResetCounters();

    FillDec(n, A);
    printf("Массив заполненный убывающими числами: \n");
    PrintMas(n, A);
    BubbleSort(n, A);
    printf("Отсортированный массив:\n");
    PrintMas(n, A);
    printf("Сумма M + C для убывающего массива: %d\n", M + C);
    ResetCounters();

    FillRand(n, A);
    printf("Массив заполненный случайными числами: \n");
    PrintMas(n, A);
    BubbleSort(n, A);
    printf("Отсортированный массив:\n");
    PrintMas(n, A);
    printf("Сумма M + C для случайного массива: %d\n", M + C);

    return 0;
}