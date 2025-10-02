#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <string.h>

#define NUM_RECORDS 4000
#define PAGE_SIZE 20

typedef struct {
    char author[12];
    char title[32];
    char publishing_house[16];
    short year;
    short number_of_pages;
} lives_people;

typedef struct {
    char author[60];
    char title[60];
    char publishing_house[60];
    short year;
    short number_of_pages;
} lives_people_big;

int convert_encoding(const char *from, const char *to, char *in_str, char *out_str, size_t out_size);

void print_table(int start, lives_people *array, int quantity) {
    printf("\n");
    printf("№   Автор                    Заглавие                 Издательство             Год        Страниц\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    
    for (int i = start; i < start + PAGE_SIZE && i < quantity; i++) {
        lives_people_big record_fix;
        convert_encoding("CP866", "UTF-8", array[i].author, record_fix.author, sizeof(record_fix.author));
        convert_encoding("CP866", "UTF-8", array[i].title, record_fix.title, sizeof(record_fix.title));
        convert_encoding("CP866", "UTF-8", array[i].publishing_house, record_fix.publishing_house, sizeof(record_fix.publishing_house));
        
        record_fix.year = array[i].year;
        record_fix.number_of_pages = array[i].number_of_pages;

        printf("%-3d %-27s %-35s %-25s %-10d %-9d\n", 
               i + 1,
               record_fix.author,
               record_fix.title,
               record_fix.publishing_house,
               record_fix.year,
               record_fix.number_of_pages);
    }
    printf("---------------------------------------------------------------------------------------------------\n");
}

int convert_encoding(const char *from, const char *to, char *in_str, char *out_str, size_t out_size) {
    iconv_t cd = iconv_open(to, from);
    if (cd == (iconv_t)-1) {
        return -1;
    }

    size_t in_len = strlen(in_str);
    size_t out_len = out_size - 1;
    char *in_buf = in_str;
    char *out_buf = out_str;

    if (iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == (size_t)-1) {
        iconv_close(cd);
        return -1;
    }

    *out_buf = '\0';
    iconv_close(cd);
    return 0;
}

int compare_records(const lives_people *a, const lives_people *b) {
    int pub_cmp = strcmp(a->publishing_house, b->publishing_house);
    if (pub_cmp != 0) {
        return pub_cmp;
    }
    return strcmp(a->author, b->author);
}

int Pyramid(int L, int R, lives_people A[]) {
    int S = 0;
    lives_people x = A[L];
    int i = L;
    while (1) {
        int j = 2 * i + 1;
        if (j > R) break;
        S++;
        if (j + 1 <= R && compare_records(&A[j + 1], &A[j]) > 0) j++;
        S++;
        if (compare_records(&x, &A[j]) >= 0) break;
        S++;
        A[i] = A[j];
        i = j;
    }
    S++;
    A[i] = x;
    return S;
}

int HeapSort(int n, lives_people A[]) {
    int S = 0;
    int L = n / 2 - 1;
    int R = n - 1;
    while (L >= 0) {
        S += Pyramid(L, R, A);
        L--;
    }

    while (R > 0) {
        S += 3;
        lives_people tmp = A[R];
        A[R] = A[0];
        A[0] = tmp;
        R--;
        S += Pyramid(0, R, A);
    }
    return S;
}

int binary_search(lives_people records[], int n, const char *publishing_house_prefix) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int pub_cmp = strncmp(records[mid].publishing_house, publishing_house_prefix, 3);
        
        if (pub_cmp == 0) {
            return mid;
        } else if (pub_cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void search_by_key_and_display_queue(lives_people records[], int n) {
    char publishing_house_prefix_utf8[10];
    
    printf("Введите первые три буквы издательства (на русском): ");
    fgets(publishing_house_prefix_utf8, sizeof(publishing_house_prefix_utf8), stdin);
    publishing_house_prefix_utf8[strcspn(publishing_house_prefix_utf8, "\n")] = 0;
    
    if (strlen(publishing_house_prefix_utf8) < 3) {
        printf("Ошибка: нужно ввести минимум три символа\n");
        return;
    }
    
    char publishing_house_prefix_cp866[10] = {0};
    if (convert_encoding("UTF-8", "CP866", publishing_house_prefix_utf8, publishing_house_prefix_cp866, sizeof(publishing_house_prefix_cp866)) == -1) {
        printf("Ошибка преобразования кодировки. Попробуйте ввести латинские символы.\n");
        strncpy(publishing_house_prefix_cp866, publishing_house_prefix_utf8, 3);
        publishing_house_prefix_cp866[3] = '\0';
    }
    
    printf("Поиск записей с издательствами, начинающимися на '%s':\n", publishing_house_prefix_utf8);
    
    int first_index = binary_search(records, n, publishing_house_prefix_cp866);
    
    if (first_index == -1) {
        printf("Записей с указанным префиксом издательства не найдено.\n");
        return;
    }
    
    int current = first_index;
    while (current >= 0 && strncmp(records[current].publishing_house, publishing_house_prefix_cp866, 3) == 0) {
        current--;
    }
    int start_index = current + 1;

    current = first_index;
    while (current < n && strncmp(records[current].publishing_house, publishing_house_prefix_cp866, 3) == 0) {
        current++;
    }
    int end_index = current - 1;

    int found = end_index - start_index + 1;
    
    printf("Найдено записей: %d\n", found);
    
    lives_people *sub_records = &records[start_index];
    int current_start = 0;
    int sorted = 1; 

    while (1) {
        print_table(current_start, sub_records, found);
        printf("Хотите продолжить просмотр?(y/n): ");
        char command[10];
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "n") == 0) {
            break;
        } else if (strcmp(command, "y") == 0) {
            if (current_start + PAGE_SIZE < found) {
                current_start += PAGE_SIZE;
            }
        } else {
            printf("Неверная команда\n");
        }
    }
}


