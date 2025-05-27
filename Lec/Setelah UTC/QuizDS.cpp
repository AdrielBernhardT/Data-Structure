#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Priority {
    int score;    
    int acheive;  
    int id;      
};

struct node{
    int id; 
    int exam_pass;
    int have_c_grade;
    int international_acheivements;
    int height;
    int priority;
    node* left;
    node* right;
} *curr = NULL, *headRoot = NULL;

int counter = 0;

struct Queue{
    int id; 
    int exam_pass;
    int have_c_grade;
    int international_acheivements;
    int convert;
    Queue* next;
    Queue* prev;
} *head, *tail, *currQueue;

void insertQueue(int id, int exam_pass, int have_c_grade, int international_acheivements){
    currQueue = (Queue*)malloc(sizeof(Queue));
    currQueue->id = id;
    currQueue->exam_pass = exam_pass;
    currQueue->have_c_grade = have_c_grade;
    currQueue->international_acheivements = international_acheivements;
    if (exam_pass==1 && have_c_grade==0){
        currQueue->convert = 0;
    } else if (exam_pass==1 && have_c_grade==1){
        currQueue->convert = 1; 
    } else if (exam_pass==0 && have_c_grade==0){
        currQueue->convert = 2; 
    } else if(exam_pass==0 && have_c_grade==1){
        currQueue->convert = 3; 
    }
    currQueue->next = NULL;
    currQueue->prev = NULL;
    if (!head) {
        head = tail = currQueue;
    } else if (head->convert > currQueue->convert) {
        currQueue->next = head;
        head->prev = currQueue;
        head = currQueue;
    } else if (tail->convert <= currQueue->convert) {
        tail->next = currQueue;
        currQueue->prev = tail;
        tail = currQueue;
    } else {
        Queue* temp = head;
        while (temp->convert <= currQueue->convert) {
            temp = temp->next;
        }
        currQueue->next = temp;
        currQueue->prev = temp->prev;
        temp->prev->next = currQueue;
        temp->prev = currQueue;
    }
    currQueue = NULL;
}

//  =================== End Queue Function ==================

// ================== AVL Tree ==================

int max(int a, int b){
    return a > b ? a : b;
}

int height(node* root){
    return root ? root->height : 0;
}

int getBalance(node* root){
    return root ? (height(root->left) - height(root->right)) : 0;
}

node* rightRotate(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* leftRotate(node* y){
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* createNode(Queue* q){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->id = q->id;
    newNode->exam_pass = q->exam_pass;
    newNode->have_c_grade = q->have_c_grade;
    newNode->international_acheivements = q->international_acheivements;
    newNode->height = 1;
    newNode->priority = counter++;
    newNode->left = newNode->right = NULL;
    return newNode;
}

node* Insert(node* root, node* newNode){
    if (root == NULL) return newNode;
    
    if (newNode->priority > root->priority || (newNode->priority == root->priority && (newNode->international_acheivements > root->international_acheivements)))
        root->left = Insert(root->left, newNode);
    else if (newNode->priority < root->priority || (newNode->priority == root->priority && (newNode->international_acheivements < root->international_acheivements)))
        root->right = Insert(root->right, newNode);
    else
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (getBalance(root->right) <= 0)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void popQueue(int id) {
    Queue* temp = head;
    while (temp && temp->id != id) {
        temp = temp->next;
    }

    if (!temp) {
        return;
    }

    if (temp == head) {
        head = head->next;
        if (head) {
            head->prev = NULL;
        } else {
            tail = NULL;
        }
    } else if (temp == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        temp->prev->next = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
    }
    
    free(temp);
}

void popTailtoAVL() {
    if (!tail) return;

    printf("Popping ID: %d\n", tail->id);

    node* newNode = createNode(tail);
    headRoot = Insert(headRoot, newNode);

    popQueue(tail->id);
}

// =============================== View AVL inOrder ==============================


void InOrder(node* root) {
    if (root) {
        InOrder(root->left);
        printf("%d ", root->id);
        InOrder(root->right);
    }
}

void preOrder(node* root) {
    if (root) {
        printf("%d ", root->id);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->id);
    }
}

// ============================== AVL Tree function end ==============================

int main(){
    int N;
    char function[5];
    int id; 
    int exam_pass;
    int have_c_grade;
    int international_acheivements;
    scanf("%d", &N); getchar();
    for (int i = 0; i < N; i++) {
        scanf("%s", function); getchar();
        if(strcmp(function,"i") == 0){
            scanf("%d %d %d %d", &id, &exam_pass, &have_c_grade, &international_acheivements); getchar();
            insertQueue(id, exam_pass, have_c_grade, international_acheivements);
        } else if(strcmp(function,"d") == 0){
            scanf("%d", &id); getchar();
            popQueue(id);
        }
    }
    
    printf("Queue (priority->not):\n");
    while (tail){
        popTailtoAVL();
    }
    
    // printf("AVL Tree InOrder: ");
    InOrder(headRoot);
    // printf("\nAVL Tree PreOrder: ");
    // preOrder(headRoot);
    // printf("\nAVL Tree PostOrder: ");
    // postOrder(headRoot);
    printf("\n");
    return 0;
}