#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int value;
    struct Node* left;
    struct Node* right;
};

Node* createNode(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildBST(Node* root, int value){
    if(root == NULL){
        return createNode(value);
    }
    if(value < root->value){
        root->left = buildBST(root->left, value);
    }else if (value > root->value){
        root->right = buildBST(root->right, value);
    }
    return root;
}

int search(Node* root, int value){
    if(root == NULL){
        return -1;
    }

    if(root->value == value){
        return root->value;
    }else if(value < root->value){
        return search(root->left, value);
    }else if (value > root->value){
        return search(root->right, value);
    }
}

void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

Node* delNode(Node* root, int value){
    if(root == NULL){
        return root;
    }

    if(value < root->value){
        root->left = delNode(root->left, value);
    }else if(value > root->value){
        root->right = delNode(root->right, value);
    }else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }else if(root->right == NULL){
            Node* temp = root->left;
            root->value = temp->value;
            root->left = NULL;
            free(root);
        }else if(root->left == NULL){
            Node* temp = root->right;
            root->value = temp->value;
            root->right = NULL;
            free(temp);
        } else {
            Node* temp = root->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            root->value = temp->value;
            root->left = delNode(root->left, temp->value);
        }
    }
    return root;
}

int main(){
    Node* root = NULL;

    root = buildBST(root, 20);
    root = buildBST(root, 18);
    root = buildBST(root, 15);
    root = buildBST(root, 16);
    root = buildBST(root, 17);
    root = buildBST(root, 19);
    
    printf("Root-Val: %d\n", root->value);
    int val = search(root, 19);
    printf("%d ", val);

    puts("");
    
    delNode(root, 19);
    
    puts("");
    inOrder(root);

    return 0;
}