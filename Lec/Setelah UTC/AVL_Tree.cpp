#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int value;
    node *left;
    node *right;
    int height;
} *curr;

node* createNode(int value) {
    node* curr = (node*)malloc(sizeof(node));
    curr->value = value;
    curr->left = NULL;
    curr->right = NULL;
    curr->height = 1; // new node is initially added at leaf
    return curr;
}

int height(node *root){
    return root ? root->height : 0;
}

int max(int a, int b){
    return (a>b) ? a:b;
}

node* rightRotate(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* leftRotate(node* x) {
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(node* root){
    if(root == NULL){
        return 0;
    } 
    return height(root->left) - height(root->right);
}

node* insert(node* root , int value){
    if(root == NULL){
        return createNode(value);
    } else if(value < root->value){
        root->left = insert(root->left, value);
    } else if(value > root->value){
        root->right = insert(root->right, value);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && value < root->left->value)
        return rightRotate(root);

    if (balance < -1 && value > root->right->value)
        return leftRotate(root);

    if (balance > 1 && value > root->left->value) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && value < root->right->value) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(node *root);

int main(){
    node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the constructed AVL tree is \n");
    preOrder(root);

    return 0;   
}

void preOrder(node *root) {
    if(root != NULL) {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}