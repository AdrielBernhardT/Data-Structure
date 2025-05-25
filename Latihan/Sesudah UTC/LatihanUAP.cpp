#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ETC getchar()

struct node{
	char name[101]; 
	int price; 
	char cate[20]; 
	char avail[20]; 
	int height; // Wajib
	node* left; // Wajib
	node* right; // Wajib
}*Node = NULL; 

int count = 0; 

node* createNode(char* name, int price, char* cate, char* avail){
	node* newNode = (node*)malloc(sizeof(node)); 
	strcpy(newNode->name, name); 
	strcpy(newNode->cate, cate); 
	strcpy(newNode->avail, avail); 
	newNode->price = price; 
	newNode->height = 1; // Wajib
	newNode->left = NULL; // Wajib
	newNode->right = NULL; // Wajib
	return newNode; 
}

int max(int a, int b){
	return a > b ? a : b; 
}

int height(node* root){
	return root? root->height : 0; 
}

int getBalanceFactor(node* root){
	return root? (height(root->left)-height(root->right)) : 0;
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


int validationName(char* name){
	if(strncmp(name, "Sally", 5) != 0 || strlen(name) < 10 || strlen(name) > 25){
		return -1; 
	}
	
	int space = 0, letterAfterSpace = 0, flag = 0, x = strlen(name); 
	
	for(int i=0; i<x; i++){
		if(name[i] == ' ' && flag == 0){
			space++; 
			flag = 1; 
		}
		if(name[i] != ' ' && flag == 1){
			letterAfterSpace++; 
			flag = 0; 
		}
	}
	
	if(space > 0 && letterAfterSpace > 0){
		return 1;
	} 
	
	return -1; 
}

node* insertAVL(node* root, node* newNode){
	if(root == NULL){ 
		return newNode; 
	} else if(strcmp(root->name, newNode->name) > 0){
		root->left = insertAVL(root->left, newNode); 
	} else if(strcmp(root->name, newNode->name) < 0){
		root->right = insertAVL(root->right, newNode); 
	} else return root; 
	
	root->height =  max(height(root->left), height(root->right)) + 1; 
	int balance = getBalanceFactor(root); 
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0){
			return rightRotate(root); // left left 
		} else{
			root->left = leftRotate(root->left); // left right 
			return rightRotate(root); 
		}
	}
	if(balance < -1){
		if(getBalanceFactor(root->right) <= 0){ 
			return leftRotate(root); // right right 
		} else{
			root->right = rightRotate(root->right); // right left 
			return leftRotate(root); 
		}
	}
	return root; 
}

node* deleteAVL(node* root, char* name){
	if(root == NULL){
		return NULL; 
	} else if(strcmp(root->name, name) > 0){
		root->left = deleteAVL(root->left, name); 
	} else if(strcmp(root->name, name) < 0){
		root->right = deleteAVL(root->right, name); 
	} else{
		if(root->left == NULL && root->right == NULL){ // Gapunya anak
			free(root); 
			return NULL;  
		} else if(root->left == NULL || root->right == NULL){ // Punya 1 anak
			node* temp = root->left ? root->left : root->right; 
			free(root); 
			return temp; 
		} else{ // Punya 2 anak
			node* temp = root->left; 
			
			while(temp->right){
				temp = temp->right; 
			}
			
			// copas nilai predecessor 
			strcpy(root->name, temp->name); 
			strcpy(root->cate, temp->cate); 
			strcpy(root->avail, temp->avail); 
			root->price = temp->price; 
			
			root->left = deleteAVL(root->left, temp->name);  
		}
	}
	
	// Copas Insert
	root->height =  max(height(root->left), height(root->right)) + 1; 
	int balance = getBalanceFactor(root); 
	
	if(balance > 1){
		if(getBalanceFactor(root->left) >= 0){
			return rightRotate(root); // left left 
		} else{
			root->left = leftRotate(root->left); // left right 
			return rightRotate(root); 
		}
	}
	if(balance < -1){
		if(getBalanceFactor(root->right) <= 0){
			return leftRotate(root); // right right 
		} else{
			root->right = rightRotate(root->right); // right left 
			return leftRotate(root); 
		}
	}
	return root; 
}

