#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    node* left;
    node* right;
    int height;
} *curr, *headRoot;

int height(node* root){
    return root? root->height : 0;
}

int getBalance(node* root){
    return root? (root->left-root->right) : 0; 
}

int max(int a, int b) {
    return a>b? a:b;
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

node* rotateLeft(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left, y->right)) + 1;
    x->height = max(height(x->left, x->right)) + 1;

    return x;
}

node* createNode() {
    curr = (node*)malloc(sizeof(node));

    printf("Value: ");
    scanf("%d", &curr->value); getchar();
    
    return curr;
}

node* Insert(node* root){
    if (!root){
        return createNode();
    } else if (curr->value < root->value) {
        root->left = Insert(root->left);
    } else if (curr->value > root->value) {
        root->right = Insert(root->right);
    } else {
        return root;
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);
    if (balance > 1){
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    if (balance < -1){
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->left = rotateRight(root->left);
            return rotateLeft(root);
        }
    }
    return root;
}

node* DeleteAVL(node* root, int target){

}


int main(){
    int value;
    do {
        headRoot = Insert(headRoot);
    } while (value != 0);
}