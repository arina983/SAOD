#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
 
void series(int n, int A[n]){
    int s=1;
    for (int i=1; i<n; i++){
        if (A[i-1]>A[i]){
            s+=1;
        }
    }
    printf("серий: %d\n", s);
}
 
void checksum(int n, int A[n]){
    int s = 0;
    for (int i=0; i<n; i++){
        s+=A[i];
    }
    printf("к.сумма: %d, ", s);
}
 
int Pyramid(int L, int R, int A[]){
    int S = 0;
    int x = A[L];
    int i = L;
    while (1) {
        int j = 2*i+1;
        if (j>R) break;
        S++;
        if (j+1 <= R && (A[j+1] > A[j])) j++;
        S++;
        if (x >= A[j]) break; 
        S++;
        A[i] = A[j];
        i = j;
    }
    S++;
    A[i] = x;
    return S;
}
 
int HeapSort(int n, int A[]){
    int S = 0;
    int L = n/2-1;
    int R=n-1;
    while (L>=0){
        S+= Pyramid(L,R,A);
        L--;
    }
 
    while (R>0){
        S += 3;
        int tmp = A[R];
        A[R] = A[0];
        A[0] = tmp;
        R--;
        S+= Pyramid(0,R,A);
        
    }
    //for (int i=0; i<n; i++) printf("%d ", A[i]);
    //printf("\n");
    return S;
}
 
int main(){
 
    printf("---------------------------------------------------------------\n");
    printf("| N    |  М + С (теорет) |            Мф+Сф                   |\n");
    printf("|_____________________________________________________________|\n");
    printf("|      |                 | Убыв.      |  Случ.       |Возр.   |\n");
    printf("|-------------------------------------------------------------|\n");
    for (int N=100; N<=500; N+=100){
        
        int C[N];
        for (int i=(N-1); i>=0; i--){
            C[i]=N-i;
        }
        //for (int i=0; i<N; i++) printf("%d ",C[i]);
    //printf("\n");
        int x1 = Pyramid(0, (N-1), C);
 
        int D[N];
        srand(time(NULL));
        for (int i=0; i<N; i++){
            D[i]=rand()%100;
        }
        //for (int i=0; i<N; i++) printf("%d ",D[i]);
    //printf("\n");
        int x2 = Pyramid(0, (N-1), D);
 
        int B[N];
        for (int i=0; i<N; i++){
            B[i]=i+1;
        }
        //for (int i=0; i<N; i++) printf("%d ",B[i]);
    //printf("\n");
        int x3 = Pyramid(0, (N-1), B);
 
        printf("|  %d  | %f  |  %d     |   %d       |%d", N ,log2(N)+2+2*log2(N), x1, x2, x3);
        printf("\n");
 
    }
 
    printf("\n");
 
    printf("-----------------------------------------------\n");
    printf("|               HeapSort(Мф+Сф)               |\n");
    printf("|_____________________________________________|\n");
    printf("| N |  Убыв.      |  Случ.       |Возр.       |\n");
    printf("|---------------------------------------------|\n");
    for (int N=100; N<=500; N+=100){
        
        int C[N];
        for (int i=(N-1); i>=0; i--){
            C[i]=N-i;
        }
        //for (int i=0; i<N; i++) printf("%d ",C[i]);
    //printf("\n");
        int x1 = HeapSort(N, C);
 
        int D[N];
        srand(time(NULL));
        for (int i=0; i<N; i++){
            D[i]=rand()%100;
        }
        //for (int i=0; i<N; i++) printf("%d ",D[i]);
    //printf("\n");
        int x2 = HeapSort(N, D);
 
        int B[N];
        for (int i=0; i<N; i++){
            B[i]=i+1;
        }
        //for (int i=0; i<N; i++) printf("%d ",B[i]);
    //printf("\n");
        int x3 = HeapSort(N, B);
 
        printf(" %d |     %d   |     %d      | %d |", N, x1, x2, x3);
        //printf("\n %f", N*log2(N)+6.5*N-4+2*N*log2(N)+N+2);
        printf("\n");
 
    }
    
 
}