void preOrder(node* root){
	// Preorder: print -> left -> right
	if(root != NULL){
		printf("Treatment   : %s\n", root->name); 
		printf("Price       : %d\n", root->price); 
		printf("Category    : %s\n", root->cate); 
		printf("Availablity : %s\n", root->avail); 
		
		preOrder(root->left); 
		preOrder(root->right); 
	}
}

void inOrder(node* root){
	// inorder: left -> print -> right
	if(root != NULL){		
		inOrder(root->left); 
		
		printf("Treatment   : %s\n", root->name); 
		printf("Price       : %d\n", root->price); 
		printf("Category    : %s\n", root->cate); 
		printf("Availablity : %s\n", root->avail); 
		
		inOrder(root->right); 
	}
}

void postOrder(node* root){
	// postorder: left -> right -> print
	if(root != NULL){		
		postOrder(root->left); 		
		postOrder(root->right); 
		
		printf("Treatment   : %s\n", root->name); 
		printf("Price       : %d\n", root->price); 
		printf("Category    : %s\n", root->cate); 
		printf("Availablity : %s\n", root->avail); 
	}
}

void view(node* node){
	system("cls"); 
	if(node == NULL){
		printf("no data\n"); 
		return; 
	}
	
	char input[10]; 
	
	do{
		printf("insert view mode [pre | in | post]: "); 
		scanf("%s", input); getchar(); 
	} while(strcmp(input, "pre") != 0 && strcmp(input, "in") != 0 && 
		strcmp(input, "post") != 0); 
		
	if(strcmp(input, "pre") == 0){
		preOrder(node); 
	} else if(strcmp(input, "in") == 0){ 
		inOrder(node); 
	} else postOrder(node);  
	
	ETC;
}

node* alreadyInTree(node* root, char* target){
	if(root == NULL){
		return NULL;  // Kalau abis
	}else if(strcmp(root->name, target) == 0){
		return root; // Cek sama
	} else if(strcmp(root->name, target) < 1){
		return alreadyInTree(root->left, target);
	} else {
		return alreadyInTree(root->right, target);
	}
}


node* del(node* root){
	system("cls"); 
	if(root == NULL){
		printf("no data\n"); 
		ETC; 
		return root; 
	}
	
	char name[101]; 
	
	printf("DELETE TREATMENT\n"); 
	printf("insert name to be deleted: "); 
	scanf("%[^\n]", name); getchar(); 
	
	if(alreadyInTree(root, name)){
		root = deleteAVL(root, name); 
		printf("[Data successfully deleted]\n"); 
		count--; 
	}
	else{
		printf("Data does not exist!\n"); 
	}
	ETC;
	
	return root; 
}

int main(){
	int choice = -1; 
	
	do{
		do{
			printf("Sally Salon\n"); 
			printf("======================\n"); 
			printf("Menu:\n"); 
			printf("1. View Available Treatment\n"); 
			printf("2. Insert New Treatment\n"); 
			printf("3. Delete Treatment\n"); 
			printf("4. Exit\n"); 
			printf("[1-4]\n"); 
			printf(">> "); 
			scanf("%d", &choice); getchar(); 
			
		} while(choice < 1 || choice > 4); 
		
		if (choice == 1){
				view(Node); 
				break; 
		}else if(choice == 2){
			char name[101], cate[20], avail[20]; 
			int price; 
			
			do{
				printf("insert name: "); 
				scanf("%[^\n]", name); getchar(); 
			} while(validationName(name) == -1); 
			
			do{
				printf("insert price [50.000 - 1.000.000]: "); 
				scanf("%d", &price); getchar(); 
			} while(price < 50000 || price > 1000000); // inclusive 
			
			do{
				printf("insert category [Hair Care | Nail Care | Body Care]: "); 
				scanf("%[^\n]", cate); getchar(); 
			} while(strcmp(cate, "Hair Care") != 0  && strcmp(cate, "Nail Care") != 0 &&
					strcmp(cate, "Body Care") != 0); // case sensitive 
					
			do{
				printf("insert availability: "); 
				scanf("%s", avail); getchar(); // case sensitive 
			} while(strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0); 
			
			node* newNode = createNode(name, price, cate, avail); 
			Node = insertAVL(Node, newNode); 
			
			printf("[New Treatment is Successfully Inserted]\n"); 
			ETC; 

			count++;  
		}else if(choice == 3){ 
			Node = del(Node); 
		}
	} while(choice != 4); 
	return 0; 
}