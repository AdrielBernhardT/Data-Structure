#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct nodes{
    char value;
    nodes* right;
    nodes* left;
};


int evaluate(nodes* root){ // Hitung hasil
    if(root->value == '+'){
        return evaluate(root->left) + evaluate(root->right);
    }
    else if(root->value == '-'){
        return evaluate(root->left) - evaluate(root->right);
    }
    else if(root->value == '*'){
        return evaluate(root->left) * evaluate(root->right);
    }
    else if(root->value == '/'){
        return evaluate(root->left) / evaluate(root->right);
    }
    else if(root->value == '^'){
        return (int) pow(evaluate(root->left), evaluate(root->right));
    }
    else{
        return root->value - '0';
    }
}

int value_converter(char eq){ // hirearki operator
    int value;
    
    if (eq == '^') value = 3;
    if (eq == '/' || eq == '*') value = 2;
    if (eq == '+' || eq == '-') value = 1;

    return value;
}

int is_opt(char eq) { // isOperator
    return (eq == '+' || eq == '-' || eq == '*' || eq == '/' || eq == '^');
}

void Infix(struct nodes* root) { // print infix
    if (root == NULL) return; // kalau ga ada root
    if (is_opt(root->value)) printf("("); // kalau ada operator maka print (
    Infix(root->left); // print left child
    printf("%c ", root->value); // print root
    Infix(root->right); // print right child
    if (is_opt(root->value)) printf(")"); // kalau ada operator maka print )
}

int search_root(char eq[], int start, int end){ // cari operator dengan hirearki terendah
    int index_t = strlen(eq), value_t = 10; // index_t = index terkecil, value_t = value terkecil

    int index_n, value_n; // index_n = index sementara, value_n = value sementara
    if (end == start) return start; // kalau start = end maka return start

    for (int i = start ; i >= end ; i--){  
        if (is_opt(eq[i])) { // kalau eq[i] adalah operator
            index_n = i, value_n = value_converter(eq[i]); // index_n = i, value_n = hirearki operator

            if (index_n < index_t && value_n < value_t){ // kalau index_n < index_t dan value_n < value_t
                index_t = index_n, value_t = value_n; // index_t = index_n, value_t = value_n
            }
        }
    }
    return index_t; // return index_t
}

struct nodes* createnew(char value){ // buat node baru
    nodes *curr = (nodes *) malloc (sizeof(nodes));
    curr->value = value; // isi value
    curr->left = curr->right = NULL; // left dan right = NULL
    return curr; // return curr
}

struct nodes *push(char eq[], int max, int start){
    int mid = search_root(eq, max, start);
    if (mid < start || mid > max) return NULL;
    struct nodes* root =  createnew(eq[mid]);
    printf("%c ", root->value);
    
    root->left = push(eq, mid-1, start);
    root->right = push(eq, max, mid+1);
    return root;
}


int main(){
    char eq[] = "8*3-5^3/5";
    nodes* root = NULL;
    int max = strlen(eq)-1;
    // printf("%c",search_root(eq));
    printf("PostFix Notation : ");
    root =  push(eq, max, 0);
    puts("");

    printf("InFix Notation : ");
    Infix(root);
    puts("");

    printf("Evaluate : %d\n", evaluate(root));
}