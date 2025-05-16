#include <stdio.h>
#include <string.h>
#define max 100

struct Node{
    int Code;
    char Status[20];
    int fuel;
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
    {1212, "", 55},
    {1414, "", 12},
    {4322, "", 33},
    {3392, "", 23},
    {7728, "", 54},
    {9928, "", 60},
};
int predefinedIndex = 0;

void inputNode() {
    if (predefinedIndex < sizeof(predefinedData) / sizeof(predefinedData[0])) {
        newNode = predefinedData[predefinedIndex];
        newNode.Code = predefinedData[predefinedIndex].Code;
        newNode.fuel = predefinedData[predefinedIndex].fuel;
        if (newNode.fuel < 50){
            strcpy(newNode.Status, "Urgent");
        } else {
            strcpy(newNode.Status, "Normal");
        }
        predefinedIndex++;
    } else {
        printf("No more predefined data available.\n");
    }
}

void insert(minHeap* heap){
    // Process data
    for (int x = 0; x < 6; x++){
        inputNode();  
        
        if(heap->size >= max){
            printf("Heap is full\n");
            return;
        }

        int i = heap->size;
        heap->arr[i] = newNode;
        heap->size++;

        while (i != 0 && heap->arr[parent(i)].fuel > heap->arr[i].fuel){
            swap(&heap->arr[parent(i)], &heap->arr[i]);
            i = parent(i);
        }
    }
}

void printHeap(minHeap* heap){
    for (int i = 0; i < heap->size; i++){
        printf("Code: %d, Status: %s, Fuel: %d\n", heap->arr[i].Code, heap->arr[i].Status, heap->arr[i].fuel);
    }
}

int main() {
    minHeap heap;
    heap.size = 0;

    insert(&heap);
    printHeap(&heap);

    return 0;
}