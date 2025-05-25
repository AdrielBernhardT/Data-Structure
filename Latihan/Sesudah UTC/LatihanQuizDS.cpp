#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int height;
    struct node *left;
    struct node *right;
} node;

node *curr = NULL;
node *headRoot = NULL;

int height(node* root){
    return root ? root->height : 0;
}

int max(int a, int b){
    return a > b ? a : b;
}

int getBalance(node* root){
    return root ? (height(root->left) - height(root->right)) : 0;
}

node *leftRotate(node* y){
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node *rightRotate(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node *createNode(){
    curr = (node*)malloc(sizeof(node));
    printf("Input value: ");
    scanf("%d", &curr->value); getchar();
    curr->height = 1;
    curr->left = NULL;
    curr->right = NULL;

    return curr;
}

node *Insert(node* root){
    if (!root){
        return createNode();  // gunakan node yg sudah diisi di curr
    }
    if(curr->value < root->value){
        root->left = Insert(root->left);
    } else if(curr->value > root->value){
        root->right = Insert(root->right);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balanceRoot = getBalance(root);

    if(balanceRoot > 1){
        if(getBalance(root->left) >= 0){
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if(balanceRoot < -1){
        if(getBalance(root->right) <= 0){
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void inorder(node* root){
    if (root){
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

node* deleteAVL(node* root, int target){
    if(!root){
        return NULL;
    }

    if (root->value > target){
        root->left = deleteAVL(root->left, target);
    } else if(root->value < target){
        root->right = deleteAVL(root->right, target);
    } else{
        if(!root->left && !root->right){
            free(root);
            return NULL;
        } 
        if(!root->left || !root->right){
            node* temp = root->left? root->left:root->right;
            free(root);
            return temp;
        }
        node* temp = root->left;
        while(temp->right){
            temp = temp->right;
        }

        root->value = temp->value;

        root->left = deleteAVL(root->left, temp->value);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balanceRoot = getBalance(root);

    if(balanceRoot > 1){
        if(getBalance(root->left) >= 0){
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if(balanceRoot < -1){
        if(getBalance(root->right) <= 0){
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

node* Delete(node* root) {
    if (!root) {
        printf("No data to delete.\n");
        return root;
    }
    int target;
    printf("Input value to delete: ");
    scanf("%d", &target); getchar();

    node* newRoot = deleteAVL(root, target);
    if (newRoot == root) {
        printf("Value %d not found.\n", target);
    } else {
        printf("Value %d deleted.\n", target);
    }
    return newRoot;
}

int main(){
    int choice;
    do{
        printf("LATIHAN\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. View\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &choice); getchar();

        if (choice == 1){
            createNode();     // input nilai ke curr
            headRoot = Insert(headRoot); // update headRoot dengan insert
        } else if (choice == 2){
            headRoot = Delete(headRoot); // update headRoot dengan delete
        } else if(choice == 3){
            inorder(headRoot);
            printf("\n");
        } else if (choice == 4){
            printf("Have a great day!\n");
        }
    } while(choice != 4);

    return 0;
}