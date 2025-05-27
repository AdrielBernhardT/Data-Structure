#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id, exam_pass, c_grade, achievements, score;
    int height;
    struct Node *left, *right;
} Node;


int getScore(int exam_pass, int c_grade) {
    if (exam_pass == 0 && c_grade == 1) return 0;
    if (exam_pass == 0 && c_grade == 0) return 1;
    if (exam_pass == 1 && c_grade == 1) return 2;
    if (exam_pass == 1 && c_grade == 0) return 3;
    return -1;
}

// ========================= AVL Tree Functions =========================
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *n) {
    return n ? n->height : 0;
}

Node* createNode(int id, int e, int c, int a) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->exam_pass = e;
    newNode->c_grade = c;
    newNode->achievements = a;
    newNode->score = getScore(e, c);
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

int isHigher(Node* a, Node* b) {
    if (a->score != b->score)
        return a->score > b->score;
    if (a->achievements != b->achievements)
        return a->achievements > b->achievements;
    return a->id < b->id;
}

Node* insert(Node* root, Node* newNode) {
    if (!root) return newNode;

    if (isHigher(newNode, root))
        root->left = insert(root->left, newNode);
    else
        root->right = insert(root->right, newNode);

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && isHigher(newNode, root->left)) return rightRotate(root);
    if (balance < -1 && !isHigher(newNode, root->right)) return leftRotate(root);
    if (balance > 1 && !isHigher(newNode, root->left)) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && isHigher(newNode, root->right)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* minValueNode(Node* root) {
    Node* curr = root;
    while (curr->left) curr = curr->left;
    return curr;
}

Node* deleteNode(Node* root, int id) {
    if (!root) return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) temp = root, root = NULL;
            else *root = *temp;
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            *root = *temp;
            root->right = deleteNode(root->right, temp->id);
        }
    }

    if (!root) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int count = 0;
void getTop3(Node* root) {
    if (!root || count >= 3) return;
    getTop3(root->left);  // highest priority on left
    if (count < 3) {
        printf("%d ", root->id);
        count++;
    }
    getTop3(root->right);
}



int main() {
    int n;
    scanf("%d", &n);
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        char op[2];
        scanf("%s", op);
        if (strcmp(op, "i") == 0) {
            int id, e, c, a;
            scanf("%d %d %d %d", &id, &e, &c, &a);
            root = insert(root, createNode(id, e, c, a));
        } else if (strcmp(op, "d") == 0) {
            int id;
            scanf("%d", &id);
            root = deleteNode(root, id);
        }
    }
    getTop3(root);
    printf("\n");
    return 0;
}
