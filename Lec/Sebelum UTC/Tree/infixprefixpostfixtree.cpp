#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//  Declare Node
struct Node {
    char data;
    Node *left;
    Node *right;
};

// Create Node
Node *createNode(char value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value; // assign input to the data
    newNode->left = newNode->right = NULL;
    return newNode;
}

int hirearkiChar(char eq){   
    if (eq == '^'){
         return 3;
    } else if (eq == '/' || eq == '*'){
        return 2;
    } else if (eq == '+' || eq == '-') {
        return 1;
    }
}

//  Check if the character is an operator
int isOperator(char c){
    return(c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

struct nodes *push(char eq[], int max, int start){ // build tree
    int mid = buildInfixTree(eq, max, start); // search root
    if (mid < start || mid > max) return NULL; // if root not found
    struct nodes* root =  createnew(eq[mid]); // create new node
    printf("%c ", root->value);
    
    root->left = push(eq, mid-1, start); // left
    root->right = push(eq, max, mid+1); // right
    return root;
}

// Infix tree
int buildInfixTree(char *InfixEquation){ // Baca infix equation
    int len = strlen(InfixEquation); // Panjang InfixEquation
    int rootIndex = 0, hirearki = 0, saveIndex = 0;
    for (int i = 0; i < len; i++){
        if(isOperator(InfixEquation[i])){
            rootIndex = i;
            hirearki = hirearkiChar(InfixEquation[i]);
            if (hirearkiChar(InfixEquation[i]) > hirearkiChar(InfixEquation[rootIndex])){
                    hirearki = hirearkiChar(InfixEquation[i]);
                    rootIndex = i;
            }
       }
    }  
    return ; 
}

// Postfix Tree
Node* buildPostfixTree(char *PostfixEquation){ // Baca postfix equation
    Node* stack[105]; // Buat stack
    int top = -1; // Inisialisasi top
    for (int i = 0; i < strlen(PostfixEquation); i++){ // Selama i kurang dari panjang PostfixEquation
        Node *newNode = createNode(PostfixEquation[i]); // Buat node baru
        if(isdigit(PostfixEquation[i])){ // Jika karakter adalah integer
            stack[++top] = newNode; // Masukkan ke stack
        }else if (isOperator(PostfixEquation[i])) { // Jika karakter adalah operator
            newNode->right = stack[top--]; // Masukkan stack ke kanan
            newNode->left = stack[top--]; // Masukkan stack ke kiri
            stack[++top] = newNode; // Masukkan ke stack
        }
    }
    return stack[top]; // Kembalikan stack
}

// Prefix Tree
Node* buildPrefixTree(Node **root, char *PrefixEquation, int *position){ // Baca prefix equation
    if(*root == NULL){ // Jika root kosong
        *root = createNode(PrefixEquation[*position]); // Buat node baru
    }
    if(isOperator(PrefixEquation[*position])){ // Jika karakter adalah operator
        *position = *position + 1; // skip Posisi berikutnya
        (*root)->left = createNode(PrefixEquation[*position]); // Buat node kiri
        buildPrefixTree(&((*root)->left), PrefixEquation, position); // Rekursi left child
        *position = *position + 1; // skip Posisi berikutnya
        (*root)->right = createNode(PrefixEquation[*position]); // Buat node kanan
        buildPrefixTree(&((*root)->right), PrefixEquation, position); // Rekursi right child 
    }
    return *root; // Kembalikan root
}

// Infix
void inOrder(Node *root){
    if(root != NULL){
        if (isOperator(root->data)){
            putchar('(');
        }
        inOrder(root->left);
        printf("%c", root->data);
        inOrder(root->right);
        if (isOperator(root->data)){
            putchar(')');
        }
    }
}

// Prefix
void preOrder(Node *root){
    if(root != NULL){
        printf("%c ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Postfix
void postOrder(Node *root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->data);
    }
}

// Hasil perhitungan
int evaluate(Node *root){
    if (root == NULL){
        return 0;
    }

    int left = evaluate(root->left);
    int right = evaluate(root->right);

    if(root->data == '+'){
        return left + right;
    } else if(root->data == '-'){
        return left - right;
    }else if(root->data == '*'){
        return left * right;
    }else if(root->data == '/'){
        return left / right;
    }else if(root->data == '^'){
        return pow(left, right);
    } else {
        return root->data - '0';
    }
}

int main(){
    char InfixEquation[105] = "3+2*5-4";
    char PostfixEquation[105] = "32+54-*";
    char PrefixEquation[105] = "*+32-54";

    int position = 0;
    // Infix
    Node *rootInfix = NULL;
    *rootInfix = push(InfixEquation, strlen(InfixEquation), 0);
    printf("Infix Result: %d\n", evaluate(rootInfix));

    inOrder(rootInfix);
    printf("\n");
    postOrder(rootInfix);
    printf("\n");
    preOrder(rootInfix);
    printf("\n");

    /*
    // Postfix
    Node* rootPostfix = buildPostfixTree(PostfixEquation);
    printf("\nPostfix Result: %d\n", evaluate(rootPostfix));
    postOrder(rootPostfix);
    printf("\n");

    position = 0;
    // Prefix
    Node* rootPrefix = buildPrefixTree(&rootPrefix, PrefixEquation, &position);
    printf("\nPrefix Result: %d\n", evaluate(rootPrefix));
    preOrder(rootPrefix);
    */
    return 0;
}