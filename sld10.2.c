#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Глобальные переменные для отслеживания глубины рекурсии
int max_depth1 = 0;
int max_depth2 = 0;
int current_depth = 0;

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

void QuickSort1(int L, int R, int A[]) {
    current_depth++;
    if (current_depth > max_depth1) max_depth1 = current_depth;
    
    int x = A[L];
    int i = L;
    int j = R;
    
    while (i < j) {
        while (A[i] < x) i++;
        while (A[j] > x) j--;
        
        if (i <= j) {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }
    
    if (L < j) QuickSort1(L, j, A);
    if (i < R) QuickSort1(i, R, A);
    
    current_depth--;
}


void QuickSort2(int L, int R, int A[]){
    current_depth++;
    if (current_depth > max_depth2) max_depth2 = current_depth;

    while(L < R){
        int x = A[L];
        int i = L;
        int j = R;

        while (i < j){
            while (A[i] < x) i ++;
            while (A[j] > x) j --;

            if (i <= j){
                int temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                i++;
                j--;
            }
        }

        if (j - L < R - i){
            if (L < j) QuickSort2(L, j, A);
            L = i;
        } else {
            if (i < R) QuickSort2(i, R, A);
            R = j;
        }
    }
    current_depth--;
}

int main(){

    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    printf("         Глубина рекурсии сортировки метода Хоара\n");
    printf("--------------------------------------------------------\n");
    printf("| N    |   QickSort1           |      QuickSort2       |\n");
    printf("|______________________________________________________|\n");
    printf("|      |  Убыв. | Случ. |Возр. |  Убыв. | Случ. |Возр. |\n");
    printf("|------------------------------------------------------|\n");
   
    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

        // Массивы для сортировки
        int A[n], B[n];
        printf("| %4d ", n);

        FillDec(n, A);
        max_depth1 = 0; current_depth = 0;
        QuickSort1(0, n-1, A);
        printf("| %4d  |", max_depth1);
        
        // Случайный массив
        FillRand(n, A);
        max_depth1 = 0; current_depth = 0;
        QuickSort1(0, n-1, A);
        printf(" %4d  |", max_depth1);
        
        // Возрастающий массив
        FillInc(n, A);
        max_depth1 = 0; current_depth = 0;
        QuickSort1(0, n-1, A);
        printf(" %4d  |", max_depth1);
        
        // Тестирование QuickSort2
        // Убывающий массив
        FillDec(n, B);
        max_depth2 = 0; current_depth = 0;
        QuickSort2(0, n-1, B);
        printf(" %4d  |", max_depth2);
        
        // Случайный массив
        FillRand(n, B);
        max_depth2 = 0; current_depth = 0;
        QuickSort2(0, n-1, B);
        printf(" %4d  |", max_depth2);
        
        // Возрастающий массив
        FillInc(n, B);
        max_depth2 = 0; current_depth = 0;
        QuickSort2(0, n-1, B);
        printf(" %4d  |\n", max_depth2);
    }
    
    printf("--------------------------------------------------------\n");
    
    
    return 0;
}