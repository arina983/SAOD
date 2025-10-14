#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct vertex {
    int data;            
    struct vertex *left;
    struct vertex *right;
    int Bal;  // Баланс вершины (-1, 0, 1)
};

typedef struct vertex Node;

// Функция для перемешивания массива
void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Функции для характеристик дерева
int tree_size(Node *p) {
    if (p == NULL) {
        return 0;
    } else {
        return 1 + tree_size(p->left) + tree_size(p->right);
    }
}

int tree_sum(Node *p) {
    if (p == NULL) {
        return 0;
    } else {
        return p->data + tree_sum(p->left) + tree_sum(p->right);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int tree_height(Node *p) {
    if (p == NULL) {
        return 0;
    } else {
        return 1 + max(tree_height(p->left), tree_height(p->right));
    }
}

int sum_path_lengths(Node *p, int l) {
    if (p == NULL) {
        return 0;
    } else {
        return l + sum_path_lengths(p->left, l + 1) + sum_path_lengths(p->right, l + 1);
    }
}

float average_height(Node *p) {
    if (p == NULL) {
        return 0.0;
    }
    int total_path_length = sum_path_lengths(p, 1);
    int size = tree_size(p);
    return (float)total_path_length / size;
}

// Обход слева направо 
void left_right(Node *p) {
    if (p != NULL) {
        left_right(p->left);
        printf("%d ", p->data);  
        left_right(p->right);
    }
}

void free_tree(Node *p) {
    if (p != NULL) {
        free_tree(p->left);
        free_tree(p->right);
        free(p);
    }
}

// Функции поворотов для АВЛ-дерева
void LL_rotate(Node **p) {
    Node *q = (*p)->left;
    (*p)->left = q->right;
    q->right = *p;
    (*p)->Bal = 0;
    q->Bal = 0;
    *p = q;
}

void RR_rotate(Node **p) {
    Node *q = (*p)->right;
    (*p)->right = q->left;
    q->left = *p;
    (*p)->Bal = 0;
    q->Bal = 0;
    *p = q;
}

void LR_rotate(Node **p) {
    Node *q = (*p)->left;
    Node *r = q->right;
    
    if (r->Bal < 0) {
        (*p)->Bal = 1;
    } else {
        (*p)->Bal = 0;
    }
    
    if (r->Bal > 0) {
        q->Bal = -1;
    } else {
        q->Bal = 0;
    }
    
    q->right = r->left;
    (*p)->left = r->right;
    r->left = q;
    r->right = *p;
    r->Bal = 0;
    *p = r;
}

void RL_rotate(Node **p) {
    Node *q = (*p)->right;
    Node *r = q->left;
    
    if (r->Bal > 0) {
        (*p)->Bal = -1;
    } else {
        (*p)->Bal = 0;
    }
    
    if (r->Bal < 0) {
        q->Bal = 1;
    } else {
        q->Bal = 0;
    }
    
    q->left = r->right;
    (*p)->right = r->left;
    r->right = q;
    r->left = *p;
    r->Bal = 0;
    *p = r;
}

// Основная функция добавления в АВЛ-дерево
void add_AVL(int D, Node **p, bool *Rost) {
    if (*p == NULL) {
        *p = (Node*)malloc(sizeof(Node));
        (*p)->data = D;
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->Bal = 0;
        *Rost = true;
    }
    else if ((*p)->data > D) {
        add_AVL(D, &((*p)->left), Rost);
        
        if (*Rost) {
            if ((*p)->Bal > 0) {
                (*p)->Bal = 0;
                *Rost = false;
            }
            else if ((*p)->Bal == 0) {
                (*p)->Bal = -1;
            }
            else {
                if ((*p)->left->Bal < 0) {
                    LL_rotate(p);
                    *Rost = false;
                }
                else {
                    LR_rotate(p);
                    *Rost = false;
                }
            }
        }
    }
    else if ((*p)->data < D) {
        add_AVL(D, &((*p)->right), Rost);
        
        if (*Rost) {
            if ((*p)->Bal < 0) {
                (*p)->Bal = 0;
                *Rost = false;
            }
            else if ((*p)->Bal == 0) {
                (*p)->Bal = 1;
            }
            else {
                if ((*p)->right->Bal > 0) {
                    RR_rotate(p);
                   *Rost = false;
                }
                else {
                    RL_rotate(p);
                    *Rost = false;
                }
            }
        }
    }
    else {
        // Вершина уже существует в дереве
        *Rost = false;
    }
}

// Функция для добавления в обычное BST
void add_BST(int D, Node **p) {
    if (*p == NULL) {
        *p = (Node*)malloc(sizeof(Node));
        (*p)->data = D;
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->Bal = 0;
    }
    else if ((*p)->data > D) {
        add_BST(D, &((*p)->left));
    }
    else if ((*p)->data < D) {
        add_BST(D, &((*p)->right));
    }
}

// Функция для создания идеально сбалансированного дерева поиска
Node* create_balanced_tree(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    int mid = (start + end) / 2;
    Node *root = (Node*)malloc(sizeof(Node));
    root->data = arr[mid];
    root->left = create_balanced_tree(arr, start, mid - 1);
    root->right = create_balanced_tree(arr, mid + 1, end);
    root->Bal = 0;

    return root;
}

int main() {
    Node *avl_tree = NULL;
    Node *bst_tree = NULL;
    Node *balanced_tree = NULL;

    int n = 100;  
    int arr[100];

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Перемешиваем массив для случайного порядка
    srand(time(NULL));
    shuffle(arr, n);

    // Построение АВЛ-дерева
    for (int i = 0; i < n; i++) {
        bool Rost = false;
        add_AVL(arr[i], &avl_tree, &Rost);
    }

    // Построение обычного BST
    for (int i = 0; i < n; i++) {
        add_BST(arr[i], &bst_tree);
    }
    
    // Сортировка массива для построения ИСДП
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    balanced_tree = create_balanced_tree(arr, 0, n - 1);
    
    // Вывод обхода АВЛ-дерева
    printf("АВЛ дерево:\n");
    printf("Обход слева направо: ");
    left_right(avl_tree);
    printf("\n");

    // Вычисление характеристик для всех деревьев
    int avl_size = tree_size(avl_tree);
    int avl_sum = tree_sum(avl_tree);
    int avl_height = tree_height(avl_tree);
    float avl_avg_height = average_height(avl_tree);
    
    int bst_size = tree_size(bst_tree);
    int bst_sum = tree_sum(bst_tree);
    int bst_height = tree_height(bst_tree);
    float bst_avg_height = average_height(bst_tree);
    
    int balanced_size = tree_size(balanced_tree);
    int balanced_sum = tree_sum(balanced_tree);
    int balanced_height = tree_height(balanced_tree);
    float balanced_avg_height = average_height(balanced_tree);

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("| n = 100  |  Размер       | Контр. сумма       |   Высота         |     Средн. высота   |\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("| ИСДП     | %8d      | %12d       |    %8d      |  %15.2f    |\n", 
           balanced_size, balanced_sum, balanced_height, balanced_avg_height);
    printf("------------------------------------------------------------------------------------------\n");
    printf("| АВЛ      | %8d      | %12d       |    %8d      |       %10.2f    |\n", 
           avl_size, avl_sum, avl_height, avl_avg_height);
    printf("------------------------------------------------------------------------------------------\n");
    printf("| Обычное  | %8d      | %12d       |    %8d      |       %10.2f    |\n", 
           bst_size, bst_sum, bst_height, bst_avg_height);
    printf("------------------------------------------------------------------------------------------\n");

    free_tree(avl_tree);
    free_tree(bst_tree);
    free_tree(balanced_tree);
    
    return 0;       
}