int main() {
    const char *file_s = "/mnt/c/Users/Ариша/Downloads/testBase1.dat";

    FILE *file = fopen(file_s, "rb");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", file_s);
        return 1;
    }

    lives_people *records = (lives_people *)malloc(NUM_RECORDS * sizeof(lives_people));
    if (records == NULL) {
        printf("Ошибка: не удалось выделить память\n");
        fclose(file);
        return 1;
    }

    size_t records_read = fread(records, sizeof(lives_people), NUM_RECORDS, file);
    fclose(file);

    printf("Выберите действие:\n");
    printf("1 - Просмотр записей\n");
    printf("2 - Поиск по ключу с формированием очереди\n");
    printf("Ваш выбор: ");
    
    char main_choice;
    scanf(" %c", &main_choice);
    while (getchar() != '\n');

    if (main_choice == '1') {
        printf("Что вывести? (n - не отсортированные, s - отсортированные): ");
        char choice;
        scanf(" %c", &choice);
        while (getchar() != '\n');

        int sorted = 0;
        if (choice == 's') {
            printf("   ОТСОРТИРОВАННЫЕ ЗАПИСИ\n");
            HeapSort(records_read, records);
            sorted = 1;
        } else if (choice == 'n') {
            printf("  НЕОТСОРТИРОВАННЫЕ ЗАПИСИ \n");
        } else {
            printf("Неверный выбор\n");
            free(records);
            return 1;
        }

        lives_people *display_array = records;
        int display_quantity = records_read;
        int current_start = 0;

        while (1) {
            print_table(current_start, display_array, display_quantity);
            printf("Хотите продолжить просмотр? (y/n) ");
            char command[10];
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = '\0';

            if (strcmp(command, "n") == 0) {
                break;
            } else if (strcmp(command, "y") == 0) {
                if (current_start + PAGE_SIZE < display_quantity) {
                    current_start += PAGE_SIZE;
                }
            } else {
                printf("Неверная команда\n");
            }
        }
    }
    else if (main_choice == '2') {
        HeapSort(records_read, records);
        printf("Поиск по ключу с формированием очереди:\n");
        search_by_key_and_display_queue(records, records_read);
    }
    else {
        printf("Неверный выбор\n");
    }
    free(records);
    return 0;
}