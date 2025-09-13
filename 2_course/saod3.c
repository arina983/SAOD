#include <stdio.h>
#include <stdlib.h>

struct vertex {
    int data;
    struct vertex *left;
    struct vertex *right;
};

int A[100];

struct vertex* ISDP(int left, int right){
    if (left > right){
        return NULL;
    }
    
    int m = (left + right) / 2; 
    struct vertex *p = (struct vertex*)malloc(sizeof(struct vertex));
    p->data = A[m];
    p->left = ISDP(left, m - 1);
    p->right = ISDP(m + 1, right);

    return p;
}

void left_right(struct vertex *p){
    if (p != NULL){
        left_right(p->left);
        printf("%d ", p->data);
        left_right(p->right);
    }
}

void free_tree(struct vertex *p) {
    if (p != NULL) {
        free_tree(p->left);
        free_tree(p->right);
        free(p);
    }
}

int size (struct vertex *p){
    if (p == NULL){
        return 0;
    } else {
        return 1 + size(p->left) + size(p->right);
    } 
}

int sum(struct vertex *p){
    if (p == NULL){
        return 0;
    } else {
        return p->data + sum(p->left) + sum(p->right);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct vertex *p){
    if (p == NULL){
        return 0;
    } else {
        return 1 + max(height(p->left), height(p->right));
    }
}

int sum_path_lengths(struct vertex *p, int l){
    if (p == NULL){
        return 0;
    } else {
        return l + sum_path_lengths(p->left, l + 1) + sum_path_lengths(p->right, l + 1);
    }
}

float average_height(struct vertex *p){
    if (p == NULL) {
        return 0.0;
    }
    int total_path_length = sum_path_lengths(p, 1);
    int tree_size = size(p);
    return (float)total_path_length / tree_size;
}

int main(){

    for (int i = 0; i < 100; i++) {
        A[i] = i + 1;
    }
    struct vertex *root = ISDP(0, 99);

    printf("Обход дерева слева направо:\n");
    left_right(root);
    printf("\n");
    printf("Размер дерева: %d\n", size(root));
    printf("Контрольная сумма: %d\n", sum(root));
    printf("Высота ИСДП: %d\n", height(root));
    printf("Средняя высота ИСДП: %.2f\n", average_height(root));
    
    free_tree(root);
    
    return 0;
}