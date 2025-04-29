#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// // === Генерация случайных символов (A-Z) ===
// void FillRandomLetters(char A[], int n) {
//     for (int i = 0; i < n; i++) {
//         A[i] = rand() % 26 + 'A';
//     }
// }

void FillRandomLetters(char* buffer, size_t size) {
    const char charset[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. 1234567890!@#$%^&*()_+-=[]{}|;\':\",./<>?~ Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. 1234567890!@#$%^&*()_+-=[]{}|;\':\",./<>?~ Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. 1234567890!@#$%^&*()_+-=[]{}|;\':\",./<>?~ Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. 1234567890!@#$%^&*()_+-=[]{}|;\':\",./<>?~";
    for (size_t i = 0; i < size - 1; i++) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buffer[size - 1] = '\0';
}

// === Линейное пробирование ===
int linear_probing_chars(char A[], char table[], int n, int m) {
    int collisions = 0;
    for (int i = 0; i < n; i++) {
        int h = A[i] % m;
        int j = 0;
        while (j < m) {
            int idx = (h + j) % m;
            if (table[idx] == 0) {
                table[idx] = A[i];
                break;
            }
            collisions++;
            j++;
        }
    }
    return collisions;
}

// === Квадратичное пробирование ===
int quadratic_probing_chars(char A[], char table[], int n, int m) {
    int collisions = 0;
    for (int i = 0; i < n; i++) {
        int h = A[i] % m;
        int j = 1;
        int attempt = 0;
        while (attempt < m) {
            if (table[h] == 0) {
                table[h] = A[i];
                break;
            }
            collisions++;
            h = (h + j * j) % m;
            j++;
            attempt++;
        }
    }
    return collisions;
}

// === Красивая печать таблицы символов ===
void PrintSymbolTableFormatted(const char table[], int size, const string& title) {
    cout << "\n" << title << ":\n";
    const int cols = 10;

    for (int row = 0; row < (size + cols - 1) / cols; row++) {
        int start = row * cols;
        int end = min(start + cols, size);
        // Индексы
        cout << "Индексы: ";
        for (int i = start; i < end; i++) {
            cout << setw(4) << i;
        }
        cout << "\nСимволы: ";
        for (int i = start; i < end; i++) {
            if (table[i] == 0)
                cout << setw(4) << '.';
            else
                cout << setw(4) << table[i];
        }
        cout << "\n";
    }
    cout << "\n";
}

// === ЗАДАНИЕ 2 ===
void task2() {
    const int n = 1024; // 1 КБ
    const int m = 101;  // 101 ячейка в хеш-таблицах
    char A[n];
    char linear_table[m] = {0};
    char quadratic_table[m] = {0};

    srand(time(NULL));
    FillRandomLetters(A, n);

    cout << "======== ЗАДАНИЕ 2. ХЕШИРОВАНИЕ СИМВОЛОВ (m = " << m << ") ========\n";
    cout << "Текст на 1КБ (первые 100 символов):\n";
    for (int i = 0; i < 100; i++) cout << A[i] << " ";
    cout << "\n";

    int linear_coll = linear_probing_chars(A, linear_table, n, m);
    int quad_coll = quadratic_probing_chars(A, quadratic_table, n, m);

    PrintSymbolTableFormatted(linear_table, m, "Хеш-таблица (линейные пробы)");
    PrintSymbolTableFormatted(quadratic_table, m, "Хеш-таблица (квадратичные пробы)");

    cout << "Количество коллизий:\n";
    cout << " - Линейные пробы:      " << linear_coll << "\n";
    cout << " - Квадратичные пробы:  " << quad_coll << "\n";
    cout << "==============================================================\n\n";
}

// === ЗАДАНИЕ 3 ===
void task3() {
    vector<int> table_sizes = {11, 13, 17, 19, 23, 29, 31, 37, 41, 101};
    const int n = 100;

    cout << "======== ЗАДАНИЕ 3. СРАВНЕНИЕ КОЛЛИЗИЙ (n = " << n << ") ========\n";
    cout << "┌────────────────┬───────────┬────────────┬────────────────┐\n";
    cout << "│ Размер таблицы │ Элементов │ Линейные   │ Квадратичные   │\n";
    cout << "│       (m)      │   (n)     │ коллизии   │   коллизии     │\n";
    cout << "├────────────────┼───────────┼────────────┼────────────────┤\n";

    for (int m : table_sizes) {
        char A[n];
        char linear_table[m];
        char quadratic_table[m];
        fill_n(linear_table, m, 0);
        fill_n(quadratic_table, m, 0);
        FillRandomLetters(A, n);

        int linear_coll = linear_probing_chars(A, linear_table, n, m);
        int quad_coll = quadratic_probing_chars(A, quadratic_table, n, m);


        cout << "│ " << setw(14) << m << " │ " << setw(9) << n
             << " │ " << setw(10) << linear_coll
             << " │ " << setw(14) << quad_coll << " │\n";
    }

    cout << "└────────────────┴───────────┴────────────┴────────────────┘\n\n";
}

// === MAIN ===
int main() {
    task2();
    task3();
    return 0;
}