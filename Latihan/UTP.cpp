#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

struct Booking{
    char fullName[35];
    char phoneNum[15];
    int age;
    char roomType[10];
} *head[105], *tail[105], *current;

int counter = 0;

void bookingHotel(){
    // Name input
    do
    {
        printf("Input full name [3..30] : ");
        scanf("%[^\n]", current->fullName); getchar();
        if(strlen(current->fullName) < 3 || strlen(current->fullName) > 30){
            printf("Full name length must be between 3 and 30\n");
        }
    } while (strlen(current->fullName) < 3 || strlen(current->fullName) > 30);

    // Phone number input
    bool valid = true, containSpace = false;
    do
    {
        printf("Input phone number : ");
        scanf("%s", current->phoneNum); getchar();
        int telp = strlen(current->phoneNum);
        // Contain space check
        for(int i = 0; i < telp; i++){
            if(current->phoneNum[i] == ' '){
                containSpace = true;
                break;
            }
        }
        // Validity check
        for(int i = 0; i < telp; i++){
            if((current->phoneNum[0] != '+' && current->phoneNum[1] != '6' && current->phoneNum[2] != '2') || !containSpace || telp < 15){
                valid = false;
                break;
            }
        }
        if(!valid){
            printf("Phone number must begin with \'+62\', contains with at least 1 space and length must be 11 (Exclude +62 and space)\n");
            containSpace = false;
        }
    } while (!valid);
    
    // Age input

}

void printBookings(){

}

void deleteBooking(){

}

int main(){
    int choice;
    do{
        printf("+----------------------+\n");
        printf("|  Hotel GrAnsylvania  |\n");
        printf("+----------------------+\n\n"); 
        printf("Hotel GrAnsylvania\n");
        printf("1. Booking Hotel\n");
        printf("2. View Bookings\n");
        printf("3. Delete Booking\n");
        printf("4. Exit\n");
        do{
            printf(">> ");
            scanf("%d", &choice); getchar();
            if (choice < 1 || choice > 4){
                printf("Invalid choice\n");
            }
        } while(choice < 1 || choice > 4);

        if(choice == 1){
            bookingHotel();
        }else if (choice == 2){
            printBookings();
        } else if (choice == 3){
            deleteBooking();
        }
    }while (choice != 4);
    return 0;
}