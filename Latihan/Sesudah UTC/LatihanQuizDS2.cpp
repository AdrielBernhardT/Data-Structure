#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    int height;
    node* left;
    node* right;
} *curr, *newHead;

int getBalance(node* root){
    return root? root->height:0;
}

int max(int a, int b){
    return a>b? a:b;
}

int height(node* root){
    return root? root->height:0;
}

node* leftRotate(node* y) {
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
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

node* createNode(){
    curr = (node*)malloc(sizeof(node));

    printf("Input value: ");
    scanf("%d", &curr->value); getchar();

    curr->height = 1;
    curr->left = NULL;
    curr->right = NULL;

    return curr;
}

node* Insert(node* root){
    if(!root){
        return NULL;
    }

    if(curr->value < root->value) {
        root->left = Insert(root->left);
    } else if(curr->value > root->value) {
        root->right = Insert(root->right);
    } else {
        return root;
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);

    if(balance > 1){
        if(getBalance(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    } else {
        if(getBalance(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void View(node* root){
    if(root){
        View(root->left);
        printf("%d", root->value);
        View(root->right);
    }
}

node* Delete(node* root, int target){
    if(!root){
        return NULL;
    }
    if(target < root->value) {
        root->left = Delete(root->left, target);
    } else if(target > root->value) {
        root->right = Delete(root->right, target);
    } else {
        if(!root->left && !root->right){
            free(root);
            return NULL;
        } else if(!root->left || !root->right) {
            node* temp = root->left?root->left:root->right;
            free(root);
            return temp;
        } else {
            node* temp = temp->left;
            while(temp->right){
                temp = temp->right;
            }
            root->value = temp->value;

            root->left = Delete(root->left,temp->value);
        }
    }
    root->height = max(height(root->left),height(root->right))+1;
    int balanceRoot = getBalance(root);

    if(balanceRoot > 1) { 
        if(getBalance(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if(balanceRoot < -1) {
        if(getBalance(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;

}

node* DeleteThis(node* root) {
    if (!root) {
        printf("No data to delete.\n");
        return root;
    }
    int target;
    printf("Input value to delete: ");
    scanf("%d", &target); getchar();

    node* newRoot = Delete(root, target);
    if (newRoot == root) {
        printf("Value %d not found.\n", target);
    } else {
        printf("Value %d deleted.\n", target);
    }
    return newRoot;
}

int main(){
    int choice;
    do {
        printf("MENU\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Delete\n");
        printf("4. Exit\n");
        do {
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 4);
        if (choice == 1) {
            newHead = Insert(newHead);
        } else if (choice == 2) {
            View(newHead);
        } else if (choice == 3) { 
            newHead = DeleteThis(newHead);
        } else {
            printf("Bye-Bye\n");
        }
        
    } while (choice != 4);
    return 0;
}