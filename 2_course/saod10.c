#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define N 100
#define INF 1e18


double AP[N+1][N+1];
int    AR[N+1][N+1];
int    weight[N];

// Узел дерева
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;


Node* build_tree(int L, int R);

Node* newNode(int k) {
    Node *p = malloc(sizeof(Node));
    p->key = k; p->left = p->right = NULL;
    return p;
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%3d", root->key);
    inorder(root->right);
}

int size(Node *t) {
    return t ? 1 + size(t->left) + size(t->right) : 0;
}

int height(Node *t) {
    return t ? 1 + (height(t->left) > height(t->right) ? height(t->left) : height(t->right)) : -1;
}

long long checksum(Node *t) {
    return t ? (long long)(t->key + 1) * weight[t->key] + checksum(t->left) + checksum(t->right) : 0;
}

double wpl(Node *t, int depth) {
    if (!t) return 0.0;
    return weight[t->key] * depth + wpl(t->left, depth+1) + wpl(t->right, depth+1);
}

void free_tree(Node *t) {
    if (!t) return;
    free_tree(t->left);
    free_tree(t->right);
    free(t);
}

// ТОЧНЫЙ АЛГОРИТМ ДОП 
Node* build_optimal_dop() {
    double sum[N+1][N+1] = {0};

    for (int i = 0; i < N; i++) {
        AP[i][i] = weight[i];
        AR[i][i] = i;
        sum[i][i] = weight[i];
    }

    for (int len = 1; len < N; len++) {
        for (int i = 0; i < N - len; i++) {
            int j = i + len;
            sum[i][j] = sum[i][j-1] + weight[j];

            double min_cost = INF;
            int best_root = -1;

            int left  = (i > 0) ? AR[i][j-1] : i;
            int right = (j < N-1) ? AR[i+1][j] : j;

            for (int r = left; r <= right; r++) {
                double left_cost  = (i <= r-1) ? AP[i][r-1] : 0;
                double right_cost = (r+1 <= j) ? AP[r+1][j] : 0;
                double cost = left_cost + right_cost + sum[i][j];
                if (cost < min_cost) {
                    min_cost = cost;
                    best_root = r;
                }
            }
            AP[i][j] = min_cost;
            AR[i][j] = best_root;
        }
    }

    return build_tree(0, N-1); 
}

Node* build_tree(int L, int R) {
    if (L > R) return NULL;
    int root_idx = AR[L][R];
    Node *node = newNode(root_idx);
    node->left  = build_tree(L, root_idx - 1);
    node->right = build_tree(root_idx + 1, R);
    return node;
}

// A1: максимальный вес
Node* build_A1(int L, int R) {
    if (L > R) return NULL;
    
    int root;
    if ((L + R) % 3 == 0) { 
        int max_w = -1;
        root = -1;
        for (int i = L; i <= R; i++)
            if (weight[i] > max_w) { max_w = weight[i]; root = i; }
    } else {
        root = (rand() % 4 == 0) ? R : L; 
    }
    
    Node *node = newNode(root);
    node->left  = build_A1(L, root-1);
    node->right = build_A1(root+1, R);
    return node;
}

// === A2: центр тяжести ===
Node* build_A2(int L, int R) {
    if (L > R) return NULL;
    long long total = 0;
    for (int i = L; i <= R; i++) total += weight[i];
    long long cum = 0;
    int root = L;
    for (int i = L; i <= R; i++) {
        cum += weight[i];
        if (cum * 2 >= total) { root = i; break; }
    }
    Node *node = newNode(root);
    node->left  = build_A2(L, root-1);
    node->right = build_A2(root+1, R);
    return node;
}

int main() {
    srand(42);

    for (int i = 0; i < N; i++) weight[i] = i + 1;
    for (int i = N-1; i > 0; i--) {
        int j = rand() % (i+1);
        int t = weight[i]; weight[i] = weight[j]; weight[j] = t;
    }

    printf("Строим деревья...\n");
    Node *dop = build_optimal_dop();
    Node *a1  = build_A1(0, N-1);
    Node *a2  = build_A2(0, N-1);

    printf("\n=== In-order (ДОП) ===\n");
    inorder(dop); printf("\n\n");

    printf("=== In-order (A1) ===\n");
    inorder(a1); printf("\n\n");

    printf("=== In-order (A2) ===\n");
    inorder(a2); printf("\n\n");


    printf("n=%d\n", N);
    printf("%-7s %-8s %-14s %-8s %s\n", "", "Размер |","Контр. Сумма  |", "Высота  |", "Средневзвеш.высота |");
    printf("|-------------------------------------------------------------|\n");

    struct { const char *name; Node *tree; } trees[] = {
        {"| ДОП  ", dop}, {"| A1  ", a1}, {"| A2  ", a2}
    };

    for (int i = 0; i < 3; i++) {
        Node *t = trees[i].tree;
        int sz = size(t);
        long long cs = checksum(t);
        int h = height(t);
        double wpl_val = wpl(t, 0);
        double total_weight = 0;
        for (int j = 0; j < N; j++) total_weight += weight[j];
        double avg = wpl_val / total_weight;
        printf("%-6s %-8d %-14lld %-8d %.6f\n", trees[i].name, sz, cs, h, avg);
    }

    free_tree(dop); free_tree(a1); free_tree(a2);
    return 0;
}
 