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

typedef struct AVLNode {
    lives_people *record;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct {
    lives_people **records;  
    int size;               
    int capacity;         
} Queue;

AVLNode *avl_tree_from_queue = NULL;
lives_people *avl_records_storage = NULL;
int avl_records_count = 0;

int convert_encoding(const char *from, const char *to, char *in_str, char *out_str, size_t out_size);
void free_avl_tree(AVLNode *root);

Queue* create_queue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Ошибка выделения памяти для очереди\n");
        return NULL;
    }
    q->records = (lives_people**)malloc(capacity * sizeof(lives_people*));
    if (q->records == NULL) {
        printf("Ошибка выделения памяти для записей очереди\n");
        free(q);
        return NULL;
    }
    q->size = 0;
    q->capacity = capacity;
    return q;
}

void enqueue(Queue *q, lives_people *record) {
    if (q->size < q->capacity) {
        q->records[q->size] = record;
        q->size++;
    } else {
        printf(">>> Ошибка: очередь переполнена!\n");
    }
}

int queue_size(Queue *q) {
    return q->size;
}

void free_queue(Queue *q) {
    if (q != NULL) {
        free(q->records);
        free(q);
    }
}

static void count_nodes_helper(AVLNode *node, int *count) {
    if (node != NULL) {
        (*count)++;
        count_nodes_helper(node->left, count);
        count_nodes_helper(node->right, count);
    }
}

static void collect_nodes_inorder_helper(AVLNode *node, lives_people *records[], int *index, int max_count) {
    if (node != NULL && *index < max_count) {
        collect_nodes_inorder_helper(node->left, records, index, max_count);
        records[(*index)++] = node->record;
        collect_nodes_inorder_helper(node->right, records, index, max_count);
    }
}

