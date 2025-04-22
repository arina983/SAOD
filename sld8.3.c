#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
 
struct person {
    char surname[50];
    char name[50];
    long phone;
    int area;
};
 
void Print(struct person some){
    printf("%s %s %ld %d\n", some.surname, some.name, some.phone, some.area);
}
 
struct person add(char* surname, char* name, long phone, int area){
    struct person newperson;
    strcpy(newperson.surname, surname);
    strcpy(newperson.name, name);
    newperson.phone = phone;
    newperson.area = area;
    return newperson;
}
 
int lesss(struct person a, struct person b, int c, int d){
    if (c==1) {
        if (strcmp(a.surname,b.surname) < 0) return 1;
        else if (strcmp(a.surname,b.surname) > 0) return 0;
        else if (d==2){ 
            if (a.name < b.name) return 1;
            else return 0;
        }
        else if (d==3){
            if (a.phone < b.phone) return 1;
            else return 0;
        }
        else if (d==4) {
            if (a.area < b.area) return 1;
            else return 0;
        }  
    }
    else if (c==2) {
        if (strcmp(a.name,b.name) < 0)  return 1;
        else if (strcmp(a.name,b.name) > 0) return 0;
        else if (d==3){
            if (a.phone < b.phone) return 1;
            else return 0;
        }
        else if (d==4) {
            if (a.area < b.area) return 1;
            else return 0;
        }  
    }
    else if (c==3) {
        if (a.phone < b.phone) return 1;
        else if (a.phone > b.phone) return 0;
        else if (d==4) {
            if (a.area < b.area) return 1;
            else return 0;
        }  
    }
}
 
void SelectSort(int n, struct person d[], int k1, int k2, int r, int* b){
    for (int i=0; i<(n-1); i++){
        int k = i;
        for (int j=(i+1); j<n; j++){ 
            if (lesss(d[b[j]],d[b[k]], k1, k2)){
                k = j;
            }
        }
            int tmp = b[k]; 
            b[k]=b[i];
            b[i] = tmp;
    }
    if (r==1){
        for (int i=0; i<n; i++){
            Print(d[b[i]]);
        }
        printf("\n");
    } else {
        for (int i=(n-1); i>=0; i--){
            Print(d[b[i]]);
        }
        printf("\n");
    }
    
}
 
void search_surname(int n, char* x, struct person A[], int* B){
    int find = 0;
    int m;
    int l=0, r= (n-1);
    while (l<r){
        m = floor((l+r)/2);
        if (strcmp(A[B[m]].surname, x) < 0) l = (m+1);
        else r = m;
    }
    if ( strcmp(A[B[l]].surname, x) == 0) find = 1;
    
    if (find == 0) printf("не найден\n");
    else {
        printf("найден\n");
        while (strcmp(A[B[l]].surname, x) == 0){
            Print(A[B[l]]);
            l++;
            if (l==n) break;
        }   
    }
}
 
void search_name(int n, char* x, struct person A[], int* B){
    int find = 0;
    int m;
    int l=0, r= (n-1);
    while (l<r){
        m = floor((l+r)/2);
        if (strcmp(A[B[m]].name, x) < 0) l = (m+1);
        else r = m;
    }
    if ( strcmp(A[B[l]].name, x) == 0) find = 1;
    
    if (find == 0) printf("не найден\n");
    else {
        printf("найден\n");
        while (strcmp(A[B[l]].name, x) == 0){
            Print(A[B[l]]);
            l++;
            if (l==n) break;
        }   
    }
}
 
void main(){
    int n = 5;
    struct person directory[] = {add("Бубенина\0", "Арина\0", 876543123, 16),
                                 add("Попова\0","Кристина\0", 3476542, 27),
                                 add("Попова\0", "Софья\0", 1234545, 21),
                                 add("Деева\0", "Ольга\0", 7656435, 37),
                                 add("Короткова\0", "Анна\0", 7564532, 18)};
    for (int i=0; i<n; i++){
        Print(directory[i]);
    }
    printf("\n");
 
    int B[n];
    printf("Индексный массив В: ");
    for (int i=0; i<n; i++){
        B[i] = i;
        printf("%d ", B[i]);
    }
    printf("\n");
 
    printf("Индексный массив C: ");
    int C[n];
    for (int i=0; i<n; i++){
        C[i] = i;
        printf("%d ", C[i]);
    }
    printf("\n");
 
    SelectSort(n, directory, 1,4, 1, B);
    SelectSort(n, directory, 2,4, 1, C);
 
    printf("Индексный массив В (сортировка по фамилии и возрасту): ");
    for (int i=0; i<n; i++){
        printf("%d ", B[i]);
    }
    printf("\n");
 
    printf("Индексный массив C (сортировка по имени и возрасту): ");
    for (int i=0; i<n; i++){
        printf("%d ", C[i]);
    }
    printf("\n");
 
    for (int i=0; i<n; i++){
        Print(directory[B[i]]);
    }
    printf("\n");
    for (int i=0; i<n; i++){
        Print(directory[C[i]]);
    }
 
    printf("\n");
    search_surname(n, "Попова", directory, B);
    printf("\n");
    search_name(n, "Ольга", directory, C);
 
}