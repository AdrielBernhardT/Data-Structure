#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char name[50];
    // long price;
    // char cat[15];
    // char avail[15];
    node* left;
    node* right;
    int height;
} *curr = NULL;

void View();
node* Insert(node* root, char* name);
node* Delete();

// ---------------------------------------

node* createNode(node* root, char* name){
    curr = (node*)malloc(sizeof(node));
    strcpy(curr->name,name);
    // curr->price = price;
    // strcpy(curr->cat,cat);
    // strcpy(curr->avail,avail);
    curr->left = NULL;
    curr->right = NULL;
    curr->height = 1;
    return root;
}

int isSpace(char* name){
    int len = strlen(name);
    for(int i = 0; i < len; i++){
        if(name[i] == ' ' && (name[i+1] != ' '||name[i+1] != '\n')){
            return 1;
        }
    }
    return 0;
}

int isLong(char* name){
    int len = strlen(name);
    if(len < 5 || len > 20){
        return 0;
    }
    return 1;
}

int nameVal(char* name){
    if(!isSpace(name) || !isLong(name) || !strncmp(name, "Sally", 5)){
        return 0;
    }
    return 1;
}

int height(node* root){
    return root? root->height : 0;
}

int getBalance(node* root){
    return root? (height(root->left)-height(root->right)) : 0;
}

int max(int a, int b){
    return a>b?a:b;
}

node* rightRotate(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;
}

int main(){
    int choice;
    do{
        printf("SALLY SALON\n");
        printf("Menu:\n");
        printf("1. View Available Treatment\n");
        printf("2. Insert New Treatment\n");
        printf("3. Delete Treatment\n");
        printf("4. Exit\n");
        printf("[1-4]\n");
        do{ 
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while(choice < 1 || choice > 4);
        
        if(choice == 1){
            View();
        } else if(choice == 2){
            
        } else if(choice == 3){
            
        }
    } while(choice != 4);
    return 0;
}