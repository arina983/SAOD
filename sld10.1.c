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

void QuickSort(int L, int R, int A[]) {
    if (L >= R) return;
    
    int x = A[L];
    int i = L;
    int j = R;
    
    while (i <= j) {
        C++;
        while (A[i] < x) {
            C++;
            i++;
        }
        
        C++;
        while (A[j] > x) {
            C++;
            j--;
        }
        
        if (i <= j) {
            // Обмен элементов
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            M += 3; // 3 операции перемещения
            i++;
            j--;
        }
    }
    
    // Рекурсивные вызовы для подмассивов
    QuickSort(L, j, A);
    QuickSort(i, R, A);
}

int main(){

    int n_values[] = {100, 200, 300, 400, 500};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    printf("               Трудоемкость метода Хоара\n");
    printf("--------------------------------------------------\n");
    printf("| N    |           QickSort (Мф+Сф)              |\n");
    printf("|________________________________________________|\n");
    printf("|      |  Убыв.      |  Случ.       |Возр.       |\n");
    printf("|------------------------------------------------|\n");
   
    // Заполнение таблицы
    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];

        // Массивы для сортировки
        int A[n];

        FillDec(n, A);
        C = 0; M = 0;
        QuickSort(0, n - 1, A);
        int dec = M + C;

        FillRand(n, A);
        C = 0; M = 0;
        QuickSort(0, n - 1, A);
        int rand = M + C;

        FillInc(n , A);
        C = 0; M = 0;
        QuickSort(0, n - 1, A);
        int inc = M + C;

        printf("| %4d | %11d | %11d | %11d |\n", 
            n, dec, rand, inc);
 }
 
 printf("---------------------------------------------------\n");

 return 0;

}