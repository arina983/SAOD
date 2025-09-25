#include <stdio.h>
#include <string.h>

int direct_comp = 0;
int rk_comp = 0;

// метод прямого поиска
void direct_search(char *T, int N, char *W, int M) {
    int found_count = 0; // Счетчик найденных вхождений
    for (int i = 0; i <= N - M; i++) {
        int match = 1;
        for (int j = 0; j < M; j++) {
            direct_comp++;
            if (T[i + j] != W[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            printf("Индекс вхождения: %d\n", i);
            found_count++;
        }
    }
    if (found_count > 0) {
        printf("Найдено вхождений: %d\n", found_count);
    } else {
        printf("Вхождений не найдено\n");
    }
    printf("Количество сравнений: %d\n", direct_comp);
    printf("----------------------------------------\n");
}

// вычислениe хеш-значения строки
unsigned long calculate_hash(char *str, int len, unsigned int a) {
    unsigned long h = 0;
    for (int i = 0; i < len; i++) {
        h = (h * 256 + (unsigned char)str[i]) % a;
    }
    return h;
}

// метод Рабина-Карпа
void RabinKarp(char *T, int N, char *W, int M, unsigned int a) {
    unsigned long hash_W = calculate_hash(W, M, a);
    int found_count = 0;
    for (int i = 0; i <= N - M; i++) {
        unsigned long hash_T = calculate_hash(T + i, M, a);
        if (hash_T == hash_W) {
            int match = 1;
            for (int j = 0; j < M; j++) {
                rk_comp++;
                if (T[i + j] != W[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("Вхождение найдено в позиции: %d\n", i);
                found_count++;
            }
        }
    }
    if (found_count > 0) {
        printf("Найдено вхождений: %d\n", found_count);
    } else {
        printf("Вхождений не найдено\n");
    }
    printf("Количество сравнений: %d\n", rk_comp);
    printf("----------------------------------------\n");
}

void compare_efficiency() {
    printf("Cравнениe эффективности методов\n");
    printf("_______________________________________________\n");
    printf("| Метод прямого поиска   |  Метод Рабина-Карпа |\n");
    printf("|______________________________________________|\n");
    printf("|     %d сравнений       |     %d сравнений     |\n",  direct_comp, rk_comp);
    printf("|______________________________________________|\n");
   
    
    if (direct_comp < rk_comp) {
        printf("Метод прямого поиска эффективнее на %d сравнений (%.1f%%)\n", 
               rk_comp - direct_comp,
               (float)(rk_comp - direct_comp) * 100 / rk_comp);
    } else if (rk_comp < direct_comp) {
        printf("Метод Рабина-Карпа эффективнее на %d сравнений (%.1f%%)\n", 
               direct_comp - rk_comp,
               (float)(direct_comp - rk_comp) * 100 / direct_comp);
    } else {
        printf("Оба метода имеют одинаковую эффективность\n");
    }
}

int main() {
    char T[1000] = "The rapid advancement of artificial intelligence and machine learning technologies is fundamentally transforming various sectors of the global raise significant ethical concerns and societal challenges. Issues such as data privacy, algorithmic bias, job displacement due to automation, and the potential for misuse of autonomous systems require careful consideration and proactive policymaking. The future will depend on our ability to harness these powerful technologies for the benefit of humanity while establishing robust frameworks to mitigate associated risks. International collaboration among governments, academic institutions, and private industry is crucial to ensure that the AI-driven future is equitable, sustainable, and aligned with human values. The pace of change is extraordinary, and adapting to this new paradigm will be one of the defining challenges of the 21st century." ;
    char W[200] = "The pace of change";
    unsigned int a = 101; 
    
    printf("ПОИСК ВСЕХ ПОДСТРОК МЕТОДОМ ПРЯМОГО ПОИСКА И РАБИНА-КАРПА\n\n");
    
    //printf("Введите текст T: ");
    //fgets(T, sizeof(T), stdin);
    //T[strcspn(T, "\n")] = '\0';
    int N = strlen(T);

    //printf("Введите образец W: ");
    //fgets(W, sizeof(W), stdin);
    //W[strcspn(W, "\n")] = '\0';
    int M = strlen(W);

    if (M == 0) {
        printf("Ошибка: образец W не может быть пустым\n");
        return 1;
    }
    
    if (M > N) {
        printf("Ошибка: образец W длиннее текста T\n");
        printf("Длина T: %d, длина W: %d\n", N, M);
        return 1;
    }
    
    printf("\nТекст: %s\n", T);
    printf("\nОбразец: %s\n\n", W);
    
    printf("МЕТОД ПРЯМОГО ПОИСКА \n");
    direct_search(T, N, W, M);
   
    printf("МЕТОД РАБИНА-КАРПА \n");
    RabinKarp(T, N, W, M, a);

    compare_efficiency();
    
    return 0;
}