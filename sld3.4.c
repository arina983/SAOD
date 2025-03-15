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
                M += 3;
            }
        }
    }
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

// Сброс счетчиков
void ResetCounters() {
    C = 0;
    M = 0;
}

int main(){
    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    printf("           Трудоемкость пузырьковой и шейкерной сортировок\n");
    printf("|__________________________________________________________________|\n");
    printf("|  N   | Mф+Cф пузырьковой          |      Mф+Cф  шейкерной        |\n");
    printf("|      |____________________________|______________________________|\n");
    printf("|      | Убыв.    | Случ.  |Возр.   | Убыв.  |  Случ.   |Возр.     |\n");

    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

         // Массивы для сортировки
         int A[n];

         // Пузырьковая сортировка
         int bubble_dec_total, bubble_rand_total, bubble_inc_total;
 
         // Убывающий массив
         FillDec(n, A);
         BubbleSort(n, A);
         bubble_dec_total = M + C;
         ResetCounters();
 
         // Случайный массив
         FillRand(n, A);
         BubbleSort(n, A);
         bubble_rand_total = M + C;
         ResetCounters();
 
         // Возрастающий массив
         FillInc(n, A);
         BubbleSort(n, A);
         bubble_inc_total = M + C;
         ResetCounters();
 
         // Шейкерная сортировка
         int shaker_dec_total, shaker_rand_total, shaker_inc_total;
 
         // Убывающий массив
         FillDec(n, A);
         ShakerSort(n, A);
         shaker_dec_total = M + C;
         ResetCounters();
 
         // Случайный массив
         FillRand(n, A);
         ShakerSort(n, A);
         shaker_rand_total = M + C;
         ResetCounters();
 
         // Возрастающий массив
         FillInc(n, A);
         ShakerSort(n, A);
         shaker_inc_total = M + C;
         ResetCounters();
 
         // Вывод строки таблицы
         printf("|  %3d |  %6d  | %6d | %6d | %6d | %6d   | %6d   |\n",
                n,
                bubble_dec_total, bubble_rand_total, bubble_inc_total,
                shaker_dec_total, shaker_rand_total, shaker_inc_total);
     }
 
     printf("|__________________________________________________________________|\n");
 
     return 0;
 }