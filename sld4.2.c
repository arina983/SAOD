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
// Теоретическая оценка M + C для Insertion Sort
int TheoreticalWork(int n, int type) {
    switch (type) {
        case 0: // Убывающий массив (худший случай)
            return (n * n - n) / 2 + 2 * (n - 1) + (n * n - n) / 2;
        case 1: // Случайный массив (средний случай)
            return (n * n - n) / 4 + (n - 1) + (n * n - n) / 4;
        case 2: // Возрастающий массив (лучший случай)
            return 2 * (n - 1) + (n - 1);
        default:
            return 0;
    }
}
int main(){
    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);
    printf("-------------------------------------------------------------------\n");
    printf("|          Трудоемкость метода прямого включения InterSort        |\n");
    printf("|_________________________________________________________________|\n");
    printf("|  N   | M+C теоретич              |      Mф+Cф                   |\n");
    printf("|______|___________________________|______________________________|\n");
    printf("|      |Убыв.    | Случ.  |Возр.   | Убыв.  |  Случ.   |Возр.     |\n");
    printf("|-----------------------------------------------------------------|\n");

    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

        // Массивы для сортировки
        int A[n];

        // Пузырьковая сортировка
        int inter_dec_total, inter_rand_total, inter_inc_total;

        // Убывающий массив
        FillDec(n, A);
        InsertSort(n, A);
        inter_dec_total = M + C;
        ResetCounters();

        // Случайный массив
        FillRand(n, A);
        InsertSort(n, A);
        inter_rand_total = M + C;
        ResetCounters();

        // Возрастающий массив
        FillInc(n, A);
        InsertSort(n, A);
        inter_inc_total = M + C;
        ResetCounters();

        // Теоретическая трудоёмкость
        int theo_dec = TheoreticalWork(n, 0); // Убывающий
        int theo_rand = TheoreticalWork(n, 1); // Случайный
        int theo_inc = TheoreticalWork(n, 2); // Возрастающий

        // Вывод строки таблицы
        printf("|  %3d |  %6d | %6d | %6d | %6d | %6d   | %6d   |\n",
               n,
               theo_dec, theo_rand, theo_inc,
               inter_dec_total, inter_rand_total, inter_inc_total);

    printf("|_________________________________________________________________|\n");

    }

    return 0;
}