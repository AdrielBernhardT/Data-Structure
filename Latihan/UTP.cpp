#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

// Defining max size hash table
#define max_size 100

// Struct
struct booking{
    char ID[6];
    char Name[35];
    char Phone[25]; // "+62" + Spaces + 11 Char
    char RoomType[10];
    int Age;
    int Nights;
    booking* next;
} *head[max_size], *tail[max_size], *curr;

int hash(){
    int X = curr->ID[2]+curr->ID[3]+curr->ID[4]-1;
    int Y = max_size;
    return X%Y;
}

// Boolean Validation
bool choiceVal(int choice){
    return 1 <= choice && choice <= 4;
}

bool nameVal(){
    return strlen(curr->Name) >= 3 && strlen(curr->Name) <= 30;
}

bool phoneVal(){
    bool space = false, valid = false;
    // Space Check
    int len = strlen(curr->Phone);
    for(int i = 0; i < len; i++){
        if(curr->Phone[i] == ' '){
            space = true;
            break;
        }
    }

    // +62 check
    if(curr->Phone[0] == '+' && curr->Phone[1] == '6' && curr->Phone[2] == '2'){
        valid = true;
    }

    // returning true or false
    if(!valid||!space||len < 15){
        return false;
    } else {
        return true;
    }
}

bool ageVal(){
    return curr->Age>=18;
}

bool roomVal(){
    return strcmp(curr->RoomType,"Regular") == 0 || strcmp(curr->RoomType,"Deluxe") == 0 || strcmp(curr->RoomType,"Suite") == 0;
}

bool nightVal(){
    return (curr->Nights >= 1 && curr->Nights <= 30);
}

// Menu 1
void BookingHotel(){
    srand(time(NULL));

    curr = (booking*)malloc(sizeof(booking));
    
    // Name
    do{
        printf("Input Full Name [3...30] : ");
        scanf("%[^\n]", curr->Name); getchar();
        if(!nameVal()){
            printf("Full name length must beetween 3 and 30\n");
        }
    } while(!nameVal());
    
    // Phone
    do{
        printf("Input Phone Number: ");
        scanf("%[^\n]", curr->Phone); getchar();
        if(!phoneVal()){
            printf("Phone number must begin with '+62', contains with at least 1 space and the length must be 11(exclude +62 and space)\n");
        }
    } while(!phoneVal());

    // Age
    do{
        printf("Input Age [minimum 18] : ");
        scanf("%d", &curr->Age); getchar();
        if(!ageVal()){
            printf("Age must be minimum 18\n");
        }
    } while(!ageVal());

    // Room Type
    do{
        printf("Input Room Type [Regular | Deluxe | Suite] (Case Sensitive) : ");
        scanf("%s", curr->RoomType); getchar();
        if(!roomVal()){
            printf("Room type must be either Regular or Deluxe or Suite (Case Sensitive)\n");
        }
    } while(!roomVal());

    // Nights
    do{
        printf("Input How Many Night You Will Stay [1..30] : ");
        scanf("%d", &curr->Nights); getchar();
        if(!nightVal()){
            printf("You can't stay less than 1 night or more than 30 nights\n");
        }  
    } while(!nightVal()); 

    // ID
    for(int i = 0; i < 5; i++){
        if(i < 2){
            curr->ID[i] = curr->RoomType[i];
        } else {
            curr->ID[i] = (rand()%10) + '0';
        }
    }
    curr->ID[1] += ('A'-'a');
    curr->ID[5] = '\0'; // Buat ID char terakhir selalu Null
    curr->next = NULL; // Buat next curr selalu Null

    int key = hash();

    // push
    if(!head[key]){
        head[key]=tail[key]=curr;
    } else {
        tail[key]->next = curr;
        tail[key] = curr;
    }

    // Display Booking Data
    printf("+=============================+\n");
    printf("| Booking ID     : %s      |\n", curr->ID);
    printf("+=============================+\n");    
    printf("  Full Name      : %s\n", curr->Name);
    printf("  Phone Number   : %s\n", curr->Phone);
    printf("  Room Type      : %s\n", curr->RoomType);
    printf("  Night Stay     : %d\n", curr->Nights);
    printf("+=============================+\n\n");    
}

// Menu 2
void ViewBookings(){
    bool flag = false;
    for(int i = 0; i < max_size; i++){
        if(head[i]){
            flag = true;
            break;
        }
    }

    if(!flag){
        printf("+-----------------------+\n");
        printf("| There is no booking ! |\n");
        printf("+-----------------------+\n\n");
    } else {
       // Display Booking Data
        for (int i = 0; i < max_size; i++){
            if(head[i]){
                booking* temp = head[i];
                while(temp){
                    printf("+=============================+\n");
                    printf("| Booking ID     : %s      |\n", temp->ID);
                    printf("+=============================+\n");    
                    printf("  Full Name      : %s\n", temp->Name);
                    printf("  Phone Number   : %s\n", temp->Phone);
                    printf("  Room Type      : %s\n", temp->RoomType);
                    printf("  Night Stay     : %d\n", temp->Nights);
                    printf("+=============================+\n\n");
                    temp = temp->next;
                }
            }
        }
    }
}


int main(){
    int choice;
    do{
        printf("+-----------------------+\n");
        printf("|   Hotel Gransylvania  |\n");
        printf("+-----------------------+\n\n");
        printf("1. Booking Hotel\n");
        printf("2. View Bookings\n");
        printf("3. Delete Bookings\n");
        printf("4. Exit\n");
        do{
            printf(">> ");
            scanf("%d", &choice); getchar();
            if(!choiceVal(choice)){
                printf("Invalid Input\n");
            }
        } while (!choiceVal(choice));

        if(choice == 1){
            BookingHotel();
        } else if(choice == 2){
            ViewBookings();
        } else if(choice == 3){
            // DeleteBookings();
        } 
        system("pause");
        system("cls");
    } while(choice != 4);
    return 0;
}