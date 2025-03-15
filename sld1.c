#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

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
int cheksum(int n, int A[n]){
    int sum = 0;
    for (int i = 0; i < n; i ++){
        sum += A[i];
    }
    return sum;
} 
int RunNumber(int n, int A[n]){
    int count = 1;
    for (int i = 1; i < n; i ++) {
        if (A[i] < A[i - 1]) {
            count ++;
        }
    }
    return count;
} 
void PrintMas(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
 
int main() {
    int n;
    printf("Введите размер массива А: ");
    scanf("%d", &n);
    int A[n];
    FillInc(n, A);
    //
    printf("Массив заполненный возрастающими числами:\n");
    PrintMas(n, A);
    printf("Количество серий: %d\n", RunNumber(n , A));
    printf("Контрольная сумма: %d\n", cheksum(n, A));

    // Заполнение массива убывающими числами
    FillDec(n, A);
    printf("Массив, заполненный убывающими числами:\n");
    PrintMas(n, A);
    printf("Количество серий: %d\n", RunNumber(n, A));
    printf("Контрольная сумма: %d\n", cheksum(n, A));

    // Заполнение массива случайными числами
    FillRand(n, A);
    printf("Массив, заполненный случайными числами:\n");
    PrintMas(n, A);
    printf("Количество серий: %d\n", RunNumber(n, A));
    printf("Контрольная сумма: %d\n", cheksum(n, A));

    return 0;
}
