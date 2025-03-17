#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
typedef struct mahasiswa{
    char NIM[10];
    char nama[50];
} mhs;

int main(){
    mhs ppti21[100];
    strcpy(ppti21[0].NIM, "2802540143");
    printf("%s\n", ppti21[0].NIM);

    return 0;
}
*/
struct mahasiswa{
    char NIM[10];
    char nama[50];
};

int main(){
    struct mahasiswa* ppti21 = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));
    // datatype* namavariable = (datatype*)malloc(sizeof(datatype));

    return 0;
}