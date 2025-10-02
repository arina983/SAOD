#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

struct vertex {
    int data;         
    struct vertex *left;
    struct vertex *right;
};

typedef struct vertex Node;

// Функция вставки в BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Функция для перемешивания массива
void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Функция удаления по данным
Node* deleteByData(Node* root, int data) {
    Node** p = &root;
    
    // Поиск элемента по данным
    while (*p != NULL) {
        if (data < (*p)->data) {
            p = &((*p)->left);
        } else if (data > (*p)->data) {
            p = &((*p)->right);
        } else {
            break; // данные найдены
        }
    }
    
    // Если элемент найден
    if (*p != NULL) {
        Node* q = *p;
        Node* r;
        Node* s;
        
        if (q->left == NULL) {
            *p = q->right;
        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            // 2 поддерева
            r = q->left;
            s = q;
            
            if (r->right == NULL) {
                r->right = q->right;
                *p = r;
            } else {
                // Поиск самого правого элемента в левом поддереве
                while (r->right != NULL) {
                    s = r;
                    r = r->right;
                }
                
                s->right = r->left;
                r->left = q->left;
                r->right = q->right;
                *p = r;
            }
        }
        printf("Удалена вершина с данными %d\n", q->data);
        free(q);
    }
    
    return root;
}

// Обход дерева слева направо (симметричный обход)
void left_right(Node *p) {
    if (p != NULL) {
        left_right(p->left);
        printf("%d ", p->data);
        left_right(p->right);
    }
}

// Функция для поиска элемента по данным
int searchByData(Node* root, int data) {
    if (root == NULL) {
        return 0;
    }
    
    if (data < root->data) {
        return searchByData(root->left, data);
    } else if (data > root->data) {
        return searchByData(root->right, data);
    } else {
        return 1; // элемент найден
    }
}

// Функция для освобождения памяти
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void preorder(Node* root) { // Обход сверху вниз
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int size = 15;
    int arr[15];

    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    srand(time(NULL));

    shuffle(arr, size);
    
    Node* root = NULL;
    
    // Строим случайное BST путём вставки в случайном порядке
    for (int i = 0; i < size; i++) {
        root = insert(root, arr[i]);
    }
    
    printf("Случайное дерево поиска:\n");
    printf("Обход слева направо: ");
    left_right(root);
    printf("\nОбход сверху вниз: ");
    preorder(root);
    printf("\n");


    printf("\nУдаление вершин по данным:\n");
    
    for (int i = 1; i <= 10; i++) {
        int data;
        printf("\nШаг %d: Введите данные для удаления: ", i);
        scanf("%d", &data);
        
        if (!searchByData(root, data)) {
            printf("Элемент с данными %d не найден в дереве!\n", data);
            i--; // не засчитываем эту попытку
            continue;
        }
        
        printf("Удаляем элемент с данными %d\n", data);
        root = deleteByData(root, data);
        
        printf("Дерево после удаления:\n");
        printf("Обход слева направо: ");
        left_right(root);
        printf("\nОбход сверху вниз: ");
        preorder(root);
        printf("\n");
    }
    
    printf("Программа завершена. Оставшееся дерево:\n");
    printf("Обход слева направо: ");
    left_right(root);
    printf("\nОбход сверху вниз: ");
    preorder(root);
    printf("\n");
    
    freeTree(root);
    return 0;
}
