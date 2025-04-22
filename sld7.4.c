#include <stdio.h>
#include <string.h>

struct Contact {
    char name[50];
    char lastname[50];
    int age;
    int number;
};

int sortKey = 1;  
int ascending = 1; 

// Функция сравнения для сортировки
int less(struct Contact a, struct Contact b) {
    int result = 0;

    if (sortKey == 1) { 
        result = strcmp(a.lastname, b.lastname);
        if (result == 0) {
            result = strcmp(a.name, b.name);
        }
    } else if (sortKey == 2) { 
        result = a.age - b.age;
        if (result == 0) {
            result = a.number - b.number;
        }
    }

    return ascending ? result : -result;
}

// Функция сравнения только по старшему ключу для поиска
int compareKey(struct Contact a, struct Contact b) {
    if (sortKey == 1) {
        return strcmp(a.lastname, b.lastname);
    } else {
        return a.age - b.age;
    }
}

void InsertSort(struct Contact contacts[], int size) {
    for (int i = 1; i < size; i++) {
        struct Contact temp = contacts[i];
        int j = i - 1;

        while (j >= 0 && less(contacts[j], temp) > 0) {
            contacts[j + 1] = contacts[j];
            j--;
        }

        contacts[j + 1] = temp;
    }
}

// Бинарный поиск по старшему ключу
int binarySearch(struct Contact contacts[], int size, struct Contact key) {
    int left = 0;
    int right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compareKey(contacts[mid], key);

        if (cmp == 0) {
            result = mid;
            if (ascending) {
                right = mid - 1; // Ищем первое вхождение
            } else {
                left = mid + 1; // Для убывающего порядка
            }
        } else if ((ascending && cmp < 0) || (!ascending && cmp > 0)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Вывод всех записей с найденным ключом
void printSearchResults(struct Contact contacts[], int size, int firstIndex, struct Contact key) {
    if (firstIndex == -1) {
        printf("Запись не найдена.\n");
        return;
    }

    printf("Найденные записи:\n");
    
    // Для возрастающего порядка
    if (ascending) {
        for (int i = firstIndex; i < size && compareKey(contacts[i], key) == 0; i++) {
            printf("%s %s, Возраст: %d, Номер: %d\n", 
                   contacts[i].lastname, contacts[i].name, contacts[i].age, contacts[i].number);
        }
    } 
    // Для убывающего порядка
    else {
        for (int i = firstIndex; i >= 0 && compareKey(contacts[i], key) == 0; i--) {
            printf("%s %s, Возраст: %d, Номер: %d\n", 
                   contacts[i].lastname, contacts[i].name, contacts[i].age, contacts[i].number);
        }
    }
}

void printContacts(struct Contact contacts[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s %s, Возраст: %d, Номер: %d\n", 
               contacts[i].lastname, contacts[i].name, contacts[i].age, contacts[i].number);
    }
    printf("\n");
}

int main() {
    struct Contact contacts[] = {
        {"Валерия", "Попова", 20, 234213},
        {"Софья", "Штейнбрехер", 31, 123513},
        {"Анна", "Попова", 27, 763421},
        {"Арина", "Бубенина", 18, 545635},
    };

    int size = sizeof(contacts) / sizeof(contacts[0]);

    printf("Исходный справочник:\n");
    printContacts(contacts, size);

    printf("Выберите ключ сортировки (1 - 'Фамилия + Имя', 2 - 'Возраст + Номер'): ");
    scanf("%d", &sortKey);

    printf("Выберите направление сортировки (1 - по возрастанию, 2 - по убыванию): ");
    scanf("%d", &ascending);
    ascending = (ascending == 1);

    InsertSort(contacts, size);

    printf("\nОтсортированный справочник:\n");
    printContacts(contacts, size);

    // Поиск по старшему ключу
    struct Contact searchKey = {"", "", 0, 0};
    
    if (sortKey == 1) {
        printf("Введите фамилию для поиска: ");
        scanf("%s", searchKey.lastname);
    } else {
        printf("Введите возраст для поиска: ");
        scanf("%d", &searchKey.age);
    }

    int firstIndex = binarySearch(contacts, size, searchKey);
    printSearchResults(contacts, size, firstIndex, searchKey);

    return 0;
}