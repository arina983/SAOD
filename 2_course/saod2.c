#include <stdio.h>
#include <stdlib.h>

struct vertex {
    int data;
    struct vertex *left;
    struct vertex *right;
};

void top_bottom(struct vertex *p){
    if (p != NULL){
        printf("%d ", p->data);
        top_bottom(p->left);
        top_bottom(p->right);
    }
}
void left_right(struct vertex *p){
    if (p != NULL){
        left_right(p->left);
        printf("%d ", p->data);
        left_right(p->right);
    }
}

void bottom_top(struct vertex *p){
    if (p != NULL){
        bottom_top(p->left);
        bottom_top(p->right);
        printf("%d ",p->data);
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
    struct vertex *root;
    root = (struct vertex*)malloc(sizeof(struct vertex));
    root->data = 1;
    root->left = NULL;

    root->right = (struct vertex*)malloc(sizeof(struct vertex));
    root->right->data = 2;
    root->right->left = NULL;
    root->right->right = NULL;

    root->right->left = (struct vertex*)malloc(sizeof(struct vertex));
    root->right->left->data = 3;
    root->right->left->right = NULL;
    root->right->left->left = NULL;

    root->right->right = (struct vertex*)malloc(sizeof(struct vertex));
    root->right->right->data = 4;
    root->right->right->right = NULL;
    root->right->right->left = NULL;

    root->right->right->left = (struct vertex*)malloc(sizeof(struct vertex));
    root->right->right->left->data = 5;
    root->right->right->left->left = NULL;
    root->right->right->left->right = NULL;
    
    root->right->right->left->left = (struct vertex*)malloc(sizeof(struct vertex));
    root->right->right->left->left->data = 6;
    root->right->right->left->left->right = NULL;
    root->right->right->left->left->left = NULL;
    
    printf("Обход сверху вниз: ");
    top_bottom(root);
    printf("\n");
    
    printf("Обход слева направо: ");
    left_right(root);
    printf("\n");
    
    printf("Обход снизу вверх: ");
    bottom_top(root);
    printf("\n");

    printf("Размер дерева: %d\n", size(root));
    printf("Сумма данных: %d\n", sum(root));
    printf("Высота дерева: %d\n", height(root));
    printf("Средняя высота дерева: %.2f\n", average_height(root));

    free_tree(root);

    return 0;
}