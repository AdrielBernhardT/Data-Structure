#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc getchar()

struct node{
    char name[50];
    long price;
    char cat[25];
    char avail[25];
    int height;
    node* left;
    node* right;
} *curr = NULL;

// =============== VIEW REQUIREMENT ===================
void infix(node* root){
    if(root){
        infix(root->left);

        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->cat); 
		printf("Availablity : %s\n", root->avail);
        
        infix(root->right);
    }
}

void prefix(node* root){
    if(root){
        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->cat); 
		printf("Availablity : %s\n", root->avail);
        
        prefix(root->left);

        prefix(root->right);
    }
}

void postfix(node* root){
    if(root){
        postfix(root->left);

        postfix(root->right);
        
        printf("Treatment   : %s\n", root->name); 
		printf("Price       : %ld\n", root->price); 
		printf("Category    : %s\n", root->cat); 
		printf("Availablity : %s\n", root->avail);
    }
}

void View(node* root){
    if(!root){
        printf("no data\n");
        return;
    }

    char choose[10];
    do{
        printf("input view order [pre | in | post]: "); 
        scanf("%s", choose); gc;
    } while(strcmp(choose,"pre")!=0 && strcmp(choose,"post")!=0 && strcmp(choose,"in")!=0);

    if(strcmp(choose,"pre")==0){
        prefix(root);
    } else if(strcmp(choose,"post")==0){
        postfix(root);
    }  else{
        infix(root);
    }   
}
// =============== END VIEW REQUIREMENT ===================



// =============== INSERT REQUIREMENT ===================

// Validation
bool isSpace(char* name){
    int len = strlen(name);
    for(int i = 0; i < len; i++){
        if (name[i] == ' ' && (name[i+1] != ' ' || name[i+1] != '\n')){
            return true;
        }
    }
    return false;
}

int nameVal(char* name){
    int len = strlen(name);
    if (!isSpace(name) || strncmp(name, "Sally", 5) != 0 || len < 5 || len > 20){
        return 0;
    }
    return 1;
}

int priceVal(long price){
    return (price > 50000 && price < 1000000) ? 1:0;
}

int catVal(char* cat){
    if(strcmp(cat,"Hair Care") == 0 || strcmp(cat, "Nail Care") == 0 ||  strcmp(cat, "Body Care") == 0){
        return 1;
    }
    return 0;
}

int availVal(char* avail){
    if(strcmp(avail,"Available") == 0 || strcmp(avail, "Unavailable") == 0){
        return 1;
    }
    return 0;
}
// End Validation

int max(int a, int b){
    return a>b? a:b;
}

int height(node*root){
    return root? root->height : 0;
}

int getBalance(node* root){
    return root? (height(root->left)-height(root->right)) : 0;
}

node* createNode(){
    curr = (node*)malloc(sizeof(node));
    printf("INSERT NEW TREATMENT\n");
    do {
        printf("input new treatment name: ");
        scanf("%[^\n]", curr->name); gc;
    } while(!nameVal(curr->name));

    do{
        printf("input treatment price: ");
        scanf("%ld", &curr->price); gc;
    } while(!priceVal(curr->price));

    do{
        printf("input treatment category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", curr->cat); gc;
    } while(!catVal(curr->cat));

    do{
        printf("input treatment availability for home service [Available | Unavailable]: ");
        scanf("%s", curr->avail); gc;
    } while(!availVal(curr->avail));

    printf("[New Treatment is Successfully Inserted]\n"); 
    gc;
    curr->height = 1;
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

node* rightRotate(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

node* leftRotate(node* y){
    node* x = y->right;
    node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

node* Insert(node* root){
    if (root == NULL){
        return createNode();
    } else if(strcmp(root->name, curr->name) > 0){
		root->left = Insert(root->left); 
	} else if(strcmp(root->name, curr->name) < 0){
		root->right = Insert(root->right); 
	} else return root; 
	
	root->height =  max(height(root->left), height(root->right)) + 1; 
	int balance = getBalance(root); 
	
	if(balance > 1){
		if(getBalance(root->left) >= 0){
			return rightRotate(root); // left left 
		} else{
			root->left = leftRotate(root->left); // left right 
			return rightRotate(root); 
		}
	}
	if(balance < -1){
		if(getBalance(root->right) <= 0){ 
			return leftRotate(root); // right right 
		} else{
			root->right = rightRotate(root->right); // right left 
			return leftRotate(root); 
		}
	}
	return root; 
    
}   

// =============== END INSERT REQUIREMENT ===================



// ================= DELETE REQUIREMENT =====================
node* deleteAVL(node* root, char* target){
    if (!root) {
        // Node tidak ditemukan, langsung return NULL
        return NULL;
    }

    if (strcmp(target, root->name) < 0) {
        root->left = deleteAVL(root->left, target);
    } else if (strcmp(target, root->name) > 0) {
        root->right = deleteAVL(root->right, target);
    } else {
        // Ketemu node yang akan dihapus

        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        if (!root->left || !root->right) {
            node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        // Dua anak: cari predecessor (max di subtree kiri)
        node* temp = root->left;
        while (temp->right) temp = temp->right;

        // Copy data predecessor ke root
        strcpy(root->name, temp->name);
        root->price = temp->price;
        strcpy(root->cat, temp->cat);
        strcpy(root->avail, temp->avail);

        // Hapus predecessor di subtree kiri
        root->left = deleteAVL(root->left, temp->name);
    }

    // Update height
    root->height = max(height(root->left), height(root->right)) + 1;

    // Balancing
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

node* Delete(node* root){
    if (!root) {
        printf("No data.\n");
        gc;
        return root;
    }

    char target[101];
    printf("DELETE TREATMENT\n");
    printf("Insert name to delete: ");
    scanf("%[^\n]", target); gc;

    node* newRoot = deleteAVL(root, target);

    if (newRoot == root) {
        // root sama berarti tidak ada perubahan (data tidak ditemukan)
        printf("Data not found!\n");
    } else {
        printf("[Data successfully deleted]\n");
    }

    return newRoot;
}

// =============== END DELETE REQUIREMENT ===================

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
        do
        {
            printf(">> ");
            scanf("%d", &choice); gc;
        } while (choice < 1 || choice > 4);

        if(choice == 1){
            View(curr);
        } else if(choice == 2){
            curr = Insert(curr);
            printf("[New Treatment is Successfully Inserted]\n"); 
            gc;
        } else if(choice == 3){
            curr = Delete(curr);
        }        
    } while (choice != 4);
    return 0;
}