#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

/* == РЕАЛИЗАЦИЯ СТЕКА == */

typedef struct {
    int data[MAX_SIZE];
    int top; //индекс вершины стека
} Stack;

// Инициализация стека
void initStack(Stack *s) {
    s->top = -1; // При инициализации стек пуст
}

// Проверка на пустоту
int isStackEmpty(Stack *s) {
    return s->top == -1;
}

// Проверка на полноту
int isStackFull(Stack *s) {
    return s->top == MAX_SIZE - 1; // Стек полон, когда top достигает последнего индекса массива
}

// Добавление элемента в стек
void push(Stack *s, int value) {
    if (isStackFull(s)) {
        printf("Ошибка: стек переполнен\n");
        return;
    }
    s->data[++s->top] = value; // Увеличиваем top и добавляем элемент
}

// Извлечение элемента из стека
int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Ошибка: стек пуст\n");
        return -1;
    }
    return s->data[s->top--]; // Возвращаем элемент и уменьшаем top
}

// 1.1 Заполнение стека возрастающими числами
void fillStackAscending(Stack *s, int start, int end) {
    for (int i = start; i <= end; i++) {
        push(s, i);
    }
}

// 1.2 Заполнение стека убывающими числами
void fillStackDescending(Stack *s, int start, int end) {
    for (int i = end; i >= start; i--) {
        push(s, i);
    }
}

// 1.3 Заполнение стека случайными числами
void fillStackRandom(Stack *s, int count, int min, int max) {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < count; i++) {
        int num = min + rand() % (max - min + 1);
        push(s, num);
    }
}

// Печать содержимого стека
void printStack(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Стек пуст\n");
        return;
    }
    
    printf("Содержимое стека (вершина сверху):\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}
// Подсчет контрольной суммы элементов стека
int calculateStackChecksum(Stack *s) {
    int sum = 0;
    for (int i = 0; i <= s->top; i++) {
        sum += s->data[i];
    }
    return sum;
}

// Подсчет количества серий в стеке
int countStackSeries(Stack *s) {
    if (isStackEmpty(s)) return 0;
    
    int count = 1; // Минимум одна серия
    
    for (int i = 0; i < s->top; i++) {
        if (s->data[i] != s->data[i+1]) {
            count++;
        }
    }
    
    return count;
}

/* == РЕАЛИЗАЦИЯ ОЧЕРЕДИ == */

typedef struct {
    int data[MAX_SIZE]; // Массив для хранения элементов
    int front, rear; // Индексы начала и конца очереди
} Queue;

// Инициализация очереди
void initQueue(Queue *q) {
    q->front = q->rear = -1; // Очередь пуста
}

// Проверка на пустоту
int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

// Проверка на полноту
int isQueueFull(Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front; // Очередь полна, когда следующий за rear индекс равен front
}

// Добавление элемента в очередь
void enqueue(Queue *q, int value) {
    if (isQueueFull(q)) {
        printf("Ошибка: очередь переполнена\n");
        return;
    }
    
    if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    
    q->data[q->rear] = value;
}

// Извлечение элемента из очереди
int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Ошибка: очередь пуста\n");
        return -1;
    }
    
    int value = q->data[q->front];
    
    if (q->front == q->rear) {
        // Очередь станет пустой после извлечения
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    
    return value;
}

// 2.1 Заполнение очереди возрастающими числами
void fillQueueAscending(Queue *q, int start, int end) {
    for (int i = start; i <= end; i++) {
        enqueue(q, i);
    }
}

// 2.2 Заполнение очереди убывающими числами
void fillQueueDescending(Queue *q, int start, int end) {
    for (int i = end; i >= start; i--) {
        enqueue(q, i);
    }
}

// 2.3 Заполнение очереди случайными числами
void fillQueueRandom(Queue *q, int count, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int num = min + rand() % (max - min + 1);
        enqueue(q, num);
    }
}

