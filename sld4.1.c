#include <stdio.h>

int C = 0;
int M = 0;

void FillInc(int n, int A[n]){
    for (int i = 0; i < n; i ++){
        A[i] = i + 1;
    }
}
void PrintMas(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void InterSort(int n, int A[n]){
    for(int i = 1; i < n; i ++){
        int temp = A[i];
        M++;
        int j = i - 1;
        while (j > 0 && A[j] > temp){
            C++;
            A[j + 1] = A[j];
            M++;
            j = j - 1;
        }
        C++;
        A[j + 1] = temp;
        M++;
    }
}
int main(){
    int n;
    printf("Введите размер массива А: ");
    scanf("%d", &n);
    int A[n];
    FillInc(n, A);
    printf("Исходный массив: \n");
    PrintMas(n, A);
    InterSort(n, A);
    printf("Отсортированный массив:\n");
    PrintMas(n, A);
    printf("Кол-во сравнений: %d\n", C);
    printf("Кол-во пересылок: %d\n", M);

    return 0;

}