static void search_by_year_helper(AVLNode *node, int year, lives_people *results[], int *count, int max_results) {
    if (node == NULL || *count >= max_results) return;
    
    search_by_year_helper(node->left, year, results, count, max_results);
    
    if (node->record->year == year && *count < max_results) {
        results[*count] = node->record;
        (*count)++;
    }
    
    search_by_year_helper(node->right, year, results, count, max_results);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int get_balance(AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode* create_avl_node(lives_people *record) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    if (node) {
        node->record = record;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
    }
    return node;
}

AVLNode* right_rotate(AVLNode *y) {
    if (y == NULL) return NULL;
    
    AVLNode *x = y->left;
    if (x == NULL) return y;
    
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* left_rotate(AVLNode *x) {
    if (x == NULL) return NULL;
    
    AVLNode *y = x->right;
    if (y == NULL) return x;
    
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insert_avl_node(AVLNode *node, lives_people *record) {
    if (node == NULL)
        return create_avl_node(record);

    if (record == NULL) return node;

    int cmp = record->year - node->record->year;
    
    if (cmp < 0)
        node->left = insert_avl_node(node->left, record);
    else 
        node->right = insert_avl_node(node->right, record);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && record->year < node->left->record->year)
        return right_rotate(node);

    if (balance < -1 && record->year > node->right->record->year)
        return left_rotate(node);

    if (balance > 1 && record->year > node->left->record->year) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && record->year < node->right->record->year) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void build_avl_tree_from_queue(Queue *q) {
    if (q == NULL || q->size == 0) {
        printf("Ошибка: очередь пуста для построения дерева\n");
        return;
    }

    free_avl_tree(avl_tree_from_queue);
    if (avl_records_storage != NULL) {
        free(avl_records_storage);
        avl_records_storage = NULL;
    }
    
    avl_tree_from_queue = NULL;
    avl_records_count = q->size;

    avl_records_storage = (lives_people*)malloc(avl_records_count * sizeof(lives_people));
    if (avl_records_storage == NULL) {
        printf("Ошибка выделения памяти для хранилища дерева\n");
        return;
    }
    
    for (int i = 0; i < q->size; i++) {
        if (q->records[i] != NULL) {
            memcpy(&avl_records_storage[i], q->records[i], sizeof(lives_people));
            avl_tree_from_queue = insert_avl_node(avl_tree_from_queue, &avl_records_storage[i]);
        }
    }
    
    printf(">>> АВЛ-ДЕРЕВО построено успешно! Записей: %d\n", avl_records_count);
    printf(">>> Ключ дерева: год издания\n");
}

int find_records_by_year(AVLNode *root, int year, lives_people *results[], int max_results) {
    int count = 0;
    search_by_year_helper(root, year, results, &count, max_results);
    return count;
}

void free_avl_tree(AVLNode *root) {
    if (root != NULL) {
        free_avl_tree(root->left);
        free_avl_tree(root->right);
        free(root);
    }
}

void print_records_table(lives_people *array, int quantity, int start, const char *title) {
    if (array == NULL || quantity <= 0) {
        printf("Нет данных для отображения\n");
        return;
    }
    
    if (title != NULL) {
        printf("\n%s\n", title);
    }
    printf("№   Автор                    Заглавие                Издательство        Год        Страниц\n");
    printf("------------------------------------------------------------------------------------------------\n");

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
    if (in_str == NULL || out_str == NULL) {
        return -1;
    }
    
    iconv_t cd = iconv_open(to, from);
    if (cd == (iconv_t)-1) {
        strncpy(out_str, in_str, out_size - 1);
        out_str[out_size - 1] = '\0';
        return -1;
    }

    size_t in_len = strlen(in_str);
    size_t out_len = out_size - 1;
    char *in_buf = in_str;
    char *out_buf = out_str;

    if (iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == (size_t)-1) {
        iconv_close(cd);
        strncpy(out_str, in_str, out_size - 1);
        out_str[out_size - 1] = '\0';
        return -1;
    }

    *out_buf = '\0';
    iconv_close(cd);
    return 0;
}

int compare_records(const lives_people *a, const lives_people *b) {
    if (a == NULL || b == NULL) return 0;
    
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
    if (records == NULL || n <= 0) return -1;
    
    int left = 0;
    int right = n - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        int pub_cmp = strncmp(records[mid].publishing_house, publishing_house_prefix, 3);
        
        if (pub_cmp < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    if (strncmp(records[right].publishing_house, publishing_house_prefix, 3) == 0) {
        return right;
    } else {
        return -1;
    }
}

void search_by_key_and_display_queue(lives_people records[], int n) {
    char publishing_house_prefix_utf8[10];
    
    printf("Введите первые три буквы издательства (на русском): ");
    if (fgets(publishing_house_prefix_utf8, sizeof(publishing_house_prefix_utf8), stdin) == NULL) {
        printf("Ошибка ввода\n");
        return;
    }
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

    Queue *found_queue = create_queue(found);
    if (found_queue == NULL) {
        printf("Ошибка создания очереди\n");
        return;
    }

    for (int i = 0; i < found; i++) {
        enqueue(found_queue, &records[start_index + i]);
    }

    build_avl_tree_from_queue(found_queue);

    lives_people *sub_records = &records[start_index];
    int current_start = 0;

    while (1) {
        print_records_table(sub_records, found, current_start, "СОДЕРЖИМОЕ ОЧЕРЕДИ:");
        printf("Хотите продолжить просмотр?(y/n): ");
        char command[10];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "n") == 0) {
            break;
        } else if (strcmp(command, "y") == 0) {
            if (current_start + PAGE_SIZE < found) {
                current_start += PAGE_SIZE;
            } else {
                printf("Достигнут конец списка.\n");
                break;
            }
        } else {
            printf("Неверная команда\n");
        }
    }
    free_queue(found_queue);
}

void print_avl_tree_paged(AVLNode *root) {
    if (root == NULL) {
        printf("Дерево пустое.\n");
        return;
    }
    
    int total_count = 0;
    count_nodes_helper(root, &total_count);
    
    printf("Всего записей в дереве: %d\n", total_count);
    
    if (total_count == 0) {
        printf("Нет записей для отображения\n");
        return;
    }
    
    lives_people **all_records = (lives_people**)malloc(total_count * sizeof(lives_people*));
    if (all_records == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    
    int index = 0;
    collect_nodes_inorder_helper(root, all_records, &index, total_count);
    
    lives_people *temp_array = (lives_people*)malloc(total_count * sizeof(lives_people));
    if (temp_array == NULL) {
        printf("Ошибка выделения памяти\n");
        free(all_records);
        return;
    }
    
    for (int i = 0; i < total_count; i++) {
        memcpy(&temp_array[i], all_records[i], sizeof(lives_people));
    }
    
    int current_start = 0;
    while (current_start < total_count) {
        printf("\nСОДЕРЖИМОЕ АВЛ-ДЕРЕВА:\n");
        print_records_table(temp_array, total_count, current_start, NULL);
        printf("Записи %d-%d из %d\n", current_start + 1, 
               (current_start + PAGE_SIZE < total_count) ? current_start + PAGE_SIZE : total_count, 
               total_count);
        
        if (current_start + PAGE_SIZE < total_count) {
            printf("Хотите продолжить просмотр? (y/n): ");
            char command[10];
            if (fgets(command, sizeof(command), stdin) == NULL) {
                break;
            }
            command[strcspn(command, "\n")] = '\0';
            
            if (strcmp(command, "n") == 0) {
                break;
            } else if (strcmp(command, "y") == 0) {
                current_start += PAGE_SIZE;
            } else {
                printf("Неверная команда, продолжаем вывод...\n");
                current_start += PAGE_SIZE;
            }
        } else {
            break;
        }
    }
    
    free(all_records);
    free(temp_array);
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

    printf("Загружено записей: %zu\n", records_read);

    while (1) {
        printf("\nВыберите действие:\n");
        printf("1 - Просмотр записей \n");
        printf("2 - Поиск по ключу с формированием очереди и построение дерева\n");
        printf("3 - Работа с АВЛ-деревом \n");
        printf("4 - Выход\n");
        printf("Ваш выбор: ");
        
        char main_choice;
        if (scanf(" %c", &main_choice) != 1) {
            printf("Ошибка ввода\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (main_choice == '1') {
            printf("Что вывести? (n - не отсортированные, s - отсортированные): ");
            char choice;
            if (scanf(" %c", &choice) != 1) {
                printf("Ошибка ввода\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            if (choice == 's') {
                printf("   ОТСОРТИРОВАННЫЕ ЗАПИСИ\n");
                HeapSort(records_read, records);
            } else if (choice == 'n') {
                printf("  НЕОТСОРТИРОВАННЫЕ ЗАПИСИ \n");
            } else {
                printf("Неверный выбор\n");
                continue;
            }

            int current_start = 0;

            while (1) {
                print_records_table(records, records_read, current_start, NULL);
                printf("Хотите продолжить просмотр? (y/n) ");
                char command[10];
                if (fgets(command, sizeof(command), stdin) == NULL) {
                    break;
                }
                command[strcspn(command, "\n")] = '\0';

                if (strcmp(command, "n") == 0) {
                    break;
                } else if (strcmp(command, "y") == 0) {
                    if (current_start + PAGE_SIZE < records_read) {
                        current_start += PAGE_SIZE;
                    } else {
                        printf("Достигнут конец списка.\n");
                        break;
                    }
                } else {
                    printf("Неверная команда\n");
                }
            }
        }
        else if (main_choice == '2') {
            HeapSort(records_read, records);
            printf("Поиск по ключу с формированием очереди и построение дерева:\n");
            search_by_key_and_display_queue(records, records_read);
        }
        else if (main_choice == '3') {
            if (avl_tree_from_queue == NULL) {
                printf("АВЛ-дерево еще не построено! Сначала выполните поиск по ключу (пункт 2).\n");
                continue;
            }
        
            printf("\nРАБОТА С АВЛ-ДЕРЕВОМ \n");
            printf("1 - Вывод всего дерева\n");
            printf("2 - Поиск по году издания\n");
            printf("Ваш выбор: ");
        
            char tree_choice;
            if (scanf(" %c", &tree_choice) != 1) {
                printf("Ошибка ввода\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
        
            if (tree_choice == '1') {
                print_avl_tree_paged(avl_tree_from_queue);
            }
            else if (tree_choice == '2') {
                int search_year;
                printf("Введите год издания для поиска: ");
                if (scanf("%d", &search_year) != 1) {
                    printf("Ошибка ввода\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
            
                lives_people *found_records[1000];
                int found_count = find_records_by_year(avl_tree_from_queue, search_year, found_records, 1000);
    
                if (found_count > 0) {
                    printf("Найдено записей с годом издания %d: %d\n", search_year, found_count);
                
                    lives_people *temp_array = (lives_people*)malloc(found_count * sizeof(lives_people));
                    if (temp_array != NULL) {
                        for (int i = 0; i < found_count; i++) {
                            memcpy(&temp_array[i], found_records[i], sizeof(lives_people));
                        }
                        print_records_table(temp_array, found_count, 0, "РЕЗУЛЬТАТЫ ПОИСКА В АВЛ-ДЕРЕВЕ:");
                        free(temp_array);
                    }
                } else {
                    printf("Записи с годом издания %d не найдены в дереве.\n", search_year);
                }
            }
            else {
                printf("Неверный выбор\n");
            }
        }
        else if (main_choice == '4') {
            break;
        }
        else {
            printf("Неверный выбор\n");
        }
    }

    free_avl_tree(avl_tree_from_queue);
    if (avl_records_storage != NULL) {
        free(avl_records_storage);
    }
    free(records);
    printf("Программа завершена.\n");
    return 0;
}