#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char name[50];
    long price;
    char category[25];
    char availability[20];
    int height;
    node* left;
    node* right;
} *headRoot, *curr;
 
int max(int a, int b) { 
    return a>b?a:b;
}

int height(node* root) {
    return root?root->height:0;
}

int getBalance(node* root) {
    return root?(height(root->left)-height(root->right)):0;
}

node* rotateLeft(node *y) {
    node *x = y->right;
    node *T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* rotateRight(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

int isAlpha(char character){
    if((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) return 1;
    return 0;
}

int isSpace(char* name, int len){
    for(int i = 0; i < len; i++){
        if(name[i] == ' ' && isAlpha(name[i+1])) return 1;
    }
    return 0;
}

int nameVal(char *name){
    int len = strlen(name);
    if(len < 5 || len > 20 || strncmp(name, "Sally", 5) != 0 || !isSpace(name, len)) return 0;
    return 1;
}

int priceVal(long price){
    if(price < 50000 || price > 1000000) return 0;
    return 1;
}

int catVal(char *cat){
    if(strcmp(curr->category, "Hair Care") != 0 && strcmp(curr->category, "Nail Care") != 0 && strcmp(curr->category, "Body Care") != 0) return 0;
    return 1;
}

int availVal(char *avail){
    if(strcmp(curr->availability, "Available") != 0 && strcmp(curr->availability, "Unavailable") != 0) return 0;
    return 1;
}

node* createNode(){
    curr = (node*)malloc(sizeof(node));
    do{
        printf("input new treatment name: ");
        scanf("%[^\n]", curr->name); getchar();
    } while (!nameVal(curr->name));
    do{
        printf("input treatment price [50000 - 1000000]: ");
        scanf("%ld", &curr->price); getchar();
    } while (!priceVal(curr->price));
    do{
        printf("input treatment category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", curr->category); getchar();
    } while (!catVal(curr->category));
    do{
        printf("input treatment availability for home service [Available | Unavailable]: ");
        scanf("%s", curr->availability); getchar();
    } while (!availVal(curr->availability));

    return curr;
}

node* Insert(node* root) {
    if(!root) {
        return createNode();
    }
    if(strcmp(curr->name, root->name) < 0) {
        root->left = Insert(root->left);
    } else if(strcmp(curr->name, root->name) > 0) {
        root->right = Insert(root->right);
    } else {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);
    if(balance > 1) {
        if(getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } 
    if(balance < -1) {
        if(getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

void inOrder(node* root){
    if(root){
        inOrder(root->left);
        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->category); 
		printf("Availablity : %s\n", root->availability);
        inOrder(root->right);
    }
}

void preOrder(node* root){
    if(root){
        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->category); 
		printf("Availablity : %s\n", root->availability);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(node* root){
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->category); 
		printf("Availablity : %s\n", root->availability);
    }
}

int viewVal(char* choose){
    if(strcmp(choose, "pre") != 0 && strcmp(choose, "in") != 0 && strcmp(choose, "post") != 0) return 0;
    return 1;
}

void View(){
    char choose[10];
    do{
        printf("input view order [pre | in | post]: ");
        scanf("%s", choose); getchar();
    } while (!viewVal(choose));

    if(strcmp(choose, "pre") == 0) {
        preOrder(headRoot);
    } else if(strcmp(choose, "in") == 0) {
        inOrder(headRoot);
    } else {
        postOrder(headRoot);
    }
}

node* deleteAVL(node* root, char* target){
    if (!root) {
        printf("No Data\n");
        return NULL;
    }
    if (strcmp(target, root->name) < 0) {
        root->left = deleteAVL(root->left, target);
    } else if (strcmp(target, root->name) > 0) {
        root->right = deleteAVL(root->right, target);
    } else {
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        } else if (!root->left || !root->right) {
            node* temp = root->left? root->left:root->right;
            free(root);
            return temp; 
        } else {
            node* temp = root->left;
            while(temp->right){
                temp = temp->right;
            }
            strcpy(root->name,temp->name);
            root->price = temp->price;
            strcpy(root->availability,temp->availability);
            strcpy(root->category,temp->category);
            
            root->left = deleteAVL(root->left, temp->name);
        }
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);
    if(balance > 1) {
        if(getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } 
    if(balance < -1) {
        if(getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

node* Delete(){
    printf("DELETE TREATMENT\n");
    if(!headRoot){
        printf("No Data");
        return headRoot;
    }
    char target[50];
    printf("input treatment name to be deleted: ");
    scanf("%[^\n]", target); getchar();
    
    node *newRoot = deleteAVL(headRoot, target);
    if (newRoot == headRoot) {
        printf("Data not found!\n");
    } else {
        printf("[Data successfully deleted]\n");
    }

    return newRoot;
}

int main(){
    int choice;
    do{
        printf("Sally Salon\n");
        printf("Menu\n");
        printf("1. Insert Treatment\n");
        printf("2. View Treatment\n");
        printf("3. Delete Treatment\n");
        printf("4. Exit\n");
        do{
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 ||choice > 4);
        if(choice == 1) {
            headRoot = Insert(headRoot);
            printf("\n[New Treatment is sucessfully inserted]\n");
            printf("Press enter to continue...");
            getchar();
        } else if(choice == 2) {
            View();
        } else if(choice == 3) {
            headRoot = Delete();
        } else {
            printf("Bye-Bye\n");
        }
    } while (choice != 4);

    return 0;
}