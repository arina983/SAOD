#include <stdio.h>
#include <stdlib.h>
int C = 0;
int M = 0;

void PrintMas(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void BubbleSort(int n, int A[n]){
    for (int i = 0; i < n - 1; i ++){
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
int controlSum(int n, int A[n]){
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
int main() {
    int n;
    printf("Введите размер массива А: ");
    scanf("%d", &n);
    int A[n];
    printf("Введите элементы массива: \n");
    for (int i = 0; i < n; i ++){
        scanf("%d", &A[i]);
    }
    
    printf("Исходный массив: \n");
    PrintMas(n, A);
    printf("Количество серий: %d\n", RunNumber(n , A));
    printf("Контрольная сумма: %d\n", controlSum(n, A));
    BubbleSort(n, A);
    printf("Отсортированный массив:\n");
    PrintMas(n, A);
    printf("Количество серий: %d\n", RunNumber(n , A));
    printf("Контрольная сумма: %d\n", controlSum(n, A));

    printf("Фактическое количество сравнений: %d\n", C);
    printf("Фактическое количество пересылок: %d\n", M);

     // M (максимальное количество сравнений) = n(n - 1) / 2
    // S (максимальное количество пересылок) = n - 1
    int theoreticalComparisons = ((n * n) - n) / 2;
    int theoreticalSwaps = n*(n-1)/2 - (n-1);

    printf("Теоретическое количество сравнений: %d\n", theoreticalComparisons);
    printf("Теоретическое количество пересылок: %d\n", theoreticalSwaps);
    
    return 0;

}