#include <stdio.h>
#include <stdlib.h>

struct BstNode{
    int data;
    BstNode* Left;
    BstNode* Right;
};

BstNode* GetNewNode(int input){
    BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
    newNode->data = input;
    newNode->Left = newNode->Right = NULL;
    return newNode;
}

BstNode* Insert(BstNode* root, int input){ // root disini artinya dia mau di sambungin ke mana
    if (root == NULL){
        root = GetNewNode(input);
        return root;
    }
    else if (input <= root->data){
        root->Left = Insert(root->Left, input); // recursive buat manggil anakannya
    }
    else {
        root->Right = Insert(root->Right, input);
    }
    return root;
}

bool search(BstNode* root, int Dicari){
    if (root == NULL){
        return false;
    }
    else if(root->data == Dicari){
        return true;
    } else if(root->data < Dicari){
        return search(root->Left, Dicari);
    } else {
        return search(root->Right, Dicari);
    }
    
}

int main(){
    BstNode* rootPtr; // pointer to root node
    rootPtr = NULL; // Set tree is empty
    rootPtr = Insert(rootPtr, 15);
    rootPtr = Insert(rootPtr, 10);
    rootPtr = Insert(rootPtr, 20);
    return 0;
}