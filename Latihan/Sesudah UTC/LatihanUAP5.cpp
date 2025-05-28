#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char name[50];
    long price;
    char category[25];
    char availability[15];
    int height;
    node* left;
    node* right;
} *curr, *headRoot;


int height(node* root){
    return root? root->height:0;
}

int getBalance (node* root) {
    return root? height(root->left)-height(root->right) : 0;
}

int max(int a, int b) {
    return a>b? a:b;
}

int isAlpha (char alpha) {
    return (alpha >= 'a' && alpha <= 'z') || (alpha >= 'a' && alpha <= 'z')? 1 : 0;
}

int isSpace (int len) {
    for (int i = 0; i < len; i++) {
        if (curr->name[i] == ' ' && isAlpha(curr->name[i+1])) return 1;
    }
    return 0;
}

int nameVal() {
    int len = strlen(curr->name);
    if (len < 5 || len > 20 || strncmp(curr->name, "Sally", 5) != 0 || !isSpace(len)) return 0;
    return 1;
}

int priceVal () {
    return curr->price >= 50000 && curr->price <= 1000000? 1 : 0;
}

int catVal () {
    return strcmp(curr->category, "Hair Care") != 0 && strcmp(curr->category, "Nail Care") != 0 && strcmp(curr->category, "Body Care") != 0 ? 0:1;
}

int availVal() {
    return strcmp(curr->availability,"Available") != 0 && strcmp(curr->availability,"Available") != 0 ? 0 : 1;
}

node* rotateRight (node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

node* rotateLeft (node* y) {
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

node* createNode (node* root) {
    curr = (node*)malloc(sizeof(node));
    do {
        printf("Input treatment name: ");
        scanf("%[^\n]", curr->name); getchar();
    } while (!nameVal());
    
    do {
        printf("Input treatment price: ");
        scanf("%ld", &curr->price); getchar();
    } while (!priceVal());

    do {    
        printf("Input treatment category: ");
        scanf("%[^\n]", curr->category); getchar();
    } while (!catVal());

    do {   
        printf("Input availablity for home service: ");
        scanf("%s", curr->availability); getchar();
    } while (!availVal);

    return curr;
}

node* Insert(node* root){
    if (!root) {
        return NULL;
    } 
    if (strcmp(curr->name,root->name) < 0) {
        root->left = Insert(root->left);
    } else if (strcmp(curr->name,root->name) > 0) {
        root->right = Insert(root->right);
    } else {
        return root;
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateRight(root->right);
        }
    }
    return root;
}

void inOrder (node* root) {
    if (root) {
        inOrder(root->left);

        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->category); 
		printf("Availablity : %s\n", root->availability);

        inOrder(root->right);
    }
}

void preOrder (node* root) {
    if (root) {
        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->category); 
		printf("Availablity : %s\n", root->availability);
        
        inOrder(root->left);
        inOrder(root->right);
    }
}

void postOrder (node* root) {
    if (root) {
        inOrder(root->left);
        inOrder(root->right);

        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->category); 
		printf("Availablity : %s\n", root->availability);
    }
}

void View(node* root){
    if (!root) {
        printf("No Data\n");
        return;
    }
    
    char choose[10];
    do{
        printf("input view order [pre | in | post]: "); 
        scanf("%s", choose); getchar();
    } while(strcmp(choose,"pre")!=0 && strcmp(choose,"post")!=0 && strcmp(choose,"in")!=0);

    if(strcmp(choose,"pre")==0){
        preOrder(root);
    } else if(strcmp(choose,"post")==0){
        postOrder(root);
    }  else{
        inOrder(root);
    }   
}

node* DeleteAVL (node* root, char* target) {
    if (!root) {
        return NULL;
    }
    if (strcmp(target, root->name) < 0) {
        root->left = DeleteAVL(root->left, target);
    } else if (strcmp(curr->name,root->name) > 0) {
        root->right = DeleteAVL(root->right, target);
    } else {
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        } else if (!root->left || !root->right) {
            node* temp = root->left?root->left:root->right;
            free(root);
            return temp;
        } else {
            node *temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }

            strcpy(root->name,temp->name);
            strcpy(root->category,temp->category);
            strcpy(root->availability,temp->availability);
            root->price = temp->price;

            root->left = DeleteAVL(root->left, temp->name);
        }
    }

    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    } else if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateRight(root->right);
        }
    }
    return root;
}

node* Delete (node* root) {
    if (!root) {
        printf("No Data\n");
        return root;
    }
    char target[50];
    printf("Delete Treatment: ");
    scanf("%[^\n]", target); getchar();
    node* newRoot = DeleteAVL(headRoot, target);

    if (newRoot == headRoot) {
        printf("No Data Found");
    } else {
        printf("Sucessfully Deleted\n");
    }

    return newRoot;
}

int main(){
    int choice;
    do {
        printf("SALLY SALON\n");
        printf("Menu:\n");
        printf("1. Input Treatment\n");
        printf("2. View Treatment\n");
        printf("3. Delete Treatment\n");
        printf("4. Exit\n");
        do {
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 4);

        if (choice == 1) {
            headRoot = Insert(headRoot);
        } else if (choice == 2) {
            View(headRoot);
        } else if (choice == 3) {
            headRoot = Delete(headRoot);
        } else {
            printf("Bye\n");
        }
    } while (choice != 4);
    return 0;
}