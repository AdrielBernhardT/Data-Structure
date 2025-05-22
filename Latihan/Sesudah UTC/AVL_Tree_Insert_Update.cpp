#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct mahasiswa{
	int age;
	char name[100];
	mahasiswa *left;
	mahasiswa *right;
	int height;
} *curr;

mahasiswa *assignToCurr(int age, const char *name){
	curr = (mahasiswa*)malloc(sizeof(mahasiswa));
	curr->age = age;
	strcpy(curr->name, name);
	curr->left = NULL;
	curr->right = NULL;
	
	return curr;
}

int max(int a, int b){
	return (a>b) ? a : b;
}

int getHeight(mahasiswa *curr){
	if(!curr){
		return 0;
	} else {
		return curr->height;
	}
}

mahasiswa *rightRotate(mahasiswa *curr){
	mahasiswa *currLeft = curr->left;
	mahasiswa *currLeftRight = curr->left->right;
	
	curr->left->right = curr;
	curr->left = currLeftRight;
	
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));
	
	return currLeft;
}

mahasiswa *leftRotate(mahasiswa *curr){
	mahasiswa *currRight = curr->right;
	mahasiswa *currRightLeft = curr->right->left;
	
	curr->right->left = curr;
	curr->right = currRightLeft;
	
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	currRight->height = 1 + max(getHeight(currRight->left), getHeight(currRight->right));
	
	return currRight;
}

int getBalance(mahasiswa *curr){
	return (getHeight(curr->left) - getHeight(curr->right));
}

mahasiswa *insertAVL(mahasiswa *curr, int age, char *name){
	if(curr == NULL){
		return assignToCurr(age, name);
	}
	
	if(age < curr->age){
		curr->left = insertAVL(curr->left, age, name);
	} else if(age > curr->age){
		curr->right = insertAVL(curr->right, age, name);
	}
	
	// update height
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	
	// identify imbalance case
	if(getBalance(curr) > 1 && getBalance(curr->left) > 0){ // LL
	// Right rotate
		return rightRotate(curr);
	} else if(getBalance(curr) < -1 && getBalance(curr->right) < 0){ // RR
	// Left rotate	
		return rightRotate(curr);
	} else if(getBalance(curr) > 1 && getBalance(curr->left) < 0){ // LR
	// Left rotate subtree, right rotate tree
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	} else if(getBalance(curr) < -1 && getBalance(curr->right) > 0){ // RL
	// Right rotate subtree, left rotate tree
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

void inOrder(mahasiswa *curr){
	if(curr == NULL){
		return;
	}
	inOrder(curr->left);
	printf("Age: %d, Name: %s\n", curr->age, curr->name);
	inOrder(curr->right);
}

void postOrder(mahasiswa *curr){
	if(curr == NULL){
		return;
	}
	postOrder(curr->left);
	postOrder(curr->right);
	printf("Age: %d, Name: %s\n", curr->age, curr->name);
}

void preOrder(mahasiswa *curr){
	if(curr == NULL){
		return;
	}
	printf("Age: %d, Name: %s\n", curr->age, curr->name);
	preOrder(curr->left);
	preOrder(curr->right);
}

void updateTree(mahasiswa *root, int age, const char *newName){
	if(!root){
		printf("Not Found!\n");
	} else if(age<root->age){
		updateTree(root->left, age, newName);
	} else if(age>root->age){
		updateTree(root->right, age, newName);
	} else if(age == root->age){
		strcpy(root->name, newName);
		printf("Name Update!\n");
	}
}

int main(){
	// AVL Tree -> (BST + Self Balancing)
	// cek terus kalo left right ga balance	
	curr = insertAVL(curr, 20, "Adriel");
	curr = insertAVL(curr, 19, "Jio");
	curr = insertAVL(curr, 17, "Jonea");
	curr = insertAVL(curr, 21, "Rio");
	curr = insertAVL(curr, 12, "Sumi");
	
	inOrder(curr);
	
	updateTree(curr, 12, "Joko");
	inOrder(curr);
			
	return 0;
}
