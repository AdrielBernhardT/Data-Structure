#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
    int id;
    char name[101];
    struct Student *next, *prev;
};

struct Student* CreateNewStudent(int id, const char *name){
    Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
    (newStudent)->id = id;
    strcpy((newStudent)->name, name);
    (newStudent)->next = NULL;
    (newStudent)->prev = NULL;
    return newStudent;
}

Student* findSuccessor(Student *curr){
    while(curr->prev){
        curr = curr->prev;
    }
    return curr;
}

struct Student *insert(struct Student *root, int id, const char *name){
    if(root == NULL){
        return CreateNewStudent(id, name);
    }
    if(id > root->id){
        root->next = insert(root->next, id, name);
    }else{
        root->prev = insert(root->prev, id, name);
    }
    return root;
}

Student* searchMhs(Student *curr, int id){
    if(curr == NULL){
        return NULL;
    } else if(curr->id == id){
        return curr;
    } else if(curr->id > id){
        return searchMhs(curr->prev, id);
    } else if(curr->id < id){ 
        return searchMhs(curr->next, id);
    }
}

void inOrder(struct Student *root) {
    if (root != NULL) {
        inOrder(root->prev);
        printf("ID: %d, Name: %s\n", root->id, root->name);
        inOrder(root->next);
    }
}

Student* deleteMhs(Student *curr, int id){
    if(curr == NULL){
        return NULL;
    } else if(curr->id > id){
        curr->prev = deleteMhs(curr->prev, id);
    } else if(curr->id < id){
        curr->next = deleteMhs(curr->next, id);
    } else {
        if(curr->prev == NULL && curr->next == NULL){
            free(curr);
            return NULL;
        } else if(curr->next && curr->prev == NULL){ // successor right child 
            Student *temp = curr->next;
            free(curr);
            return temp;
        } else if(curr->prev && curr->next == NULL){ // successor left child 
            Student *temp = curr->prev;
            free(curr);
            return temp;
        } else {
            Student *Sucessor = findSuccessor(curr->next);
            // Copy data from Successor to current node
            curr->id = Sucessor->id;
            strcpy(curr->name, Sucessor->name);
            // Delete Successor
            curr->next = deleteMhs(curr->next, Sucessor->id);

            return curr;
        }
    }
    return curr;
}

Student *deleteAll(Student *root){
    while (root){
        root = deleteMhs(root, root->id);
    }
    return root;
}

int main(){
    struct Student *root = NULL;

    root = insert(root, 100, "Louis");
    root = insert(root, 101, "Brandon");
    root = insert(root, 90, "Angeline");
    root = insert(root, 103, "Bryant");
    root = insert(root, 77, "Calvin");
    root = insert(root, 95, "Giselle");
    root = insert(root, 94, "Nathan");
    root = insert(root, 93, "Marchelle");

    inOrder(root);

    Student *mhs = searchMhs(root, 99);
    if(mhs == NULL){
        printf("Not Found\n");
    } else {
        printf("ID: %d\nName: %s\n", mhs->id, mhs->name);
    }

    puts("After Delete");
    root = deleteMhs(root, 100);
    root = deleteMhs(root, 95);
    inOrder(root);

    puts("After Delete All");
    root = deleteAll(root);
    inOrder(root);
    
    return 0;
}