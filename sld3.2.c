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

void ShakerSort(int n, int A[n]){
    int L = 0, R = n - 1;
    int k;
    do {
        k = L;

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

        for (int j = R; j > L; j --){
            C++;
            if (A[j] < A[j - 1]){
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                M += 3;
                k = j;
            }
        }
        L = k;
    } while (L < R);
}
int main(){
    int n;
    printf("Введите размер массива А: ");
    scanf("%d", &n);

    srand(time(NULL));
    int A[n];

    FillInc(n, A);
    //заполнение массива возрастающими числами
    printf("Массив заполненный возрастающими числами:\n");
    PrintMas(n, A);

    C = 0; M = 0;

    ShakerSort(n, A);
    printf("Массив после сортировки: \n");
    PrintMas(n, A);

    printf("Kоличество сравнений: %d\n", C);
    printf("Kоличество пересылок: %d\n", M);
    printf("Сумма M + C: %d\n\n", M + C);

    //Заполнение массива убывающими числами
    FillDec(n, A);
    printf("Массив заполненный убывающими числами:\n");
    PrintMas(n, A);
    C = 0; M = 0;
    ShakerSort(n, A);
    printf("Массив после сортировки: \n");
    PrintMas(n, A);

    printf("Kоличество сравнений: %d\n", C);
    printf("Kоличество пересылок: %d\n", M);
    printf("Сумма M + C: %d\n\n", M + C);

    // Заполнение массива случайными числами
    FillRand(n, A);
    printf("Массив, заполненный случайными числами:\n");
    PrintMas(n, A);
    C = 0; M = 0;
    ShakerSort(n, A);
    printf("Массив после сортировки: \n");
    PrintMas(n, A);
    printf("Kоличество сравнений: %d\n", C);
    printf("Kоличество пересылок: %d\n", M);
    printf("Сумма M + C: %d\n\n", M + C);

    return 0;
}