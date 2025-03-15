#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Счетчики сравнений и перестановок
int C = 0;
int M = 0;

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
int selectSort(int arr[], int n){
    for (int i = 0; i < n - 1; i ++){
        int k = i;
        for (int j = i + 1; j < n; j ++){
            C ++;  // Увеличиваем счетчик сравнений
            if(arr[j] < arr[k]){
                k = j;
            }
        }
            M++; // Увеличиваем счетчик пересылок
        int temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;
    }
    return 0;
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
void InsertSort(int n, int A[n]){
    for(int i = 1; i < n; i ++){
        int temp = A[i];
        M++;
        int j = i - 1;
        while (j >= 0 && A[j] > temp){
            C++;
            A[j + 1] = A[j];
            M++;
            j--;
        }
        C++;
        A[j + 1] = temp;
        M++;
    }
}

// Сброс счетчиков
void ResetCounters() {
    C = 0;
    M = 0;
}
int main(){
    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);
    printf("|Трудоемкость квадратичных методов сортировки|\n");
    printf("|-------------------------------------------|\n");
    printf("|      |              Мф+Сф                 |\n");
    printf("|      |____________________________________|\n");
    printf("|  N   | Select  | Buble |  Shaker| Insert  |\n");
    printf("|-------------------------------------------|\n");

    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

        // Массивы для сортировки
        int A[n];

        // Шeйкерная сортировка
        int shaker_rand_total;


        // Случайный массив
        FillRand(n, A);
        ShakerSort(n, A);
        shaker_rand_total = M + C;
        ResetCounters();

        // Пузырьковая сортировка
        int bubble_rand_total;

        // Случайный массив
        FillRand(n, A);
        BubbleSort(n, A);
        bubble_rand_total = M + C;
        ResetCounters();

        // Select сортировка
        int select_rand_total;

        // Случайный массив
        FillRand(n, A);
        selectSort(A, n);
        select_rand_total = M + C;
        ResetCounters();

        // Insert сортировка
        int insert_rand_total;

        // Случайный массив
        FillRand(n, A);
        InsertSort(n, A);
        insert_rand_total = M + C;
        ResetCounters();

        // Вывод строки таблицы
        printf("|  %3d |  %6d | %6d | %6d | %6d |\n",
            n,
            select_rand_total, bubble_rand_total, shaker_rand_total, insert_rand_total);

 printf("|___________________________________________|\n");

        }
    return 0;
}