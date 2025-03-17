#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct karakter {
    char Name[105];
    char Rank[25];
    int HP; 
    long int Magic;
    long int Gold;
};

int count = 0;

struct karakter* player = NULL;

void insert(){
    srand(time(NULL));
    player = (struct karakter*)realloc(player, (count + 1) * sizeof(struct karakter));

    printf("Name : ");
    scanf("%[^\n]", player[count].Name); getchar();

    do{
        printf("Rank : ");
        scanf("%s", player[count].Rank); getchar();
        if (strcmp(player[count].Rank, "Bronze") != 0 && strcmp(player[count].Rank, "Silver") != 0 && strcmp(player[count].Rank, "Gold") != 0){
            printf("Rank must be [Bronze/Silver/Gold]\n");
        }
    }while(strcmp(player[count].Rank, "Bronze") != 0 && strcmp(player[count].Rank, "Silver") != 0 && strcmp(player[count].Rank, "Gold") != 0);
    
    player[count].HP = (rand()%10*1000)+30000;
    printf("HP   : %d\n", player[count].HP);
    printf("Magic: ");
    scanf("%ld", &player[count].Magic); getchar();
    printf("Gold : ");
    scanf("%ld", &player[count].Gold); getchar();

    system("cls");

    printf("Player Info\n");
    printf("Name : %s\n", player[count].Name); 
    printf("Rank : %s\n", player[count].Rank); 
    printf("HP   : %d\n", player[count].HP); 
    printf("Magic: %ld\n", player[count].Magic);
    printf("Gold : %ld\n", player[count].Gold); 
    count++;
}

void view(){
    for (int i = 0; i < count; i++){
        printf("Player %d\n", i+1);
        printf("-----------------------------\n");
        printf("Name : %s\n", player[i].Name);
        printf("Rank : %s\n", player[i].Rank);
        printf("-----------------------------\n");
    }
}

void hapus(){
    int choose;
    do{
        printf("Delete Player >> ");
        scanf("%d", &choose); getchar();
        if(choose<=0 || choose > count){
            printf("Input must be between 1-%d\n", count);
        }
    } while (choose<=0 || choose > count);
    
    system("cls");
    count--;
    for (int i = choose-1; i < count; i++){
        strcpy(player[i].Name, player[i+1].Name);
        strcpy(player[i].Rank, player[i+1].Rank);
        player[i].HP = player[i+1].HP;
        player[i].Magic = player[i+1].Magic;
        player[i].Gold = player[i+1].Gold;
    }
}

void upgrade(){
    int choose;
    do{
        printf("Upgrade Player >> ");
        scanf("%d", &choose); getchar();
        if(choose<=0 || choose > count){
            printf("Input must be between 1-%d\n", count);
        }
    } while (choose<=0 || choose > count);
    system("cls");
    
    choose-=1;
    printf("Player Info\n");
    printf("Name : %s\n", player[choose].Name); 
    printf("Rank : %s\n", player[choose].Rank); 
    player[choose].HP += 150;
    player[choose].Magic += 150;
    player[choose].Gold -= 50;
    printf("HP   : %d\n", player[choose].HP); 
    printf("Magic: %ld\n", player[choose].Magic);
    printf("Gold : %ld\n", player[choose].Gold); 
}

int main(){
    int choice;
    do{
        printf("Player Menu\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Delete\n");
        printf("4. Upgrade\n");
        printf("5. Cancel\n");

        printf(">> ");
        scanf("%d", &choice); getchar();

        if (choice == 1){
            insert();
        } else if(choice == 2){
            view();
        } else if(choice == 3){
            hapus();
        } else if(choice == 4){
            upgrade();
        }
        printf("Enter to continue..."); getchar();
        system("cls");
    } while (choice != 5);
    return 0;
}