// Печать содержимого очереди
void printQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Очередь пуста\n");
        return;
    }
    
    printf("Содержимое очереди (начало слева):\n");
    int i = q->front;
    while (1) {
        printf("%d ", q->data[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}
// Подсчет контрольной суммы элементов очереди
int calculateQueueChecksum(Queue *q) {
    if (isQueueEmpty(q)) return 0;
    
    int sum = 0;
    int i = q->front;
    while (1) {
        sum += q->data[i];
        if (i == q->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    return sum;
}

// Подсчет количества серий в очереди
int countQueueSeries(Queue *q) {
    if (isQueueEmpty(q)) return 0;
    
    int count = 1; // Минимум одна серия
    int i = q->front;
    
    while (i != q->rear) {
        int next = (i + 1) % MAX_SIZE;
        if (q->data[i] != q->data[next]) {
            count++;
        }
        i = next;
    }
    
    return count;
}

/* == РЕАЛИЗАЦИЯ СПИСКА == */

typedef struct Node {
    int data; // Значение узла
    struct Node *next;// Указатель на следующий узел
} Node;

// Создание нового узла списка
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// 3.1 Печать элементов списка
void printList(Node *head) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    
    printf("Содержимое списка:\n");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// 3.2 Подсчет контрольной суммы элементов списка
int calculateChecksum(Node *head) {
    int sum = 0;
    while (head != NULL) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

// 3.3 Подсчет количества серий в списке
int countSeries(Node *head) {
    if (head == NULL) return 0;
    
    int count = 1; // Минимум одна серия
    
    while (head->next != NULL) {
        if (head->data != head->next->data) {
            count++;
        }
        head = head->next;
    }
    
    return count;
}

// 4. Удаление всех элементов списка
void deleteList(Node **head) {
    Node *current = *head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL; // обнуляем указатель
}

/* == ГЛАВНАЯ ФУНКЦИЯ == */

int main() {
    printf("=== Демонстрация работы стека ===\n");
    Stack myStack;
    initStack(&myStack);
    
    printf("\n1. Заполнение стека возрастающими числами от 1 до 10:\n");
    fillStackAscending(&myStack, 1, 10);
    printStack(&myStack);
    printf("Контрольная сумма: %d\n", calculateStackChecksum(&myStack));
    printf("Количество серий: %d\n", countStackSeries(&myStack));
    
    printf("\n2. Заполнение стека убывающими числами от 10 до 1:\n");
    initStack(&myStack); // Очищаем стек
    fillStackDescending(&myStack, 1, 10);
    printStack(&myStack);
    printf("Контрольная сумма: %d\n", calculateStackChecksum(&myStack));
    printf("Количество серий: %d\n", countStackSeries(&myStack));
    
    printf("\n3. Заполнение стека 5 случайными числами от 10 до 20:\n");
    initStack(&myStack);
    fillStackRandom(&myStack, 5, 10, 20);
    printStack(&myStack);
    printf("Контрольная сумма: %d\n", calculateStackChecksum(&myStack));
    printf("Количество серий: %d\n", countStackSeries(&myStack));
    
    printf("\n=== Демонстрация работы очереди ===\n");
    Queue myQueue;
    initQueue(&myQueue);
    
    printf("\n1. Заполнение очереди возрастающими числами от 1 до 10:\n");
    fillQueueAscending(&myQueue, 1, 10);
    printQueue(&myQueue);
    printf("Контрольная сумма: %d\n", calculateQueueChecksum(&myQueue));
    printf("Количество серий: %d\n", countQueueSeries(&myQueue));
    
    printf("\n2. Заполнение очереди убывающими числами от 10 до 1:\n");
    initQueue(&myQueue);
    fillQueueDescending(&myQueue, 1, 10);
    printQueue(&myQueue);
    printf("Контрольная сумма: %d\n", calculateQueueChecksum(&myQueue));
    printf("Количество серий: %d\n", countQueueSeries(&myQueue));
    
    printf("\n3. Заполнение очереди 5 случайными числами от 10 до 20:\n");
    initQueue(&myQueue);
    fillQueueRandom(&myQueue, 5, 10, 20);
    printQueue(&myQueue);
    printf("Контрольная сумма: %d\n", calculateQueueChecksum(&myQueue));
    printf("Количество серий: %d\n", countQueueSeries(&myQueue));
    
    printf("\n=== Демонстрация работы списка ===\n");
    Node *myList = NULL;
    
    // Создаем список:
    myList = createNode(1);
    myList->next = createNode(2);
    myList->next->next = createNode(5);
    myList->next->next->next = createNode(7);
    myList->next->next->next->next = createNode(2);
    myList->next->next->next->next->next = createNode(3);
    
    printf("\n1. Печать списка:\n");
    printList(myList);
    
    printf("\n2. Контрольная сумма элементов списка: %d\n", 
           calculateChecksum(myList));
    
    printf("\n3. Количество серий в списке: %d\n", 
           countSeries(myList));
    
    printf("\n4. Удаление списка...\n");
    deleteList(&myList);
    printList(myList);
    
    return 0;
}