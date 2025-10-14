#include <stdio.h>
#include <stdlib.h>

struct vertex {
    int data;            
    struct vertex *left;
    struct vertex *right;
    int Bal; 
};

typedef struct vertex Node;

void LR_rotate(Node **p) {
    if (p == NULL || *p == NULL) return;
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
    if (p == NULL || *p == NULL) return;
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

int LL1(Node **p){
    if (p == NULL || *p == NULL) return 0;
    Node *q = (*p)->left;
    if (q->Bal == 0){
        q->Bal = 1;
        (*p)->Bal = -1;
        return 0;
    } else {
        q->Bal = 0;
        (*p)->Bal = 0;
        (*p)->left = q->right;
        q->right = *p;
        *p = q; 
        return 1;
    }
}

int RR1(Node **p) {
    if (p == NULL || *p == NULL) return 0;
    Node *q = (*p)->right;
    if (q->Bal == 0) {
        q->Bal = -1;
        (*p)->Bal = 1;
        return 0;
    } else {
        q->Bal = 0;
        (*p)->Bal = 0;
    }
    (*p)->right = q->left;
    q->left = *p;
    *p = q;
    return 1;
}

int BL(Node **p){
    if (p == NULL || *p == NULL) return 0;
    int dec = 1;
    if ((*p) -> Bal == -1){
        (*p) ->Bal = 0;
    }else if ((*p) -> Bal == 0){
        (*p)->Bal = 1;
        dec = 0;
    }else if((*p)->Bal == 1){
        Node *q = (*p)->right;
        int sub_bal = q->Bal;
        if (sub_bal >= 0){
            RR1(p);
            if (sub_bal == 0) dec = 0;
        } else {
            RL_rotate(p);
        }
    }
    return dec;
}

int BR(Node **p){
    if (p == NULL || *p == NULL) return 0;
    int dec = 1;
    if ((*p)->Bal == 1){
        (*p)->Bal = 0;
    } else if((*p)->Bal == 0){
        (*p)->Bal = -1;
        dec = 0;
    } else if((*p)->Bal == -1){
        Node *q = (*p)->left;
        int sub_bal = q->Bal;
        if(sub_bal <= 0){
            LL1(p);
            if (sub_bal == 0) dec = 0;
        } else {
            LR_rotate(p);
        }
    }
    return dec;
}
int del(Node **r, Node **to_free){
    if (r == NULL || *r == NULL || to_free == NULL) return 0;
    int dec = 0;
    if((*r)->right != NULL){
        dec = del(&(*r)->right, to_free);
        if (dec) dec = BR(r);
    } else {
        (*to_free)->data = (*r)->data;
        Node *temp = *r;
        *r = (*r)->left; 
        free(temp);
        dec = 1;
    }
    return dec;
}
int DELETE(int x, Node **p){
    if (p == NULL || *p == NULL) return 0;

    Node *curr = *p;
    int dec = 0;
    if (x < curr->data) {
        dec = DELETE(x, &curr->left);
        if (dec) dec = BL(p);
    } else if (x > curr->data) {
        dec = DELETE(x, &curr->right);
        if (dec) dec = BR(p);
    } else {
        Node *q = curr;
        if (q->left == NULL) {
            *p = q->right;
            free(q);
            dec = 1;
        } else if (q->right == NULL) {
            *p = q->left;
            free(q);
            dec = 1;
        } else {
            dec = del(&q->left, &q);
            if (dec) dec = BL(p);
        }
    }
    return dec;
}

void left_right(Node *p) {
    if (p != NULL) {
        left_right(p->left);
        printf("%d ", p->data);  
        left_right(p->right);
    }
}

int add_AVL(int D, Node **p, int* Rost) {
    if (*p == NULL) {
        *p = (Node*)malloc(sizeof(Node));
         if (*p == NULL) {
            *Rost = 0;
            return 0;
        }
        (*p)->data = D;
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->Bal = 0;
        *Rost = 1;
        return 1;
    }
    else if ((*p)->data > D) {
        add_AVL(D, &((*p)->left), Rost);
        
        if (*Rost) {
            if ((*p)->Bal > 0) {
                (*p)->Bal = 0;
                *Rost = 0;

            }
            else if ((*p)->Bal == 0) {
                (*p)->Bal = -1;
            }
            else {
                if ((*p)->left->Bal < 0) {
                    LL1(p);
                    *Rost = 0;
                }
                else {
                    LR_rotate(p);
                    *Rost = 0;
                }
            }
        }
    }
        else if ((*p)->data < D) {
        add_AVL(D, &((*p)->right), Rost);
        
        if (*Rost) {
            if ((*p)->Bal < 0) {
                (*p)->Bal = 0;
                *Rost = 0;
            }
            else if ((*p)->Bal == 0) {
                (*p)->Bal = 1;
            }
            else {
                if ((*p)->right->Bal > 0) {
                    RR1(p);
                   *Rost = 0;
                }
                else {
                    RL_rotate(p);
                    *Rost = 0;
                }
            }
        }
    } 
    else {
        *Rost = 0;
    }
    return 0;
}

void free_tree(Node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(){
    Node *root = NULL;
    int Rost = 0;

    printf("Вставка чисел 1-10:\n");
    for (int i = 1; i <= 10; i++) {
        add_AVL(i, &root, &Rost);
        printf("После вставки %d: ", i);
        left_right(root);
        printf("\n");
    }

    printf("\nВведите 10 чисел для удаления:\n");
    for (int i = 0; i < 10; i++) {
        int key;
        scanf("%d", &key);
        DELETE(key, &root);
        printf("После удаления %d: ", key);
        left_right(root);
        printf("\n");
    }
    free_tree(root);
    return 0;
}