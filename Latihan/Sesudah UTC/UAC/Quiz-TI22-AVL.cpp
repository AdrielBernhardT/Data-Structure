#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char name[25];
    long long int date;
    int height;
    int index;
    node* left;
    node* right;
} *curr, *headRoot;

int max(int a, int b){
    return a>b?a:b;
}

int height(node* root){
    return root? root->height : 0;
}

int getBalance(node* root){
    return root? height(root->left)-height(root->right) : 0;
}

node* rotateLeft(node* y){
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* rotateRight(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}


node* createNode(){
    curr = (node*)malloc(sizeof(node));
    curr->height = 1;
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

node* Insert(node* root){
    if(!root){
        return createNode();
    }

    if (curr->date < root->date) {
        root->left = Insert(root->left);
    } else  if (curr->date > root->date) {
        root->right = Insert(root->right);
    } else {
        if (strcmp(curr->name, root->name) < 0) {
            root->left = Insert(root->left);
        } else if (strcmp(curr->name, root->name) > 0) {
            root->right = Insert(root->right);
        } else {
            return root;
        }
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);   
    if(balance > 1){
        if(getBalance(root->left) >= 0){
            return rotateRight(root->left);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if(balance < -1){
        if(getBalance(root->left) <= 0){
            return rotateLeft(root->right);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    } 
    return root;
}

int n = 1;

void inOrder(node* root){
    if(root){
        inOrder(root->left);
        root->index = n++;
        inOrder(root->right);
    }
}

node* DeleteAVL(node* root, int index){
    if(!root){
        printf("Empty\n");
        return NULL;
    }
    
    if(index < root->index){
        root->left = DeleteAVL(root->left, index);
    } else if(index > root->index){
        root->right = DeleteAVL(root->right, index);
    } else {
        if(!root->left && !root->right){
            free(root);
            return NULL;
        } else if (!root->left || !root->right){
            node* temp = root->left?root->left:root->right;
        } else {
            node* temp = root->left;
            while(temp->right){
                temp = temp->right;
            }
            root->date = temp->date;
            strcpy(root->name, temp->name);

            root->left = DeleteAVL(root->left, temp->index);
        }
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);   
    if(balance > 1){
        if(getBalance(root->left) >= 0){
            return rotateRight(root->left);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if(balance < -1){
        if(getBalance(root->left) <= 0){
            return rotateLeft(root->right);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    } 
    return root;
}

node* Delete(int index){
    if(!headRoot){
        printf("Empty No Data\n");
        return headRoot;
    } 

    node* newRoot = DeleteAVL(headRoot, index);
    return newRoot;
}

void inOrderPrint(node* root){
    if(root){
        inOrderPrint(root->left);
        printf("%lld %s\n", root->date, root->name);
        inOrderPrint(root->right);
    }
}

int main(){
    int P, Q;
    int X;
    scanf("%d %d", &P, &Q); getchar();
    for(int i = 0; i < P; i++){
        scanf("%lld %s", &curr->date, curr->name); getchar();
        headRoot = Insert(headRoot);
    }

    
    for (int i = 0; i < Q; i++) {
        inOrder(headRoot);
        scanf("%d", &X); getchar();
        headRoot = Delete(X);
        n = 1;
    }

    
    return 0;
}