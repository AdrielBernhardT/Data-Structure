#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Buat Node & Curr
struct mahasiswa{
	int age;
	char name[100];
	mahasiswa *left;
	mahasiswa *right;
	int height;
} *curr;

// Buat function Assign to Curr untuk mengisi curr dengan data
mahasiswa *assignToCurr(int age, const char *name){
	curr = (mahasiswa*)malloc(sizeof(mahasiswa));
	curr->age = age;
	strcpy(curr->name, name);
	curr->left = NULL;
	curr->right = NULL;
	
	return curr;
}

// Buat function max untuk mencari nilai max dari 2 angka
int max(int a, int b){
	return (a>b) ? a : b;
}

// Buat function getHeight untuk mendapatkan tinggi dari node
int getHeight(mahasiswa *curr){
	if(!curr){
		return 0;
	} else {
		return curr->height;
	}
}

// -------------------------------------------------------------------------------------------------------------
// curr = x
// currLeft = y
// currLeftRight = T2

// Buat function rightRotate untuk melakukan right rotation
mahasiswa *rightRotate(mahasiswa *curr){
	mahasiswa *currLeft = curr->left; // assign currLeft dengan curr->left
	mahasiswa *currLeftRight = curr->left->right; // assign currLeftRight dengan curr->left->right
	
	curr->left->right = curr; // curr->left->right = curr
	curr->left = currLeftRight; // curr->left = currLeftRight
	
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));
	
	return currLeft;
}

// -------------------------------------------------------------------------------------------------------------

// curr = x
// currRight = y
// currRightLeft = T2

// Buat function leftRotate untuk melakukan left rotation
mahasiswa *leftRotate(mahasiswa *curr){
	mahasiswa *currRight = curr->right;
	mahasiswa *currRightLeft = curr->right->left;
	
	curr->right->left = curr;
	curr->right = currRightLeft;
	
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	currRight->height = 1 + max(getHeight(currRight->left), getHeight(currRight->right));
	
	return currRight;
}

// -------------------------------------------------------------------------------------------------------------

// Buat function getBalance untuk mendapatkan balance dari node
int getBalance(mahasiswa *curr){
	return (getHeight(curr->left) - getHeight(curr->right));
}

// Buat function insertAVL untuk melakukan insert data ke dalam AVL Tree
mahasiswa *insertAVL(mahasiswa *curr, int age, char *name){
	if(curr == NULL){
		return assignToCurr(age, name);
	}
	
	// insert data
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

// Delete Node AVL Tree
mahasiswa *minValueNode(mahasiswa *node) {
	mahasiswa *current = node; // assign current ke node yang mau di delete
	while (current->left != NULL){ // selama current->left tidak NULL
		current = current->left; // assign current ke current->left
	} 
	return current; // return current
}

mahasiswa *deleteNode(mahasiswa *root, int age) {
	if (root == NULL){ // jika ga ada root atau avl tree kosong
		return root;
	}

	if (age < root->age) // jika age dicari lebih kecil dari root->age
		root->left = deleteNode(root->left, age); // cari di left
	else if (age > root->age) // jika age dicari lebih besar dari root->age
		root->right = deleteNode(root->right, age); // cari di right
	else { // jika ketemu
		if ((root->left == NULL) || (root->right == NULL)) { // jika left atau right dari root NULL
			mahasiswa *temp = root->left ? root->left : root->right; // assign temp ke root->left jika root->left tidak NULL, jika NULL assign ke root->right
			if (temp == NULL) { // jika temp NULL karena ga ada anak kanan sama kiri
				temp = root; // assign temp ke root
				root = NULL; // assign root ke NULL
			} else // jika ada 1 anak kiri atau anak kanan yang masih ada
				*root = *temp; // assign root ke temp
			free(temp); // free temp
		} else { // jika ada 2 anak
			mahasiswa *temp = minValueNode(root->right); // assign temp ke minValueNode dari root->right
			// Assign isi dari root dengan isi dari temp
			root->age = temp->age; 
			strcpy(root->name, temp->name);
			// Delete node yang sudah di assign ke root
			root->right = deleteNode(root->right, temp->age); 
		}
	}

	if (root == NULL){
		return root;
	}

	root->height = 1 + max(getHeight(root->left), getHeight(root->right)); // update height

	int balance = getBalance(root); // get balance factor

	if (balance > 1 && getBalance(root->left) >= 0) // LL 
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0) { // LR
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0) // RR
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0) { // RL
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
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
