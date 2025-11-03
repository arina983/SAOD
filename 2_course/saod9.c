#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXN 105

int W[MAXN], keys[MAXN];
int AW[MAXN][MAXN], AP[MAXN][MAXN], AR[MAXN][MAXN];

void initMatrices() {
    memset(AW, 0, sizeof(AW));
    memset(AP, 0, sizeof(AP));
    memset(AR, 0, sizeof(AR));
}

void printMatrix(int n, const char* name, int mat[MAXN][MAXN]) {
    printf("\n--- %s (n=%d) ---\n", name, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i) printf("%6d ", mat[i][j]);
            else printf("       ");
        }
        printf("\n");
    }
}

void buildOptimalBST(int n) {
    initMatrices();

    for (int i = 0; i < n; i++) {
        AW[i][i] = W[i];
        for (int j = i + 1; j < n; j++) {
            AW[i][j] = AW[i][j - 1] + W[j];
        }
    }

    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }

    for (int h = 2; h < n; h++) {
        for (int i = 0; i < n - h; i++) {
            int j = i + h;
            int m = AR[i][j - 1];
            int min_cost = (m > i ? AP[i][m - 1] : 0) + (m < j ? AP[m + 1][j] : 0);
            int best_k = m;

            int right_bound = j;
            if (i + 1 <= j) {
                right_bound = AR[i + 1][j];
            }
            if (right_bound > j) right_bound = j;

            for (int k = m + 1; k <= right_bound; k++) {
                int left = (k > i) ? AP[i][k - 1] : 0;
                int right = (k < j) ? AP[k + 1][j] : 0;
                int x = left + right;
                if (x < min_cost) {
                    min_cost = x;
                    best_k = k;
                }
            }
            AP[i][j] = min_cost + AW[i][j];
            AR[i][j] = best_k;
        }
    }
}

void inorder(int n, int i, int j) {
    if (i > j || i < 0 || j >= n) return;
    int root = AR[i][j];
    if (root < i || root > j) return;
    inorder(n, i, root - 1);
    printf("%d ", keys[root]);
    inorder(n, root + 1, j);
}

double computeAP(int n, int i, int j, int depth) {
    if (i > j || i < 0 || j >= n) return 0.0;
    if (i == j) return depth * W[i];
    int root = AR[i][j];
    if (root < i || root > j) return 0.0;
    return computeAP(n, i, root - 1, depth + 1) +
           computeAP(n, root + 1, j, depth + 1) +
           depth * W[root];
}

int height(int n, int i, int j) {
    if (i > j || i < 0 || j >= n) return -1;
    if (i == j) return 0;
    int root = AR[i][j];
    if (root < i || root > j) return 0;
    int l = height(n, i, root - 1);
    int r = height(n, root + 1, j);
    return 1 + (l > r ? l : r);
}

int controlSum(int n) {
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        sum += AP[i][i + 1];
    }
    return sum;
}

int main() {
    srand(time(0));

    int n10 = 10;
    printf("Матрицы для первых 10 символов (n=10) \n");
    printf("Веса: ");
    for (int i = 0; i < n10; i++) {
        W[i] = 1 + rand() % 100;
        keys[i] = i;
        printf("%d ", W[i]);
    }
    printf("\n\n");

    buildOptimalBST(n10);
    printMatrix(n10, "Матрица весов AW[i][j]", AW);
    printMatrix(n10, "Матрица взвешенных высот AP[i][j]", AP);
    printMatrix(n10, "Матрица корней AR[i][j]", AR);

    int n100 = 100;
    printf("\n\nПостроение дерева оптимального поиска n=100\n");
    for (int i = 0; i < n100; i++) {
        W[i] = 1 + rand() % 100;
        keys[i] = i;
    }

    buildOptimalBST(n100);

    printf("Обход слева-направо (n=100):\n");
    inorder(n100, 0, n100 - 1);
    printf("\n\n");

    double AP_manual = computeAP(n100, 0, n100 - 1, 0);
    double AW_root = AW[0][n100 - 1];
    double ratio = AP[0][n100-1]/ AW_root;


    printf("AP[0,99] (матрица) = %d\n", AP[0][n100-1]);
    printf("AP[0,99] (ручной)  = %.2f\n", AP_manual);
    printf("AW[0,99]           = %.0f\n", AW_root);
    printf("AP[0,n]/AW[0,n]    = %.6f\n\n", ratio);

    int size = n100;
    int ctrl = controlSum(n100);
    int h = height(n100, 0, n100 - 1);
    double avg = ratio;

    printf("+-------+--------+-------------+--------+--------------------+\n");
    printf("| n=100 | Размер | Контр.сумма | Высота | Средневзв.высота   |\n");
    printf("+-------+--------+-------------+--------+--------------------+\n");
    printf("| ДОП   |  %-5d |     %-8d|   %-4d |      %-13.6f |\n", size, ctrl, h, avg);
    printf("+-------+--------+-------------+--------+--------------------+\n");

    return 0;
}
