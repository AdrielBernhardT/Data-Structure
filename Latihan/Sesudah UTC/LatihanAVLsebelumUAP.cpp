#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    int height;
    node* left;
    node* right;
};

int height(node* root){
    return root? root->height:0;
}

int getBalance(node* root){
    return root? (height(root->left)-height(root->right)) : 0;
}

int max(int a, int b){
    return a > b? a : b;
}

node* rotateLeft(node* y){
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    return x;
}

node* rotateRight(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    return x;
}

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

node* Insert(node* root, int value){
    if (!root){
        return createNode(value);
    } 
    if (value < root->value) {
        root->left = Insert(root->left, value);
    } else if (value > root->value) {
        root->right = Insert(root->right, value);
    } else {
        return root;
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);
    
    if(balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if(balance < -1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    } 
    return root;
}

void View(node* root) {
    if(root){
        View(root->left);
        printf("Value: %d\n", root->value);
        View(root->right);
    }
}

node* deleteAVL(node* root, int target){
    if (!root) {
        return NULL;
    } 
    if (target < root->value) {
        root->left = deleteAVL(root->left, target);
    } else if (target > root->value) {
        root->right = deleteAVL(root->right, target);
    } else {
        if (!root->right && !root->left) {
            free(root);
            return NULL;
        } else if ( !root->left || !root->right) {
            node* temp = root->left?root->left:root->right;
            free(root);
            return temp;
        } else {
            node* temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }   

            root->value = temp->value;

            root->left = deleteAVL(root->left, temp->value); 
        }
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);
    
    if(balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if(balance < -1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    } 
    return root;
}

node* Delete(node* root) {
    if (!root) {
        printf("No Data\n");
        return NULL;
    }

    int target;
    printf("Delete Value: ");
    scanf("%d", &target); getchar();
    node* newRoot = deleteAVL(root,target);

    if (newRoot == root) {
        printf("Data Not Found\n");
    } else {
        printf("[Data successfully deleted]\n");
    }

    return newRoot;
}

int main(){
    int value;
    node* root = NULL;
    do {
        printf("Input Value: ");
        scanf("%d", &value); getchar();
        root = Insert(root, value);
        printf("Tree:\n");
        View(root);
        printf("\n");
    } while (value != 0);

    for (int i = 0; i < 5; i++)
    {
        root = Delete(root);
        printf("Tree:\n");
        View(root);
        printf("\n");
    }
    

    return 0;
}