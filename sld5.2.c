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
// Сортировка Шелла с последовательностью шагов по формуле Д. Кнута
void ShellSortKnuth(int n, int A[n]){
    C = 0;
    M = 0;
    int h = 1;
    while(h <= n / 3){
        h = h * 3 + 1; // Формула Д. Кнута
    }
    while (h > 0){
        for(int i = h; i < n; i ++){
            int t = A[i];
            M ++;
            int j = i;
            while(j >= h && A[j - h] > t){
                C ++;
                A[j] = A[j - h];
                M ++;
                j -= h;
            }
            C ++;
            A[j] = t;
            M ++;
        }
        h = (h - 1) / 3; // Уменьшаем шаг
    }
}

// Сортировка Шелла с другой последовательностью шагов (степени двойки)
void ShellSortOther(int n, int A[n]) {
    C = 0;
    M = 0;
    int h = 1;
    while (h < n) {
        h = h * 2;  // Последовательность шагов: 1, 2, 4, 8, 16, ...
    }
    while (h > 0) {
        for (int i = h; i < n; i++) {
            int temp = A[i];
            M++;
            int j = i;
            while (j >= h && A[j - h] > temp) {
                C++;
                A[j] = A[j - h];
                M++;
                j -= h;
            }
            C++;
            A[j] = temp;
            M++;
        }
        h = h / 2;  // Уменьшаем шаг
    }
}



int main(){
    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    printf("|              Исследoвание трудоемкости метода Шелла                                       |\n");
    printf("|-------------------------------------------------------------------------------------------|\n");
    printf("|   N  | h1...hm по формуле Д.Кнута |  Shell Mф+Сф  |h1...hm по др. формуле|  Shell Mф + Сф | \n");
    printf("|______|____________________________________________________________________________________|\n");
    printf("|      |                            |               |                      |                |\n");

    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

        // Массивы для сортировки
        int A[n];
        int B[n];

        FillRand(n, A);
        for (int j = 0; j < n; j++) {
            B[j] = A[j];  // Копия массива для второй сортировки
        }
        
          // Сортировка Шелла с последовательностью шагов по формуле Д. Кнута
          ShellSortKnuth(n, A);
          int shell_C_knuth = C;
          int shell_M_knuth = M;
  
          // Сортировка Шелла с другой последовательностью шагов
          ShellSortOther(n, B);
          int shell_C_other = C;
          int shell_M_other = M;
   
          // Вывод результатов
          printf("| %4d | 1, 4, 13, 40, 121,   ...   | %7d       | 1, 2, 4, 8, 16, ...  | %7d        |\n", n, shell_C_knuth + shell_M_knuth, shell_C_other + shell_M_other);
          printf("|-------------------------------------------------------------------------------------------|\n");
      }
   
  
  
          return 0;
}