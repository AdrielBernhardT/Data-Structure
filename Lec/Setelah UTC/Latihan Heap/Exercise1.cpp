#include <stdio.h>
#define max 100

struct Node{
    char name[20];
    int labaKotor;
    int HPP;
    int labaBersih;
}newNode;

struct minHeap{
    int size;
    Node arr[max];
};

void swap(Node* a, Node*b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    return(i-1)/2;
}

int leftChild(int i){
    return(i*2+1);
}

int rightChild(int i){
    return(i*2+2);
}

Node predefinedData[] = {
    {"Cilokal", 1000, 250, 0},
    {"Eserut", 500, 100, 0},
    {"SotoMadura", 700, 300, 0},
    {"BebekBarokah", 750, 50, 0},
    {"PijaHat", 1800, 1100, 0},
    {"Kaepce", 800, 30, 0},
    {"SoBakso", 300, 50, 0},
    {"AyamMoza", 2000, 200, 0},
    {"CirengHot", 1200, 400, 0}
};
int predefinedIndex = 0;

void inputNode() {
    if (predefinedIndex < sizeof(predefinedData) / sizeof(predefinedData[0])) {
        newNode = predefinedData[predefinedIndex];
        newNode.labaBersih = newNode.labaKotor - newNode.HPP;
        predefinedIndex++;
    } else {
        printf("No more predefined data available.\n");
    }
}

void insert(minHeap* heap){
    // Process data
    for (int x = 0; x < 9; x++){
        inputNode();     
        
        if(heap->size >= max){
            printf("Full");
            return;
        }

        int i = heap->size;
        heap->arr[i] = newNode;
        heap->size++;

        while(i != 0 && heap->arr[parent(i)].labaBersih < heap->arr[i].labaBersih){
            swap(&heap->arr[parent(i)], &heap->arr[i]);
            i = parent(i);
        }
    }
}

void printHeap(minHeap* heap){
    printf("Daftar UMKM:");
    for(int i = 0; i < heap->size; i++){
        printf(" %s", heap->arr[i].name);
    }
    printf("\nPrioritas: %s\n", heap->arr[0].name);
}

int main(){
    minHeap heap;
    heap.size = 0;

    int choice;
    do{
        printf("1. Insert\n2. Print\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                insert(&heap);
                break;
            case 2:
                printHeap(&heap);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 3);
    return 0;
}