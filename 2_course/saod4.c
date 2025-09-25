#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct vertex {
    int data;         
    int index;      
    struct vertex *left;
    struct vertex *right;
};

typedef struct vertex Node;

// Функция добавления с двойной косвенностью (итеративная)
void add_iterative(int D, int idx, Node **pRoot) {
    Node **p = pRoot;
    
    while (*p != NULL) {
        if (D < (*p)->data) {
            p = &((*p)->left);
        } else if (D > (*p)->data) {
            p = &((*p)->right);
        } else {
            return; 
        }
    }
    
    if (*p == NULL) {
        *p = (Node*)malloc(sizeof(Node));
        (*p)->data = D;
        (*p)->index = idx; 
        (*p)->left = NULL;
        (*p)->right = NULL;
    }
}

// Рекурсивная функция добавления
void add_recursive(int D, int idx, Node **p) {
    if (*p == NULL) {
        *p = (Node*)malloc(sizeof(Node));
        (*p)->data = D;
        (*p)->index = idx; 
        (*p)->left = NULL;
        (*p)->right = NULL;
    } else if (D < (*p)->data) {
        add_recursive(D, idx, &((*p)->left));
    } else if (D > (*p)->data) {
        add_recursive(D, idx, &((*p)->right));
    } else {
        
    }
}

int size(Node *p) {
    if (p == NULL) {
        return 0;
    } else {
        return 1 + size(p->left) + size(p->right);
    } 
}

int sum(Node *p) {
    if (p == NULL) {
        return 0;
    } else {
        return p->data + sum(p->left) + sum(p->right);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *p) {
    if (p == NULL) {
        return 0;
    } else {
        return 1 + max(height(p->left), height(p->right));
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
    int tree_size = size(p);
    return (float)total_path_length / tree_size;
}


void left_right(Node *p) {
    if (p != NULL) {
        left_right(p->left);
        printf("%d ", p->index);
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

// Функция для создания идеально сбалансированного дерева поиска
Node* create_balanced_tree(int arr[], int start, int end, int *index_counter) {
    if (start > end) {
        return NULL;
    }
    
    int mid = (start + end) / 2;
    Node *root = (Node*)malloc(sizeof(Node));
    root->data = arr[mid];
    root->index = (*index_counter)++;
    root->left = create_balanced_tree(arr, start, mid - 1, index_counter);
    root->right = create_balanced_tree(arr, mid + 1, end, index_counter);
    
    return root;
}

int main() {
    srand(time(NULL));
    
    int sequence[100];
    for (int i = 0; i < 100; i++) {
        sequence[i] = i + 1;
    }
    
    for (int i = 99; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = sequence[i];
        sequence[i] = sequence[j];
        sequence[j] = temp;
    }
    
    
    // Создаем два случайных дерева поиска
    Node *root_iterative = NULL; 
    Node *root_recursive = NULL; 
    
    for (int i = 0; i < 100; i++) {
        add_iterative(sequence[i], i + 1, &root_iterative);
        add_recursive(sequence[i], i + 1, &root_recursive);
    }
    
    // Создаем идеально сбалансированное дерево поиска (ИСДП)
    int sorted_sequence[100];
    for (int i = 0; i < 100; i++) {
        sorted_sequence[i] = i + 1;
    }
    int index_counter = 1;
    Node *root_balanced = create_balanced_tree(sorted_sequence, 0, 99, &index_counter);
    
    printf("Обход дерева (добавление с двойной косвенностью): ");
    left_right(root_iterative);
    printf("\n\n");
    
    printf("Обход дерева (рекурсивное добавление): ");
    left_right(root_recursive);
    printf("\n\n");
    
    printf("Обход ИСДП: ");
    left_right(root_balanced);
    printf("\n\n");

    printf("------------------------------------------------------------------------------------------\n");
    printf("| n = 100  |  Размер       | Контр. сумма       |   Высота         |     Средн. высота   |\n");
    printf("-----------------------------------------------------------------------------------------|\n");
    printf("| ИСДП     | %8d      | %12d       |    %8d      |  %15.2f    |\n", 
           size(root_balanced), sum(root_balanced), height(root_balanced), average_height(root_balanced));
    printf("-----------------------------------------------------------------------------------------|\n");
    printf("| СДП1     | %8d      | %12d       |    %8d      |       %10.2f    |\n", 
           size(root_iterative), sum(root_iterative), height(root_iterative), average_height(root_iterative));
    printf("-----------------------------------------------------------------------------------------|\n");
    printf("| СДП2     | %8d      | %12d       |    %8d      |       %10.2f    |\n", 
           size(root_recursive), sum(root_recursive), height(root_recursive), average_height(root_recursive));
    printf("-----------------------------------------------------------------------------------------|\n");

    free_tree(root_iterative);
    free_tree(root_recursive);
    free_tree(root_balanced);

    return 0;
}