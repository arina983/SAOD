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

// Сброс счетчиков
void ResetCounters() {
    C = 0;
    M = 0;
}

int main(){
    srand(time(NULL));
    int n_values[] = {100, 200,300,400,500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    printf("            Трудоемкость пузырьковой сортировки\n");
    printf("|---------------------------------------------------------|\n");
    printf("|  N   |  M+C (теоретич.)  | Mфакт+Cфакт                  |\n");
    printf("|      |                   |------------------------------|\n");
    printf("|------|-------------------|  Убыв.   |  Случ.   |Возр.   |\n");

    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

        // Теоретическая трудоемкость
        int theoreticalC = ((n * n) - n) / 2;
        int theoreticalM_worst = 3*(n * n - n) / 4;  // Худший случай (3 * (n * n - n)) / 4;
        int theoretical_total_worst = theoreticalC + theoreticalM_worst;

        // Фактическая трудоемкость
        int A[n];

        // Убывающий массив
        FillDec(n, A);
        BubbleSort(n, A);
        int dec_total = M + C;
        ResetCounters();

        // Случайный массив
        FillRand(n, A);
        BubbleSort(n, A);
        int rand_total = M + C;
        ResetCounters();

        // Возрастающий массив
        FillInc(n, A);
        BubbleSort(n, A);
        int inc_total = M + C;
        ResetCounters();

        // Вывод строки таблицы
        printf("| %3d  | %17d | %8d | %8d  | %5d |\n", n, theoretical_total_worst, dec_total, rand_total, inc_total);
    }

    printf("|---------------------------------------------------------|\n");

    return 0;
    
}