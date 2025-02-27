#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
    int id;
    char name[101];
    struct Student *right, *left;
};

struct Student* CreateNewStudent(int id, const char *name){
    Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->right = NULL;
    newStudent->left = NULL;
    return newStudent;
}

struct Student *insert(struct Student *root, int id, const char *name){
    if(root == NULL){
        return CreateNewStudent(id, name);
    }
    if(id > root->id){
        root->right = insert(root->right, id, name);
    }else{
        root->left = insert(root->left, id, name);
    }
    return root;
}

void inorder(struct Student *root){
    if(root == NULL){
        return;
    }
    inorder(root->left); // Kiri
    printf("%d %s\n", root->id, root->name); // Print
    inorder(root->right); // Kanan
}

void postorder(struct Student *root){
    if(root == NULL){
        return;
    }
    postorder(root->left); // Kiri
    postorder(root->right); // Kanan
    printf("%d %s\n", root->id, root->name); // Print
}

void preorder(struct Student *root){
    if(root == NULL){
        return;
    }
    printf("%d %s\n", root->id, root->name); // Print
    preorder(root->left); // Kiri
    preorder(root->right); // Kanan
}

struct Student *search(struct Student *root, int id){
    if(root == NULL){
        printf("Not Found\n");
        return NULL;
    } 
    if(root->id == id){
        puts("Found");
        return root;
    } else if(id > root->id){
        return search(root->right, id);
    }else{
        return search(root->left, id);
    }
}

struct Student *update(struct Student *root, int id, const char *newName){
    if(root == NULL){
        printf("Not Found\n");
        return NULL;
    } 
    if(root->id == id){
        puts("Found");
        strcpy(root->name, newName);
        return root;
    } else if(id > root->id){
        return update(root->right, id, newName);
    }else{
        return update(root->left, id, newName);
    }
}

int main(){
    struct Student *root = NULL;

    puts("Inserting...\n");
    // Insert
    root = insert(root, 5, "Anto");
    root = insert(root, 10, "Budi");
    root = insert(root, 3, "Caca");
    root = insert(root, 13, "Dedi");
    root = insert(root, 1, "Elos");

    puts("Traversal...\n");
    // inorder traversal
    inorder(root);
    // Search
    struct Student *searchStudent = search(root, 10);
    if (searchStudent != NULL){
        printf("ID: %d\nName: %s\n\n", searchStudent->id, searchStudent->name);
    }
    // preorder traversal
    preorder(root);
    // Update
    struct Student *updateStudent = update(root, 10, "Budi Santoso");
    // postorder traversal
    postorder(root);

    return 0;
}

/*
// Preorder
1. print
2. left
3. right

// postorder
1. left
2. right
3. print
*/