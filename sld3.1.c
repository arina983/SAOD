#include <stdio.h> 

int C = 0;
int M = 0;

void FillInc(int n, int A[n]){
    for (int i = 0; i < n; i ++){
        A[i] = i + 1;
    }
}
int controlSum(int n, int A[n]){
    int sum = 0;
    for(int i = 0; i < n; i ++){
        sum += A[i];
    }
    return sum;
}
void ShakerSort(int n, int A[n]){
    int L = 0, R = n - 1;
    int k;
    while (L < R) {
        k = R;
    for (int i = L; i < R; i ++){
        C++;
            if(A[i] > A[i + 1]){
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                M += 3;
                k = i;
            }
        }
        R = k;

        k = L;
        for (int i = R; i > L; i --){
            C++;
            if (A[i] < A[i - 1]){
                int temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                M += 3;
                k = i;
            }
        }
        L = k;
    }
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
//вывод заполненного массива
void PrintMas(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int n; 
    printf("Введите размер массива: ");
    scanf("%d", &n);
    int A[n];
    printf("Массив заполненный возрастающими числами: ");
    FillInc(n, A);
    PrintMas(n, A);
    printf("Контрольная суммма до сортировки:  %d\n", controlSum(n, A));
    printf("Число серий в массиве до сортировки: %d\n", RunNumber(n, A));
    
    ShakerSort(n, A);
    printf("Отсортированный массив: ");
    PrintMas(n, A);
    printf("Контрольная суммма после сортировки:  %d\n", controlSum(n, A));
    printf("Число серий в массиве после сортировки: %d\n", RunNumber(n, A));
    printf("Количeство сравнений(С): %d\n", C);
    printf("Количество пересылок(М): %d\n", M);

    return 0;
}